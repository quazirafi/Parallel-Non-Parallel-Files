#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#else
#define omp_get_thread_num()0
#endif

main(int argc, char **argv){
  int i,n=200,chunk,a[n],dinamico,hebras,suma=0;
  
  if(argc<5){
    fprintf(stderr,"\nFalta iteraciones o chunk\n <iteraciones> <chunk> <valor de dyn-var> <numero de threads>");
    exit(-1);
  }
  n= atoi(argv[1]); if(n>200) n=200; chunk=atoi(argv[2]);
  
  dinamico= atoi(argv[3]);
  if(dinamico>1 || dinamico<0){
    fprintf(stderr, "La variable dyn-var tiene que ser verdadero o falso, 0 o 1");
    exit(-1);
  }
  hebras= atoi(argv[4]);
  omp_set_dynamic(dinamico);
  omp_set_num_threads(hebras);
  
  
dummyMethod3();
  for(i=0;i<n;i++) a[i]=i;
  
  #pragma omp parallel for firstprivate(suma)\
dummyMethod4();
			dummyMethod1();
	lastprivate(suma) schedule(dynamic,chunk)
  for(i=0;i<n;i++){
      suma=suma+ a[i];
      printf("thread %d suma a [%d] suma=%d\n", omp_get_thread_num(),i,suma);
      printf("Valor de la variable dyn-var: %d \n",omp_get_dynamic());
      printf("Valor de la variable nthreads_var: %d\n",omp_get_max_threads());
      printf("Valor de la variable thread_limit-var: %d\n", omp_get_thread_limit()); //suponemos versión 3.0 de openMP
      //printf("Valor de la variable run-sched-var: %d\n",omp_get_schedule(n,chunk));
      printf("Valor de la función omp_get_num_threads: %d\n",omp_get_num_threads());
      printf("Valor de la función omp_get_num_procs: %d\n",omp_get_num_procs());
      printf("Valor de la función omp_in_parallel: %d\n",omp_in_parallel());
      printf("\n");
  }
			dummyMethod2();
    
      printf("\nFuera de 'parallel for' suma=%d\n",suma);
      printf("Valor de la variable dyn-var: %d\n",omp_get_dynamic());
      printf("Valor de la variable nthreads_var: %d\n",omp_get_max_threads());
      printf("Valor de la variable thread_limit-var: %d\n",omp_get_thread_limit()); //suponemos versión 3.0 de openMP
      //printf("Valor de la variable run-sched-var: ",omp_get_schedule(n,chunk));
      printf("Valor de la función omp_get_num_threads: %d\n",omp_get_num_threads());
      printf("Valor de la función omp_get_num_procs: %d\n",omp_get_num_procs());
      printf("Valor de la función omp_in_parallel: %d\n",omp_in_parallel());
      printf("\n");
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