#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//#include "util.h"

/*
Joseph McDonald, jacobi-omp.h
*/

int main(int argc, char* argv[])
{
    int i;

    int N = atoi(argv[1]);
    double h =(double) 1/(N+1);
    double hsq = h*h;

    double *u = malloc(sizeof(double)*N);
    double *utemp = malloc(sizeof(double)*N);
    double f = 1.;

    int iter = 0;
    int T = 25;
    double res = sqrt(N);
    double sum;
    double diff;

dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < N; ++i)
        u[i] = 0.;


    #pragma omp parallel 
dummyMethod2();
    {
        #pragma omp single
        printf("Computing u with Jacobi on %d threads.\n", omp_get_num_threads());
    }

    double start = omp_get_wtime();

															dummyMethod3();
        for (iter = 0; iter < T; iter++) {

            #pragma omp parallel shared(utemp, u, sum) private(diff)
            {
                #pragma omp single
                {
                    sum = 0.;

                    utemp[0] = hsq*(f -(-u[1])/hsq)/2;
                    utemp[N-1] = hsq*(f - (-u[N-2])/hsq)/2;
                }

            //#pragma omp parallel shared(utemp, u, sum) private(diff)
                {
                    #pragma omp for
                    for (i = 1; i < N-1; ++i)
                        utemp[i] = hsq*(f - (-u[i-1] - u[i+1])/hsq)/2;

                    #pragma omp for
                    for (i = 0; i < N; ++i)
                        u[i] = utemp[i];

                    #pragma omp for reduction (+:sum)
                    for (i = 1; i < N-1; ++i) {
                        diff = (-u[i-1] + 2*u[i] - u[i+1])/hsq - 1;
                        sum += diff*diff;
                    }
                }

                #pragma omp single
                {
                    diff = (2*u[0] - u[1])/hsq - 1;
                    sum += diff*diff;

                    diff = (-u[N-2] + 2*u[N-1])/hsq - 1;
                    sum += diff*diff;

                    res = sqrt(sum);        
                }
            }
        }
															dummyMethod4();
    

    double end = omp_get_wtime();
    double elapsed = end - start;

    printf("Jacobi:\n");
    printf("residual = %f\n", res);
    printf("iterations = %d\n", iter);
    printf("elapsed time = %f\n", elapsed);
    printf("midpoint = %f\n", u[N/2]);

    free(u);
    free(utemp);

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