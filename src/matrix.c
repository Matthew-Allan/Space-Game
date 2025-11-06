#include "matrix.h"

#include <stdio.h>

#define matmn_opp_bdy(opp, mat, out, m, n, count) \
    for(size_t c = 0; c < count; c++, out += m * n, mat += m * n) { \
        for(size_t i = 0; i < m; i++) { \
            for(size_t j = 0; j < n; j++) { \
                matijr(out, i, j, m) = matijr(mat, i, j, m) opp; \
            } \
        } \
    }

void matmn_add_slr(float *mat, float scalar, float *out, size_t m, size_t n, size_t count) { matmn_opp_bdy(+ scalar, mat, out, m, n, count); }

void mat2_add_slr(mat2 mat, float scalar, mat2 out, size_t count) { matmn_add_slr(marr(mat), scalar, marr(out), 2, 2, count); }
void mat3_add_slr(mat3 mat, float scalar, mat3 out, size_t count) { matmn_add_slr(marr(mat), scalar, marr(out), 3, 3, count); }
void mat4_add_slr(mat4 mat, float scalar, mat4 out, size_t count) { matmn_add_slr(marr(mat), scalar, marr(out), 4, 4, count); }

void matmn_mlt_slr(float *mat, float scalar, float *out, size_t m, size_t n, size_t count) { matmn_opp_bdy(* scalar, mat, out, m, n, count); }

void mat2_mlt_slr(mat2 mat, float scalar, mat2 out, size_t count) { matmn_mlt_slr(marr(mat), scalar, marr(out), 2, 2, count); }
void mat3_mlt_slr(mat3 mat, float scalar, mat3 out, size_t count) { matmn_mlt_slr(marr(mat), scalar, marr(out), 3, 3, count); }
void mat4_mlt_slr(mat4 mat, float scalar, mat4 out, size_t count) { matmn_mlt_slr(marr(mat), scalar, marr(out), 4, 4, count); }

void matmn_div_slr(float *mat, float scalar, float *out, size_t m, size_t n, size_t count) { matmn_opp_bdy(/ scalar, mat, out, m, n, count); }

void mat2_div_slr(mat2 mat, float scalar, mat2 out, size_t count) { matmn_div_slr(marr(mat), scalar, marr(out), 2, 2, count); }
void mat3_div_slr(mat3 mat, float scalar, mat3 out, size_t count) { matmn_div_slr(marr(mat), scalar, marr(out), 3, 3, count); }
void mat4_div_slr(mat4 mat, float scalar, mat4 out, size_t count) { matmn_div_slr(marr(mat), scalar, marr(out), 4, 4, count); }

void matmn_add(float *mat_a, float *mat_b, float *out, size_t m, size_t n, size_t count) { matmn_opp_bdy(+ matijr(mat_b, i, j, m), mat_a, out, m, n, count); }

void mat2_add(mat2 mat_a, mat2 mat_b, mat2 out, size_t count) { matmn_add(marr(mat_a), marr(mat_b), marr(out), 2, 2, count); }
void mat3_add(mat3 mat_a, mat3 mat_b, mat3 out, size_t count) { matmn_add(marr(mat_a), marr(mat_b), marr(out), 3, 3, count); }
void mat4_add(mat4 mat_a, mat4 mat_b, mat4 out, size_t count) { matmn_add(marr(mat_a), marr(mat_b), marr(out), 4, 4, count); }

void matmn_sub(float *mat_a, float *mat_b, float *out, size_t m, size_t n, size_t count) { matmn_opp_bdy(- matijr(mat_b, i, j, m), mat_a, out, m, n, count); }

void mat2_sub(mat2 mat_a, mat2 mat_b, mat2 out, size_t count) { matmn_sub(marr(mat_a), marr(mat_b), marr(out), 2, 2, count); }
void mat3_sub(mat3 mat_a, mat3 mat_b, mat3 out, size_t count) { matmn_sub(marr(mat_a), marr(mat_b), marr(out), 3, 3, count); }
void mat4_sub(mat4 mat_a, mat4 mat_b, mat4 out, size_t count) { matmn_sub(marr(mat_a), marr(mat_b), marr(out), 4, 4, count); }

void matmn_mlt_matnp(float *mat_a, float *mat_b, float *out, size_t m, size_t n, size_t p, size_t count) {
    matmn(m, p, temp);
    for(size_t c = 0; c < count; c++, out += m * p, mat_a += m * n) {
        for(size_t i = 0; i < m; i++) {
            for(size_t j = 0; j < p; j++) {
                float val = 0;
                for(size_t k = 0; k < n; k++) {
                    val += matijr(mat_a, i, k, m) * matijr(mat_b, k, j, n);
                }
                matij(temp, i, j) = val;
            }
        }
        for(size_t i = 0; i < m; i++) {
            for(size_t j = 0; j < p; j++) {
                matijr(out, i, j, m) = matij(temp, i, j);
            }
        }
    }
}

void mat2_mlt(mat2 mat_a, mat2 mat_b, mat2 out, size_t count) { matmn_mlt_matnp(marr(mat_a), marr(mat_b), marr(out), 2, 2, 2, count); }
void mat3_mlt(mat3 mat_a, mat3 mat_b, mat3 out, size_t count) { matmn_mlt_matnp(marr(mat_a), marr(mat_b), marr(out), 3, 3, 3, count); }
void mat4_mlt(mat4 mat_a, mat4 mat_b, mat4 out, size_t count) { matmn_mlt_matnp(marr(mat_a), marr(mat_b), marr(out), 4, 4, 4, count); }

void print_matmn(float *mat, size_t m, size_t n, size_t count) {
    for(size_t c = 0; c < count; c++, mat += m * n) {
        for(size_t i = 0; i < m; i++) {
            for(size_t j = 0; j < n; j++) {
                printf("%-6.3g ", matijr(mat, i, j, m));
            }
            printf("\n");
        }
        printf(c == count - 1 ? "" : "------------------\n");
    }
}

void print_mat2(mat2 mat, size_t count) { print_matmn(marr(mat), 2, 2, count); }
void print_mat3(mat3 mat, size_t count) { print_matmn(marr(mat), 3, 3, count); }
void print_mat4(mat4 mat, size_t count) { print_matmn(marr(mat), 4, 4, count); }