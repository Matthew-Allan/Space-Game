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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds_size, inds, GL_STATIC_DRAW);
}

void createCube(VertexArrObj *cubeVAO) {
    float verticies[] = {
         1,  1, -1,
         1, -1, -1,
         1,  1,  1,
         1, -1,  1,
        -1,  1, -1,
        -1, -1, -1,
        -1,  1,  1,
        -1, -1,  1
    };

    unsigned int indices[] = {
        4, 2, 0,
        2, 7, 3,
        6, 5, 7,
        1, 7, 5,
        0, 3, 1,
        4, 1, 5,
        4, 6, 2,
        2, 6, 7,
        6, 4, 5,
        1, 3, 7,
        0, 2, 3,
        4, 0, 1
    };

    setupVAO(cubeVAO, verticies, sizeof(verticies), indices, sizeof(indices));

    // Tell the shader how to interpret the VBO.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
}

void drawCube(VertexArrObj *cubeVAO) {
    glBindVertexArray(cubeVAO->id);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}