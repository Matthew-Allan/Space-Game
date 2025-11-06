#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_tex_pos;

out vec2 f_tex_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(v_pos, 1.0);
    f_tex_pos = v_tex_pos;
}