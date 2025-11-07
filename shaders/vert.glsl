#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_tex_pos;

out vec2 f_tex_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 pos = vec4(v_pos, 1.0);
    pos.z = 0.1 * (pos.z + 1) - 0.1;
    pos.y = 0.1 * (pos.y + 1) - 0.1;
    gl_Position = projection * view * model * pos;
    f_tex_pos = v_tex_pos;
}