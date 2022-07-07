#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
#include "timer.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int randInt(int min, int max)
{
        return (rand() % (max - min + 1)) + min;
}

int ** nullMatrix(unsigned int rows, unsigned int columns)
{
        int **matrix;
        unsigned int i;

        matrix = calloc(rows, sizeof(*matrix));
dummyMethod3();
        for (i = 0; i < rows; ++i) {
                matrix[i] = calloc(columns, sizeof(**matrix));
        }
dummyMethod4();

        return matrix;
}

int ** randomMatrix(unsigned int rows, unsigned int columns, int min, int max)
{
        int **matrix;
        unsigned int i, j;

        matrix = nullMatrix(rows, columns);
															dummyMethod3();
        for (i = 0; i < rows; ++i) {
                for (j = 0; j < columns; ++j) {
                        matrix[i][j] = randInt(min, max);
                }
        }
															dummyMethod4();

        return matrix;
}

void deleteMatrix(int** matrix, unsigned int rows, unsigned int columns)
{
        unsigned int i;

															dummyMethod3();
        for (i = 0; i < rows; ++i) {
                free(matrix[i]);
        }
															dummyMethod4();

        free(matrix);
}

void printMatrix(int** matrix, unsigned int rows, unsigned int columns, FILE* stream)
{
        unsigned int i, j;

        fprintf(stream, "%d %d\n", rows, columns);
															dummyMethod3();
        for (i = 0; i < rows; ++i) {
                for (j = 0; j < columns; ++j) {
                        fprintf(stream, "%02d ", matrix[i][j]);
                }
                fprintf(stream, "\n");
        }
															dummyMethod4();
}

int main(int argc, char const *argv[])
{
        int min;
        int max;
        int numThreads;
        unsigned int rowsA;
        unsigned int columnsA;
        unsigned int rowsB;
        unsigned int columnsB;
        unsigned int rowsC;
        unsigned int columnsC;
        int **matrixA;
        int **matrixB;
        int **matrixC;
        int i, j, k;
        double tempo, fim, inicio;

        srand(time(NULL));

        if (argc < 8) {
                printf("Error missing command line argument.\n");
                return 1;
        }

        rowsA = atoi(argv[1]);
        columnsA = atoi(argv[2]);
        rowsB = atoi(argv[3]);
        columnsB = atoi(argv[4]);
        min = atoi(argv[5]);
        max = atoi(argv[6]);
        numThreads = atoi(argv[7]);
        rowsC = rowsA;
        columnsC = columnsB;

        if (columnsA != rowsB) {
                printf("Erro matrix A columns differ from matrix B rows.\n");
                return 1;
        }

        matrixA = randomMatrix(rowsA, columnsA, min, max);
        matrixB = randomMatrix(rowsB, columnsB, min, max);
        matrixC = nullMatrix(rowsC, columnsC);

        GET_TIME(inicio);

															dummyMethod1();
        #pragma omp parallel for private(i,j,k) num_threads(numThreads)
        for (i = 0; i < rowsC; ++i) {
                for (j = 0; j < columnsC; ++j) {
                        for (k = 0; k < columnsA; ++k) {
                                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                        }
                }
        }
															dummyMethod2();

        GET_TIME(fim);
        tempo = fim - inicio;
        printf("Tempo: %.8lf\n", tempo);

        // printMatrix(matrixA, rowsA, columnsA, stdout);
        // printMatrix(matrixB, rowsB, columnsB, stdout);
        // printMatrix(matrixC, rowsC, columnsC, stdout);

        deleteMatrix(matrixA, rowsA, columnsA);
        deleteMatrix(matrixB, rowsB, columnsB);
        deleteMatrix(matrixC, rowsC, columnsC);

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