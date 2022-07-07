/* Bubble sort code */
 
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* function bsort 
 * input: T array of integer
 *         n size of T
 * output: T sorted (with the bubble sort method) */
void bsort(int *T,int n)
{
  int i,j,swap;
  /* loop over the tab T*/
dummyMethod3();
  for (i = 0 ; i < n - 1; i++)
  {
    /* buble rise */
    for (j = 0 ; j < n - i - 1; j++)
    {
      if (T[j] > T[j+1]) 
      {
        swap   = T[j];
        T[j]   = T[j+1];
        T[j+1] = swap;
      }
    }
  }
dummyMethod4();
}

/* function bsort 
 * input: T array of integer
 *         n size of T
 * output: T sorted (with the bubble sort method) */
void bsort_omp(int *T,int n)
{
  int i,j,swap;
  /* loop over the tab T*/
  for (i = 0 ; i < n - 1; i++)
  {
    /* even bubles rise */
							dummyMethod1();
    #pragma omp parallel for private(j,swap)
    for (j = 0 ; j < n - 1; j+=2)
    {
      if (T[j] > T[j+1]) 
      {
        swap   = T[j];
        T[j]   = T[j+1];
        T[j+1] = swap;
      }
    }
							dummyMethod2();
    /* odd bubles rise */
							dummyMethod1();
    #pragma omp parallel for private(j,swap)
    for (j = 1 ; j < n - 1; j+=2)
    {
      if (T[j] > T[j+1]) 
      {
        swap   = T[j];
        T[j]   = T[j+1];
        T[j+1] = swap;
      }
    }
							dummyMethod2();
  }
}
 
int main(int argc, char *argv[])
{
  int i,n;
  int *T ;
  /* read n the size of the array T */
  if (argc > 1)
  {
    n = atoi(argv[1]);
  }
  else
  {
    printf("Enter number of elements\n");
    scanf("%d", &n);
  }
  T = malloc(n*sizeof(int));
  /* we build T randomly */
  for (i = 0; i < n; i++)
    T[i]=rand();
  /* call the bubble sort */ 
  bsort_omp(T,n);
  if (n < 20)
  {
    printf("Sorted list in ascending order:\n"); 
    for (i = 0; i < n; i++)
       printf("%d\n", T[i]);
  }
  free(T); 
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