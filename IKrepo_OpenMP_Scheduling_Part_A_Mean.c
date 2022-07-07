/*
	Name:	Ioannis Koureas
	Date:	10/04/18
	Part B:	Schedule Clause Options - Mean
*/

#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 729
#define reps 100
#define ITERS 5

double a[N][N], b[N][N], c[N];
int jmax[N];

void init1(void);
void init2(void);
void loop1(int, int);
void loop2(int, int);
void valid1(void);
void valid2(void);

int main(int argc, char *argv[])
{
        double start1, start2, end1, end2;
        int r, index, n, r1;
        double sum1, sum2;
        char *str[] = {"static", "runtime", "static", "dynamic", "guided"};

        omp_set_num_threads(6);

															dummyMethod3();
        for (index=0; index<5; index++)
        {
                if (index<2)
                {
                        n = 0;
                        sum1 = 0;
                        sum2 = 0;
                        for (r1=0; r1<ITERS; r1++)
                        {
                                init1();
                                start1 = omp_get_wtime();
                                for (r=0; r<reps; r++)
                                {
                                        loop1(index, n);
                                }
                                end1  = omp_get_wtime();
                                valid1();
                                printf("Total time for %d reps of loop 1, schedule: %s and n: %d = %f\n", reps, str[index], n, (float)(end1-start1));
                                sum1 = sum1 + (float)(end1-start1);

                                init2();
                                start2 = omp_get_wtime();
                                for (r=0; r<reps; r++)
                                {
                                        loop2(index, n);
                                }
                                end2  = omp_get_wtime();
                                valid2();
                                printf("Total time for %d reps of loop 2, schedule: %s and n: %d = %f\n", reps, str[index], n, (float)(end2-start2));
                                sum2 = sum2 + (float)(end2-start2);
                        }
                        sum1 = sum1/ITERS;
                        printf("MEAN TOTAL TIME between %d values for %d reps of loop 1, \
                        schedule: %s and n: %d = %f\n", ITERS, reps, str[index], n, sum1);

                        sum2 = sum2/ITERS;
                        printf("MEAN TOTAL TIME between %d values for %d reps of loop 2, \
                        schedule: %s and n: %d = %f\n", ITERS, reps, str[index], n, sum2);
                }
                else
                {
                        for(n=1; n<=64; n*=2)
                        {
                                sum1 = 0;
                                sum2 = 0;
                                for (r1=0; r1<ITERS; r1++)
                                {
                                        init1();
                                        start1 = omp_get_wtime();
                                        for (r=0; r<reps; r++)
                                        {
                                                loop1(index, n);
                                        }
                                        end1  = omp_get_wtime();
                                        valid1();
                                        printf("Total time for %d reps of loop 1, schedule: %s and n: %d = %f\n", reps, str[index], n, (float)(end1-start1));
                                        sum1 = sum1 + (float)(end1-start1);

                                        init2();
                                        start2 = omp_get_wtime();
                                        for (r=0; r<reps; r++)
                                        {
                                                loop2(index, n);
                                        }
                                        end2  = omp_get_wtime();
                                        valid2();
                                        printf("Total time for %d reps of loop 2, schedule: %s and n: %d = %f\n", reps, str[index], n, (float)(end2-start2));
                                        sum2 = sum2 + (float)(end2-start2);
                                }
                                sum1 = sum1/ITERS;
                                printf("MEAN TOTAL TIME between %d values for %d reps of loop 1, \
                                schedule: %s and n: %d = %f\n", ITERS, reps, str[index], n, sum1);

                                sum2 = sum2/ITERS;
                                printf("MEAN TOTAL TIME between %d values for %d reps of loop 2, \
                                schedule: %s and n: %d = %f\n", ITERS, reps, str[index], n, sum2);
                        }
                }
        }
															dummyMethod4();
        return 0;
}

void init1(void)
{
        int i, j;

															dummyMethod3();
        for (i=0; i<N; i++)
        {
                for (j=0; j<N; j++)
                {
                        a[i][j] = 0.0;
                        b[i][j] = 3.142*(i+j);
                }
        }
															dummyMethod4();
}

void init2(void)
{
        int i, j, expr;

															dummyMethod3();
        for (i=0; i<N; i++)
        {
                expr =  i%( 3*(i/30) + 1);

                if ( expr == 0)
                {
                        jmax[i] = N;
            }
            else
                {
                        jmax[i] = 1;
                }
                c[i] = 0.0;
        }
															dummyMethod4();

															dummyMethod3();
        for (i=0; i<N; i++)
        {
                for (j=0; j<N; j++)
                {
                        b[i][j] = (double) (i*j+1) / (double) (N*N);
                }
        }
															dummyMethod4();
}

