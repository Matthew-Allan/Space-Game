#include "vaos.h"

#include <stddef.h>
#include <stdlib.h>

#include "wfobj.h"

// Set up a vertex array object that the game board should be rendered on.
void setupVAO(VertexArrObj *VAO, float *verts, size_t verts_size, GLuint *inds, size_t inds_size, GLsizei face_cnt) {
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

    VAO->faces = face_cnt;
}

int loadVAOs(VertexArrObj *station_VAOs, const char **paths, size_t count) {
    for(size_t i = 0; i < count; i++) {
        if(loadVAO(&station_VAOs[i], paths[i]) == -1) {
            return -1;
        }
    }
    return 0;
}

int loadVAO(VertexArrObj *station_VAO, const char *path) {
    size_t size, faces;
    float *geom = loadObjectData(path, WF_OBJ_HAS_NORMS, &size, &faces);
    if(geom == NULL) {
        return -1;
    }

    setupVAO(station_VAO, geom, size * faces, NULL, 0, faces);
    free(geom);

    // Tell the shader how to interpret the VBO.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), ((float *) 0) + 3);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    return 0;
}

void drawVAO(VertexArrObj *VAO) {
    glBindVertexArray(VAO->id);
    glDrawArrays(GL_TRIANGLES, 0, VAO->faces * 3);
}

void drawVAOInstanced(VertexArrObj *VAO, size_t count) {
    glBindVertexArray(VAO->id);
    glDrawArraysInstanced(GL_TRIANGLES, 0, VAO->faces * 3, count);
}