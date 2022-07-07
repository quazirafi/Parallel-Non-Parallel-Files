/* Examples illustrating the use of the schedule clause.
 * Author: Naga Kandasamy
 * Date created: 10/06/2014
 * Compile as follows: gcc -o omp_scheduling omp_scheduling.c -fopenmp -std=c99 -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void invariant_amount_of_work(int);
void unpredictable_amount_of_work(int);
int UD(int, int); // Random number generator

#define MIN_TIME 2
#define MAX_TIME 10
#define AVG_TIME 3

int
main (int argc, char **argv)
{
  if (argc != 2){
      printf ("Usage: omp_scheduling <num threads> \n");
      exit (0);
  }
  
  int thread_count = atoi (argv[1]);

  int n = 100; 
  int i; 
  srand(2104);

  /* Parallelize the for loop using static scheduling for load balancing. Here Loop iterations are divided into pieces of size 
   * chunk and then statically assigned to threads. If chunk is not specified, the iterations are evenly (if possible) divided 
   * contiguously among the threads. */
  printf("Parallelizing the for loop by assigning each thread an almost equal chunk size. \n");   
							dummyMethod1();
#pragma omp parallel for num_threads(thread_count) private(i) schedule(static)
    for (i = 0; i < n; i++){
        printf ("Thread %d executes loop iteration %d. \n", omp_get_thread_num (), i);
    }
							dummyMethod2();

    int chunk_size = 2;
    printf("\n Parallelizing the for loop by assigning each thread a chunk of size %d. \n", chunk_size);
							dummyMethod1();
    #pragma omp parallel for num_threads(thread_count) private(i) schedule(static, chunk_size)
    for (i = 0; i < n; i++){
          printf ("Thread %d executes loop iteration %d. \n", omp_get_thread_num (), i);
    }
							dummyMethod2();


    /* The static schedule is appropriate for the simplest case: a parallel region containing a single for construct with each 
     * iteration requiring the same amount of work. */
    printf("\nParallelizing the for loop using static scheduling. Each thread performs an invariant amount of work per iteration. \n");
    struct timeval start, stop;
    gettimeofday (&start, NULL);
  
							dummyMethod1();
#pragma omp parallel for num_threads(thread_count) private(i) schedule(static)
    for (i = 0; i < n; i++){
	      invariant_amount_of_work(AVG_TIME); // Each thread performs about the same amount of work per iteration
    }
							dummyMethod2();
    gettimeofday (&stop, NULL);
    printf ("Time taken to execute the %d loop iterations = %fs. \n \n", n,
		     (float) (stop.tv_sec - start.tv_sec + (stop.tv_usec - start.tv_usec) / (float) 1000000));


      /* The static schedule may not be appropriate for the case in which each loop iteration requires an unpredictable amount of work. */
    printf("\nParallelizing the for loop using static scheduling. Each thread performs an unpredictable amount of work per iteration. \n");
    srand(2014); // Set the seed for the random number generator
    gettimeofday (&start, NULL);
  
							dummyMethod1();
#pragma omp parallel for num_threads(thread_count) private(i) schedule(static)
    for (i = 0; i < n; i++){
	      unpredictable_amount_of_work(UD(MIN_TIME, MAX_TIME)); // Each thread performs about the same amount of work per iteration
    }
							dummyMethod2();
    gettimeofday (&stop, NULL);
    printf ("Time taken to execute the %d loop iterations = %fs. \n \n", n,
		     (float) (stop.tv_sec - start.tv_sec + (stop.tv_usec - start.tv_usec) / (float) 1000000));


    /* The dynamic schedule is appropriate for the case of a for construct with the iterations requiring varying, or even unpredictable, 
     * amounts of work. No thread waits at the barrier for longer than it takes another thread to execute its final iteration. This requires 
     * that iterations be assigned one at a time to threads as they become available, with synchronization for each assignment. The 
     * synchronization overhead can be reduced by specifying a minimum chunk size k greater than 1, so that threads are assigned k at a time 
     * until fewer than k remain. This guarantees that no thread waits at the barrier longer than it takes another thread to execute 
     * its final chunk of (at most) k iterations.
     * */
    printf("\nParallelizing the for loop using dynamic scheduling. Each thread performs an unpredictable amount of work per iteration. \n");
    srand(2014);
    chunk_size = 1; // Can be tuned by the programmer; the default chunk size for dynamic scheduling is one
    gettimeofday (&start, NULL);
  
							dummyMethod1();
#pragma omp parallel for num_threads(thread_count) private(i) schedule(dynamic, chunk_size)
    for (i = 0; i < n; i++){
        unpredictable_amount_of_work(UD(MIN_TIME, MAX_TIME)); // Each thread performs an unpredictable amount of work per iteration
    }
							dummyMethod2();
    
    gettimeofday (&stop, NULL);
    printf ("Time taken to execute the %d loop iterations = %fs. \n \n", n,
		     (float) (stop.tv_sec - start.tv_sec + (stop.tv_usec - start.tv_usec) / (float) 1000000));

     
    /* The guided schedule guarantees that no thread waits at the barrier longer than it takes another thread to execute its 
     * final iteration, or final k iterations if a chunk size of k is specified. Among such schedules, the guided schedule is 
     * characterized by the property that it requires the fewest synchronizations. For chunk size k, a typical implementation 
     * will assign q = ceiling(n/p) iterations to the first available thread, where p is the number of threads, set n to the larger 
     * of n-q and p*k, and repeat until all iterations are assigned. */

     printf("\nParallelizing the for loop using guided scheduling. Each thread performs an unpredictable amount of work per iteration. \n");
     srand(2014);
     gettimeofday (&start, NULL);
  
							dummyMethod1();
#pragma omp parallel for num_threads(thread_count) private(i) schedule(guided, chunk_size)
    for (i = 0; i < n; i++){
	      unpredictable_amount_of_work(UD(MIN_TIME, MAX_TIME)); // Each thread performs an unpredictable amount of work per iteration
    }
							dummyMethod2();
    gettimeofday (&stop, NULL);
    printf ("Time taken to execute the %d loop iterations = %fs. \n \n", n,
		     (float) (stop.tv_sec - start.tv_sec + (stop.tv_usec - start.tv_usec) / (float) 1000000));


    return 0;
}


/* Function simulates some processing by sleeping for the specified amount of time. */
void invariant_amount_of_work(int processing_time)
{
	sleep(processing_time);
}

/* Function simulates some processing by sleeping for the specified amount of time. */
void unpredictable_amount_of_work(int processing_time)
{
	sleep(processing_time);
}


/* Returns a random number between MIN_TIME and MAX_TIME. */
int UD(int min, int max)
{
  return((int)floor((double)(min + (max - min + 1)*((float)rand()/(float)RAND_MAX))));
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