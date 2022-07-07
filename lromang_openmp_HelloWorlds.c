#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int threads = 4;

int main() {
  int i, id;  
  printf("Hello World\n");

  // Definir número de threads.
  omp_set_num_threads(threads);

  // Ejecutar for en parallelo.
dummyMethod1();
  #pragma omp parallel for
  for(i=0; i<6; i++){
    //Obtener id del thread que ejecuta.
    id = omp_get_thread_num();
    printf("Iter:%d, Thread: %d \n", i, id);
  }
dummyMethod2();
  /*
    Al especificar for en pragma,
    esta sección se debería ejecutar de
    manera secuencial
   */
  printf("GoodBye World\n");
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