/***
	Programa: 			movie.c
	Autor: 	  			Mustafa Atik
	Implementado en c por: 		E. López - J. García
	Función:  			Algoritmo de generación de sistema de recomendación de películas que utiliza el método 
					de mínimos cuadrados alternos.
	Fecha de implementación: 	3 de octubre, 2020
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// install eigen
// mpic++ -I /Users/mustafaatik/Downloads/eigen/ main.cpp -o main && mpirun  --allow-run-as-root  -np 2 ./main
// http://stackoverflow.com/questions/15939757/is-it-possible-to-run-openmpi-on-a-local-computer-and-a-remote-cluster
// http://mpitutorial.com/tutorials/running-an-mpi-cluster-within-a-lan/
// https://www.open-mpi.org/papers/sc-2009/jjhursey-iu-booth.pdf
// http://stackoverflow.com/questions/2546298/vector-usage-in-mpic
// http://stackoverflow.com/questions/38592854/how-to-send-the-data-in-an-eigenmatrixxd-with-mpi

int ratingsRows = 0;
int ratingsCols = 0;

/** Inicialización de funciones del algoritmo **/
void load_csv (char *path, int  **ratings);												// 1
void factorize();															// 2
int getRandomNumber(); 															// 3
void initRandomMatrix(int **matrix, int rows, int cols); 										// 4
void als(int **ratings, int maxUserId, int maxMovieId, int rank, int threadNumber);	 						// 5
float sumElements(int **matrix, int rows, int cols);											// 6
void square(int **matrix, int rows, int cols, int **result);										// 7
void subsctracMatrixes(int **m1, int **m2, int rows, int cols, int **result);								// 8
void getCol(int **matrix, int rows, int nCol, int **result);										// 9
void setCol(int **matrix, int rows, int nCol, int *newCol, int **result);								// 10
void multiplyMatrixes(int **m1, int **m2, int colsRows, int rowsM1, int colsM2, int **result);						// 11
void transpose(int **matrix, int rows, int cols, int **transpose);	  								// 12  
void sumVectors(int *v1, int *v2,  int size, int **result); 										// 13
void escalarByVector(float escalar, int *vector, int size, int **result);								// 14
int multiplyRowByCol(int *row, int *col, int size) ;											// 15
/** Fin inicialización de funciones **/


int main(int argc, char ** argv) {
    time_t t;

	// initializes random number generator
	srand((unsigned) time(&t));

    factorize();
    return 0;
}

void load_csv (char *path, int  **ratings) {													// 1

    int ** toReturn;

    FILE* data = fopen(path, "r");
    char line[1024];
    int r=0, c;
    toReturn = (int **)calloc(29, sizeof(int *));
    while (fgets(line, 1024, data) != NULL) {
        toReturn[r] = (int *)calloc(3, sizeof(int *));
        c = 0;
        char * number = strtok(line, ",");
        while (number != NULL) {
            toReturn[r][c] = atoi(number);
            c++;
            number = strtok(NULL, ",");
        }
        r++;

    }

    ratingsRows = r;
    ratingsCols = c;
    *ratings = toReturn;

}

void factorize() {									 											// 2
    int **ratings;
    load_csv("data.txt", &ratings);
    int maxUserId = 7;
    int maxMovieId = 9;
    int cols = maxMovieId, rows = maxUserId;

							dummyMethod3();
    for (int i = 4; i < 5; ++i) {
        printf("Thread number: %d\n", i);
        als(ratings, maxUserId, maxMovieId, 4, 1);
    }
							dummyMethod4();

}

int getRandomNumber() {								 										 	// 3
	return rand() % 1000 / 100;
}


void initRandomMatrix(int **matrix, int rows, int cols) {    									// 4
    int **m = (int **)calloc(rows, sizeof(int *));
							dummyMethod3();
    for (int i = 0; i < rows; i++) {
        m[i] = (int *)calloc(cols, sizeof(int *));
		for (int j = 0; j < cols; j++) {
			m[i][j] = getRandomNumber();
		}
	}
							dummyMethod4();
    *matrix = m;
}

