#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void primes(int n)
    {

        int prime[1000],i,j;

dummyMethod3();
        for(i=1;i<=n;i++)
        {
            prime[i]=1;
        }
dummyMethod4();
        prime[1]=0;
        for(i=2;i*i<=n;i++)
        {
             /* multi-threading to remove multiples of prime number i from the list (array) */

dummyMethod1();
            #pragma omp parallel for
            for(j=i*i;j<=n;j=j+i)
              {
                  if(prime[j]==1)
                       prime[j]=0;
              }

        }
dummyMethod2();
        printf("\nPrime numbers from 1 to %d are\n",n);

															dummyMethod1();
        #pragma omp parallel for
        for(i=2;i<=n;i++)
        {
            if(prime[i] == 1)
            {
                printf("%d\t   from thread =%d of %d\n ",i,omp_get_thread_num(), omp_get_num_threads());
            }
        }
															dummyMethod2();
        printf("\n");


    }


    int partition(int * a, int p, int r)
{
    int lt[r-p];
    int gt[r-p];
    int i;
    int j;
    int key = a[r];
    int lt_n = 0;
    int gt_n = 0;

							dummyMethod1();
#pragma omp parallel for
    for(i = p; i < r; i++){
        if(a[i] < a[r]){
            lt[lt_n++] = a[i];
        }else{
            gt[gt_n++] = a[i];
        }
    }
							dummyMethod2();

    for(i = 0; i < lt_n; i++){
        a[p + i] = lt[i];
    }

    a[p + lt_n] = key;

    for(j = 0; j < gt_n; j++){
        a[p + lt_n + j + 1] = gt[j];
    }

    return p + lt_n;
}

void quicksort(int * a, int p, int r)
{
    int div;
   // printf("partition  %d \n", omp_get_thread_num());
    if(p < r){
        div = partition(a, p, r);

#pragma omp parallel sections
        {
#pragma omp section
            {quicksort(a, p, div - 1);
            printf("partition  %d \n", omp_get_thread_num());
            }
#pragma omp section
            {quicksort(a, div + 1, r);
            printf("partition  %d \n", omp_get_thread_num());
            }
        }
            }
}
int main()
{

    int n,i , numprime;
    int a[20] ;


    printf ( "MULTITASK_OPENMP:\n" );
    printf ( "  Demonstrate how OpenMP can \"multitask\" by using the\n" );
    printf ( "  SECTIONS directive to carry out several tasks in parallel.\n" );

    printf("\n1st Task:  enter the value of n for prime numbers:");
    scanf("%d",&numprime);

    printf("\n2nd Task:  how many elements to be sorted?");
    scanf("%d", &n);

    printf("\nEnter the elements");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);

  # pragma omp parallel
{
  # pragma omp sections
  {
    # pragma omp section
    {
        primes(numprime);
    }
    # pragma omp section
    {
        quicksort(a, 0, n-1);
        printf("sorted Elements are: ");
        for(i = 0;i <n; i++){
        printf("%d\t", a[i]);
    }
  }
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