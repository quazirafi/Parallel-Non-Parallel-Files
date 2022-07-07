#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NUM_THREADS 4

int linearSearch(int* array, int size, int find)
{
  int found = -1;
dummyMethod1();
  #pragma omp parallel for
  for(int i = 0; i<size; i++)
  {
    if(array[i] == find)
    {
      found = i+1;
    }
  }
dummyMethod2();
  return found;
}

int main(int argc, char* argv[])
{
  if(argc!=2)
  {
    fprintf(stderr, "%s", "error, input quantity parameter");
    return 1;
  }

  clock_t start = clock();
  char* a = argv[1];
  int n = atoi(a);
  //Search for an random index within our range of numbers
  srand(time(NULL));
  int findIndex = rand() / (RAND_MAX/n+1);
  FILE* fp;
  fp = fopen("100000000numbers","r");
  int* array = malloc(n * sizeof(int));

			dummyMethod3();
  for(int index = 0; index<n; index++)
  {
    fscanf(fp, "%d", &array[index]);
  }
			dummyMethod4();
  int number = array[findIndex];
  linearSearch(array,n,number);
  clock_t end = clock();
  double elapsedTime = (double) (end-start)/CLOCKS_PER_SEC;
  printf("The time elapsed to find a number in an array of size %d is: %f\n",n ,elapsedTime);


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