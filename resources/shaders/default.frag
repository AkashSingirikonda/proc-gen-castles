#version 330 core
in vec3 world_pos;
in vec3 world_norm;
in vec2 uv_pos;
in mat3 TBN;

out vec4 fragColor;

uniform sampler2D wallTex;
uniform bool useNormalMap;
uniform bool useTextureMap;

uniform float k_a;
uniform float k_d;
uniform float k_s;
uniform float shine;

uniform vec4 cAmbient;
uniform vec4 cDiffuse;
uniform vec4 cSpecular;

uniform vec4 camera_position;

int MAX_LIGHTS = 10;

uniform int light_type[10];

uniform vec4 light_position[10];
uniform vec4 light_direction[10];
uniform vec2 light_data[10];

uniform vec4 light_color[10];
uniform vec3 light_func[10];


float lightFalloff(float x, float inner, float outer){
    float c = (x - inner) / (outer - inner);
    float c_2 = c * c;
    return -2.0f * c_2 * c + 3.0f * c_2;
}

void main() {
    vec4 pos = vec4(world_pos, 1);
    vec4 norm = vec4(normalize(world_norm), 0.0f);

    norm = texture(wallTex, uv_pos);
    norm = norm * 2.f - 1.f; // convert to proper range
    norm.xyz = normalize(TBN * norm.xyz);
//    norm = normalize(norm);
    norm.w = 0;

    vec4 dir_camera = normalize(camera_position - pos);
    dir_camera.w = 0;

    fragColor = k_a * cAmbient;

    for(int i = 0; i < MAX_LIGHTS; i++){
        vec4 sum = vec4(0.0);

        int type = light_type[i];
        vec4 light_pos = light_position[i];
        vec4 light_dir = light_direction[i];
        vec2 data = light_data[i];
        vec4 color = light_color[i];
        vec3 func = light_func[i];

        if(type == -1){
            continue;
        }

        vec4 L;
        float f = 1;

        if(type == 1 || type == 3){ // point or spot
            vec4 delta = light_pos - pos;
            L = normalize(delta);
            float d = length(delta);
            f = min(1, 1 / (func.x + d * func.y + d * d * func.z));
        } else if(type == 2) { // directional
            L = -normalize(light_dir);
        }

        float I = 1;
        if(type == 3){ // spot
            float angle = acos(dot(L, -normalize(light_dir)));
            if(angle > data.y){
                continue;
            }
            if(angle > data.y - data.x){
                I = 1 - lightFalloff(angle, data.y - data.x, data.y);
            }
        }

        if(dot(norm, L) > 0){
            sum += k_d * cDiffuse * dot(norm, L);
        }

        vec4 R = normalize(reflect(-L, norm));
        if(dot(R, dir_camera) > 0 && shine > 0){
            sum += k_s * cSpecular * pow(dot(R, dir_camera), shine);
        }

        fragColor += I * f * color * sum;

        // test textures:
//        fragColor = texture(wallTex, uv_pos);
//        fragColor = vec4(1);
//        fragColor.x = uv_pos.y;
    }
}
