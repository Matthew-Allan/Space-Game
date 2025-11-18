#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec3 v_norm;

out float f_bright;

uniform mat4 model;
uniform mat4 cam;

void main() {
    vec4 pos = vec4(v_pos, 1.0);
    pos.y = 0.2 * pos.y;
    gl_Position = cam * model * pos;
    f_bright = dot(vec3(0.0, 1.0, 0.0), normalize(transpose(inverse(mat3(model))) * v_norm));
}