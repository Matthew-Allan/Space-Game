#include "objectshad.h"

#include <stddef.h>

#include "core/shader.h"

int buildObjectShader(ObjectShader *shader) {
    if(buildShader(&shader->program, VERT_SHADER_PATH, FRAG_SHADER_PATH, NULL) == -1) {
        return -1;
    }

    shader->model = glGetUniformLocation(shader->program, "model");
    shader->cam = glGetUniformLocation(shader->program, "cam");
    return 0;
}