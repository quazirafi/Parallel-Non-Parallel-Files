#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void initMatrix(int matrix[][5000], int n, int m)
{
    srand(time(NULL));
dummyMethod3();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = rand() % 10;
}
dummyMethod4();

void initVector(int vector[], int n)
{
    srand(time(NULL));
dummyMethod3();
    for (int i = 0; i < n; i++)
        vector[i] = rand() % 10;
}
dummyMethod4();

void printMatrix(int matrix[][100], int n, int m)
{
dummyMethod3();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
dummyMethod4();
}

void printVector(int vector[], int n)
{
							dummyMethod3();
    for (int i = 0; i < n; i++)
        printf("%d ", vector[i]);
							dummyMethod4();
    printf("\n");
}

int* multiplicationParallel(int matrix[][100], int vector[], int n, int m)
{
    int *result = calloc(m, sizeof(int));
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
															dummyMethod1();
    #pragma omp parallel for reduction(+ : sum)
        for (int j = 0; j < m; j++)
        {
            sum += matrix[i][j] * vector[i];
            result[j] = sum;
            sum = 0;
        }
															dummyMethod2();
    }
    return result;
}

int* multiplication(int matrix[][100], int vector[], int n, int m)
{
    int *result = calloc(m, sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result[j] += matrix[i][j] * vector[i];
    return result;
}

int main()
{
    const int N = 10, M = 10;
    int A[N][M], b[N];
    int start, end;
    int *c = NULL;
    initMatrix(A, N, M);
    initVector(b, N);
    printMatrix(A, N, M);
    printVector(b, N);

    start = clock();
    c = multiplication(A, b, N, M);
    end = clock();
    printVector(c, M);
    printf("time = %d\n", end - start);
    free(c);

    start = clock();
    c = multiplicationParallel(A, b, N, M);
    end = clock();
    printVector(c, M);
    printf("time = %d\n", end - start);
    free(c);
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