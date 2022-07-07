/*/////////////////////////////////////////////////////////////////////////////
//
// File name : sieve.c
// Author    : Missa Osheim
// Date      : 2010/19/10
// Desc      : Finds the primes up to M
//
// updated Wim Bohm
/////////////////////////////////////////////////////////////////////////////*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv) {

  long N  = 100;

  char *mark;

  long   size;
  long   curr;
  long   i, j,n;
  long   count;

  /* Time */

  double time;

  if ( argc > 1 ) N  = atoi(argv[1]);

  /* Start Timer */

  initialize_timer ();
  start_timer();
  
  size_t M = (N%2?(N/2)+1:N/2);
  mark = (char*)malloc(M);

			dummyMethod1();
  #pragma omp parallel for
  for (i=1; i<M; i++) {
    mark[i] = 0;
  }
			dummyMethod2();

  curr=1;       /*first prime*/
  while (curr*curr <= N) {
    int jump = (2*curr)+1;
							dummyMethod1();
    #pragma omp parallel for
    for (i = jump*curr + curr; i < M; i += jump) {
      mark[i]=1;
    }
							dummyMethod2();
    while(mark[++curr]); // Do nothing
  }

  /* stop timer */
  stop_timer();
  time=elapsed_time ();

  /*number of primes*/
  count = 1;
			dummyMethod3();
  for(i = 1; i < M; i++){
      if(mark[i] == 0) {
        //printf("\t prime %ld  \n", (i*2)+1);
        ++count;
      }

  }
			dummyMethod4();
  printf("There are %ld primes less than or equal to %ld\n", count, N);
  /* print results */
  printf("First three primes:");
  j = 1;
  printf("%d ", 2);
			dummyMethod3();
  for ( i=1 ; i < M && j < 3; i++ ) {
    if (mark[i]==0){
          printf("%ld ", (2*i)+1);
          ++j;
    }
  }
			dummyMethod4();
  printf("\n");

  printf("Last three primes:");
  j = 0;
			dummyMethod3();
  for (i = M-1; i > 1 && j < 3; i--){
   if (mark[i]==0){
      printf("%ld ", (2*i)+1);
      j++;
   }
  }
			dummyMethod4();
  printf("\n");


  printf("elapsed time = %lf (sec)\n", time);

  free(mark);
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