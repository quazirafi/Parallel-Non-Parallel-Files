/*
* Author of C++ script: Mustafa Atik - muatik@gmail.com 
* Authors of C script: 
*   Anderson Ballesteros - anderson.ballesteros@correo.usa.edu.co 
*   Sebastian Mancipe - sebastian.mancipe@correo.usa.edu.co
* Sergio Arboleda University
* Bogota, Colombia
* 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int ratingsRows = 0;
int ratingsCols = 0;

void load_csv (char *path, int  **ratings);
void factorize();
int getRandomNumber();
void initRandomMatrix(int **matrix, int rows, int cols);
void als(int **ratings, int maxUserId, int maxMovieId, int rank, int threadNumber);
void transpose(int **matrix, int rows, int cols, int **transpose);
void sumVectors(int *v1, int *v2,  int size, int **result);
int multiplyRowByCol(int *row, int *col, int size) ;
void escalarByVector(float escalar, int *vector, int size, int **result);
void getCol(int **matrix, int rows, int nCol, int **result);
void setCol(int **matrix, int rows, int nCol, int *newCol, int **result);
void multiplyMatrixes(int **m1, int **m2, int colsRows, int rowsM1, int colsM2, int **result);
void subsctracMatrixes(int **m1, int **m2, int rows, int cols, int **result);
void square(int **matrix, int rows, int cols, int **result);
float sumElements(int **matrix, int rows, int cols);

int main(int argc, char ** argv) {
    time_t t;

	// initializes random number generator
	srand((unsigned) time(&t));

    factorize();
    return 0;
}

// Lee los datos separados por comas que se encuentran en un archivo y
// los transforma en una matriz 
void load_csv (char *path, int  **ratings) {

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

// Inicializa los datos del algoritmo de mínimos cuadrados alternos
void factorize() {
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

// Obtiene un número random entre 0-9
int getRandomNumber() {
	return rand() % 1000 / 100;
}

// Inicializa una matriz con valores random
void initRandomMatrix(int **matrix, int rows, int cols) {
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


// Algoritmo de mínimos cuadrados alternos
void als(int **ratings, int maxUserId, int maxMovieId, int rank, int threadNumber) {

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
        // Sección paralela utilizando la directiva for schedule(static)
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

// Retorna la suma de los elementos de una matriz
float sumElements(int **matrix, int rows, int cols) {
    float sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            sum += matrix[i][j];
        }
    }
    return sum;
}

// Eleva al cuadrado cada elemento de una matriz
void square(int **matrix, int rows, int cols, int **result) {
    int **r = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        r[i] = (int *)calloc(cols, sizeof(int *));
        for (int j = 0; j < cols; j++) {
            r[i][j] = matrix[i][j] * matrix[i][j];
        }
    }
    *result = r;
}

// Resta entre matrices
void subsctracMatrixes(int **m1, int **m2, int rows, int cols, int **result) {
    int **r = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        r[i] = (int *)calloc(cols, sizeof(int *));
        for (int j = 0; j < cols; j++) {
            r[i][j] = m1[i][j] - m2[i][j];
        }
    }
    *result = r;
}

// Obtiene una columna de un matriz la columna se almacena en forma de vector
void getCol(int **matrix, int rows, int nCol, int **result) {
    int *r = (int *)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        // printf("%d\n", matrix[i][nCol]);
        r[i] = matrix[i][nCol];
        // printf("%d\n", r[i]);
    }
    *result = r;
}

// Modifica una columna de una matriz, recibiendo la nueva columna en forma de vector
void setCol(int **matrix, int rows, int nCol, int *newCol, int **result) {
    for (int i = 0; i < rows; i++) {
        // printf("%d\n", matrix[i][nCol]);
        matrix[i][nCol] = newCol[i];
        // printf("%d\n", matrix[i][nCol]);
    }
    *result = matrix;
    
}

// Multiplicación entre matrices
void multiplyMatrixes(int **m1, int **m2, int colsRows, int rowsM1, int colsM2, int **result) {
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


// Halla la transpuesta de una matriz
void transpose(int **matrix, int rows, int cols, int **transpose) {
    int **mt = (int **)calloc(cols, sizeof(int *));
    for (int i = 0; i < cols; i++) {
        mt[i] = (int *)calloc(rows, sizeof(int *));
        for (int j = 0; j < rows; j++) {
            mt[i][j] = matrix[j][i];
        }
        
    }

    *transpose = mt;
    
}

// Realiza la suma de 2 vectores
void sumVectors(int *v1, int *v2,  int size, int **result) {
    int *r = (int *)calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++) {
        r[i] = v1[i] + v2[i];
    }
    *result = r;
}

// Realiza la multiplicación entre un escalar y un vector
void escalarByVector(float escalar, int *vector, int size, int **result) {
    int *r = (int *)calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++) {
        r[i] = vector[i] * escalar;
    }
    *result = r;

}

// Multiplicación entre una fila y una columna de diferentes matrices
// El resultado es un escalar
int multiplyRowByCol(int *row, int *col, int size) {
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