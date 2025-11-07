#ifndef OBJECTS_H
#define OBJECTS_H

#include <glad/glad.h>

typedef GLuint VertexBufObj;
typedef GLuint ElementBufObj;

typedef struct VertexArrObj{
    GLuint id;
    ElementBufObj ebo;
    VertexBufObj vbo;
} VertexArrObj;

void createCube(VertexArrObj *cubeVAO);
void drawCube(VertexArrObj *cubeVAO);

#endif