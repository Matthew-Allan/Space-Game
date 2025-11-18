#ifndef CAMERA_H
#define CAMERA_H

#include <stdint.h>
#include <glad/glad.h>

#include "matrix.h"
#include "transform.h"

typedef struct Camera {
    Transform trans;
    float fov;
} Camera;

void initCam(Camera *cam, vec3 pos);

void uploadCamMat(Camera *cam, GLuint camLoc);

#endif