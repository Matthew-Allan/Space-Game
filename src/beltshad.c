#include "beltshad.h"

#include <stddef.h>

#include <seng/shader.h>

int buildBeltShader(BeltShader *shader) {
    if(buildShader(&shader->program, BLT_VERT_SHADER_PATH, BLT_FRAG_SHADER_PATH, NULL) == -1) {
        return -1;
    }

    shader->cam = glGetUniformLocation(shader->program, "cam");
    return 0;
}