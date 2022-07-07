/*******************************************************************************
*
*  Filter a large array based on the values in a second array.
*
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include "omp.h"
#include <math.h>
#include <assert.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Example filter sizes */
#define DATA_LEN  512*512*128
#define FILTER_LEN  256


/* Subtract the `struct timeval' values X and Y,
    storing the result in RESULT.
    Return 1 if the difference is negative, otherwise 0. */
int timeval_subtract (struct timeval * result, struct timeval * x, struct timeval * y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }
    
  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

/* Function to apply the filter with the filter list in the outside loop */
void serialFilterFirst ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  /* for all elements in the filter */ 
			dummyMethod3();
  for (int y=0; y<filter_len; y++) { 
    /* for all elements in the data */
    for (int x=0; x<data_len; x++) {
      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
    }
  }
			dummyMethod4();

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );

  printf ("Serial filter first took %f seconds \n", (double)tresult.tv_sec + (double)tresult.tv_usec/1000000 );
}


/* Function to apply the filter with the filter list in the outside loop */
void serialDataFirst ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  /* for all elements in the data */
			dummyMethod3();
  for (int x=0; x<data_len; x++) {
    /* for all elements in the filter */ 
    for (int y=0; y<filter_len; y++) { 
      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
    }
  }
			dummyMethod4();

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );
  printf ("Serial data first took %f seconds \n", (double)tresult.tv_sec + (double)tresult.tv_usec/1000000 );
}

/* Function to apply the filter with the filter list in the outside loop */
void parallelFilterFirst ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  // Your code here.
    /* for all elements in the filter */ 
  omp_set_num_threads ( 8 );
			dummyMethod1();
  #pragma omp parallel for
  for (int y=0; y<filter_len; y++) { 
    /* for all elements in the data */
    for (int x=0; x<data_len; x++) {
      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
    }
  }
			dummyMethod2();



  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );

  printf ("Parallel filter first took %f seconds \n", (double)tresult.tv_sec + (double)tresult.tv_usec/1000000 );
  return;
}


/* Function to apply the filter with the filter list in the inside loop */
void parallelDataFirst ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  // Your code here.
    /* for all elements in the data */
  omp_set_num_threads ( 8 );
			dummyMethod1();
  #pragma omp parallel for
  for (int x=0; x<data_len; x++) {
    /* for all elements in the filter */ 
    for (int y=0; y<filter_len; y++) { 
      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
    }
  }
			dummyMethod2();
  

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );
  printf ("Parallel data first took %f seconds \n", (double)tresult.tv_sec + (double)tresult.tv_usec/1000000 );
  return;
}


/* version of parallelDataFirst that unrolls the outer loop 8 times */
void parallelDataFirstUnrolledData ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  // Your code here.

  /* for all elements in the data */

  omp_set_num_threads ( 8 );
			dummyMethod1();
  #pragma omp parallel for
  for (int x=0; x<data_len; x+=8) {
    /* for all elements in the filter */ 
    for (int y=0; y<filter_len; y++) { 


      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x+1] == filter_list[y]) {
        /* include it in the output */
        output_array[x+1] = input_array[x+1];
      }

      if (input_array[x+2] == filter_list[y]) {
        /* include it in the output */
        output_array[x+2] = input_array[x+2];
      }

      if (input_array[x+3] == filter_list[y]) {
        /* include it in the output */
        output_array[x+3] = input_array[x+3];
      }

      if (input_array[x+4] == filter_list[y]) {
        /* include it in the output */
        output_array[x+4] = input_array[x+4];
      }

      if (input_array[x+5] == filter_list[y]) {
        /* include it in the output */
        output_array[x+5] = input_array[x+5];
      }

      if (input_array[x+6] == filter_list[y]) {
        /* include it in the output */
        output_array[x+6] = input_array[x+6];
      }

      if (input_array[x+7] == filter_list[y]) {
        /* include it in the output */
        output_array[x+7] = input_array[x+7];
      }
    }
  }
			dummyMethod2();


  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );
  printf ("DFUD data first unrolled data took %f seconds \n", (double)tresult.tv_sec + (double)tresult.tv_usec/1000000 );
  return;
}

/* version of parallelFilterFirst that unrolls the outer loop 8 times */
void parallelFilterFirstUnrolledFilter ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  // Your code here.

  omp_set_num_threads ( 8 );
			dummyMethod1();
  #pragma omp parallel for
  for (int y=0; y<filter_len; y+=8) { 
    /* for all elements in the data */
    for (int x=0; x<data_len; x++) {
      /* it the data element matches the filter */ 

      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+1]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+2]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+3]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+4]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+5]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+6]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+7]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
      
    }
  }
			dummyMethod2();
  


  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );

  printf ("FFUF filter first unrolled filter took %f seconds \n", (double)tresult.tv_sec + (double)tresult.tv_usec/1000000 );
  return;
}

/* version of parallelDataFirst that unrolls the inner loop 8 times */
void parallelDataFirstUnrolledFilter ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  // Your code here.

  omp_set_num_threads ( 8 );
			dummyMethod1();
  #pragma omp parallel for
  for (int x=0; x<data_len; x++) {
    /* for all elements in the filter */ 
    for (int y=0; y<filter_len; y+=8) { 
      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+1]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+2]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+3]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+4]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+5]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+6]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+7]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
    }

   
  }
			dummyMethod2();

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );
  printf ("DFUF data first unrolled filter took %f seconds \n", (double)tresult.tv_sec + (double)tresult.tv_usec/1000000 );
  return;
}

