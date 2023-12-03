#version 330 core

in vec2 uv;

uniform sampler2D tex;

uniform bool pixelFilter;
uniform bool kernelFilter;

uniform int width;
uniform int height;

out vec4 fragColor;

void main()
{
    if(kernelFilter){
        vec4 sum = vec4(0);

        float pixelWidth = 1.0f / width;
        float pixelHeight = 1.0f / height;
        for(int i = -2; i <= 2; i++){
            for(int j = -2; j <= 2; j++){
                sum += texture(tex, vec2(pixelWidth * i + uv.x, pixelHeight * j + uv.y));
            }
        }

        fragColor = sum / 25.0f;
    } else {
        fragColor = texture(tex, uv);
    }

    if(pixelFilter){
        fragColor = 1 - fragColor;
    }
}
