#include "transform.h"

#include <stdlib.h>

void initTrans(Transform *trans, vec3 offset, Transform *parent) {
    cpyVec3(offset, trans->offset);
    trans->parent = parent;
    setVec4(trans->orientation, 0, 0, 0, 1);
}

void transComponents(Transform *trans, mat3 rot, vec3 disp) {
    cpyVec3(trans->offset, disp);
    quatRotationMat(trans->orientation, rot);
}

void outputMat(mat3 rot, vec3 disp, mat4 mat) {
    cpyVec3(rot[matI], mat[matI]);
    cpyVec3(rot[matJ], mat[matJ]);
    cpyVec3(rot[matK], mat[matK]);
    
    cpyVec3(disp, mat[matL]);

    mat[matI][vecW] = 0;
    mat[matJ][vecW] = 0;
    mat[matK][vecW] = 0;
    mat[matL][vecW] = 1;
}

void invTransMat(Transform *trans, mat4 mat) {
    mat3 rotation; vec3 displacement;
    transComponents(trans, rotation, displacement);
    mat3Transpose(rotation, rotation, 1);
    mat3MltVec(rotation, displacement, displacement, 1);
    vec3MltSlr(displacement, -1, displacement, 1);

    outputMat(rotation, displacement, mat);
}

void transMat(Transform *trans, mat4 mat) {
    mat3 rotation; vec3 displacement;
    transComponents(trans, rotation, displacement);

    outputMat(rotation, displacement, mat);
}