#include "objects.h"

#include <stddef.h>

// Set up a vertex array object that the game board should be rendered on.
void setupVAO(VertexArrObj *VAO, float *verts, size_t verts_size, GLuint *inds, size_t inds_size) {
    // Generate a vertex array object.
    glGenVertexArrays(1, &VAO->id);
    glBindVertexArray(VAO->id);

    // Generate buffer objects.
    glGenBuffers(1, &VAO->vbo);
    glGenBuffers(1, &VAO->ebo);

    // Bind the virtual and element buffer objects.
    glBindBuffer(GL_ARRAY_BUFFER, VAO->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO->ebo);

    // Send the vertex and index data to the buffer objects.
    glBufferData(GL_ARRAY_BUFFER, verts_size, verts, GL_STATIC_DRAW);
    if(inds_size > 0) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds_size, inds, GL_STATIC_DRAW);
    }
}

void createCube(VertexArrObj *cubeVAO) {
    float verticies[] = {
        -1,  1, -1,   0,  1,  0,
         1,  1,  1,   0,  1,  0,
         1,  1, -1,   0,  1,  0,
        -1,  1, -1,   0,  1,  0,
        -1,  1,  1,   0,  1,  0,
         1,  1,  1,   0,  1,  0,
         1,  1,  1,   0,  0,  1,
        -1, -1,  1,   0,  0,  1,
         1, -1,  1,   0,  0,  1,
         1,  1,  1,   0,  0,  1,
        -1,  1,  1,   0,  0,  1,
        -1, -1,  1,   0,  0,  1,
        -1,  1,  1,  -1,  0,  0,
        -1, -1, -1,  -1,  0,  0,
        -1, -1,  1,  -1,  0,  0,
        -1,  1,  1,  -1,  0,  0,
        -1,  1, -1,  -1,  0,  0,
        -1, -1, -1,  -1,  0,  0,
         1, -1, -1,   0, -1,  0,
        -1, -1,  1,   0, -1,  0,
        -1, -1, -1,   0, -1,  0,
         1, -1, -1,   0, -1,  0,
         1, -1,  1,   0, -1,  0,
        -1, -1,  1,   0, -1,  0,
         1,  1, -1,   1,  0,  0,
         1, -1,  1,   1,  0,  0,
         1, -1, -1,   1,  0,  0,
         1,  1, -1,   1,  0,  0,
         1,  1,  1,   1,  0,  0,
         1, -1,  1,   1,  0,  0,
        -1,  1, -1,   0,  0, -1,
         1, -1, -1,   0,  0, -1,
        -1, -1, -1,   0,  0, -1,
        -1,  1, -1,   0,  0, -1,
         1,  1, -1,   0,  0, -1,
         1, -1, -1,   0,  0, -1
    };

    setupVAO(cubeVAO, verticies, sizeof(verticies), NULL, 0);

    // Tell the shader how to interpret the VBO.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), ((float *) 0) + 3);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void drawCube(VertexArrObj *cubeVAO) {
    glBindVertexArray(cubeVAO->id);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void drawCubes(VertexArrObj *cubeVAO, size_t count) {
    glBindVertexArray(cubeVAO->id);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, count);
}