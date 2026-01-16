#include "vector.h"

#include <math.h>
#include <stdio.h>

#define vecx(x) vec ## x
#define fvecx(x, v) fvec ## x (v)

#define vecxAdd(x, vec_a, vec_b, out, count) vec ## x ## Add(vec_a, vec_b, out, count)
#define vecxMlt(x, vec_a, vec_b, out, count) vec ## x ## Mlt(vec_a, vec_b, out, count)
#define vecxDiv(x, vec_a, vec_b, out, count) vec ## x ## Div(vec_a, vec_b, out, count)

#define vecxAddSlrBdy(x, vec, scalar, out, count) \
    vecx(x) scalar_vec = fvecx(x, scalar); \
    vecxAdd(x, vec, scalar_vec, out, count);

void vec2AddSlr(vec2 vec, float scalar, vec2 out, size_t count) { vecxAddSlrBdy(2, vec, scalar, out, count) }
void vec3AddSlr(vec3 vec, float scalar, vec3 out, size_t count) { vecxAddSlrBdy(3, vec, scalar, out, count) }
void vec4AddSlr(vec4 vec, float scalar, vec4 out, size_t count) { vecxAddSlrBdy(4, vec, scalar, out, count) }

#define vecxMltSlrBdy(x, vec, scalar, out, count) \
    vecx(x) scalar_vec = fvecx(x, scalar); \
    vecxMlt(x, vec, scalar_vec, out, count);

void vec2MltSlr(vec2 vec, float scalar, vec2 out, size_t count) { vecxMltSlrBdy(2, vec, scalar, out, count) }
void vec3MltSlr(vec3 vec, float scalar, vec3 out, size_t count) { vecxMltSlrBdy(3, vec, scalar, out, count) }
void vec4MltSlr(vec4 vec, float scalar, vec4 out, size_t count) { vecxMltSlrBdy(4, vec, scalar, out, count) }

#define vecxDivSlrBdy(x, vec, scalar, out, count) \
    vecx(x) scalar_vec = fvecx(x, scalar); \
    vecxDiv(x, vec, scalar_vec, out, count);

void vec2DivSlr(vec2 vec, float scalar, vec2 out, size_t count) { vecxDivSlrBdy(2, vec, scalar, out, count) }
void vec3DivSlr(vec3 vec, float scalar, vec3 out, size_t count) { vecxDivSlrBdy(3, vec, scalar, out, count) }
void vec4DivSlr(vec4 vec, float scalar, vec4 out, size_t count) { vecxDivSlrBdy(4, vec, scalar, out, count) }

#define vecxOppBdy(x, opp, vec_a, vec_b, out, count) \
    for(size_t i = 0; i < count; i++) { \
        for(int j = vecX; j < x; j++) { \
            ((vecx(x) *) out)[i][j] = ((vecx(x) *) vec_a)[i][j] opp vec_b[j]; \
        } \
    }

void vec2Add(vec2 vec_a, vec2 vec_b, vec2 out, size_t count) { vecxOppBdy(2, +, vec_a, vec_b, out, count) }
void vec3Add(vec3 vec_a, vec3 vec_b, vec3 out, size_t count) { vecxOppBdy(3, +, vec_a, vec_b, out, count) }
void vec4Add(vec4 vec_a, vec4 vec_b, vec4 out, size_t count) { vecxOppBdy(4, +, vec_a, vec_b, out, count) }
    
void vec2Sub(vec2 vec_a, vec2 vec_b, vec2 out, size_t count) { vecxOppBdy(2, -, vec_a, vec_b, out, count) }
void vec3Sub(vec3 vec_a, vec3 vec_b, vec3 out, size_t count) { vecxOppBdy(3, -, vec_a, vec_b, out, count) }
void vec4Sub(vec4 vec_a, vec4 vec_b, vec4 out, size_t count) { vecxOppBdy(4, -, vec_a, vec_b, out, count) }

