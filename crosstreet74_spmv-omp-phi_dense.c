//
//  dense.c
//  
//  Created by Hussian Alamri on September 2012
//

#include "dense.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Acquired from Matrix Market http://math.nist.gov/MatrixMarket/ with few modifications */
MATRIX* ReadMatrix(FILE *file) {
    MM_typecode matcode;
    int         M, N, nz, ret_code, i, j, k;
    double      *val;
    double      **A;
    MATRIX      *m;
        
    if (mm_read_banner(file, &matcode) != 0)
    {
        printf("Could not process Matrix Market banner.\n");
        exit(1);
    }    
    
    
    /*  This is how one can screen matrix types if their application */
    /*  only supports a subset of the Matrix Market data types.      */
    
    if (mm_is_complex(matcode) && mm_is_matrix(matcode) &&
        mm_is_sparse(matcode) )
    {
        printf("Sorry, this application does not support ");
        printf("Matrix Market type: [%s]\n", mm_typecode_to_str(matcode));
        exit(1);
    }
    
    
    /* find out size of sparse matrix .... */
    
    if ((ret_code = mm_read_mtx_crd_size(file, &M, &N, &nz)) !=0)
        exit(1);
        
    /* reseve memory for matrices */
    m = (MATRIX *) malloc(sizeof(MATRIX));
    int*  I = (int *) malloc(nz * sizeof(int));
    int*  J = (int *) malloc(nz * sizeof(int));
    val = (double *) malloc(nz * sizeof(double));
            
    /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
    /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
    /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */
    
							dummyMethod3();
    for (i=0; i<nz; i++)
    {
        fscanf(file, "%d %d %lf\n", &I[i], &J[i], &val[i]);
        I[i]--;  /* adjust from 1-based to 0-based */
        J[i]--;
    }
							dummyMethod4();
    
    if (file !=stdin) fclose(file);
        
    A = (double**) malloc(M * sizeof(double*));
            
							dummyMethod3();
    for (i = 0; i < M; ++i) {
        A[i] = (double*) malloc(N * sizeof(double));
    }
							dummyMethod4();
                
							dummyMethod3();
    for(j=0; j < M; ++j) {
        for(k=0; k < N; ++k) {
            A[j][k] = 0.0;
        }
    }
							dummyMethod4();
    
							dummyMethod3();
    for(i=0; i < nz; ++i) {
        j = I[i];
        k = J[i];
        A[j][k] = val[i];
    }
							dummyMethod4();
        
    m->nnz = nz;
    m->nrows = M;
    m->ncols = N;
    m->mel = A;
    
	return m;
}

void WriteMatrix(FILE *file, MATRIX* reM) {
    MM_typecode matcode;
    int i, jjj, k;
    int nz = reM->nnz;
    int*  I = (int *) malloc(nz * sizeof(int));
    int*  J = (int *) malloc(nz * sizeof(int));
    double* val = (double *) malloc(nz * sizeof(double));
    int nrows = reM->nrows;
    int ncols = reM->ncols;
    int N = nrows;
    int M = ncols;

    k = 0;    
    while (k < nz) {
															dummyMethod3();
        for (i = 0; i < nrows; ++i) {
            for (jjj = 0; jjj < ncols; ++jjj) {
                if((double)reM->mel[i][jjj] != (double)0) {
                    I[k] = i;
                    J[k] = jjj;
                    val[k] = reM->mel[i][jjj];
                    k++;
                }
            }
        }
															dummyMethod4();
        break;
    } // end while
    
    mm_initialize_typecode(&matcode);
    mm_set_matrix(&matcode);
    mm_set_coordinate(&matcode);
    mm_set_real(&matcode);
    
    mm_write_banner(file, matcode);
    mm_write_mtx_crd_size(file, M, N, nz);
    
    /* NOTE: matrix market files use 1-based indices, i.e. first element
     of a vector has index 1, not 0.  */
    
							dummyMethod3();
    for (i=0; i<nz; i++)
        fprintf(file, "%d %d %10.3g\n", I[i]+1, J[i]+1, val[i]);
							dummyMethod4();
    
    fflush(file);
    
    #ifdef LOG
    printf("Closing file...\n");
    #endif
    
    fclose(file);
    
    free(I);
    free(J);
    free(val);
}

double DotProduct(const double *a, const double *b, int n) {
     double result = 0.0f;
    int i;
    
							dummyMethod1();
    #pragma omp parallel for default(shared) private(i) reduction(+:result)
    for(i = 0; i < n; i++) {
        result += (a[i] * b[i]);
    }
							dummyMethod2();
    
    return result;
}


double* MultiplyMatrix(MATRIX *m, double *val) {
	int          i,
                 j,
                 s,
		 s1;
    int nrows = m->nrows;
    int ncols = m->ncols;
    double*  r = malloc(ncols * sizeof(double));
    double**  mal = m->mel;
    double        result;
    
							dummyMethod1();
    #pragma omp parallel for private(s)
    for (s=0; s < nrows; s++) {
        r[s] = 0;
    }
							dummyMethod2();

							dummyMethod1();
    #pragma omp parallel for default(shared) private(i, j)  reduction(+:result)
    for (i=0; i< nrows; ++i) {
        for (j=0; j < ncols; ++j) {
            result += (double) (mal[i][j] * val[j]);
        }
        r[i] = result;
    }
							dummyMethod2();
    
    return r;
}

void PrintMatrix(MATRIX *m) {
    int i,
        j;
    
							dummyMethod3();
    for (i = 0; i < m->nrows; i++) {
        for (j = 0; j < m->ncols; j++) {
            printf("%f ", m->mel[i][j]);
        }
        printf("\n");
    }
							dummyMethod4();
}

void DestroyMatrix(MATRIX *m) {
    int i;
    
							dummyMethod3();
    for (i = 0; i < m->nrows; ++i) {
        free(m->mel[i]);
    }
							dummyMethod4();
    
    free(m->mel);
    free(m);
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