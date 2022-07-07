#include<getopt.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<unistd.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


void init2d(double **matrix, int numRowCol, double base);
void init1d(double **vector, int vecSize,  double base);
void mxm(double *matrixA, double *matrixB, double *matrixC, int size);
void mxmjki(double *matrixA, double *matrixB, double *matrixC, int size);
void mxmikj(double *matrixA, double *matrixB, double *matrixC, int size);
void mxm2(double *matrixA, double *matrixB, double *matrixC, int size);
void mxv(double *matrix, double *vector1, double *vector2, int size);
void mmT(double *matrix, int size);
void print_matrix(double *matrix, int size);
void print_vector(double *vector, int size);
double normf(double *matrix, int size);
double get_wctime();

int main(int argc, char* argv[]){
    
    //The following makes sure that a valid argument for the Dimensions of the matrix is  given by the user
    int dim;
    int threads;
    
    if (argc > 2){
        dim = atoi(argv[1]);
        threads = atoi(argv[2]);
    }
    else{
        printf("invalid argument: NULL\n");
        return 0;
    }
    
    if (dim == 0){
        printf("invalid argument: %d \n" ,dim);
        return 0;
    }
    if (threads == 0){
        printf("Please input a valid number of threads\n");
        return 0;
    }
    
    
    omp_set_num_threads(threads); //Sets the number of threads the parallel program utilizes
    
    double *matrixA;
    double *matrixB;
    double *matrixC;
    //double *vector1;
    //double *vector2;
    double start, end;
    
    start = get_wctime();
    init2d(&matrixA, dim, 1);
    init2d(&matrixB, dim, 2);
    init2d(&matrixC, dim, 0);
   // init1d(&vector1, dim, 1);
   // init1d(&vector2, dim, 0);
    end = get_wctime();
    
    //Printing of Matrices and Vectors
    
    
    

    printf("using matrix/vector size of %d\n", dim);
    //printf("matrix/vector initialization:%10.7f ms\n", (end - start) * 1000.0);
    
    printf( (dim < 5 ) ? "matrix A:\n": "");
    print_matrix(matrixA, dim);

    printf( (dim < 5 ) ? "matrix B:\n": "");
    print_matrix(matrixB, dim);

    printf( (dim < 5 ) ? "matrix C:\n": "");
    print_matrix(matrixC, dim);
    
   // printf( (dim < 5 ) ? "vector v1:\n": "");
   // print_vector(vector1, dim);

   // printf( (dim < 5 ) ? "vector v2:\n": "");
   // print_vector(vector2,dim);
   
  
    //Computes matrix matrix and prints the necessary information
    /*if(dim <= 1000){
        printf("Computing C = A * B (mxm)\n");
        start = get_wctime();
        mxm(matrixA, matrixB, matrixC, dim);
        end = get_wctime();
        printf("matrix/matrix multiplication:%10.7f ms\n", (end - start) * 1000.0);
        printf( (dim < 5) ? "\nmatrix C:\n": "");
        print_matrix(matrixC, dim);
    }*/
   
    
    //Computing mxm ikj multiplication
    printf("Computing C = A * B (mxm2) multiplication with loop orderin ijk\n");
    start = get_wctime();
    mxm2(matrixA, matrixB, matrixC, dim);
    end = get_wctime();
    printf("matrix/matrix multiplication:%10.7f ms\n", (end - start) * 1000.0);
    printf( (dim < 5) ? "\nmatrix C:\n": "");
    print_matrix(matrixC, dim);
    
    //Computing mxm jki multiplication
    memset(matrixC,0, dim * dim * sizeof(double));
    printf("Computing C = A * B (mxm) multiplication with loop orderin ikj\n");
    start = get_wctime();
    mxmikj(matrixA, matrixB, matrixC, dim);
    end = get_wctime();
    printf("matrix/matrix multiplication:%10.7f ms\n", (end - start) * 1000.0);
    printf( (dim < 5) ? "\nmatrix C:\n": "");
    print_matrix(matrixC, dim);
        

    /*Computes matrix vector and prints the necessary information
    printf("Computing v2 = B * v1\n");
    start = get_wctime();
    mxv(matrixB, vector1, vector2, dim);
    end = get_wctime();
    printf("matrix/vector multiplication:%10.7f ms\n", (end - start) * 1000.0);
    printf( (dim < 5) ? "\nvector 2:\n": "");
    print_vector(vector2, dim);*/
  
    
    //Computes the matrix matrix mutliplication 2 and prints out the necessary information
    printf("\nComputing C = A * B (mxm) with jki \n");
    memset(matrixC, 0, dim * dim * sizeof(double)); //Clears out C before mxm2
    start = get_wctime();
    mxmjki(matrixA, matrixB, matrixC, dim);
    end = get_wctime();
    printf("matrix/matrix multiplication:%10.7f ms\n\n", (end - start) * 1000.0);
    printf( (dim < 5) ? "matrix C:\n": "");
    print_matrix(matrixC, dim);

    //Computes the transpotion of matrix B, moved till after mxm2 so B isn't changed
    printf("Computing the transpostion of  B in parallel\n");
    printf( (dim < 5) ? "matrix B:\n": "");
    start = get_wctime();
    mmT(matrixB, dim);
    end = get_wctime();
    print_matrix(matrixB, dim);
    printf("matrix transpose:%10.7f ms\n", (end - start) * 1000.0);
    
    
    free(matrixA);
    free(matrixB);
    free(matrixC);

    //free(vector1);
    //free(vector2);  
}

