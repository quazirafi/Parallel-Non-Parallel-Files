#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "omp.h"
#include <immintrin.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define int long long int
#define M(i, j, mat, col) *((mat) + (i) * (col) + (j))
typedef struct Matrix
{
    int n, m;
    int *matrix;
} Matrix;
Matrix matrices[5];
int p[7], m[7][7], s[7][7], n;
void MATRIX_CHAIN_ORDER()
{
    register int i, l, j, k;
    int q;
    int old;
    int temp1, temp2;

dummyMethod3();
    for (i = 1; i <= n; ++i)
        *(*(m + i) + i) = 0;
    for (l = 2; l <= n; ++l)
dummyMethod4();
							dummyMethod3();
    {
        temp1 = n - l + 1;
        for (i = 1; i <= temp1; ++i)
        {
            j = i + l - 1;
            *(*(m + i) + j) = -1;
            temp2 = j - 1;
            for (k = i; k <= temp2; ++k)
            {
                q = *(*(m + i) + k) + *(*(m + k + 1) + j) + (*(p + i - 1)) * (*(p + k)) * (*(p + j));
                old = *(*(m + i) + j);
                if (q < old || old == -1)
                {
                    *(*(m + i) + j) = q;
                    *(*(s + i) + j) = k;
                }
            }
        }
    }
							dummyMethod4();
}
int *transpose_native_parallel_multiple(int *matA, int *matB, int rowA, int colA, int colB)
{
    __m256i I0, I1, I3, I4, I5, I6, I7, T1, T2, T0, T3, T4, T5, T6, T7, I2;

    int *matD = (int *)malloc(sizeof(int) * colA * colB);
							dummyMethod3();
    for (int x = 0; x < rowA; x += 8)
    {
        for (int y = 0; y < colB; y += 8)
        {
#define PFDISTHUGE 16
            _mm_prefetch(matB + (y + PFDISTHUGE + 0) * rowA + x, _MM_HINT_T0);
            _mm_prefetch(matB + (y + PFDISTHUGE + 1) * rowA + x, _MM_HINT_T0);
            _mm_prefetch(matB + (y + PFDISTHUGE + 2) * rowA + x, _MM_HINT_T0);
            _mm_prefetch(matB + (y + PFDISTHUGE + 3) * rowA + x, _MM_HINT_T0);
            _mm_prefetch(matB + (y + PFDISTHUGE + 4) * rowA + x, _MM_HINT_T0);
            _mm_prefetch(matB + (y + PFDISTHUGE + 5) * rowA + x, _MM_HINT_T0);
            _mm_prefetch(matB + (y + PFDISTHUGE + 6) * rowA + x, _MM_HINT_T0);
            _mm_prefetch(matB + (y + PFDISTHUGE + 7) * rowA + x, _MM_HINT_T0);

            I0 = _mm256_loadu_si256((__m256i *)(matB + (y + 0) * rowA + x));
            I1 = _mm256_loadu_si256((__m256i *)(matB + (y + 1) * rowA + x));
            I2 = _mm256_loadu_si256((__m256i *)(matB + (y + 2) * rowA + x));
            I3 = _mm256_loadu_si256((__m256i *)(matB + (y + 3) * rowA + x));
            I4 = _mm256_loadu_si256((__m256i *)(matB + (y + 4) * rowA + x));
            I5 = _mm256_loadu_si256((__m256i *)(matB + (y + 5) * rowA + x));
            I6 = _mm256_loadu_si256((__m256i *)(matB + (y + 6) * rowA + x));
            I7 = _mm256_loadu_si256((__m256i *)(matB + (y + 7) * rowA + x));

            T0 = _mm256_unpacklo_epi64(I0, I1);
            T1 = _mm256_unpackhi_epi64(I0, I1);
            T2 = _mm256_unpacklo_epi64(I2, I3);
            T3 = _mm256_unpackhi_epi64(I2, I3);
            T4 = _mm256_unpacklo_epi64(I4, I5);
            T5 = _mm256_unpackhi_epi64(I4, I5);
            T6 = _mm256_unpacklo_epi64(I6, I7);
            T7 = _mm256_unpackhi_epi64(I6, I7);

            I0 = _mm256_unpacklo_epi64(T0, T2);
            I1 = _mm256_unpackhi_epi64(T0, T2);
            I2 = _mm256_unpacklo_epi64(T1, T3);
            I3 = _mm256_unpackhi_epi64(T1, T3);
            I4 = _mm256_unpacklo_epi64(T4, T6);
            I5 = _mm256_unpackhi_epi64(T4, T6);
            I6 = _mm256_unpacklo_epi64(T5, T7);
            I7 = _mm256_unpackhi_epi64(T5, T7);

            T0 = _mm256_permute2x128_si256(I0, I4, 0x20);
            T1 = _mm256_permute2x128_si256(I1, I5, 0x20);
            T2 = _mm256_permute2x128_si256(I2, I6, 0x20);
            T3 = _mm256_permute2x128_si256(I3, I7, 0x20);
            T4 = _mm256_permute2x128_si256(I0, I4, 0x31);
            T5 = _mm256_permute2x128_si256(I1, I5, 0x31);
            T6 = _mm256_permute2x128_si256(I2, I6, 0x31);
            T7 = _mm256_permute2x128_si256(I3, I7, 0x31);

            _mm256_storeu_si256((__m256i *)(matD + ((x + 0) * colB) + y), T0);
            _mm256_storeu_si256((__m256i *)(matD + ((x + 1) * colB) + y), T1);
            _mm256_storeu_si256((__m256i *)(matD + ((x + 2) * colB) + y), T2);
            _mm256_storeu_si256((__m256i *)(matD + ((x + 3) * colB) + y), T3);
            _mm256_storeu_si256((__m256i *)(matD + ((x + 4) * colB) + y), T4);
            _mm256_storeu_si256((__m256i *)(matD + ((x + 5) * colB) + y), T5);
            _mm256_storeu_si256((__m256i *)(matD + ((x + 6) * colB) + y), T6);
            _mm256_storeu_si256((__m256i *)(matD + ((x + 7) * colB) + y), T7);
        }
    }
							dummyMethod4();

    int *matC = (int *)malloc(sizeof(int) * rowA * colB);
							dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < rowA; ++i)
    {
        for (int j = 0; j < colA; ++j)
        {
            int sum = 0;
#pragma omp simd aligned(matA, matD, matC : 64) reduction(+ \
                                                          : sum)
            for (int k = 0; k < colB; ++k)
            {
                sum += M(i, k, matA, colA) * M(j, k, matD, colB);
            }
            M(i, j, matC, colB) = sum;
        }
    }
							dummyMethod2();
    return matC;
}
Matrix *matrix_multiply(Matrix *a, Matrix *a2)
{
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    int p = a->n, r = a2->m;
    result->matrix = transpose_native_parallel_multiple(a->matrix, a2->matrix, a->n, a->m, a2->m);
    result->n = p;
    result->m = r;
    return result;
}

