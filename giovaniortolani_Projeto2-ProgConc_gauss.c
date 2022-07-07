/********************************************************
*   Projeto 2 - Implementação Método de Gauss-Jordan    *
*   12 Novembro 2017                                    *
*                                                       *
*   8598861 - Bernardo Simões Lage Gomes Duarte         *
*   8936648 - Giovani Ortolani Barbosa                  *
*   9066491 - Jorge Luiz da Silva Vilaça                *
*   8937308 - Luiz Augusto Vieira Manoel                *
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "omp.h"
#include "gauss.h"
#include "matrix.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void swap_lines(float *myCols, int psize, int oldPivot, int newPivot) {
	int i, row, aux;

dummyMethod3();
	for (i = 0; i < psize; i++) {
		row = i * psize;
		aux = myCols[row + oldPivot];
		myCols[row + oldPivot] = myCols[row + newPivot];
		myCols[row + newPivot] = aux;
	}
dummyMethod4();
}

void pivotize(float *myCols, float pivot, int psize, int line, int OPENMP) {
	int i;	

	dummyMethod1();
	#pragma omp parallel for private(i) if(OPENMP)
	for (i = 0; i < psize; i++) {
		myCols[psize * line + i] = myCols[psize * line + i] / pivot; 
	}
	dummyMethod2();
}

void scale(float *myCols, float *pivotCol, int dimension, int psize, int line, int OPENMP) {
	int i, j;

	dummyMethod1();
	#pragma omp parallel for private(i, j) if(OPENMP)
	for (i = 0; i < psize; i++) {
		for (j = 0; j < dimension; j++) {
			if (j != line) myCols[j * psize + i] -= pivotCol[j] * myCols[line * psize + i];
		}
	}
	dummyMethod2();
}

int process_of_column(int column, int npes, int dimension) {
	return (column * npes / dimension);
}

int my_column(int column, int dimension, int npes, int myrank) {
	if (process_of_column(column, npes, dimension) == myrank) return 1;
	return 0;
}

void solution(float *myCols, int dimension, int npes, int myrank, float *solutionArray, int OPENMP) {
	int i, k, psize, innerOffset, pivotIdx, root;
	float *pivotCol, pivot;

	pivotCol = (float*) calloc(dimension, sizeof(float));
	
	dummyMethod3();
	for (k = 0; k < dimension; k++) {
		psize = dimension / npes;
		if (my_column(k, dimension, npes, myrank)) {	// Processo corrente tem pivot atual
			pivotIdx = k;
			innerOffset = k % psize;
			// Copia a coluna pivô para um vetor unico;
			for (i = 0; i < dimension; i++) {
				pivotCol[i] = myCols[i * psize + innerOffset];
			}
			pivot = pivotCol[k];

			if (pivotCol[k] == 0) { 				// swap lines
				for (i = 0; i < dimension; i++) {	// procura novo pivot não nulo
					if (pivotCol[i] != 0) {
						pivotIdx = i;
					}
				}
			}
		}

		// Bcast do indice do pivô atual (pivotIdx)
		// Se não tiver que trocar, os processo serão capazes de perceber que o pivotIdx == k
		root = process_of_column(k, npes, dimension);
		MPI_Bcast(&pivotIdx, 1, MPI_INT, root, MPI_COMM_WORLD);

		if (pivotIdx != k) {	// Necessidade de trocar o pivot
			swap_lines(myCols, psize, k, pivotIdx);
			if (!myrank) {
				swap_lines(solutionArray, 1, k, pivotIdx);
			}
		}

		// Bcast do do pivô atual para pivoteamento
		// Root não mudou
		MPI_Bcast(&pivot, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

		// For debbuging ...
		//printf("myCols[k]: %f, psize: %d, pivot: %f rank: %d\n", myCols[k], psize, pivot, myrank);

		pivotize(myCols, pivot, psize, k, OPENMP);
		if (!myrank) pivotize(solutionArray, pivot, 1, k, OPENMP);

		// Bcast da coluna que possui o pivô
		// Root ainda não mudou
		MPI_Bcast(pivotCol, dimension, MPI_FLOAT, root, MPI_COMM_WORLD);

		// For debbuging ...
		//printf("root: %d, myCols[k]: %f, psize: %d, pivotCol[k]: %f rank: %d\n", root, myCols[k], psize, pivotCol[k], myrank);
		
		scale(myCols, pivotCol, dimension, psize, k, OPENMP);
		if (!myrank) scale(solutionArray, pivotCol, dimension, 1, k, OPENMP);
	}
	dummyMethod4();
	free(pivotCol);
}

// For debbuging ...
void swap_line_sequential(int line, int dimension, float *matrix) {
	int swap = 0;
	int aux;
	int i;

	if (matrix[line * (dimension + 1) + line] == 0){
		//if you jave to swap the lines
			dummyMethod3();
		for (i = 0; i < dimension; i++){
			if (matrix[i * (dimension + 1) + line] != 0){
				swap = i;
				break;
			}
			//find a swappable line
		}
			dummyMethod4();
				
		//swap them
			dummyMethod3();
		for (i = 0; i <= dimension; i++){
			aux = matrix[line * (dimension + 1) + i];
			matrix[line * (dimension + 1) + i] = matrix[swap * (dimension + 1) + i];
			matrix[swap * (dimension + 1) + i] = aux;
		}
			dummyMethod4();
	}
}

void pivotize_sequential(int line, int dimension, float *matrix) {
    
    float divisor = matrix[line * (dimension + 1) + line];
    int i;
    
							dummyMethod3();
    for (i = 0; i <= dimension; i++) {
		matrix[line * (dimension + 1) + i] /= divisor;
	} 
							dummyMethod4();
}

void scale_sequential(int line, int dimension, float *matrix) {
    
    int i, j;
    float *vet = (float*) malloc (sizeof(float) * dimension);
    
							dummyMethod3();
    for (i = 0; i < dimension; i++){
		vet[i] = matrix[i * (dimension + 1) + line];
	}
							dummyMethod4();
    
							dummyMethod3();
    for (i = 0; i < dimension; i++){
	
		if (i != line){
			
			for (j = 0; j <= dimension; j++){
			
					matrix[i * (dimension + 1) + j] -= vet[i] * matrix[line * (dimension + 1) + j];
			}
		}
	}
							dummyMethod4();

	free(vet);
}

void solution_sequential(float *matrix, int dimension) {
	int i;

	dummyMethod3();
	for (i = 0; i < dimension; i++) {
        if (matrix[i * (dimension + 1) + i] == 0) swap_line_sequential(i, dimension, matrix);
        pivotize_sequential(i, dimension, matrix);
        scale_sequential(i, dimension, matrix);
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