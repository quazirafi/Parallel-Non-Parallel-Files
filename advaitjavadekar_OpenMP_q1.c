#include <stdio.h>   // printf()
#include "omp.h"
#include <stdlib.h>  // rand()
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 1000

void initialize(int a[SIZE][SIZE]);
int sequentialSum(int a[SIZE][SIZE]);
int parallelSum(int a[SIZE][SIZE]);

int main(int argc, char** argv) {
   int array[SIZE][SIZE];

   if (argc > 1) {
        omp_set_num_threads( atoi(argv[1]) );
   }

   initialize(array);
   printf("\nSequential sum: \t%d\nParallel sum: \t%d\n\n",
            sequentialSum(array),
            parallelSum(array) );

   return 0;
} 

/* fill array with random values */
void initialize(int a[SIZE][SIZE]) {
   int i, j;
dummyMethod3();
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         a[i][j] = rand() % 100;
      }
   }
dummyMethod4();
}

/* sum the array sequentially */
int sequentialSum(int a[SIZE][SIZE]) {
   int i, j, sum = 0;
					dummyMethod3();
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         sum += a[i][j];
      }
   }
					dummyMethod4();
   return sum;
}

/* sum the array using multiple threads */
int parallelSum(int a[SIZE][SIZE]) {
   int i, j, sum = 0;
   int tmp;
   for (i = 0; i < SIZE; i++) {
      tmp = 0;
											dummyMethod1();
      #pragma omp parallel for default(shared)
      for (j = 0; j < SIZE; j++) {
         tmp += a[i][j];
      }
											dummyMethod2();
      sum += tmp;
   }
   return sum;
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