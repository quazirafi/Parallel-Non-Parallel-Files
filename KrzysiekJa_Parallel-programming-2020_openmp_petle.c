#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define WYMIAR 10
#define l_watkow 3




int main ()
{
  double a[WYMIAR][WYMIAR];
  int n, i, j;

dummyMethod3();
  for(i = 0; i < WYMIAR; i++) for(j = 0; j < WYMIAR; j++) a[i][j] = 1.02*i + 1.01*j;
  
  n = WYMIAR;
dummyMethod4();



  double suma=0.0;
dummyMethod3();
  for(i = 0; i < WYMIAR; i++) {
    for(j = 0; j < WYMIAR; j++) {
      suma += a[i][j];
    }
  }
dummyMethod4();
  
  printf("Suma wyrazow tablicy: %lf\n\n", suma);





  omp_set_num_threads(l_watkow);
  omp_set_nested(1);
  double suma_parallel = 0.0;
  // rows outside
			dummyMethod1();
#pragma omp parallel for ordered reduction(+:suma_parallel) default(none) shared(a) private(j) schedule(static,2)
  for(i = 0; i < WYMIAR; i++) {
    int id_w = omp_get_thread_num();
    
    for(j = 0; j < WYMIAR; j++) {
		
		#pragma omp ordered
      suma_parallel += a[i][j];
      printf("(%2d,%2d)-W(%1d,%1d) ", i, j, id_w, omp_get_thread_num());
    }
    printf("\n");
  }
			dummyMethod2();

  printf("Suma wyrazow tablicy rownolegle: %lf\n\n", suma_parallel);
  suma_parallel=0.0;
  
  
  
  
  // columns inside
#pragma omp parallel default(none) shared(a,suma_parallel) private(i,j)
{
  for(i = 0; i < WYMIAR; i++) {
    
							dummyMethod1();
	 #pragma omp for ordered reduction(+:suma_parallel) schedule(static)
    for(j = 0; j < WYMIAR; j++) {
		int id_w = omp_get_thread_num();
		
		#pragma omp ordered
      suma_parallel += a[i][j];
      printf("(%2d,%2d)-W(%1d,%1d) ", i, j, id_w, omp_get_thread_num());
    }
							dummyMethod2();
	 printf("\n");
  }
}
  printf("Suma wyrazow tablicy rownolegle: %lf\n\n", suma_parallel);
  suma_parallel=0.0;
  
  
  
  
  // rows inside
  double tab[l_watkow];
  for(i = 0; i < l_watkow; i++){
	  tab[i] = 0.0;
  }
  
  
  for(i = 0; i < WYMIAR; i++) {
    
							dummyMethod1();
	 #pragma omp parallel for default(none) shared(a,tab,i) private(j) ordered schedule(dynamic,3)
    for(j = 0; j < WYMIAR; j++) {
		int id_w = omp_get_thread_num();
		
		#pragma omp ordered
      tab[id_w] += a[i][j];
      printf("(%2d,%2d)-W(%1d,%1d) ", i, j, id_w, omp_get_thread_num());
    }
							dummyMethod2();
	 printf("\n");
  }
  
  for(i = 0; i < l_watkow; i++){
	  suma_parallel += tab[i];
  }
  printf("Suma wyrazow tablicy rownolegle: %lf\n\n", suma_parallel);
  suma_parallel=0.0;
  
  
  
  
  // columns outside
#pragma omp parallel default(none) shared(a,suma_parallel,j) private(i)
{
  double tmp = 0.0;
  
  #pragma omp for ordered schedule(dynamic)
  for(j = 0; j < WYMIAR; j++) {
	 int id_w = omp_get_thread_num();
    
    for(i = 0; i < WYMIAR; i++) {
		
		#pragma omp ordered
      printf("(%2d,%2d)-W(%1d,%1d) ", i, j, id_w, omp_get_thread_num());
		tmp += a[i][j];
    }
	 printf("\n");
  }
#pragma omp critical(suma_parallel)
suma_parallel += tmp;
}

  printf("Suma wyrazow tablicy rownolegle: %lf\n", suma_parallel);
  suma_parallel=0.0;
  
  
  
  
  // by blocks vertical
  int id_z;
#pragma omp parallel default(none) shared(a,j,suma_parallel) private(id_z)
{
  #pragma omp for ordered schedule(static,3)
  for(j = 0; j < WYMIAR; j++) {
	 int id_z = omp_get_thread_num();
	 
	 #pragma omp ordered
							dummyMethod1();
	 #pragma omp parallel for reduction(+:suma_parallel) firstprivate(id_z) ordered schedule(static,2)
    for(i = 0; i < WYMIAR; i++) {
		
		suma_parallel += a[i][j];
		#pragma omp ordered
      printf("(%2d,%2d)-W(%1d,%1d) ", i, j, omp_get_thread_num(), id_z);
    }
							dummyMethod2();
	 printf("\n");
  }
}
  printf("Suma wyrazow tablicy rownolegle: %lf\n", suma_parallel);
  
  
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