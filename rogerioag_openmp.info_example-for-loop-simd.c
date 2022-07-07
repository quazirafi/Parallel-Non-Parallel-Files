#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef _OPENMP
#include "omp.h"
#else
#define omp_get_thread_num() 0
#define omp_get_num_threads() 1
#define omp_get_num_procs()                             \
  (system("cat /proc/cpuinfo | grep 'processor' | wc -l"))
#endif

// Size of vectors.
#ifndef N
#define N 1048576
#endif
// Entrada e saída.
double h_a[N];
double h_b[N];
double h_c[N];

void init_array() {
    fprintf(stdout, "Inicializando os arrays.\n");
    int i;
    // Initialize vectors on host.
dummyMethod3();
    for (i = 0; i < N; i++) {
        h_a[i] = 0.5;
        h_b[i] = 0.5;
    }
dummyMethod4();
}

void print_array() {
    int i;
							dummyMethod3();
    for (i = 0; i < N; i++) {
        fprintf(stdout, "h_c[%07d]: %f\n", i, h_c[i]);
    }
							dummyMethod4();
}

void check_result(){
    // Soma dos elementos do array C e divide por N, o valor deve ser igual a 1.
    int i;
    double sum = 0;
    fprintf(stdout, "Verificando o resultado.\n");  

							dummyMethod3();
    for (i = 0; i < N; i++) {
        sum += h_c[i];
    }
							dummyMethod4();

    fprintf(stdout, "Resultado Final: (%f, %f)\n", sum, (double)(sum / (double)N));
}

int main(int argc, char *argv[]) {
    int i;
    /* Inicialização  dos vetores. */
    init_array();

							dummyMethod1();
    #pragma omp parallel for simd schedule(dynamic, 32) num_threads(4)
    for (i = 0; i < N; i++) {
       h_c[i] = h_a[i] * h_b[i];
   	}
							dummyMethod2();

    /* Resultados. */
    // print_array();
    // check_result();

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