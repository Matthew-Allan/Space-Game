#ifndef MATRIX_H
#define MATRIX_H

#include <sys/types.h>
#include <math.h>

#include "vector.h"

#define matmn(m, n, name) float name[n][m]

typedef matmn(2, 2, mat2);
typedef matmn(3, 3, mat3);
typedef matmn(4, 4, mat4);

#define matI 0
#define matJ 1
#define matK 2
#define matW 3

#define mat2(i, j) {i, j}
#define mat3(i, j, k) {i, j, k}
#define mat4(i, j, k, w) {i, j, k, w}

#define fmat2(v) mat2(fvec2(v), fvec2(v))
#define fmat3(v) mat3(fvec3(v), fvec3(v), fvec3(v))
#define fmat4(v) mat4(fvec4(v), fvec4(v), fvec4(v), fvec4(v))

#define mat2i(a, b) mat2(vec2(a, 0), vec2(0, b))
#define mat3i(a, b, c) mat3(vec3(a, 0, 0), vec3(0, b, 0), vec3(0, 0, c))
#define mat4i(a, b, c, d) mat4(vec4(a, 0, 0, 0), vec4(0, b, 0, 0), vec4(0, 0, c, 0), vec4(0, 0, 0, d))

#define fmat2i(v) mat2i(v, v)
#define fmat3i(v) mat3i(v, v, v)
#define fmat4i(v) mat4i(v, v, v, v)

#define scale_mat(x, y, z) mat4i(x, y, z, 1)
#define trans_mat(x, y, z) mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(x, y, z, 1))

#define rotx_mat(theta) mat4(vec4(1, 0, 0, 0), vec4(0, cosf(theta), sinf(theta), 0), vec4(0, -sinf(theta), cosf(theta), 0), vec4(0, 0, 0, 1))
#define roty_mat(theta) mat4(vec4(cosf(theta), 0, -sinf(theta), 0), vec4(0, 1, 0, 0), vec4(sinf(theta), 0, cosf(theta), 0), vec4(0, 0, 0, 1))
#define rotz_mat(theta) mat4(vec4(cosf(theta), sinf(theta), 0, 0), vec4(-sinf(theta), cosf(theta), 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1))

#define rot_axis_mat(rx, ry, rz, theta) mat4( \
    vec4((      cosf(theta)) + (rx * rx * (1 - cosf(theta))), (rz *  sinf(theta)) + (ry * rx * (1 - cosf(theta))), (ry * -sinf(theta)) + (rz * rx * (1 - cosf(theta))), 0), \
    vec4((rz * -sinf(theta)) + (rx * ry * (1 - cosf(theta))), (      cosf(theta)) + (ry * ry * (1 - cosf(theta))), (rx *  sinf(theta)) + (rz * ry * (1 - cosf(theta))), 0), \
    vec4((ry *  sinf(theta)) + (rx * rz * (1 - cosf(theta))), (rx * -sinf(theta)) + (ry * rz * (1 - cosf(theta))), (      cosf(theta)) + (rz * rz * (1 - cosf(theta))), 0), \
    vec4(0, 0, 0, 1) \
)

#define ortho_mat_sp(a, b) (2.f / (a - b))
#define ortho_mat_tp(a, b) (((float) (a + b)) / (b - a))

#define ortho_mat(left, right, bottom, top, near, far) mat4( \
    vec4(ortho_mat_sp(right, left), 0, 0, 0), \
    vec4(0, ortho_mat_sp(top, bottom), 0, 0), \
    vec4(0, 0, ortho_mat_sp(near, far), 0), \
    vec4(ortho_mat_tp(right, left), ortho_mat_tp(top, bottom), ortho_mat_tp(far, near), 1) \
)

#define persp_mat(fov, aspect, near, far) mat4( \
    vec4(1.f / (aspect * tanf(fov / 2)), 0, 0, 0), \
    vec4(0, 1.f / tanf(fov / 2), 0, 0), \
    vec4(0, 0, (far + near) / (near - far), -1), \
    vec4(0, 0, (2 * far * near) / (near - far), 0) \
)

#define marr(mat) ((float *) (mat))

#define matijr(mat, i, j, row) (mat[(j * row) + i])
#define matij(mat, i, j) (mat[j][i])

void mat2_add_slr(mat2 mat, float scalar, mat2 out, size_t count);
void mat3_add_slr(mat3 mat, float scalar, mat3 out, size_t count);
void mat4_add_slr(mat4 mat, float scalar, mat4 out, size_t count);

void matmn_add_slr(float *mat, float scalar, float *out, size_t m, size_t n, size_t count);

void mat2_mlt_slr(mat2 mat, float scalar, mat2 out, size_t count);
void mat3_mlt_slr(mat3 mat, float scalar, mat3 out, size_t count);
void mat4_mlt_slr(mat4 mat, float scalar, mat4 out, size_t count);

void matmn_mlt_slr(float *mat, float scalar, float *out, size_t m, size_t n, size_t count);

void mat2_div_slr(mat2 mat, float scalar, mat2 out, size_t count);
void mat3_div_slr(mat3 mat, float scalar, mat3 out, size_t count);
void mat4_div_slr(mat4 mat, float scalar, mat4 out, size_t count);

void matmn_div_slr(float *mat, float scalar, float *out, size_t m, size_t n, size_t count);

void mat2_add(mat2 mat_a, mat2 mat_b, mat2 out, size_t count);
void mat3_add(mat3 mat_a, mat3 mat_b, mat3 out, size_t count);
void mat4_add(mat4 mat_a, mat4 mat_b, mat4 out, size_t count);

void matmn_add(float *mat_a, float *mat_b, float *out, size_t m, size_t n, size_t count);

void mat2_sub(mat2 mat_a, mat2 mat_b, mat2 out, size_t count);
void mat3_sub(mat3 mat_a, mat3 mat_b, mat3 out, size_t count);
void mat4_sub(mat4 mat_a, mat4 mat_b, mat4 out, size_t count);

void matmn_sub(float *mat_a, float *mat_b, float *out, size_t m, size_t n, size_t count);

void mat2_mlt(mat2 mat_a, mat2 mat_b, mat2 out, size_t count);
void mat3_mlt(mat3 mat_a, mat3 mat_b, mat3 out, size_t count);
void mat4_mlt(mat4 mat_a, mat4 mat_b, mat4 out, size_t count);

void matmn_mlt_matnp(float *mat_a, float *mat_b, float *out, size_t m, size_t n, size_t p, size_t count);

void print_mat2(mat2 mat, size_t count);
void print_mat3(mat3 mat, size_t count);
void print_mat4(mat4 mat, size_t count);

void print_matmn(float *mat, size_t m, size_t n, size_t count);

#endif