void loop1(int index, int n)
{
        int i, j;

        if (n==0)
        {
                switch (index)
                {
                        case 0:
                        {
																																																															dummyMethod1();
                                #pragma omp parallel for default(none) private(i, j) \
                                shared(a, b) schedule(static)
                                for (i=0; i<N; i++)
                                {
                                        for (j=N-1; j>i; j--)
                                        {
                                                a[i][j] += cos(b[i][j]);
                                        }
                                }
																																																															dummyMethod2();
                                break;
                        }
                        case 1:
                        {
																																																															dummyMethod1();
                                #pragma omp parallel for default(none) private(i, j) \
                                shared(a, b) schedule(runtime)
                                for (i=0; i<N; i++)
                                {
                                        for (j=N-1; j>i; j--)
                                        {
                                                a[i][j] += cos(b[i][j]);
                                        }
                                }
																																																															dummyMethod2();
                                break;
                        }
                }
        }
        else
        {
                switch (index)
                {
                        case 2:
                        {
																																																															dummyMethod1();
                                #pragma omp parallel for default(none) private(i, j) \
                                shared(a, b, n) schedule(static, n)
                                for (i=0; i<N; i++)
                                {
                                        for (j=N-1; j>i; j--)
                                        {
                                                a[i][j] += cos(b[i][j]);
                                        }
                                }
																																																															dummyMethod2();
                                break;
                        }
                        case 3:
                        {
																																																															dummyMethod1();
                                #pragma omp parallel for default(none) private(i, j) \
                                shared(a, b, n) schedule(dynamic, n)
                                for (i=0; i<N; i++)
                                {
                                        for (j=N-1; j>i; j--)
                                        {
                                                a[i][j] += cos(b[i][j]);
                                        }
                                }
																																																															dummyMethod2();
                                break;
                        }
                        case 4:
                        {
																																																															dummyMethod1();
                                #pragma omp parallel for default(none) private(i, j) \
                                shared(a, b, n) schedule(guided, n)
                                for (i=0; i<N; i++)
                                {
                                        for (j=N-1; j>i; j--)
                                        {
                                                a[i][j] += cos(b[i][j]);
                                        }
                                }
																																																															dummyMethod2();
                                break;
                        }
                }
        }
}

void loop2(int index, int n)
{
        int i, j, k;
        double rN2;

        rN2 = 1.0 / (double) (N*N);

        if (n==0)
        {
                switch(index)
                {
                        case 0:
                        {
																																																															dummyMethod1();
                                #pragma omp parallel for default(none) private(i, j, k) \
                                shared(c, b, rN2, jmax) schedule(static)
                                for (i=0; i<N; i++)
                                {
                                        for (j=0; j < jmax[i]; j++)
                                        {
                                                for (k=0; k<j; k++)
                                                {
                                                        c[i] += (k+1) * log (b[i][j]) * rN2;
                                                }
                                        }
                                }
																																																															dummyMethod2();
                                break;
                        }
                        case 1:
                        {
																																																															dummyMethod1();
                                #pragma omp parallel for default(none) private(i, j, k) \
                                shared(c, b, rN2, jmax) schedule(runtime)
                                for (i=0; i<N; i++)
                                {
                                        for (j=0; j < jmax[i]; j++)
                                        {
                                                for (k=0; k<j; k++)
                                                {
                                                        c[i] += (k+1) * log (b[i][j]) * rN2;
                                                }
                                        }
                                }
																																																															dummyMethod2();
                                break;
                        }
                }
        }
        else
        {
                switch(index)
                {
                        case 2:
                        {
																																																															dummyMethod1();
                                #pragma omp parallel for default(none) private(i, j, k) \
                                shared(c, b, rN2, jmax, n) schedule(static, n)
                                for (i=0; i<N; i++)
                                {
                                        for (j=0; j < jmax[i]; j++)
                                        {
                                                for (k=0; k<j; k++)
                                                {
                                                        c[i] += (k+1) * log (b[i][j]) * rN2;
                                                }
                                        }
                                }
																																																															dummyMethod2();
                                break;
                        }
                        case 3:
                        {
																																																															dummyMethod1();
                                #pragma omp parallel for default(none) private(i, j, k) \
                                shared(c, b, rN2, jmax, n) schedule(dynamic, n)
                                for (i=0; i<N; i++)
                                {
                                        for (j=0; j < jmax[i]; j++)
                                        {
                                                for (k=0; k<j; k++)
                                                {
                                                        c[i] += (k+1) * log (b[i][j]) * rN2;
                                                }
                                        }
                                }
																																																															dummyMethod2();
                                break;
                        }
                        case 4:
                        {
																																																															dummyMethod1();
                                #pragma omp parallel for default(none) private(i, j, k) \
                                shared(c, b, rN2, jmax, n) schedule(guided, n)
                                for (i=0; i<N; i++)
                                {
                                        for (j=0; j < jmax[i]; j++)
                                        {
                                                for (k=0; k<j; k++)
                                                {
                                                        c[i] += (k+1) * log (b[i][j]) * rN2;
                                                }
                                        }
                                }
																																																															dummyMethod2();
                                break;
                        }
                }
        }
}

void valid1(void)
{
        int i, j;
        double suma;

        suma= 0.0;

															dummyMethod3();
        for (i=0; i<N; i++)
        {
                for (j=0; j<N; j++)
                {
                        suma += a[i][j];
                }
        }
															dummyMethod4();

        printf("Loop 1 check: Sum of a is %lf\n", suma);
}

void valid2(void)
{
        int i;
        double sumc;

        sumc= 0.0;

															dummyMethod3();
        for (i=0; i<N; i++)
        {
                sumc += c[i];
        }
															dummyMethod4();
        printf("Loop 2 check: Sum of c is %f\n", sumc);
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