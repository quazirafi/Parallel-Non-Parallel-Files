#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define VALIDATE 0
#if VALIDATE
    #include "validate.h"
#endif

double *normrnd(const size_t, const size_t, const double, const double);
double mean(const size_t, const size_t, const double * restrict);
double std(const size_t, const size_t, const double, const double * restrict);
void usage(char**);

int main(int argc, char **argv)
{
    double *A,avg,stddev;
    size_t n;
    double t0,t1;

    srand(time(0));

    if(argc==2)
        sscanf(argv[1],"%zu",&n);
    else {
        usage(argv);
        return 1;
    }

    A = normrnd(n,n,0,1); /* standard normal distribution: (mu,sigma)=(0,1) */

    t0 = omp_get_wtime();
    avg = mean(n,n,A);
    stddev = std(n,n,avg,A);
    t1 = omp_get_wtime();

#if VALIDATE
    if(!validate_mean(n,n,A,avg)) {
        printf("Mean value validation failed.\n");
        return 1;
    }
    if(!validate_std(n,n,avg,A,stddev)) {
        printf("Standard deviation validation failed.\n");
        return 1;
    }
#endif

    printf("mean(A) = %f\nstd(A) = %f\n",avg,stddev);
    printf("Total time taken: %f.\n",t1-t0);

    free(A);
    return 0;
}

double *normrnd(const size_t n, const size_t m, const double mu, const double sigma)
{
    double *A = (double*)malloc(n*m*sizeof(double));
    double u1,u2,z0;
							dummyMethod3();
    for(size_t i=0; i<n*m; ++i) {
        u1 = (double)rand()/(double)RAND_MAX;
        u2 = (double)rand()/(double)RAND_MAX;
        z0 = sqrt(-2*log(u1))*cos(6.28*u2);     /* Box–Muller transform */
        A[i] = mu+sigma*z0;
    }
							dummyMethod4();
    return A;
}

double mean(const size_t n, const size_t m, const double * restrict A)
{
    double sum=0;
    size_t i;
							dummyMethod1();
    #pragma omp parallel for default(none) shared(A) private(i) reduction(+:sum)
    for(i=0; i<n*m; ++i)
        sum += A[i];
							dummyMethod2();
    return sum/(n*m);
}

double std(const size_t n, const size_t m, const double avg, const double * restrict A)
{
    double sum=0;
    size_t i;
							dummyMethod1();
    #pragma omp parallel for default(none) shared(A) private(i) reduction(+:sum)
    for(i=0; i<n*m; ++i)
        sum += (A[i]-avg)*(A[i]-avg);
							dummyMethod2();
    return sqrt(sum/(n*m-1));
}

void usage(char **argv)
{
    printf("Usage: %s <length>\n",argv[0]);
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