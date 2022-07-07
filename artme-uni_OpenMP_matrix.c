#include "matrix.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int mat_print(char *output, double *matrix, int size)
{
    FILE *fp;
    if ((fp = fopen(output, "w")) == NULL)
    {
        printf("Не удалось открыть файл");
        getchar();
        return -1;
    }

dummyMethod3();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            fprintf(fp, "%lf ", matrix[i + size * j]);
        }

        fprintf(fp, "\n");
    }
dummyMethod4();

    fprintf(fp, "\n");

    fclose(fp);

    return 0;
}

int mat_mult_by_column(const double *matrix, const double *column, double*result, int size)
{

							dummyMethod1();
#pragma omp parallel for default(none) shared(matrix, column, result, size)
    for (int i = 0; i < size; ++i)
    {
        result[i] = 0;

        for (int j = 0; j < size; ++j)
        {
           result[i] += matrix[i + size * j] * column[j];
        }
    }
							dummyMethod2();

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