//Function Definitions
void init2d(double **matrix, int numRowCol, double base){
    
    int i,j;
    
    //Allocates space for the array. Takes the 1D array and for every element i makes an  array within it giving us a 2D array
    *matrix = malloc(numRowCol * numRowCol * sizeof(double *));
    
    //Itterates through our 2D array assigning the values given by Prof. Larkins
    //Except its in Parallel
    
							dummyMethod1();
    #pragma omp parallel for private(i,j)
    for(i=0; i < numRowCol; i++){
       for(j=0; j < numRowCol; j++){
          (*matrix)[(i*numRowCol)+j] = base * (i + (0.1 * j));
        
        }
    }
							dummyMethod2();
}

void init1d(double **vector, int size, double base){

    int i;

    //Allocates space for the vector
    *vector = malloc(size * sizeof(double *));
   
							dummyMethod3();
    for (i=0; i<size; i++){
        (*vector)[i] = base * (i + 1);
    }
							dummyMethod4();

}

void mxm(double *matrixA, double *matrixB, double *matrixC, int size){

    int i,j,k;

							dummyMethod3();
    for(i=0; i<size; i++){
        for(j=0;  j<size; j++){
            for(k=0; k<size;k++){
                matrixC[(i * size)+j] += matrixA[(i * size)+k] * matrixB[(k * size)+j];
            }
        }
    }
							dummyMethod4();
}
//The original matrix x matrix code with loop orderin ikj
void mxmikj(double *matrixA, double *matrixB, double *matrixC, int size){

    int i,j,k;

    #pragma omp parallel shared(matrixA, matrixB, matrixC) private(i,j,k)
    {
        #pragma omp for schedule(static)
															dummyMethod3();
        for(i=0; i<size; i++){
            for(k=0; k<size; k++){
                for(j=0; j<size; j++){
                    matrixC[(i * size)+j] += matrixA[(i * size)+k] * matrixB[(k * size)+j];
                    if( i == 0 && j == 0 && k == 0)
                        printf("number of threads in use: %i\n", omp_get_num_threads());
                }
            }

        }
															dummyMethod4();
    }
}
//The original matrix x matrix code with loop ordering jki
void mxmjki(double *matrixA, double *matrixB, double *matrixC, int size){

    int i,j,k;
    #pragma omp parallel shared(matrixA, matrixB, matrixC)
    {
        #pragma omp for private(i,j,k)
															dummyMethod3();
        for(j=0; j<size; j++){
            for(k=0; k<size; k++){
                for(i=0; i<size; i++){
                    matrixC[(i * size)+j] += matrixA[(i * size)+k] * matrixB[(k * size)+j];
                }
            }
        }
															dummyMethod4();
    }
}
//MXM2 running in parallel. Shared matrices are used so that data can be updated constantly by the different threads
void mxm2( double *matrixA, double *matrixB, double *matrixC, int size){
    int i,j,k;
    #pragma omp parallel shared(matrixA, matrixB, matrixC) private(i,j,k)
    {    
        #pragma omp for schedule(static)
															dummyMethod3();
        for(i=0; i<size; i++){
            for(j=0; j<size; j++){
                for(k=0; k<size; k++){
                    matrixC[(i * size)+j] += matrixA[(i * size)+k] * matrixB[(j * size)+k];
                }
            }
        }
															dummyMethod4();
    }    
}
void mxv(double *matrix, double *vector1, double *vector2, int size){
    int i, j; 
							dummyMethod3();
    for (i=0; i<size; i++){
        for(j=0; j<size; j++){
            vector2[i] += matrix[(i * size) + j] * vector1[j];
        }
    }
							dummyMethod4();
}

void mmT(double *matrix, int size){

    int i,j;
    double swap;

    #pragma omp parallel shared (matrix, size) private(i,j,swap)
    {
        #pragma omp for schedule(static)
															dummyMethod3();
        for(i=0; i<size; i++){
            for(j=i; j<size; j++){
                swap = matrix[(i * size)+j];
                matrix[(i * size)+j] = matrix[(j * size)+i];
                matrix[(j * size)+i] = swap;
            }
        }
															dummyMethod4();
    }
}
void print_matrix(double *matrix, int size){

    int i, j;
    
    if(size < 5){
															dummyMethod3();
        for(i=0; i<size; i++ ){
            printf("| ");
            for(j=0; j<size; j++){
                printf("%.2f ", matrix[(i*size)+j] );
            }
            printf( "|\n" );
        }
															dummyMethod4();
 
        printf("norm:  %.3f\n\n", normf(matrix, size));
    }
}

void print_vector(double *vector, int size){
    
    int i;

    if (size < 5){
        printf("| ");
															dummyMethod3();
        for(i =0; i<size; i++){
            printf ("%.2f ", vector[i]);
        }
															dummyMethod4();
        printf("|\n\n");
    }
}

double normf(double *matrix, int size){

    int i,j;
    double norm = 0;

							dummyMethod3();
    for (i=0; i<size; i++){
        for(j=0; j<size;  j++){
            norm += (matrix[(i * size) + j] * matrix[(i * size) + j]);
            }
    }
							dummyMethod4();
    return sqrt(norm);
}

double get_wctime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec + 1E-6 * tv.tv_usec);
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