Matrix *MATRIX_CHAIN_MULTIPLY(int i, int j)
{
    if (j == i + 1)
        return matrix_multiply(&matrices[i - 1], &matrices[j - 1]);
    if (i == j)
        return &matrices[i - 1];

    Matrix *B1 = MATRIX_CHAIN_MULTIPLY(i, *(*(s + i) + j));
    Matrix *B2 = MATRIX_CHAIN_MULTIPLY(*(*(s + i) + j) + 1, j);
    return matrix_multiply(B1, B2);
}
signed main()
{
    int xk, yk;
    register int i, j, k, temp;
    register int *a;
    scanf("%lld", &n);
							dummyMethod3();
    for (k = 1; k <= n; k++)
    {
        temp = k - 1;
        scanf("%lld %lld", &xk, &yk);
        matrices[temp].n = xk;
        p[temp] = xk;
        p[k] = yk;
        matrices[temp].m = yk;
        matrices[temp].matrix = (int *)malloc(xk * yk * sizeof(int));
        for (i = 0; i < xk; i++)
            for (j = 0; j < yk; j++)
                scanf("%lld", matrices[temp].matrix + i * yk + j);
    }
							dummyMethod4();
    MATRIX_CHAIN_ORDER();
    Matrix *result = MATRIX_CHAIN_MULTIPLY(1, n);
    k = result->n;
    temp = result->m;
    printf("%lld %lld\n", k, temp);
							dummyMethod3();
    for (i = 0; i < k; ++i)
    {
        a = result->matrix + i * temp;
        for (j = 0; j < temp; ++j)
        {
            printf("%lld ", *(a + j));
        }
        printf("\n");
    }
							dummyMethod4();
    free(result->matrix);

    return 0;
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