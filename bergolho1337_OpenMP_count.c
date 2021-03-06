/*
********************************************
    Programming Assignment 5.3 (p.269)
********************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include "../timer.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

const int MAX_THREADS = 1024;
const int MAX_VALUE = 255;

/* Only executed by main thread */
void Get_args(int argc, char* argv[], int *thread_count, int *n, int *num_method);
void Usage(char* prog_name);
void generateData (int data[], int n);
void Serial_CountSort (int data[], int n);
void Parallel_CountSort (int data[], int n, int thread_count);
void printData (int data[], int n);
int compare (const void *a, const void *b);
void checkSort (int data[], int n);

int main(int argc, char* argv[]) 
{
   int *data;
   double start, finish, elapsed;
   int thread_count, n, num_method;

   /* Get number of threads from command line */
   Get_args(argc,argv,&thread_count,&n,&num_method);

   data = (int*)malloc(sizeof(int)*n);
   generateData(data,n);

   printf("[!] Size of the data vector = %d\n",n);
   checkSort(data,n);
   //printf("Before sorting\n");
   //printData(data,n);
   
   switch (num_method)
   {
       case 1: GET_TIME(start);
               Serial_CountSort(data,n);
               GET_TIME(finish);
               elapsed = finish - start;
               printf("[!] Serial Counting Sort = %.15lf\n",elapsed);
               break;
       case 2: GET_TIME(start);
               qsort(data,n,sizeof(int),compare);
               GET_TIME(finish);
               elapsed = finish - start;
               printf("[!] Serial qsort = %.15lf\n",elapsed);
               break;
       case 3: GET_TIME(start);
               Parallel_CountSort(data,n,thread_count);
               GET_TIME(finish);
               elapsed = finish - start;
               printf("[!] Parallel Counting Sort = %.15lf\n",elapsed);
               break;
   }

   checkSort(data,n);
   //printf("After sorting\n");
   //printData(data,n);
   
   free(data);
   return 0;
}  /* main */

/*------------------------------------------------------------------
 * Function:  generateData
 * Purpose:   Genrate a random vector of data
 * In arg:    Integer array and size of the vector
 */
void generateData (int data[], int n)
{
    int i;
							dummyMethod4();
							dummyMethod3();
    for (i = 0; i < n; i++) data[i] = rand() % MAX_VALUE;
}

/*------------------------------------------------------------------
 * Function:  printData
 * Purpose:   Print the vector of data
 * In arg:    Integer array and size of the vector
 */
void printData (int data[], int n)
{
    int i;
							dummyMethod4();
							dummyMethod3();
    for (i = 0; i < n; i++) printf("%d ",data[i]);
    printf("\n");
}

/*------------------------------------------------------------------
 * Function:    Serial_CountSort
 * Purpose:     Serial CountSort
 * In args:     Integer data array and size of the vector
 */
void Serial_CountSort (int data[], int n)
{
    int i, j, count;
    int *temp = (int*)malloc(sizeof(int)*n);

							dummyMethod3();
    for (i = 0; i < n; i++)
    {
        count = 0;
        /* Count how many elements are less than data[i] */
        for (j = 0; j < n; j++)
        {
            if (data[j] < data[i]) count++;
            else if (data[j] == data[i] && j < i) count++;
        }
        /* Put the element in the correct position */
        temp[count] = data[i];
    }
							dummyMethod4();
    memcpy(data,temp,n*sizeof(int));
    free(temp);
}

/*------------------------------------------------------------------
 * Function:    Parallel_CountSort
 * Purpose:     Parallel CountSort
 * In args:     Integer data array and size of the vector
 */
void Parallel_CountSort (int data[], int n, int thread_count)
{
    int i, j, count;
    int *temp = (int*)malloc(sizeof(int)*n);

    omp_set_num_threads(thread_count);

							dummyMethod1();
    #pragma omp parallel for private(i,j,count) shared(data,temp,n,thread_count)
    for (i = 0; i < n; i++)
    {
        count = 0;
        /* Count how many elements are less than data[i] */
        for (j = 0; j < n; j++)
        {
            if (data[j] < data[i]) count++;
            else if (data[j] == data[i] && j < i) count++;
        }
        /* Put the element in the correct position */
        temp[count] = data[i];
    }
							dummyMethod2();
    memcpy(data,temp,n*sizeof(int));
    free(temp);
}

/*------------------------------------------------------------------
 * Function:    Get_args
 * Purpose:     Get the command line args
 * In args:     argc, argv
 * Globals out: thread_count, total_tosses
 */
void Get_args(int argc, char* argv[], int *thread_count, int *n, int *num_method) 
{
   if (argc != 4) Usage(argv[0]);
   *thread_count = atoi(argv[1]);  
   if (*thread_count <= 0 || *thread_count > MAX_THREADS) Usage(argv[0]);
   *n = atoi(argv[2]);
   if (*n <= 0) Usage(argv[0]);
   *num_method = atoi(argv[3]);
   if (*num_method < 0 || *num_method > 3) Usage(argv[0]);
}  /* Get_args */

/*------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Print a message explaining how to run the program
 * In arg:    prog_name
 */
void Usage(char* prog_name) 
{
   fprintf(stderr, "====================================================\n"); 
   fprintf(stderr, "Usage: %s <number of threads> <n> <num_method>\n", prog_name);
   fprintf(stderr, "   n is the size of data vector\n");
   fprintf(stderr, "   n should be evenly divisible by the number of threads\n");
   fprintf(stderr, "   num_method is the number of the method\n");
   fprintf(stderr, "   1 - Serial CountSort\n");
   fprintf(stderr, "   2 - qsort\n");
   fprintf(stderr, "   3 - Parallel CountSort\n");
   fprintf(stderr, "====================================================\n");
   exit(EXIT_FAILURE);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:  compare
 * Purpose:   Compare function for qsort()
 */
int compare (const void *a, const void *b)
{
    int *arg1 = (int*)a;
    int *arg2 = (int*)b;

    if (*arg1 < *arg2) return -1;
    if (*arg1 > *arg2) return 1;
    return 0;
}

/*------------------------------------------------------------------
 * Function:  checkSort
 * Purpose:   Check if an array is sorted
 */
void checkSort (int data[], int n)
{
    int i, sort;
    sort = 1;
							dummyMethod3();
    for (i = 1; i < n && sort; i++)
        if (data[i] < data[i-1]) sort = 0;
							dummyMethod4();
    if (sort)
        printf("[!] The array is sorted!\n");
    else
        printf("[!] The array is NOT sorted!\n");
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