#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec3 v_norm;

out float f_bright;

uniform mat4 model;
uniform mat4 cam;

mat4 scale = mat4(
    100, 0, 0, 0,
    0, 100, 0, 0,
    0, 0, 100, 0,
    0, 0, 0, 1
);

void main() {
    vec4 pos = vec4(v_pos, 1.0);
    gl_Position = cam * model * scale * pos;
    f_bright = dot(vec3(0.0, 1.0, 0.0), normalize(transpose(inverse(mat3(model))) * v_norm));
}