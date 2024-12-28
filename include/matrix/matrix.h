#ifndef MATRIX_H
#define MATRIX_H
#include <stddef.h>
#include <stdio.h>

typedef struct matrix Matrix;

struct matrix {
    size_t nr;
    size_t nc;
    size_t n;
    float * vals;
};

void matrix_accdwn (const Matrix * matrix, Matrix * result);
void matrix_accrgt (const Matrix * matrix, Matrix * result);
void matrix_addsca (const Matrix * left, float right, Matrix * result);
float matrix_avgall (const Matrix * matrix);
void matrix_avgdwn (const Matrix * matrix, Matrix * result);
void matrix_avgrgt (const Matrix * matrix, Matrix * result);
void matrix_bctdwn (const Matrix * matrix, Matrix * result);
void matrix_bctrgt (const Matrix * matrix, Matrix * result);
Matrix * matrix_create (size_t nr, size_t nc);
void matrix_divsca (const Matrix * matrix, float factor, Matrix * result);
void matrix_dotpro (const Matrix * left, const Matrix * right, Matrix * result);
void matrix_destroy (Matrix ** matrix);
void matrix_ebeadd (const Matrix * left, const Matrix * right, Matrix * result);
void matrix_ebediv (const Matrix * left, const Matrix * right, Matrix * result);
void matrix_ebemap (const Matrix * matrix, float (*f) (float), Matrix * result);
void matrix_ebesub (const Matrix * left, const Matrix * right, Matrix * result);
void matrix_hadpro (const Matrix * left, const Matrix * right, Matrix * result);
float matrix_maxall (const Matrix * matrix);
void matrix_maxdwn (const Matrix * matrix, Matrix * result);
void matrix_maxrgt (const Matrix * matrix, Matrix * result);
float matrix_minall (const Matrix * matrix);
void matrix_mindwn (const Matrix * matrix, Matrix * result);
void matrix_minrgt (const Matrix * matrix, Matrix * result);
void matrix_print (FILE * stream, Matrix * matrix, char * title);
float matrix_sdvall (const Matrix * matrix);
void matrix_sdvdwn (const Matrix * matrix, Matrix * result);
void matrix_sdvrgt (const Matrix * matrix, Matrix * result);
void matrix_scapro (const Matrix * left, float right, Matrix * result);
// void matrix_stzall (const Matrix * matrix, float * avg, float * stddev, float * result);
// void matrix_stzrgt (const Matrix * matrix, Matrix * avgs, Matrix * stddevs, Matrix * result);
void matrix_stzdwn (const Matrix * matrix, Matrix * avgs, Matrix * stddevs, Matrix * result);
void matrix_subsca (const Matrix * left, float right, Matrix * result);
bool matrix_testeq (const Matrix * a, const Matrix * b, float eps);
void matrix_transp (const Matrix * matrix, const Matrix * result);
float matrix_varall (const Matrix * matrix);
void matrix_vardwn (const Matrix * matrix, Matrix * result);
void matrix_varrgt (const Matrix * matrix, Matrix * result);
void matrix_zero_ (Matrix * matrix);

#endif
