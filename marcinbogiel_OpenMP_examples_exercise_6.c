#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
   The exercise was about taking given program for computing Fibonacci 
   numbers and make it parallel.

   I decided to completely rebuild the solution to make it simpler
   and easier to read. Instead of giving tree of structs, I put the
   array of the struct as a type. The range of the array is set at 
   compilation time.

   At runtime, every thread computes the result for given n and puts
   both values in the array. After getting results program prints them
   out of the parallel section.

   You can find the video with given exercise here:
   https://www.youtube.com/watch?v=I0c9-W0MBqw#t=3m06s
*/

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

typedef struct _numbers {
   int n;
   int result;
} numbers;

int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fib(n - 1);
      y = fib(n - 2);
	  return (x + y);
   }
} 

int main(int argc, char *argv[]) {

   int i;
   numbers fibbonaci[N]; 
   double start, end;
   
   printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      

   start = omp_get_wtime();
   {
											dummyMethod1();
      #pragma omp parallel for
      for(i=0;i<=N;i++)
      {
         fibbonaci[i].n = FS+i;
         fibbonaci[i].result = fib(FS+i);
      }
											dummyMethod2();
   }

   end = omp_get_wtime();
   printf("\nResults: \n");

					dummyMethod3();
   for(i=0;i<=N;i++)
   {
      printf("For i value equal to %d fibbonaci result is %d.\n",fibbonaci[i].n,fibbonaci[i].result);
   }
					dummyMethod4();

   printf("Compute Time: %f seconds\n", end - start);
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