#include "omp.h"
#include<sys/time.h>
#include<stdlib.h>
#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int arr[100000000];

int main (int argc, char *argv[])
{
        int n = 100000000;
        int  number_of_threads, choice, dynamic_length;

/*verifying command line arguments*/
  if (argc < 4)
  {
      printf("Please Input atleast 3 Command Line arguments\n");
      exit(0);
  }
        /*intializing command line arguments*/
        number_of_threads = atoi(argv[1]);
        choice = atoi(argv[2]);
        dynamic_length = atoi(argv[3]);

/*initializing array*/
omp_set_num_threads(number_of_threads);
dummyMethod1();
        #pragma omp parallel for   
        for (int i=0; i<n; ++i)
                arr[i] = rand()%1000;

struct timeval start, end;
dummyMethod2();
gettimeofday(&start, NULL);
double t1 = (double)start.tv_sec+ (double)(start.tv_usec/1000000.0);
/*1 for static and 2 for dynamic*/
if (choice == 1)
{
															dummyMethod1();
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < n; ++i)
        {
                arr[i] = arr[i] * arr[i];
        }
															dummyMethod2();
}
else
{
        /*using dynamic*/
															dummyMethod1();
        #pragma omp parallel for schedule(dynamic, dynamic_length)
        for (int i = 0; i < n; ++i)
        {
                arr[i] = arr[i] * arr[i];
        }
															dummyMethod2();
}
gettimeofday(&end, NULL);
double t2 = (double)end.tv_sec+ (double)(end.tv_usec/1000000.0);
double time_spent = t2-t1;
        if (choice == 1)
        {
                printf("\n Threads: %d Schedule: Static Time: %f",number_of_threads, time_spent);
        }
        else
        {
                printf("\n Threads: %d Schedule: dynamic  dynamic_length: %d Time: %f",number_of_threads,dynamic_length, time_spent);
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