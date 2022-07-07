#ifdef _OPENMP
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#else
#define omp_get_thread_num() 0
#endif
#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>  // biblioteca donde se encuentra la funciÃ³n printf()
#include <time.h>   // biblioteca donde se encuentra la funciÃ³n clock_gettime()

//#define VECTOR_LOCAL
#define VECTOR_GLOBAL 
//#define VECTOR_DYNAMIC 
                       

#ifdef VECTOR_GLOBAL
#define MAX 5792 //sqrt 2^25
    double m1[MAX][MAX], v2[MAX], v3[MAX];
#endif
int main(int argc, char **argv)
{

    int i;

    //struct timespec cgt1, cgt2;
    double cgt1, cgt2, ncgt; //para tiempo de ejecucion

    //Leer argumento de entrada (n de componentes de la matriz)
    if (argc < 2)
    {
        printf("Faltan nº componentes de la matriz\n");
        exit(-1);
    }

    unsigned int N = atoi(argv[1]); // MÃ¡ximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)
//printf("TamaÃ±o Vectores:%u (%u B)\n",N, sizeof(unsigned int));
#ifdef VECTOR_LOCAL
    double v1[N], v2[N], v3[N]; // TamaÃ±o variable local en tiempo de ejecuciÃ³n ...
                                // disponible en C a partir de C99
#endif
#ifdef VECTOR_GLOBAL
    if (N > MAX)
        N = MAX;
#endif
#ifdef VECTOR_DYNAMIC
    double **m1, *v2, *v3;
    m1 = (double **)malloc(N * sizeof(double*)); // malloc necesita el tamaÃ±o en bytes
    v2 = (double *)malloc(N * sizeof(double));
    v3 = (double *)malloc(N * sizeof(double));
    if ((m1 == NULL) || (v2 == NULL) || (v2 == NULL))
    {
        printf("No hay suficiente espacio para los vectores o matriz \n");
        exit(-2);
    }

    for (int i = 0; i < N; i++)
    {
        m1[1] = (double *)malloc(N * sizeof(double));
        if( m1[i] == NULL ){
            printf("No hay suficiente espacio para las columnas de la matriz \n");
            exit(-2);
        }
    }
    
#endif

    //Inicializar 
    if (N < 9) {
															dummyMethod1();
        #pragma omp parallel for
        for (i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
                m1[i][j] = N ;
            v2[i] = N;
        }
															dummyMethod2();
    } else
    {
															dummyMethod1();
        #pragma omp parallel for
        for (i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
                m1[i][j] = N ;
            v2[i] = N ;
        }
															dummyMethod2();
    }

    int j1;
    double suma;
    //Calcular suma de vectores
    cgt1 = omp_get_wtime();

    #pragma omp parallel private(i)
    {
        for (i = 0; i < N; i++)
																							dummyMethod1();
        #pragma omp parallel for reduction(+:v3[i])
            for (j1 = 0; j1 < N; j1++)
                v3[i] += m1[i][j1] * v2[j1];
																							dummyMethod2();
    }

    cgt2 = omp_get_wtime();

    ncgt = cgt2 - cgt1;

    //Imprimir resultado de la suma y el tiempo de ejecuciÃ³n
    printf("Hebras %d\n", omp_get_max_threads( ));

    if (N < 10)
    {
        printf("Tiempo:%11.9f\t / TamaÃ±o Vectores:%u\n", ncgt, N);
        for (i = 0; i < N; i++){
            printf("#");
            for(int j = 0; j < N; j++)
                printf("%.2f ",m1[i][j]);
            printf("#");
            
            if(i == N-1)
                printf("* #%.2f# = #%.3f#\n",v2[i], v3[i]);
            else 
                printf("  #%.2f# = #%.3f#\n",v2[i], v3[i]);
        }
    }
    else
        printf("Tiempo:%11.9f\n/ Tamanyo matriz y Vectores:%u\n/ M1[0][0] +* V2[0]=V3[0](%8.6f +* %8.6f=%8.6f) / \n/ M1[%d][%d] +* V2[%d]=V3[%d](%8.6f +* %8.6f = %8.6f) /\n",  //Este print f no representa los calculos correctos, esta como si fueran los vectores.
               ncgt, N, m1[0][0], v2[0], v3[0], N - 1, N - 1, N - 1, N - 1, m1[N - 1][N - 1], v2[N - 1], v3[N - 1]);

#ifdef VECTOR_DYNAMIC
    for(i = 0; i < N; i++)
        free(m1[i]);
    free(m1); // libera el espacio reservado para m1
    free(v2); // libera el espacio reservado para v2
    free(v3); // libera el espacio reservado para v3
#endif
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