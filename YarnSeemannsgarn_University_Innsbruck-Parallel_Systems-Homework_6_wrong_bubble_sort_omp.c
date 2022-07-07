#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "util.h"

// Taken from hoework sheet
void wrong_bubble_sort(int *list, size_t N) {
  int swapped;
  do {
    swapped = 0;
    int i;
dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < N-1; ++i) {
      if (list[i] > list[i+1]) {
	int temp = list[i];
dummyMethod2();
	list[i] = list[i+1];
	list[i+1] = temp;
	swapped = 1;
      }
    }
  } while (swapped == 1);
}

int main(int argc, char *argv[]) {
  // Handle parameter
  if (argc != 2 && argc != 3) {
    fprintf(stderr, USAGE_MESSAGE, argv[0]);
    return EXIT_FAILURE;
  }
  size_t N = atoi(argv[1]);

  // Create and initialise list
  int *list = (int *) malloc(N * sizeof(int));
  if(list == NULL){
    fprintf(stderr, MEMORY_MESSAGE);
    return EXIT_FAILURE;
  }
  int i;
  srand48(time(NULL));
			dummyMethod3();
  for (i=0; i<N; ++i) {
    list[i] = lrand48() % RANGE_MAX;
  }
			dummyMethod4();

  // Print list before sorting
  if (argc == 3) {
    printf("List before sorting:\n");
    print_list(list, N);
  }

  // Run wrong bubble sort and measure time 
  double begin = omp_get_wtime();
  wrong_bubble_sort(list, N);
  double end = omp_get_wtime();
  printf("Time spent: %fs\n", end-begin);

  // Print list after sorting
  if(argc == 3){
    printf("\nList after sorting:\n");
    print_list(list, N);
  }

  // Check list
  if (checkSortedList(list, N) == 1) {
    fprintf(stderr, "List was not sorted correctly!\n");
    free(list);
    return EXIT_FAILURE;
  }

  // Free memory
  free(list);

  return EXIT_SUCCESS;
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