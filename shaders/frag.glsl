#version 330 core
in float f_bright;

out vec4 col;

void main() {
    col = vec4(0, 1, 1, 1) * ((f_bright + 1) / 2);
}