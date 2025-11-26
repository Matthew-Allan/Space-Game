#ifndef VOAS_H
#define VOAS_H

#include <glad/glad.h>
#include <stddef.h>

typedef GLuint VertexBufObj;
typedef GLuint ElementBufObj;

typedef struct VertexArrObj{
    GLuint id;
    ElementBufObj ebo;
    VertexBufObj vbo;
    int faces;
} VertexArrObj;

int loadVAO(VertexArrObj *station_VAO, const char *path);
void drawVAO(VertexArrObj *VAO);
void drawVAOInstanced(VertexArrObj *VAO, size_t count);

#endif