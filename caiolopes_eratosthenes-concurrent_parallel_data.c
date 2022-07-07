#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 * Based on "Parallel programming in C with MPI and OpenMP"
 * by Quinn
 */

int main(int argc, char *argv[]) {
  unsigned first, i, index, n, prime, num_threads;
  char *marked;

  if (argc < 3) {
    printf("Usage: %s n [--print all]\n"
           "n: maximum number\n"
           "num_threads: number of threads\n"
           "--print: print num of primes (optional)\n"
           "all: print all primes (optional)\n", argv[0]);
    exit(1);
  }

  n = atoi(argv[1]);
  num_threads = atoi(argv[2]);

  marked = (char *) malloc(n+1);

  if (marked == NULL) {
    printf("Cannot allocate enough memory\n");
    exit(1);
  }

			dummyMethod3();
  for (i = 0; i < n+1; i++) {
    marked[i] = 1;
  }
			dummyMethod4();

  marked[0] = 0;
  marked[1] = 1;
  index = 2;
  prime = 2;
  
  do {
    first = 2 * prime;

							dummyMethod1();
    #pragma omp parallel for num_threads(num_threads)
    for (i = first; i <= n; i += prime) {
      marked[i] = 0;
    }
							dummyMethod2();
    
    while (!marked[++index]);

    prime = index;
  } while (prime * prime <= n);

//  if (argc > 3) {
//    count = 0;
//    for (i = 0; i <= n; i++) {
//      count += marked[i];
//    }

//    printf("\nThere are %d primes less than or equal to %d\n\n", count, n);
//  }
  if (argc > 3) {
      if(!strcmp(argv[3], "--print") || !strcmp(argv[3], "--print\n")) {
          int count = 0;
          if((argc > 4) && (!strcmp(argv[4], "all") || !strcmp(argv[4], "all\n"))) {
																											dummyMethod3();
              for (int i = 0; i <= n; i++) {
                  if (marked[i] == 1) {
                      printf("%d\n", i);
                      count++;
                  }
              }
																											dummyMethod4();
          } else {
																											dummyMethod3();
              for (int i = 0; i <= n; i++) {
                  if (marked[i] == 1) {
                      count++;
                  }
              }
																											dummyMethod4();
          }
          printf("There are %d primes less than or equal to %d\n", count, n);
      }
  }

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