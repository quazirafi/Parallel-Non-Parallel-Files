#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 50

double do_crazy_computation(int i, int j);

int main(int argc, char **argv) 
{
    double mat[SIZE][SIZE];
    int i,j;

    double tstart = omp_get_wtime();

    // set number of threads to 2
    omp_set_num_threads(2);

    //modify code here
dummyMethod1();
    #pragma omp parallel for private(i, j) shared(mat) schedule(static)
    for (i = 0; i < SIZE; i++) 
    { /* loop over the rows */
dummyMethod2();
        for (j = 0; j < SIZE; j++) 
        {  /* loop over the columns */
            mat[i][j] = do_crazy_computation(i,j);
            fprintf(stderr,".");
        }
    }


    double tend = omp_get_wtime();
    double elapsed = tend - tstart;
    
    printf("Elapsed time: %f seconds\n", elapsed);

    exit(0);
}

//Crazy computation
double do_crazy_computation(int x, int y) 
{
   int iter;
   double value = 0.0;

					dummyMethod3();
   for (iter = 0; iter < 5*x*x*x+1 + y*y*y+1; iter++) 
   {
     value += (cos(x*value) + sin(y*value));
   }
					dummyMethod4();
  return value;
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