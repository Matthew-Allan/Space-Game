#version 330 core
in float f_bright;

out vec4 col;

void main() {
    col = vec4(0, 1, 1, 1) * ((f_bright + 1) / 2);
    
    // col = vec4(vec3((2.0 * 0.1 * 100) / (100 + 0.1 - (gl_FragCoord.z * 2 - 1) * (100 - 0.1))) / 100, 1);
}