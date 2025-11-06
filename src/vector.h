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

void vec2_add_slr(vec2 vec, float scalar, vec2 out, size_t count);
void vec3_add_slr(vec3 vec, float scalar, vec3 out, size_t count);
void vec4_add_slr(vec4 vec, float scalar, vec4 out, size_t count);

void vec2_mlt_slr(vec2 vec, float scalar, vec2 out, size_t count);
void vec3_mlt_slr(vec3 vec, float scalar, vec3 out, size_t count);
void vec4_mlt_slr(vec4 vec, float scalar, vec4 out, size_t count);

void vec2_div_slr(vec2 vec, float scalar, vec2 out, size_t count);
void vec3_div_slr(vec3 vec, float scalar, vec3 out, size_t count);
void vec4_div_slr(vec4 vec, float scalar, vec4 out, size_t count);

void vec2_add(vec2 vec_a, vec2 vec_b, vec2 out, size_t count);
void vec3_add(vec3 vec_a, vec3 vec_b, vec3 out, size_t count);
void vec4_add(vec4 vec_a, vec4 vec_b, vec4 out, size_t count);

void vec2_sub(vec2 vec_a, vec2 vec_b, vec2 out, size_t count);
void vec3_sub(vec3 vec_a, vec3 vec_b, vec3 out, size_t count);
void vec4_sub(vec4 vec_a, vec4 vec_b, vec4 out, size_t count);

void vec2_mlt(vec2 vec_a, vec2 vec_b, vec2 out, size_t count);
void vec3_mlt(vec3 vec_a, vec3 vec_b, vec3 out, size_t count);
void vec4_mlt(vec4 vec_a, vec4 vec_b, vec4 out, size_t count);

void vec2_div(vec2 vec_a, vec2 vec_b, vec2 out, size_t count);
void vec3_div(vec3 vec_a, vec3 vec_b, vec3 out, size_t count);
void vec4_div(vec4 vec_a, vec4 vec_b, vec4 out, size_t count);

float vec2_dot(vec2 vec_a, vec2 vec_b);
float vec3_dot(vec3 vec_a, vec3 vec_b);
float vec4_dot(vec4 vec_a, vec4 vec_b);

float vec2_len(vec2 vec);
float vec3_len(vec3 vec);
float vec4_len(vec4 vec);

void set_vec2(vec2 vec, float x, float y);
void set_vec3(vec3 vec, float x, float y, float z);
void set_vec4(vec4 vec, float x, float y, float z, float w);

void cpy_vec2(vec2 src, vec2 dst);
void cpy_vec3(vec3 src, vec3 dst);
void cpy_vec4(vec4 src, vec4 dst);

void vec2_norm(vec2 vec, vec2 out);
void vec3_norm(vec3 vec, vec3 out);
void vec4_norm(vec4 vec, vec4 out);

void cross_product(vec3 vec_a, vec3 vec_b, vec3 out);

void print_vec2(vec2 vec, size_t count);
void print_vec3(vec3 vec, size_t count);
void print_vec4(vec4 vec, size_t count);

#endif