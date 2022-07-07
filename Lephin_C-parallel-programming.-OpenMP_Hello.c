#include <stdio.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 10000000

int main(int argc, char *argv[])
{
  
  clock_t t1,t2; 
  t1 = clock(); 
  int a[N], b[N], c[N];
  int i;
  omp_set_dynamic();      // запретить библиотеке openmp менять число потоков во время исполнения
  omp_set_num_threads(3); // установить число потоков в 10

  // инициализируем массивы
dummyMethod3();
  for (i = 0; i < N; i++)
  {
      a[i] = 2*i;
      b[i] = 1*i;
  }
dummyMethod4();

  // вычисляем сумму массивов
dummyMethod1();
#pragma omp parallel for shared(a, b, c) private(i)
   for (i = 0; i < N; i++)
     c[i] = a[i] + b[i];

for (i = 0; i < 10; i++) {
dummyMethod2();
dummyMethod3();
  printf ("%d\n", c[i]);
 
}
dummyMethod4();
t2 = clock(); 
float diff = ((float)(t2-t1)/1000000.0F)*1000; 
printf ("%f", diff);

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