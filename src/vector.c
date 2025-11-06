#include "vector.h"

#include <math.h>
#include <stdio.h>

#define vecx(x) vec ## x
#define fvecx(x, v) fvec ## x (v)

#define vecx_add(x, vec_a, vec_b, out, count) vec ## x ## _add(vec_a, vec_b, out, count)
#define vecx_mlt(x, vec_a, vec_b, out, count) vec ## x ## _mlt(vec_a, vec_b, out, count)
#define vecx_div(x, vec_a, vec_b, out, count) vec ## x ## _div(vec_a, vec_b, out, count)

#define rot_vec2_exp(vec, i, x) vec[(vecX + i) % x], vec[(vecY + i) % x]
#define rot_vec3_exp(vec, i, x) rot_vec2_exp(vec, i, x), vec[(vecZ + i) % x]
#define rot_vec4_exp(vec, i, x) rot_vec3_exp(vec, i, x), vec[(vecW + i) % x]

#define rot_vecx(vec, i, x) {rot_vec ## x ## _exp(vec, i, x)}

#define rot_vec2(vec, i) rot_vecx(vec, i, 2)
#define rot_vec3(vec, i) rot_vecx(vec, i, 3)
#define rot_vec4(vec, i) rot_vecx(vec, i, 4)

#define vecx_add_slr_bdy(x, vec, scalar, out, count) \
    vecx(x) scalar_vec = fvecx(x, scalar); \
    vecx_add(x, vec, scalar_vec, out, count);

void vec2_add_slr(vec2 vec, float scalar, vec2 out, size_t count) { vecx_add_slr_bdy(2, vec, scalar, out, count) }
void vec3_add_slr(vec3 vec, float scalar, vec3 out, size_t count) { vecx_add_slr_bdy(3, vec, scalar, out, count) }
void vec4_add_slr(vec4 vec, float scalar, vec4 out, size_t count) { vecx_add_slr_bdy(4, vec, scalar, out, count) }
#define vecx_mlt_slr_bdy(x, vec, scalar, out, count) \
    vecx(x) scalar_vec = fvecx(x, scalar); \
    vecx_mlt(x, vec, scalar_vec, out, count);

void vec2_mlt_slr(vec2 vec, float scalar, vec2 out, size_t count) { vecx_mlt_slr_bdy(2, vec, scalar, out, count) }
void vec3_mlt_slr(vec3 vec, float scalar, vec3 out, size_t count) { vecx_mlt_slr_bdy(3, vec, scalar, out, count) }
void vec4_mlt_slr(vec4 vec, float scalar, vec4 out, size_t count) { vecx_mlt_slr_bdy(4, vec, scalar, out, count) }

#define vecx_div_slr_bdy(x, vec, scalar, out, count) \
    vecx(x) scalar_vec = fvecx(x, scalar); \
    vecx_div(x, vec, scalar_vec, out, count);

void vec2_div_slr(vec2 vec, float scalar, vec2 out, size_t count) { vecx_div_slr_bdy(2, vec, scalar, out, count) }
void vec3_div_slr(vec3 vec, float scalar, vec3 out, size_t count) { vecx_div_slr_bdy(3, vec, scalar, out, count) }
void vec4_div_slr(vec4 vec, float scalar, vec4 out, size_t count) { vecx_div_slr_bdy(4, vec, scalar, out, count) }

#define vecx_opp_bdy(x, opp, vec_a, vec_b, out, count) \
    for(size_t i = 0; i < count; i++) { \
        for(int j = vecX; j < x; j++) { \
            ((vecx(x) *) out)[i][j] = ((vecx(x) *) vec_a)[i][j] opp vec_b[j]; \
        } \
    }

void vec2_add(vec2 vec_a, vec2 vec_b, vec2 out, size_t count) { vecx_opp_bdy(2, +, vec_a, vec_b, out, count) }
void vec3_add(vec3 vec_a, vec3 vec_b, vec3 out, size_t count) { vecx_opp_bdy(3, +, vec_a, vec_b, out, count) }
void vec4_add(vec4 vec_a, vec4 vec_b, vec4 out, size_t count) { vecx_opp_bdy(4, +, vec_a, vec_b, out, count) }
    
void vec2_sub(vec2 vec_a, vec2 vec_b, vec2 out, size_t count) { vecx_opp_bdy(2, -, vec_a, vec_b, out, count) }
void vec3_sub(vec3 vec_a, vec3 vec_b, vec3 out, size_t count) { vecx_opp_bdy(3, -, vec_a, vec_b, out, count) }
void vec4_sub(vec4 vec_a, vec4 vec_b, vec4 out, size_t count) { vecx_opp_bdy(4, -, vec_a, vec_b, out, count) }

