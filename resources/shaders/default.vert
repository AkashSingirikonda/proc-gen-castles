#version 330 core

layout(location = 0) in vec3 object_pos;
layout(location = 1) in vec3 object_normal;
layout(location = 2) in vec2 uv;

out vec3 world_pos;
out vec3 world_norm;
out vec2 uv_pos;
// out mat3 TBN; // matrix to convert from tangent space

uniform mat4 model;
uniform mat4 norm_inv;
uniform mat4 view;
uniform mat4 proj;

void main() {
    vec4 pos = vec4(object_pos, 1.0);
    world_pos = vec3(model * pos);

    world_norm = vec3(normalize(norm_inv * vec4(object_normal, 0)));

    uv_pos = uv;

    // calculate TBN, multiply by model to get to ws
//    vec3 tangent = normalize(mat3(model) * vec3(uv.x, 0, 0)); // is this right? might need to be calculated in cpu and passed in
//    vec3 normal = normalize(mat3(model) * object_normal);
//    vec3 bitangent = normalize(mat3(model) * cross(tangent, normal));
//    TBN = mat3(tangent, bitangent, normal);

    gl_Position = (proj * view * model) * pos;
}