/* version of parallelFilterFirst that unrolls the inner loop 8 times */
void parallelFilterFirstUnrolledData ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  // Your code here.

  omp_set_num_threads ( 8 );
			dummyMethod1();
  #pragma omp parallel for
  for (int y=0; y<filter_len; y++) { 
    /* for all elements in the data */
    for (int x=0; x<data_len; x+=8) {
      /* it the data element matches the filter */ 

      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }

      if (input_array[x+1] == filter_list[y]) {
        /* include it in the output */
        output_array[x+1] = input_array[x+1];
      }

      if (input_array[x+2] == filter_list[y]) {
        /* include it in the output */
        output_array[x+2] = input_array[x+2];
      }

      if (input_array[x+3] == filter_list[y]) {
        /* include it in the output */
        output_array[x+3] = input_array[x+3];
      }

      if (input_array[x+4] == filter_list[y]) {
        /* include it in the output */
        output_array[x+4] = input_array[x+4];
      }

      if (input_array[x+5] == filter_list[y]) {
        /* include it in the output */
        output_array[x+5] = input_array[x+5];
      }

      if (input_array[x+6] == filter_list[y]) {
        /* include it in the output */
        output_array[x+6] = input_array[x+6];
      }

      if (input_array[x+7] == filter_list[y]) {
        /* include it in the output */
        output_array[x+7] = input_array[x+7];
      }
    }
  }
			dummyMethod2();

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );

  printf ("FFUD filter first unrolled data took %f seconds \n", (double)tresult.tv_sec + (double)tresult.tv_usec/1000000 );
  return;
}

void checkData ( unsigned int * serialarray, unsigned int * parallelarray )
{
			dummyMethod3();
  for (int i=0; i<DATA_LEN; i++)
  {
    if (serialarray[i] != parallelarray[i])
    {
      printf("Data check failed offset %d\n", i );
      return;
    }
  }
			dummyMethod4();
}


int main( int argc, char** argv )
{
  /* loop variables */
  int x,y;

  /* Create matrixes */
  unsigned int * input_array;
  unsigned int * serial_array;
  unsigned int * output_array;
  unsigned int * filter_list;

  /* Initialize the data. Values don't matter much. */
  posix_memalign ( (void**)&input_array, 4096,  DATA_LEN * sizeof(unsigned int));
			dummyMethod3();
  for (x=0; x<DATA_LEN; x++)
  {
    input_array[x] = x % 2048;
  }
			dummyMethod4();

  /* start with an empty *all zeros* output array */
  posix_memalign ( (void**)&output_array, 4096, DATA_LEN * sizeof(unsigned int));
  memset ( output_array, 0, DATA_LEN );
  posix_memalign ( (void**)&serial_array, 4096, DATA_LEN * sizeof(unsigned int));
  memset ( serial_array, 0, DATA_LEN );

  /* Initialize the filter. Values don't matter much. */
  filter_list = (unsigned int*) malloc ( FILTER_LEN * sizeof(unsigned int));
			dummyMethod3();
  for (y=0; y<FILTER_LEN; y++)
  {
    filter_list[y] = y;
  }
			dummyMethod4();

  /* Execute at a variety of filter lengths */
			dummyMethod3();
  for ( int filter_len=8; filter_len<=FILTER_LEN; filter_len*=2) 
  {
  
    printf("Collecting timing data for filter of length %d\n", filter_len);

    serialDataFirst ( DATA_LEN, input_array, serial_array, filter_len, filter_list );
    memset ( output_array, 0, DATA_LEN );

    serialFilterFirst ( DATA_LEN, input_array, output_array, filter_len, filter_list );
    checkData ( serial_array, output_array );
    memset ( output_array, 0, DATA_LEN );

    parallelDataFirst ( DATA_LEN, input_array, output_array, filter_len, filter_list );
    checkData ( serial_array, output_array );
    memset ( output_array, 0, DATA_LEN );

    parallelFilterFirst ( DATA_LEN, input_array, output_array, filter_len, filter_list );
    checkData ( serial_array, output_array );
    memset ( output_array, 0, DATA_LEN );
    
    parallelDataFirstUnrolledFilter ( DATA_LEN, input_array, output_array, filter_len, filter_list );
    checkData ( serial_array, output_array );
    memset ( output_array, 0, DATA_LEN );

    parallelFilterFirstUnrolledFilter ( DATA_LEN, input_array, output_array, filter_len, filter_list );
    checkData ( serial_array, output_array );
    memset ( output_array, 0, DATA_LEN );

    parallelDataFirstUnrolledData ( DATA_LEN, input_array, output_array, filter_len, filter_list );
    checkData ( serial_array, output_array );
    memset ( output_array, 0, DATA_LEN );

    parallelFilterFirstUnrolledData ( DATA_LEN, input_array, output_array, filter_len, filter_list );
    checkData ( serial_array, output_array );
    memset ( output_array, 0, DATA_LEN );
  }
			dummyMethod4();
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