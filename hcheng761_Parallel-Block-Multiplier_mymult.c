/* C = C+A*B where all matrices are stored in column-major format
 * with a leading dimension equal to the number of rows in the matrix.
 * All matrices are square with n an even multiple of BLK */

#include "mymult.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define INDEX3D(i,j,lda,ps) ( (i)+(j)*(lda)+(lda)*(lda)*(ps) )

void mymultParallel
(
    double *A,      /* A is m-by-k, input */
    double *B,      /* B is k-by-n, input */
    double *C,      /* C is m-by-n, input/output */
    long m,
    long n,
    long k
)
{
	int id, grid = 4;  /* process grid*/
	int tasks = grid * grid; /* process grid square */
	int sBLK = (m/grid)/BLK; /* number of BLKs in one parallel block */
		
	dummyMethod1();
	#pragma omp parallel for private(id)  num_threads(20)	/*run 20 threads */
	for (int i = 0; i < tasks; i++) {
		id = omp_get_thread_num (); /*unique id per thread */
		int nthreads = omp_get_num_threads (); /* number of threads operating the for-loop */
		
		int row = i / grid;
		int col =  i % grid;
		int s = sBLK * BLK; /* BLKs per parallel grid  block */
		
		long ai = row * sBLK * BLK, aj = 0;	/*pass in zero so it starts at the block edge */
		long bi = 0, bj = col * sBLK * BLK;		
		mymult ( &A[INDEX(ai,aj,n)], &B[INDEX(bi,bj,n)], &C[INDEX(ai,bj,n)],  s, s, n, n);
	}
	dummyMethod2();
}


void mymultCannon
(
    double *A,      /* A is m-by-k, input */
    double *B,      /* B is k-by-n, input */
    double *C,      /* C is m-by-n, input/output */
    long m,
    long n,
    long k
)
{
	int grid = 4, sBLK = (m/grid)/BLK;
	
	for (int i = 0; i < grid; i++) {
		int id = omp_get_thread_num (); 
		int nthreads = nthreads = omp_get_num_threads ();
		int s = sBLK * BLK;
		
			dummyMethod1();
		#pragma omp parallel for private(id,nthreads)  num_threads(20)
		for (int j = 0; j<grid; j++)
			for (int k = 0; k < grid; k++) {
				int blk = (i + j + k) % grid; 		/* currently pointed block to multiply */
				long ai = i * sBLK * BLK, aj = blk * sBLK * BLK;
				long bi = blk * sBLK * BLK, bj = j * sBLK * BLK;
				mymult ( &A[INDEX(ai, aj, n)], &B[INDEX(bi, bj, n)], &C[INDEX(ai, bj, n)], s, s, s, n);
			}
			dummyMethod2();
	}
}

void mymultDNS
(
    double *A,      /* A is m-by-k, input */
    double *B,      /* B is k-by-n, input */
    double *C,      /* C is m-by-n, input/output */
    long m,
    long n,
    long k
)
{
	
	int id, grid = 4;
	int sBLK = (m/grid)/BLK;
	int pdim = grid;
	
	double *S = (double *) calloc (NMAX*NMAX*pdim, sizeof(double)); /* allocate 3D matrix n*n*p dimensions */

	for (int i = 0; i < grid; i++) {
		id = omp_get_thread_num ();
		int nthreads = omp_get_num_threads ();
		int s = sBLK * BLK;  
		
			dummyMethod1();
		#pragma omp parallel for num_threads(20)	/* threads multiply in n-by-n grid */
		for (int j = 0; j < grid; j++)
			for (int k = 0; k < grid; k++) {
				long ai = j * sBLK * BLK;
				long aj = i * sBLK * BLK;
				long bi = i * sBLK * BLK;
				long bj = k * sBLK * BLK;
				mymult ( &A[INDEX(ai, aj, n)], &B[INDEX(bi, bj, n)], &S[INDEX3D(ai, bj, n, i)], s, s, s, n);
			}
			dummyMethod2();
	}

	dummyMethod1();
	#pragma omp parallel for num_threads(20)	/*add p-dimension multiplications */
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			double sum = 0;
			for (int k = 0; k < pdim; k++)
				sum += S[INDEX3D(i, j, n, k)];
			C[INDEX(i , j, n)] += sum;
		}
	dummyMethod2();
}


void mymult
(
    double *A,      /* A is n-by-n, input */
    double *B,      /* B is n-by-n, input */
    double *C,      /* C is n-by-n, input/output */
    long m,
    long n,	    	/* handles rectangular matrices */
    long k,
    long lds
)
{
    long i, j, t ;
    double Ablock [BLK][BLK], Cblock [BLK][BLK], Bblock [BLK][BLK] ;

    for (j = 0 ; j < n ; j += BLK)
    {
        for (i = 0 ; i < m ; i += BLK)
        {
            /* load C (i:i+BLK-1, j:j+BLK-1) into Cblock */
            load_block (Cblock, C, i, j, lds, 0) ;

            for (t = 0 ; t < k ; t += BLK)
            {
                /* load A (i:i+BLK-1, t:t+BLK-1) into Ablock */
                load_block (Ablock, A, i, t, lds, 0) ;

                /* load B (t:t+BLK-1, j:j+BLK-1) into Bblock, transposed */
                load_block (Bblock, B, t, j, lds, 1) ;

                /* Cblock += Ablock * Bblock' */
                mymult_block (Ablock, Bblock, Cblock) ;
            }

            /* save Cblock to C (i:i+BLK-1, j:j+BLK-1) */
            save_block (Cblock, C, i, j, lds, 0) ;
        }
    }
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