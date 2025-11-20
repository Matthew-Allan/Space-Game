#ifndef BELT_SHAD_H
#define BELT_SHAD_H

#include <glad/glad.h>

typedef struct BeltShader {
    GLuint program;
    GLuint cam;
} BeltShader;

#define BLT_FRAG_SHADER_PATH "shaders/belt/frag.glsl"
#define BLT_VERT_SHADER_PATH "shaders/belt/vert.glsl"

int buildBeltShader(BeltShader *shader);

#endif