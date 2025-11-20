#version 330 core

in vec3 f_col;

out vec4 col;

void main() {
    col = vec4(f_col, 1);
    // col = vec4(vec3((2.0 * 0.1 * 100) / (100 + 0.1 - (gl_FragCoord.z * 2 - 1) * (100 - 0.1))) / 100, 1);
}