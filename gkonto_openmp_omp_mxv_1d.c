#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* 
   export OMP_PLACES="{0:4:1},{4:4:1},{8:4:1},{12:4:1}"
   export OMP_PROC_BIND=close
   export OMP_NUM_THREADS=16
*/   

# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <omp.h>

void main ( int argc, char *argv[] )
  
{
  double *a, *b, *c;
  int i, j, k, N;
  
        if (argc != 2) {
		printf ("Usage : %s <matrix size>\n", argv[0]);
                exit(1);
	}
	N = strtol(argv[1], NULL, 10);

  	/*
  	Allocate the matrices.
  	*/
  	a = ( double * ) malloc ( N * N * sizeof ( double ) );
  	b = ( double * ) malloc ( N * sizeof ( double ) );
  	c = ( double * ) malloc ( N * sizeof ( double ) );
  	/*
  	Assign values to the B and C matrices.
  	*/
  	srand ( time ( NULL));

					dummyMethod3();
  	for ( i = 0; i < N; i++ ) 
    		for (j = 0; j < N; j++ )
	      		a[i*N+j] = ( double ) rand() / (RAND_MAX * 2.0 - 1.0);
					dummyMethod4();

	dummyMethod3();
	for ( i = 0; i < N; i++ )
	    	b[i] = ( double ) rand() / (RAND_MAX * 2.0 - 1.0);
	dummyMethod4();
   

															dummyMethod1();
  	#pragma omp parallel for private (i,j,k) shared (a, b, c)
        for ( i = 0; i < N; i++) {
   		double sum = 0.0;
    		for ( j = 0; j < N; j++ ) {
    		        for (k =0; k < N; k++)
        			sum = sum + a[i*N+j] * b[j];
        		}
        	c[i] = sum;	
  	}
															dummyMethod2();
  
 
	/*for ( i = 0; i < N; i++ ) {
	    	for (j = 0; j < N; j++ )
	      		printf ("%1.3f ", a[i*N+j]); 
	    	printf("\t %1.3f ", b[i]);
	    	printf("\t %1.3f \n", c[i]);
       	}*/
 
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