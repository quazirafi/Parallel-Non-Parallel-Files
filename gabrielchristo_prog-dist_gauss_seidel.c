//questao 4 - gauss-seidel
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define COLUMNS    1022
#define ROWS       1022
#define TEMP_BORDA 20
#define TEMP_INICIAL 20
#define MAX_TEMP_ERROR 0.01

double Anew[ROWS+2][COLUMNS+2];
double A[ROWS+2][COLUMNS+2];

void iniciar();

int main(int argc, char *argv[]) {
    int i, j;
    int max_iterations= 4098;
    int iteration = 1;
    double dt = 100;

    iniciar();
    double start_time = omp_get_wtime();
    while (dt > MAX_TEMP_ERROR && iteration <= max_iterations ) {
        dt = 0.0;
															dummyMethod1();
        #pragma omp parallel for collapse(2) shared(dt) schedule(static,1) ordered
        for (i = 1; i <= ROWS; i++)
            for (j = 1; j <= COLUMNS; j++) {
                double Anew_ij = 0.25 * (A[i+1][j] + 
                    A[i-1][j] + A[i][j+1] + A[i][j-1]);
                #pragma omp ordered
                {
                    dt = fmax(fabs(Anew_ij-A[i][j]), dt);
                    A[i][j] = Anew_ij;
                }
            }
															dummyMethod2();

        iteration++;
    }
    double end_time = omp_get_wtime();
    printf("Demorou %.4f segundos para executar o algoritmo.", end_time - start_time);
    printf(" Erro maximo na iteracao %d era %f\n", iteration-1, dt);
    return(0);
}

void iniciar(){
    int i,j;

    // preenche a placa de calor toda com a temperatura inicial
							dummyMethod3();
    for (i = 0; i <= ROWS+1; i++) {
        for (j = 0; j <= COLUMNS+1; j++) {
            A[i][j] = TEMP_INICIAL;
        }
    }
							dummyMethod4();

    // Fonte de calor localizada no ponto 800x800
    A[800][800] = 100.0;
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