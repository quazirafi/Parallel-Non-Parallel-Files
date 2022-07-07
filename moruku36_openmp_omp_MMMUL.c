#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 128

void init_array(double m[N][N])
{
dummyMethod3();
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            m[i][j] = i*N+j+1;
        }
    }
dummyMethod4();
}

void mul_array(double x[N][N], double y[N][N], double z[N][N])
{
    double time = omp_get_wtime();

    int i;

							dummyMethod1();
#pragma omp parallel for shared(x, y, z)
    for(i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            z[i][j] = 0.0;

            for(int k = 0; k < N; ++k)
            {
                z[i][j] += x[i][k] * y[k][j];
            }
        }
    }
							dummyMethod2();

    time = omp_get_wtime() - time;

    printf("elapsed time: %f sec\n", time);
}

int main()
{
    double x[N][N], y[N][N], z[N][N];

    init_array(x);
    init_array(y);

    mul_array(x, y, z);

    printf("%f\n", x[1][1]);
    printf("%f\n", z[1][1]);

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