void vec2Mlt(vec2 vec_a, vec2 vec_b, vec2 out, size_t count) { vecxOppBdy(2, *, vec_a, vec_b, out, count) }
void vec3Mlt(vec3 vec_a, vec3 vec_b, vec3 out, size_t count) { vecxOppBdy(3, *, vec_a, vec_b, out, count) }
void vec4Mlt(vec4 vec_a, vec4 vec_b, vec4 out, size_t count) { vecxOppBdy(4, *, vec_a, vec_b, out, count) }

void vec2Div(vec2 vec_a, vec2 vec_b, vec2 out, size_t count) { vecxOppBdy(2, /, vec_a, vec_b, out, count) }
void vec3Div(vec3 vec_a, vec3 vec_b, vec3 out, size_t count) { vecxOppBdy(3, /, vec_a, vec_b, out, count) }
void vec4Div(vec4 vec_a, vec4 vec_b, vec4 out, size_t count) { vecxOppBdy(4, /, vec_a, vec_b, out, count) }

void crossProduct(vec3 vec_a, vec3 vec_b, vec3 out) {
    out[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
    out[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
    out[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
}

#define vecxDot(x, vec_a, vec_b) \
    float val = 0; \
    for(int i = vecX; i < x; i++) { \
        val += vec_a[i] * vec_b[i]; \
    } \
    return val;

float vec2Dot(vec2 vec_a, vec2 vec_b) { vecxDot(2, vec_a, vec_b) }
float vec3Dot(vec3 vec_a, vec3 vec_b) { vecxDot(3, vec_a, vec_b) }
float vec4Dot(vec4 vec_a, vec4 vec_b) { vecxDot(4, vec_a, vec_b) }

#define vecxLenBdy(x, vec) \
    float val = 0; \
    for(int i = vecX; i < x; i++) { \
        val += vec[i] * vec[i]; \
    } \
    return sqrtf(val);

float vec2Len(vec2 vec) { vecxLenBdy(2, vec) }
float vec3Len(vec3 vec) { vecxLenBdy(3, vec) }
float vec4Len(vec4 vec) { vecxLenBdy(4, vec) }

#define vecxNormBdy(x, vec, out) \
    float len = vec ## x ## Len(vec); \
    for(int i = vecX; i < x; i++) { \
        out[i] = vec[i] / len; \
    }

void vec2Norm(vec2 vec, vec2 out) { vecxNormBdy(2, vec, out) }
void vec3Norm(vec3 vec, vec3 out) { vecxNormBdy(3, vec, out) }
void vec4Norm(vec4 vec, vec4 out) { vecxNormBdy(4, vec, out) }

void setVec2(vec2 vec, float x, float y) {
    vec[vecX] = x;
    vec[vecY] = y;
}

void setVec3(vec3 vec, float x, float y, float z) {
    setVec2(vec, x, y);
    vec[vecZ] = z;
}
void setVec4(vec4 vec, float x, float y, float z, float w) {
    setVec3(vec, x, y, z);
    vec[vecW] = w;
}

#define cpyVecxBdy(x, src, dst) \
    for(int i = vecX; i < x; i++) { \
        dst[i] = src[i]; \
    }

void cpyVec2(vec2 src, vec2 dst) { cpyVecxBdy(2, src, dst) }
void cpyVec3(const vec3 src, vec3 dst) { cpyVecxBdy(3, src, dst) }
void cpyVec4(vec4 src, vec4 dst) { cpyVecxBdy(4, src, dst) }

#define printVecxBdy(x, vec, count) \
    for(size_t i = 0; i < count; i++) { \
        printf("<%4.3g", ((vecx(x) *) vec)[i][vecX]); \
        for(int j = vecY; j < x; j++) { \
            printf(", %4.3g", ((vecx(x) *) vec)[i][j]); \
        } \
        printf(">\n"); \
    }

void printVec2(vec2 vec, size_t count) { printVecxBdy(2, vec, count) }
void printVec3(vec3 vec, size_t count) { printVecxBdy(3, vec, count) }
void printVec4(vec4 vec, size_t count) { printVecxBdy(4, vec, count) }