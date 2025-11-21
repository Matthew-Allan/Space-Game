#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glad/glad.h>

#include "matrix.h"
#include "quaternion.h"

typedef struct Transform {
    struct Transform *parent;
    quaternion orientation;
    vec3 offset;
} Transform;

void transMat(Transform *trans, mat4 mat);
void invTransMat(Transform *trans, mat4 mat);

void initTrans(Transform *trans, vec3 offset, Transform *parent);

void uploadTransMat(Transform *trans, GLuint modelLoc);

void parentTrans(Transform *trans, Transform *parent);
void orphanTrans(Transform *trans);
void orphanTransAt(Transform *trans);

#endif