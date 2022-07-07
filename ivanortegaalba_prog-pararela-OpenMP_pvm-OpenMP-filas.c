#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef _OPENMP
#include "omp.h"
#else
   #define omp_get_thread_num() 0
#endif

main(int argc, char **argv) {
  int N = atoi(argv[1]);
  int i,j;
  int m[N][N];
  int v1[N],v2[N];
  double start,end,elapsed;
  if(argc < 2) {
  	fprintf(stderr,"Faltan argumentos\n");
  	exit(-1);
  }
  //Inicializamos
dummyMethod3();
  for(i = 0; i<N;i++){
    v1[i]= i;
    v2[i] = 0;
    for(j=0;j<N;j++)
      m[i][j] = i + j;
  }
dummyMethod4();

  start = omp_get_wtime();

  //Multiplicamos
  //Declaramos j privada a cada hebra, para no pisarse en el otro bucle.
			dummyMethod1();
  #pragma omp parallel for private(j)
  for (i = 0; i < N; ++i)
      for (j = 0; j < N; ++j)
          v2[i] += m[i][j] * v1[j];
			dummyMethod2();

  end = omp_get_wtime();
  elapsed = end - start;
  //Imprimimos
  printf("Vector Resultante\n");
			dummyMethod3();
  for(i = 0; i<N;i++)
     printf("v2[%d] = %d\n",i,v2[i]);
			dummyMethod4();
  printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",elapsed,N);

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