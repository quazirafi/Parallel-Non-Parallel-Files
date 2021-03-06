#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* Calculates a definite integral by using a quadrature rule.
 * Uses worksharing directives. */

/* For the default values of a, b, and n, sequential time on my i3-540 is 0.15 s,
 * and parallel time is 0.08 s (Release x86, /O2 /Ot /Oi). */

/* There's not much difference between the different scheduling schemes.
 * Dynamic with small chunk size is bad, but with at least 100 is okay, like the others.
 * The other schedules give about the same time - around 0.10 s.
 * (Static, 100) is maybe the fastest, at 0.08 s, but not by much.*/

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <omp.h>

#define MAX_NUM_THREADS 8
#define MAX 1024
#define ACCURACY 0.01

typedef struct Results Results;

struct Results {
    double val;
    double time;
};


// The function whose integral we calculate
inline double f(const double x) {
    register const double pi = 3.141592653589793;
    double value;
    value = 50.0 / (pi * (2500.0 * x * x + 1.0));
    return value;
}


/************************/
/* SEQUENTIAL ALGORITHM */
/************************/

void seqQuad(const unsigned n, const double a, const double b, double *total, double *execTime) {
    unsigned i;
    double total_q = 0.0;
    double wtime;
    double x;

    wtime = omp_get_wtime();

							dummyMethod3();
    for (i = 0; i < n; i++) {
        x = ((double)(n - i - 1)*a + (double)(i)*b) / (double)(n - 1);
        total_q = total_q + f(x);
    }
							dummyMethod4();

    wtime = omp_get_wtime() - wtime;

    total_q = (b - a) * total_q / (double)n;

    *total = total_q;
    *execTime = (double)wtime;
}

Results sequential(const unsigned n, const double a, const double b) {
    Results results;
    seqQuad(n, a, b, &results.val, &results.time);
    return results;
}


/**********************/
/* PARALLEL ALGORITHM */
/**********************/

void parQuad(const unsigned n, const double a, const double b, double *total, double *execTime) {
    int i;
    double total_q = 0.0;
    double wtime;
    double x;

    wtime = omp_get_wtime();

															dummyMethod1();
#pragma omp parallel for default(none) \
                     private(i, x) \
                     reduction(+:total_q) \
                     schedule(static, 100)
        for (i = 0; i < n; i++) {
            x = ((double)(n - i - 1)*a + (double)(i)*b) / (double)(n - 1);
            total_q = total_q + f(x);
        }
															dummyMethod2();

    wtime = omp_get_wtime() - wtime;
    
    total_q = (b - a) * total_q / (double)n;

    *total = total_q;
    *execTime = (double)wtime;
}

Results parallel(const unsigned n, const double a, const double b) {
    Results results;
    parQuad(n, a, b, &results.val, &results.time);
    return results;
}


void compareAndPrint(const unsigned n, const double a, const double b) {
    Results seq, par;

    seq = sequential(n, a, b);
    par = parallel(n, a, b);

    printf("  Sequential estimate quadratic rule   = %24.16f\n", seq.val);
    printf("  Parallel estimate quadratic rule     = %24.16f\n", par.val);
    printf("Sequential time quadratic rule   = %f s\n", seq.time);
    printf("Parallel time quadratic rule     = %f s\n", par.time);
    if (fabs(seq.val - par.val) < ACCURACY)
        printf("\tTest PASSED!\n");
    else
        printf("\a\tTest FAILED!!!\n");
    printf("\n");
}


int main(int argc, char *argv[]) {
    unsigned n;
    double a;
    double b;
    const double exact = 0.49936338107645674464;

    if (argc != 4) {
        n = 10000000;
        a = 0.0;
        b = 10.0;
    }
    else {
        n = (unsigned)atoi(argv[1]);
        a = atof(argv[2]);
        b = atof(argv[3]);
    }

    printf("\n");
    printf("QUAD:\n");
    printf("  Estimate the integral of f(x) from A to B.\n");
    printf("  f(x) = 50 / ( pi * ( 2500 * x * x + 1 ) ).\n");
    printf("\n");
    printf("  A        = %f\n", a);
    printf("  B        = %f\n", b);
    printf("  N        = %u\n", n);
    //printf("  Exact    = %24.16f\n", exact);
    printf("\n");

    compareAndPrint(n, a, b);

    printf("  Normal end of execution.\n");
    printf("\n");

    getchar();
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