#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec3 v_norm;

out vec3 f_col;

uniform mat4 cam;

uniform uint r_min = 200u;
uniform uint r_max = 1000u;

#define PI 3.1415926538

#define sqr(a) (a * a)

uint iHash(uint inp) {
    uint state = inp * 747796405u + 2891336453u;
    uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

float fHash(uint inp) {
    return float(iHash(inp)) / 4294967295u;
}

vec3 getCol(uint seed) {
    return vec3(
        0.9 + 0.1 * fHash(seed * 3459u),
        0.3 + 0.5 * fHash(seed * 2347u),
        0.3 + 0.5 * fHash(seed * 1235u)
    );
}

float brightness() {
    return ((dot(vec3(0.0, 1.0, 0.0), v_norm) + 1) / 2);
}

vec3 getOffset(uint seed) {
    float theta = fHash(seed * 5423u) * 2 * PI;
    float radius = sqrt(fHash(seed * 4321u) * (sqr(r_max) - sqr(r_min)) + sqr(r_min));
    return vec3(radius * cos(theta), 0, radius * sin(theta));
}

void main() {
    uint seed = iHash(uint(gl_InstanceID));
    vec4 pos = vec4(v_pos + getOffset(seed), 1.0);
    gl_Position = cam * pos;

    f_col = getCol(seed) * brightness();
}