void als(int **ratings, int maxUserId, int maxMovieId, int rank, int threadNumber) {			// 5

    int **U, **M;
    initRandomMatrix(&U, maxUserId, rank);
    initRandomMatrix(&M, rank, maxMovieId);  

    int **A = (int **)calloc(maxUserId, sizeof(int *));
    int **W = (int **)calloc(maxUserId, sizeof(int *));
    
							dummyMethod3();
    for (int i = 0; i < maxUserId; i++) {
        A[i] = (int *)calloc(maxMovieId, sizeof(int *));
        W[i] = (int *)calloc(maxMovieId, sizeof(int *));
    }
							dummyMethod4();
    

							dummyMethod3();
    for (int i = 0; i < ratingsRows; i++) {
        int ui = ratings[i][0] - 1; // userId index
        int mi = ratings[i][1] - 1; // movieId index
        int ri = ratings[i][2]; // rating
        A[ui][mi] = ri;
        W[ui][mi] = 1;
    }
							dummyMethod4();
    
    float Eta = 0.03;
    float eta = Eta;
    int maxIteration = 2000;

    int ui, mi, ri;
    float error;
    int *tempU;
    float *errorHistory = (float *)calloc(maxIteration, sizeof(float *));
    int errorHistorySize = 0;
    float start = omp_get_wtime();
     for (int iteration = 0; iteration < maxIteration; ++iteration) {

															dummyMethod1();
        #pragma omp parallel for num_threads(threadNumber) schedule(static) private(ui, mi, ri, error, tempU)
        for (int i = 0; i < ratingsRows; ++i) {
            int ui = ratings[i][0] - 1; // userId index
            int mi = ratings[i][1] - 1; // movieId index
            int ri = ratings[i][2]; // rating
            
            tempU = (int *)calloc(rank, sizeof(int *));
            int *MCol;
            getCol(M, rank, mi, &MCol);
            error = ri - multiplyRowByCol(U[ui], MCol, rank);
            
            escalarByVector(eta*error, MCol, rank, &tempU);
            sumVectors(U[ui], tempU, rank, &tempU);

            int *MColTemp;
            escalarByVector(eta*error, U[ui], rank, &MColTemp);
            sumVectors(MColTemp, MCol, rank, &MColTemp);

            setCol(M, rank, mi, MColTemp, &M);
            U[ui] = tempU;
        }
															dummyMethod2();

        if (iteration % ((int) maxIteration /15) == 0) {
            eta*=0.8;
            
            int **mTemp;
            multiplyMatrixes(U, M, rank, maxUserId, maxMovieId, &mTemp);
            subsctracMatrixes(A, mTemp, maxUserId, maxMovieId, &mTemp);
            square(mTemp, maxUserId, maxMovieId, &mTemp);
            errorHistory[errorHistorySize] = sumElements(mTemp, maxUserId, maxMovieId);
            errorHistorySize++;
        }
    }

    double elapse = omp_get_wtime() - start;
    printf("elapse: %f\n", elapse);
    printf("errors:\n");
    for (int j = 0; j < errorHistorySize; j++) {
        printf("error: %.2f\n", errorHistory[j]);
    }
    

}

float sumElements(int **matrix, int rows, int cols) {											// 6
    float sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            sum += matrix[i][j];
        }
    }
    return sum;
}

void square(int **matrix, int rows, int cols, int **result) {									// 7
    int **r = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        r[i] = (int *)calloc(cols, sizeof(int *));
        for (int j = 0; j < cols; j++) {
            r[i][j] = matrix[i][j] * matrix[i][j];
        }
    }
    *result = r;
}

void subsctracMatrixes(int **m1, int **m2, int rows, int cols, int **result) {					// 8
    int **r = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        r[i] = (int *)calloc(cols, sizeof(int *));
        for (int j = 0; j < cols; j++) {
            r[i][j] = m1[i][j] - m2[i][j];
        }
    }
    *result = r;
}

void getCol(int **matrix, int rows, int nCol, int **result) {									// 9
    int *r = (int *)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        // printf("%d\n", matrix[i][nCol]);
        r[i] = matrix[i][nCol];
        // printf("%d\n", r[i]);
    }
    *result = r;
}

void setCol(int **matrix, int rows, int nCol, int *newCol, int **result) {						// 10
    for (int i = 0; i < rows; i++) {
        // printf("%d\n", matrix[i][nCol]);
        matrix[i][nCol] = newCol[i];
        // printf("%d\n", matrix[i][nCol]);
    }
    *result = matrix;
    
}

void multiplyMatrixes(int **m1, int **m2, int colsRows, int rowsM1, int colsM2, int **result) {	// 11
    int **r = (int **)calloc(rowsM1, sizeof(int *));
    for (int i = 0; i < rowsM1; i++) {
        r[i] = (int *)calloc(colsM2, sizeof(int *));
        for (int j = 0; j < colsM2; j++) {
            int sum = 0;
            for (int k = 0; k < colsRows; k++){
                sum+= m1[i][k] * m2[k][j];
            }
            r[i][j] = sum;
        }
    }
    *result = r;
}


void transpose(int **matrix, int rows, int cols, int **transpose) {								// 12
    int **mt = (int **)calloc(cols, sizeof(int *));
    for (int i = 0; i < cols; i++) {
        mt[i] = (int *)calloc(rows, sizeof(int *));
        for (int j = 0; j < rows; j++) {
            mt[i][j] = matrix[j][i];
        }
        
    }

    *transpose = mt;
    
}

void sumVectors(int *v1, int *v2,  int size, int **result) {									// 13
    int *r = (int *)calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++) {
        r[i] = v1[i] + v2[i];
    }
    *result = r;
}

void escalarByVector(float escalar, int *vector, int size, int **result) {						// 14
    int *r = (int *)calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++) {
        r[i] = vector[i] * escalar;
    }
    *result = r;

}

int multiplyRowByCol(int *row, int *col, int size) {											// 15
    int toReturn = 0;
    for (int i = 0; i < size; i++) {
        toReturn += row[i] * col[i];
    }
    return toReturn;
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