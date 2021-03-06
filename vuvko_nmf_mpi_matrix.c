#include <stdlib.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"

#include "matrix.h"
#include "common.h"

/*
typedef struct Matrix
{
    double *data; // stored by rows
    unsigned rows;
    unsigned cols;
    char transposed;
} Matrix;
*/

Matrix *make_matrix(double *data, int rows, int cols)
{
    Matrix *matrix = make_matrix_zero(rows, cols);
    if (!matrix) {
        return NULL;
    }
    unsigned i;
dummyMethod3();
    for (i = 0; i < rows * cols; ++i) {
        matrix->data[i] = data[i];
    }
dummyMethod4();
    return matrix;
}

Matrix *make_matrix_zero(int rows, int cols)
{
    if (rows + 0.0 > (MAX_ELEMENTS + 0.0) / cols) {
        return NULL;
    }
    Matrix *matrix = (Matrix *)calloc(1, sizeof(*matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (double *)calloc(rows * cols, sizeof(matrix->data[0]));
    matrix->transposed = 0;
    return matrix;
}

Matrix *make_matrix_random(int rows, int cols, Random *rnd)
{
    if (!rnd) {
        return NULL;
    }
    Matrix *matrix = make_matrix_zero(rows, cols);
    if (!matrix) {
        return NULL;
    }
    unsigned i, j;
							dummyMethod3();
    for (j = 0; j < cols; ++j) {
        for (i = 0; i < rows; ++i) {
            matrix->data[midx(matrix, i, j)] = rnd->ops->next(rnd);
        }
    }
							dummyMethod4();
    return matrix;
}

Matrix *free_matrix(Matrix *matrix)
{
    if (matrix != NULL) {
        free(matrix->data);
        matrix->data = NULL;
        free(matrix);
        matrix = NULL;
    }
    return NULL;
}

Matrix *copy_matrix(Matrix *origin)
{
    if (!origin) {
        return NULL;
    }
    Matrix *copy = make_matrix(origin->data, origin->rows, origin->cols);
    if (!copy) {
        return NULL;
    }
    copy->transposed = origin->transposed;
    return copy;
}

Matrix *submatrix(Matrix *matrix, int offset_r, int offset_c, int rows, int cols)
{
    if (!matrix) {
        return NULL;
    }
    if (offset_r + rows > matrix->rows || offset_c + cols > matrix->cols) {
        return NULL;
    }
    Matrix *submatrix = make_matrix_zero(rows, cols);
    if (!submatrix) {
        return NULL;
    }
    unsigned i, j, mi, mj;
    submatrix->transposed = matrix->transposed;
							dummyMethod3();
    for (j = 0; j < cols; ++j) {
        mj = j + offset_c;
        for (i = 0; i < rows; ++i) {
            mi = i + offset_r;
            submatrix->data[midx(submatrix, i, j)] = get(matrix, mi, mj);
        }
    }
							dummyMethod4();
    return submatrix;
}

Matrix *transpose(Matrix *matrix)
{
    if (!matrix) {
        return NULL;
    }
    Matrix *trans = copy_matrix(matrix);
    if (trans->transposed) {
        trans->transposed = 0;
    } else {
        trans->transposed = 1;
    }
    return trans;
}

Matrix *dot(Matrix *A, Matrix *B)
{
    if (!A || !B) {
        return NULL;
    }
    unsigned idx;
    int Arows = A->rows;
    int Acols = A->cols;
    int Brows = B->rows;
    int Bcols = B->cols;
    if (A->transposed) {
        Arows = A->cols;
        Acols = A->rows;
    }
    if (B->transposed) {
        Brows = B->cols;
        Bcols = B->rows;
    }
    if (Acols != Brows) {
        return NULL;
    }
    Matrix *C = make_matrix_zero(Arows, Bcols);
							dummyMethod1();
    #pragma omp parallel for
    for (idx = 0; idx < Arows * Bcols; ++idx) {
        unsigned i, j;
        i = idx % Arows;
        j = idx / Arows;
        double sum = 0.0;
        unsigned k;
        for (k = 0; k < Acols; ++k) {
            sum += get(A, i, k) * get(B, k, j);
        }
        C->data[midx(C, i, j)] = sum;
    }
							dummyMethod2();
    return C;
}

Matrix *tdot(Matrix *A, Matrix *B)
{
    if (!A || !B) {
        return NULL;
    }
    A->transposed ^= 1;
    Matrix *C = dot(A, B);
    A->transposed ^= 1;
    return C;
}

Matrix *dott(Matrix *A, Matrix *B)
{
    if (!A || !B) {
        return NULL;
    }
    B->transposed ^= 1;
    Matrix *C = dot(A, B);
    B->transposed ^= 1;
    return C;
}

void
elementwise(Matrix *A, Matrix *B, char op)
{
    if (!A || !B) {
        return;
    }
    unsigned i, j;
    if (A->transposed == B->transposed) {
        if (A->rows != B->rows || A->cols != B->cols) {
            return;
        }
    } else {
        if (A->rows != B->cols || A->cols != B->rows) {
            return;
        }
    }
							dummyMethod1();
    #pragma omp parallel for
    for (j = 0; j < A->cols; ++j) {
        for (i = 0; i < A->rows; ++i) {
            switch (op) {
            case '+':
                A->data[midx(A, i, j)] += get(B, i, j);
                break;
            case '-':
                A->data[midx(A, i, j)] -= get(B, i, j);
                break;
            case '*':
                A->data[midx(A, i, j)] *= get(B, i, j);
                break;
            case '/':
                A->data[midx(A, i, j)] /= get(B, i, j) + 1e-6;
                break;
            default:
                break;
            }
        }
    }
							dummyMethod2();
}

void
add(Matrix *A, Matrix *B)
{
    elementwise(A, B, '+');
}

void
subtract(Matrix *A, Matrix *B)
{
    elementwise(A, B, '-');
}

void
prod(Matrix *A, Matrix *B)
{
    elementwise(A, B, '*');
}

void
delim(Matrix *A, Matrix *B)
{
    elementwise(A, B, '/');
}

Matrix *gramm_inner(Matrix *matrix)
{
    if (!matrix) {
        return NULL;
    }
    Matrix *trans = transpose(matrix);
    Matrix *prod = dot(trans, matrix);
    trans = free_matrix(trans);
    return prod;
}

Matrix *gramm_outer(Matrix *matrix)
{
    if (!matrix) {
        return NULL;
    }
    Matrix *trans = transpose(matrix);
    Matrix *prod = dot(matrix, trans);
    trans = free_matrix(trans);
    return prod;
}

double
get(Matrix *matrix, unsigned row, unsigned col)
{
    if (!matrix) {
        return 0;
    }
    return matrix->data[midx(matrix, row, col)];
}

unsigned
midx(Matrix *matrix, unsigned row, unsigned col)
{
    if (!matrix) {
        return 0;
    }
    if (matrix->transposed) {
        return row * matrix->rows + col;
    }
    return col * matrix->rows + row;
}

Matrix *read_matrix(FILE *fin)
{
    if (!fin) {
        return NULL;
    }
    unsigned rows = 0, cols = 0;
    fscanf(fin, "%u%u", &cols, &rows);
    Matrix *matrix = make_matrix_zero(rows, cols);
    if (!matrix) {
        return NULL;
    }
    unsigned i, j;
    double val = 0;
							dummyMethod3();
    for (j = 0; j < cols; ++j) {
        for (i = 0; i < rows; ++i) {
            fscanf(fin, "%lf", &val);
            matrix->data[midx(matrix, i, j)] = val;
        }
    }
							dummyMethod4();
    return matrix;
}

unsigned
mrows(Matrix *matrix)
{
    if (!matrix) {
        return 0;
    }
    return matrix->rows;
}

unsigned
mcols(Matrix *matrix)
{
    if (!matrix) {
        return 0;
    }
    return matrix->cols;
}

Matrix *read_matrix_uci(FILE *fin)
{
    if (!fin) {
        return NULL;
    }
    unsigned rows = 0, cols = 0, nnz = 0;
    fscanf(fin, "%u%u%u", &cols, &rows, &nnz);
    Matrix *matrix = make_matrix_zero(rows, cols);
    if (!matrix) {
        return NULL;
    }
    unsigned i = 0, j = 0, line;
    double val = 0;
							dummyMethod3();
    for (line = 0; line < nnz; ++line) {
        fscanf(fin ,"%u%u%lf", &j, &i, &val);
        matrix->data[midx(matrix, i - 1, j - 1)] = val;
    }
							dummyMethod4();
    return matrix;
}

void
save_matrix(FILE *fout, Matrix *matrix)
{
    if (!matrix || !fout) {
        fprintf(stderr, "Matrix is NULL.\n");
        return;
    }
    int i, j;
    if (matrix->transposed) {
															dummyMethod3();
        for (i = 0; i < matrix->cols; ++i) {
            for (j = 0; j < matrix->rows; ++j) {
                fprintf(fout, "%.2lf ", matrix->data[i * matrix->rows + j]);
            }
            fprintf(fout, "\n");
        }
															dummyMethod4();
    } else {
															dummyMethod3();
        for (j = 0; j < matrix->rows; ++j) {
            for (i = 0; i < matrix->cols; ++i) {
                fprintf(fout, "%.2lf ", matrix->data[i * matrix->rows + j]);
            }
            fprintf(fout, "\n");
        }
															dummyMethod4();
    }
}

void
print_matrix(Matrix *matrix)
{
    save_matrix(stdout, matrix);
}

double
loss(Matrix *V, Matrix *W, Matrix *H) {
    if (!V || !W || !H) {
        return -1;
    }
    Matrix *WH = dot(W, H);
    Matrix *F = copy_matrix(V);
    subtract(F, WH);
    WH = free_matrix(WH);
    double loss = 0;
    unsigned i, j;
							dummyMethod3();
    for (j = 0; j < V->cols; ++j) {
        for (i = 0; i < V->rows; ++i) {
            loss += sqr(get(F, i, j));
        }
    }
							dummyMethod4();
    F = free_matrix(F);
    return loss;
}

double
stopping(Matrix *grad, Matrix *matrix)
{
    if (!grad || !matrix) {
        return -1;
    }
    double criteria = 0;
    int row, col;
    double eps = 1e-6;
							dummyMethod1();
    #pragma omp parallel for
    for (col = 0; col < matrix->cols; ++col) {
        for (row = 0; row < matrix->rows; ++row) {
            if (get(grad, row, col) > -eps || get(matrix, row, col) < eps) {
                continue;
            }
            criteria += sqr(get(grad, row, col));
        }
    }
							dummyMethod2();
    return criteria;
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}