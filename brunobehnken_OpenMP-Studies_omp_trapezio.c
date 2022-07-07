#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double f(double x) {
        double return_val;
        return_val = exp(x);
        return return_val;
}
void main() {
double integral;     /* Armazena resultado em integral */
double a, b;            /* Limite esquerdo e direito */
long  i,n;                  /* Número de Trapezóides */
double h;                /* Largura da base do Trapezóide */
double x;
    a = 0.0;
    b = 1.0;
    n = 800000000;
    h = (b-a)/n;
    integral = (f(a) + f(b))/2.0;
    omp_set_num_threads(8);
    double start = omp_get_wtime();
dummyMethod1();
#pragma omp parallel for reduction(+:integral) shared(n, h)
    for (i = 1; i < n-1; i++) {
        integral += f(a + i*h);
    }
dummyMethod2();

    integral *= h ;
    printf("Com n = %ld trapezoides, a estimativa \n", n);
    printf("da integral de %f ate %f = %lf \n", a, b, integral);
    printf("Tempo: \t %f \n", omp_get_wtime()-start);

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