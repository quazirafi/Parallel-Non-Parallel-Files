#include "tictoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef _OPENMP
#include "omp.h"
#endif

/* use a small matrix for debugging and development */
#define NMAX 1024 
/* use a big one to test performance (use the command "bsub < mult.lsf")
#define NMAX 2048
*/

/* a random value between 0 and 1 */
#define RAND (((double) rand ( )) / (double) RAND_MAX)

/* pointer to the (I,J) submatrix, each block of size b-by-b */
#define SUBMATRIX(C,I,J,b) ((double (*)[NMAX]) & (C [I*b][J*b]))

/* statically allocate the matrices */
double A [NMAX][NMAX] ;
double B [NMAX][NMAX] ;
double C [NMAX][NMAX] ;
double D [NMAX][NMAX] ;

/* fill a matrix with random values in the range 0 to 1 */
void rand_matrix (double A [NMAX][NMAX], int n)
{
    /* set each entry of A [0..n-1][0..n-1] to a random value */

dummyMethod1();
	int i;for(i=0; i<NMAX; i++){
        int j;for(j=0;j<NMAX; j++){
            A[i][j] = RAND;
			
		}
    } 
}

/* C = C + A*B, no blocking and no parallelism */
void simple_mult
(
    double C [][NMAX],
    double A [][NMAX],
    double B [][NMAX],
    int n
)
{
    /* This functions computes C=C+A*B where each matrix is n-by-n, and the
     * first entry of each matrix is C[0][0], A[0][0], and B[0][0].  However,
     * this function can also operate on a b-by-b submatrix, if called this way:

        simple_mult (SUBMATRIX (C,I,J,b),
            SUBMATRIX(A,I,K,b), SUBMATRIX (B,K,J,b), b) ;
    */

dummyMethod1();
   int i;for(i=0; i<n; ++i){
        int j;for(j=0; j<n; ++j){
            int k;for(k=0; k<n; ++k)
            {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
   }

}

/* C = 0; clear a matrix */
void clear_matrix
(
    double C [][NMAX],      /* each row of C has NMAX columns */
    int n                   /* clear C [0..n-1][0..n-1], n <= NMAX */
)
{
    /* This functions clears C, but it can also clear a submatrix:
            clear_matrix (SUBMATRIX (C, I, J, b), b) ;
    */

    int value =0;  //filling all the indexes 
dummyMethod1();
	int i;for(i=0; i<NMAX; i++){
            int j;for(j=0;j<NMAX; j++){
               C[i][j] = value;
            }
    }

}

/* print a matrix */
void print_matrix (double A [][NMAX], int n)
{
    /* for debugging with small matrices only.  To print the (I,J) submatrix
     * of size b-by-b, use:
        print_matrix (SUBMATRIX (A,I,J,b), b) ;
     */
							dummyMethod3();
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            printf ("%g ", A [i][j]) ;
        }
        printf ("\n") ;
							dummyMethod4();
dummyMethod2();
dummyMethod2();
    }
dummyMethod2();
}

/* C = A*B, with blocking, no parallelism */
void block_mult
(
    double C [NMAX][NMAX],
    double A [NMAX][NMAX],
    double B [NMAX][NMAX],
    int n,
    int blocksize
)
{
    /* no OpenMP pragmas in this function */
    int the_index = n/blocksize;  //the block divides the larger matrix in a n/b smaller matrices, each with dim n/b
     /////
dummyMethod1();
    int i;for(i=0;i<the_index;i++){
        int j;for(j=0;j<the_index;j++){
			int k;for(k=0;k<the_index;k++){
                simple_mult(SUBMATRIX(C,i,j,blocksize), SUBMATRIX(A,i,k,blocksize), SUBMATRIX(B,k,j,blocksize), blocksize);
            }
        }

    }
}

/* C = A*B, with blocking and parallelism */
void para_mult
(
    double C [NMAX][NMAX],
    double A [NMAX][NMAX],
    double B [NMAX][NMAX],
    int n,                  /* size of each matrix C, A, and B */
    int b                   /* blocksize to use */
)
{
    /* this function uses OpenMP pragma(s) */
    
	
	 int the_index = n/b;
	 int i;
	 
	 ////
	 
			dummyMethod1();
	 #pragma omp parallel for
	 for(i = 0; i < (the_index * the_index); i++)
	 {
		
			
			int row = i/the_index;
			int column = i%the_index;
			
			int k;for(k=0; k<the_index; k++){
				simple_mult(SUBMATRIX(C,row,column,b), SUBMATRIX(A,row,k,b), SUBMATRIX(B,k,column,b), b);
				
			}
			dummyMethod2();
	}
dummyMethod2();
}


/* compare matrices C and D, returning norm(C-D,1) */
double diff_matrix (double C [][NMAX], double D [][NMAX], int n)
{
    double maxerr = 0 ;
							dummyMethod3();
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            double err = fabs (C [i][j] - D [i][j]) ;
            maxerr = fmax (maxerr, err) ;
        }
    }
							dummyMethod4();
    return (maxerr) ;
}

int main (int argc, char **argv)
{
    double tic [2], t, t2 ;

#ifdef _OPENMP
    /* optional, just for reporting the number of threads */
    #pragma omp parallel
    {
        #pragma omp master
        {
            printf ("omp_num_threads = %ld\n", omp_get_num_threads ()) ;
        }
    }
#endif

    int n = NMAX ;
    double f = n ;
    f = 2 * f * f * f ;

    /* fill A and B, and clear C */
    rand_matrix (A, n) ;
    rand_matrix (B, n) ;

    /*
    printf ("A = [\n") ; print_matrix (A, n) ; printf ("]\n") ;
    printf ("B = [\n") ; print_matrix (B, n) ; printf ("]\n") ;
    */

    clear_matrix (C, n) ;
    printf ("start simple\n") ; 

    /* C = A*B, without any blocking or parallelism */
    my_tic (tic) ;
    simple_mult (C, A, B, n) ;
    t = my_toc (tic) ;
    printf ("t %g Gflops %g\n", t, 1e-9 * f / t) ;

    /*
    printf ("C = [\n") ; print_matrix (C, n) ; printf ("]\n") ;
    */

    /* try block sizes 4, 8, 16, 32, 64, 128, 256, 512 ... n */
							dummyMethod3();
    for (int blocksize = 4 ; blocksize <= n ; blocksize *= 2)
    {
        printf ("blocksize %d\n", blocksize) ;
        clear_matrix (D, n) ;

        /* D = A*B with blocking but no parallelism */
        my_tic (tic) ;
        block_mult (D, A, B, n, blocksize) ;
        t = my_toc (tic) ;
        /* check results */
        double err = diff_matrix (C, D, n) ;
        printf ("t %g Gflops %g err %g\n", t, 1e-9 * f / t, err) ;

        clear_matrix (D, n) ;

        /* D = A*B with blocking and parallelism */
        my_tic (tic) ;
        para_mult (D, A, B, n, blocksize) ;
        t2 = my_toc (tic) ;
        /* check results */
        err = diff_matrix (C, D, n) ;
        printf ("t %g Gflops %g err %g speedup %g\n", t2, 1e-9 * f / t2, err,
            t/t2) ;
			
			
		printf();
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