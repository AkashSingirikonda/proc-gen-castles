#version 330 core

layout(location = 0) in vec3 object_pos;
layout(location = 1) in vec3 object_normal;

out vec3 world_pos;
out vec3 world_norm;

uniform mat4 model;
uniform mat4 norm_inv;
uniform mat4 view;
uniform mat4 proj;

void main() {
    vec4 pos = vec4(object_pos, 1.0);
    world_pos = vec3(model * pos);

    world_norm = vec3(normalize(norm_inv * vec4(object_normal, 0)));

    gl_Position = (proj * view * model) * pos;
}
