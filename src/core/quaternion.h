#ifndef QUATERNION_H
#define QUATERNION_H

#include "matrix.h"

typedef vec4 quaternion;

void quatRotationMat(quaternion quat, mat3 mat);
void quatFromEuler(quaternion quat, float x, float y, float z);
void quatMlt(quaternion quat_a, quaternion quat_b, quaternion out);
void quatConj(quaternion quat, quaternion out);

#define quatNorm(quat, out) vec4Norm(quat, out)

#endif