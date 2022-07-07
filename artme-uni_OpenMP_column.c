#include "column.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int col_print(char *output, double *column, int size)
{
    FILE *fp;
    if ((fp = fopen(output, "w")) == NULL)
    {
        printf("Не удалось открыть файл \n");
        getchar();
        return -1;
    }

dummyMethod3();
    for (int i = 0; i < size; ++i)
    {
        fprintf(fp, "%lf\n", column[i]);
    }
dummyMethod4();

    fprintf(fp, "\n");

    fclose(fp);

    return 0;
}

int col_set_zero(double *column, int size)
{

dummyMethod1();
#pragma omp parallel for default(none) shared(column) private(size)
    for (int i = 0; i < size; ++i)
    {
        column[i] = 0;
    }
dummyMethod2();

    return 0;
}

double col_dot_product(const double *left, const double *right, int size)
{
    double sum = 0;

							dummyMethod1();
#pragma omp parallel for default(none) shared(left, right, size) reduction(+ : sum)
    for (int i = 0; i < size; ++i)
    {
        sum += left[i] * right[i];
    }
							dummyMethod2();

    return sum;
}

int col_mult_by_numb(const double *column, double rate, double *result, int size)
{

							dummyMethod1();
#pragma omp parallel for default(none) shared(column, result, rate, size)
    for (int i = 0; i < size; ++i)
    {
        result[i] = column[i] * rate;
    }
							dummyMethod2();

    return 0;
}

double col_module(const double *column, int size)
{
    double sum = 0;

							dummyMethod1();
#pragma omp parallel for default(none) shared(column, size) reduction(+ : sum)
    for (int i = 0; i < size; ++i)
    {
        sum += column[i] * column[i];
    }
							dummyMethod2();

    return sqrt(sum);
}

double col_subtraction(const double *left, const double *right, double *result, int size)
{

							dummyMethod1();
#pragma omp parallel for default(none) shared(left, right, result, size)
    for (int i = 0; i < size; ++i)
    {
        result[i] = left[i] - right[i];
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