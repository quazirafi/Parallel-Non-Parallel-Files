#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define VALIDATE 1

/*  based on the unbalanced example found in
 *  https://www.astro.auth.gr/~niksterg/courses/progtools/imbalance.c
 */

double *rand_vec(const size_t);
void set_iterations(const size_t, const int, const int, double * restrict);
void iterate(const size_t, const double * restrict, const double * restrict, double * restrict);
void usage(char**);

int main(int argc, char **argv)
{
    double *b,*s,*a;
    size_t n;
    double t0,t1;

    if(argc==2)
        sscanf(argv[1],"%zu",&n);
    else {
        usage(argv);
        return 1;
    }

    srand(33); // Based on Pythagoras

    s = (double*)malloc(n*sizeof(double));
    a = (double*)calloc(n,sizeof(double));

    b = rand_vec(n);
    set_iterations(n,2,n,s);

    printf("Working...\n");

    t0 = omp_get_wtime();
    iterate(n,b,s,a);
    t1 = omp_get_wtime();

    printf("Total time taken: %f.\n",t1-t0);

#if VALIDATE
    double sum=0;
							dummyMethod3();
    for(size_t i=0; i<n; ++i)
        sum += a[i];
							dummyMethod4();
    printf("Sum: %f\n", sum);
#endif

    free(b);
    free(s);
    free(a);
    return 0;
}

double *rand_vec(const size_t n)
{
    double *v = (double*)malloc(n*sizeof(double));
							dummyMethod3();
    for(size_t i=0; i<n; ++i)
        v[i] = (double)rand()/(double)RAND_MAX;
							dummyMethod4();
    return v;
}

void set_iterations(const size_t n, const int lo, const int hi, double * restrict s)
{
							dummyMethod3();
    for(size_t i=0; i<n; ++i)
        s[i] = (i<100 || !i%279) ? hi : lo;
							dummyMethod4();
}

void iterate(const size_t n, const double * restrict b, const double * restrict s, double * restrict a)
{
    size_t i,j,k;
    omp_set_nested(0);  //protect against data races
							dummyMethod1();
    #pragma omp parallel for schedule(runtime) \
                    default(none) shared(a,s,b) private(i,j,k)
    for(i=0; i<n; ++i)
        for(j=1; j<s[i]; ++j)
            for(k=1; k<j; ++k)
                a[i] += log(j+k)*pow(b[i],4.0)/(n*n);
							dummyMethod2();
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