#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
#ifdef_OPENMP
int my_rank = omp_get_thread_num();
int thread_count = omp_get_num_threads();
#else
int my_rank = 0;
int thread_count = 1;
#endif
*/

int thread_count;

int main(int argc, char *argv[])
{
  register int i, j, cnt, val, size = 0;
  register int *a, *b;
  struct timeval start, end;

  printf("RankSort Inner Parallelization OpenMP\n");

  /* check command line */
  if (argc != 3) {fprintf(stderr, "usage: %s number_of_elements number_of_threads\n", argv[0]); exit(-1);}
  size = atoi(argv[1]);
  if (size < 1) {fprintf(stderr, "number of elements must be at least 1\n"); exit(-1);}
  
  thread_count = atoi(argv[2]);
  if (thread_count < 1) {fprintf(stderr, "number of threads must be at least 1\n"); exit(-1);}

  /* allocate arrays */
  a = (int *)malloc(size * sizeof(int));
  b = (int *)malloc(size * sizeof(int));
  if ((a == NULL) || (b == NULL)) {fprintf(stderr, "could not allocate arrays\n"); exit(-1);}

  /* generate input */
  for (i = 0; i < size; i++) a[i] = -((i & 2) - 1) * i;
			dummyMethod1();
  printf("sorting %d unsorted values with %d threads.\n", size, thread_count);

  /* start time */
  gettimeofday(&start, NULL);
  
  /* sort the values */
  for (i = 0; i < size; i++) {
    cnt = 0;
    val = a[i];

#pragma omp parallel for num_threads(thread_count) default(none) shared (size,a,b,val) reduction(+:cnt)    
							dummyMethod3();
    for (j = 0; j < size; j++) {
      if (val > a[j]) cnt++;
    }
							dummyMethod4();
    b[cnt] = val;
  }
			dummyMethod2();

  /* end time */
  gettimeofday(&end, NULL);
  printf("runtime: %.4lf s\n", end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0);

  /* verify result */
  i = 1;
  while ((i < size) && (b[i - 1] < b[i])) i++;
  if (i < size) printf("NOT sorted\n\n"); else printf("sorted\n\n");

  free(a);
  free(b);
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