void vec2_mlt(vec2 vec_a, vec2 vec_b, vec2 out, size_t count) { vecx_opp_bdy(2, *, vec_a, vec_b, out, count) }
void vec3_mlt(vec3 vec_a, vec3 vec_b, vec3 out, size_t count) { vecx_opp_bdy(3, *, vec_a, vec_b, out, count) }
void vec4_mlt(vec4 vec_a, vec4 vec_b, vec4 out, size_t count) { vecx_opp_bdy(4, *, vec_a, vec_b, out, count) }

void vec2_div(vec2 vec_a, vec2 vec_b, vec2 out, size_t count) { vecx_opp_bdy(2, /, vec_a, vec_b, out, count) }
void vec3_div(vec3 vec_a, vec3 vec_b, vec3 out, size_t count) { vecx_opp_bdy(3, /, vec_a, vec_b, out, count) }
void vec4_div(vec4 vec_a, vec4 vec_b, vec4 out, size_t count) { vecx_opp_bdy(4, /, vec_a, vec_b, out, count) }

void cross_product(vec3 vec_a, vec3 vec_b, vec3 out) {
    vec3 a_1 = rot_vec3(vec_a, 1), a_2 = rot_vec3(vec_a, 2);
    vec3 b_1 = rot_vec3(vec_b, 1), b_2 = rot_vec3(vec_b, 2);
    vec3_mlt(a_1, b_2, a_1, 1);
    vec3_mlt(a_2, b_1, a_2, 1);
    vec3_sub(a_2, a_1, out, 1);
}

#define vecx_dot(x, vec_a, vec_b) \
    float val = 0; \
    for(int i = vecX; i < x; i++) { \
        val += vec_a[i] * vec_b[i]; \
    } \
    return val;

float vec2_dot(vec2 vec_a, vec2 vec_b) { vecx_dot(2, vec_a, vec_b) }
float vec3_dot(vec3 vec_a, vec3 vec_b) { vecx_dot(3, vec_a, vec_b) }
float vec4_dot(vec4 vec_a, vec4 vec_b) { vecx_dot(4, vec_a, vec_b) }

#define vecx_len_bdy(x, vec) \
    float val = 0; \
    for(int i = vecX; i < x; i++) { \
        val += vec[i] * vec[i]; \
    } \
    return sqrtf(val);

float vec2_len(vec2 vec) { vecx_len_bdy(2, vec) }
float vec3_len(vec3 vec) { vecx_len_bdy(3, vec) }
float vec4_len(vec4 vec) { vecx_len_bdy(4, vec) }

#define vecx_norm_bdy(x, vec, out) \
    float len = vec ## x ## _len(vec); \
    for(int i = vecX; i < x; i++) { \
        out[i] = vec[i] / len; \
    }

void vec2_norm(vec2 vec, vec2 out) { vecx_norm_bdy(2, vec, out) }
void vec3_norm(vec3 vec, vec3 out) { vecx_norm_bdy(3, vec, out) }
void vec4_norm(vec4 vec, vec4 out) { vecx_norm_bdy(4, vec, out) }

void set_vec2(vec2 vec, float x, float y) {
    vec[vecX] = x;
    vec[vecY] = y;
}

void set_vec3(vec3 vec, float x, float y, float z) {
    set_vec2(vec, x, y);
    vec[vecZ] = z;
}
void set_vec4(vec4 vec, float x, float y, float z, float w) {
    set_vec3(vec, x, y, z);
    vec[vecW] = w;
}

#define cpy_vecx_bdy(x, src, dst) \
    for(int i = vecX; i < x; i++) { \
        dst[i] = src[i]; \
    }

void cpy_vec2(vec2 src, vec2 dst) { cpy_vecx_bdy(2, src, dst) }
void cpy_vec3(vec3 src, vec3 dst) { cpy_vecx_bdy(3, src, dst) }
void cpy_vec4(vec4 src, vec4 dst) { cpy_vecx_bdy(4, src, dst) }

#define print_vecx_bdy(x, vec, count) \
    for(size_t i = 0; i < count; i++) { \
        printf("<%4.3g", ((vecx(x) *) vec)[i][vecX]); \
        for(int j = vecY; j < x; j++) { \
            printf(", %4.3g", ((vecx(x) *) vec)[i][j]); \
        } \
        printf(">\n"); \
    }

void print_vec2(vec2 vec, size_t count) { print_vecx_bdy(2, vec, count) }
void print_vec3(vec3 vec, size_t count) { print_vecx_bdy(3, vec, count) }
void print_vec4(vec4 vec, size_t count) { print_vecx_bdy(4, vec, count) }