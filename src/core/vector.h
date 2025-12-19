#ifndef VECTOR_H
#define VECTOR_H

#include <sys/types.h>

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

#define vecX 0
#define vecY 1
#define vecZ 2
#define vecW 3

#define vec2(x, y) {(x), (y)}
#define vec3(x, y, z) {(x), (y), (z)}
#define vec4(x, y, z, w) {(x), (y), (z), (w)}

#define fvec2(v) vec2(v, v)
#define fvec3(v) vec3(v, v, v)
#define fvec4(v) vec4(v, v, v, v)

#define varr(vec) ((float *) (vec))

static const vec3 UP_VEC = vec3(0, 1, 0);
static const vec3 DOWN_VEC = vec3(0, -1, 0);

static const vec3 BACKWARD_VEC = vec3(0, 0, 1);
static const vec3 FORWARD_VEC = vec3(0, 0, -1);

static const vec3 RIGHT_VEC = vec3(1, 0, 0);
static const vec3 LEFT_VEC = vec3(-1, 0, 0);

static const vec3 ORIGIN_VEC = vec3(0, 0, 0);

#define X_AXIS RIGHT_VEC
#define Y_AXIS UP_VEC
#define Z_AXIS BACKWARD_VEC

void vec2AddSlr(vec2 vec, float scalar, vec2 out, size_t count);
void vec3AddSlr(vec3 vec, float scalar, vec3 out, size_t count);
void vec4AddSlr(vec4 vec, float scalar, vec4 out, size_t count);

void vec2MltSlr(vec2 vec, float scalar, vec2 out, size_t count);
void vec3MltSlr(vec3 vec, float scalar, vec3 out, size_t count);
void vec4MltSlr(vec4 vec, float scalar, vec4 out, size_t count);

void vec2DivSlr(vec2 vec, float scalar, vec2 out, size_t count);
void vec3DivSlr(vec3 vec, float scalar, vec3 out, size_t count);
void vec4DivSlr(vec4 vec, float scalar, vec4 out, size_t count);

void vec2Add(vec2 vec_a, vec2 vec_b, vec2 out, size_t count);
void vec3Add(vec3 vec_a, vec3 vec_b, vec3 out, size_t count);
void vec4Add(vec4 vec_a, vec4 vec_b, vec4 out, size_t count);

void vec2Sub(vec2 vec_a, vec2 vec_b, vec2 out, size_t count);
void vec3Sub(vec3 vec_a, vec3 vec_b, vec3 out, size_t count);
void vec4Sub(vec4 vec_a, vec4 vec_b, vec4 out, size_t count);

void vec2Mlt(vec2 vec_a, vec2 vec_b, vec2 out, size_t count);
void vec3Mlt(vec3 vec_a, vec3 vec_b, vec3 out, size_t count);
void vec4Mlt(vec4 vec_a, vec4 vec_b, vec4 out, size_t count);

void vec2Div(vec2 vec_a, vec2 vec_b, vec2 out, size_t count);
void vec3Div(vec3 vec_a, vec3 vec_b, vec3 out, size_t count);
void vec4Div(vec4 vec_a, vec4 vec_b, vec4 out, size_t count);

float vec2Dot(vec2 vec_a, vec2 vec_b);
float vec3Dot(vec3 vec_a, vec3 vec_b);
float vec4Dot(vec4 vec_a, vec4 vec_b);

float vec2Len(vec2 vec);
float vec3Len(vec3 vec);
float vec4Len(vec4 vec);

void setVec2(vec2 vec, float x, float y);
void setVec3(vec3 vec, float x, float y, float z);
void setVec4(vec4 vec, float x, float y, float z, float w);

void cpyVec2(vec2 src, vec2 dst);
void cpyVec3(const vec3 src, vec3 dst);
void cpyVec4(vec4 src, vec4 dst);

void vec2Norm(vec2 vec, vec2 out);
void vec3Norm(vec3 vec, vec3 out);
void vec4Norm(vec4 vec, vec4 out);

void crossProduct(vec3 vec_a, vec3 vec_b, vec3 out);

void printVec2(vec2 vec, size_t count);
void printVec3(vec3 vec, size_t count);
void printVec4(vec4 vec, size_t count);

#endif