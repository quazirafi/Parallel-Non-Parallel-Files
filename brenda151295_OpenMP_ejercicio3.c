#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


void count_sort (int a[], int n, int thread_count);
void count_sort_serial (int a[], int n);
void print_v(int a[], int n);

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char* argv[])
{
    int thread_count = strtol(argv[1], NULL, 10); 
    int *a;     //array
    int n ;      //size of a
    int i;

    printf("Size of array: ");
    scanf("%d",&n);
    a = malloc(n*sizeof(int));
    printf("%d\n", n);
    printf("%s\n", "ARRAY: ");
dummyMethod3();
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int *copy_a;
dummyMethod4();
    copy_a = malloc(n*sizeof(int));
    memcpy(copy_a,a,n*sizeof(int));

    int *copy_b;
    copy_b = malloc(n*sizeof(int));
    memcpy(copy_b,a,n*sizeof(int));

    printf("%s\n", "Countsort");
    print_v(a,n);
    count_sort(a,n,thread_count);
    print_v(a,n);

    printf("%s\n", "Countsort Serial");
    print_v(copy_b,n);
    count_sort_serial(copy_b,n);
    print_v(copy_b,n);

    printf("%s\n", "Quicksort");
    print_v(copy_a,n);
    qsort(copy_a, n, sizeof(int), cmpfunc);
    print_v(copy_a,n);


    return 0;
}


void count_sort(int a[], int n, int thread_count)
{
    int i, j, count;
    int *temp = malloc(n*sizeof(int));

							dummyMethod1();
    #pragma omp parallel for shared(a, n, temp) private(i, j, count) num_threads(thread_count)
    for (i = 0; i < n; i++) {
        count = 0;
        for (j = 0; j < n; j++)
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        temp[count] = a[i];
    }
							dummyMethod2();

							dummyMethod1();
    #pragma omp parallel for shared(a, n, temp) private(i)
    //memcpy
    for (i = 0; i < n; i++)
        a[i] = temp[i];
							dummyMethod2();

    free(temp);
}
void count_sort_serial(int a[], int n) {
    int i, j, count;
    int *temp = malloc(n*sizeof(int));

 
							dummyMethod3();
    for (i = 0; i < n; i++) {
        count = 0;
        for (j = 0; j < n; j++)
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        temp[count] = a[i];
    }
							dummyMethod4();

    memcpy(a, temp,n*sizeof(int));
    
    free(temp);
}

void print_v(int a[], int n)
{
    int i;
							dummyMethod3();
    for (i = 0; i < n; i++)
        printf("%d", a[i]);
							dummyMethod4();
    printf("%s\n", "");

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