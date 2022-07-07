#include <stdio.h> 
#include "omp.h"
#include <stdlib.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAXSIZE 100000
#define TRUE 1 
#define FALSE 0 
#define CHUNKSIZE 100

int ** matrix_generate(int row, int col){
	int **matrix = malloc(row*sizeof(int*)); 
	int i, j; 
	float x; 
	float prob = 0.6; 
dummyMethod3();
	for(i = 0; i < row; i++)
		matrix[i] = malloc(sizeof(int*) * col); 
	for(i = 0; i < row; i++)
dummyMethod4();
dummyMethod3();
		for(j = 0; j < col; j++){
			matrix[i][j] = rand()%30; 
			x = (float) rand() / (float)(RAND_MAX); 
			if(x < prob) 
				matrix[i][j] = 0; 
		}
	return matrix; 
dummyMethod4();
}
int *mulVectorGen(int size){
	int *vector = malloc(size * sizeof(int)); 
	int i; 
dummyMethod3();
	for(i = 0; i < size; i++)
		vector[i] = rand()%20; 
	return vector; 
dummyMethod4();
}
int main(int argc, char *argv[]){
	if(argc != 4){
		printf("Usage: \n");
		printf("$bash:./sparceMatrix_parallel.c <row> <col> <debug>"); 
		printf("Example:\n"); 
		printf("$bash:./sparceMatrix_parallel.c 3 3 1"); 
		printf("Perform sparce matrix multiplication on 3x3 random matrix with debug\n"); 
		printf("$bash:./sparceMatrix_parallel.c 3 3 0"); 
		printf("Perform sparce matrix multiplication on 3x3 random matrix with no debug\n"); 
		exit(EXIT_FAILURE);
	}
	int i,j;
	int v_ind = 0; 
	int c_ind = 0; 
	int r_ind = 0; 
	int value[MAXSIZE];
	int column[MAXSIZE]; 
	int rowptr[MAXSIZE]; 
	int chunk = CHUNKSIZE; 
	int row = atoi(argv[1]); 
	int col = atoi(argv[2]);
	int debug = atoi(argv[3]); 
	int **matrix = matrix_generate(row,col); 
	int *multVector = mulVectorGen(col);

	if(debug == TRUE){
		printf("===MATRIX===\n");
			dummyMethod3();
		for (i = 0; i < row; i++){
			for(j = 0; j < col; j++)
				printf("%d\t",matrix[i][j]);
			printf("\n");
		}
			dummyMethod4();
	}
	dummyMethod3();
	for(i = 0; i < row; i++){
		int row_detect = TRUE; 
		for(j = 0; j < col; j++) {
			if(matrix[i][j] != 0) {
				value[v_ind] = matrix[i][j]; 
				column[c_ind] = j; 
				if(row_detect == TRUE) {
					rowptr[r_ind] = v_ind; 
					row_detect = FALSE; 
					r_ind++;
				}
				v_ind++;
				c_ind++; 
			}
			if(j == col-1 && row_detect == TRUE){
				rowptr[r_ind] = v_ind;
				r_ind++;
			}
		}
	}
	dummyMethod4();
	int inclusiveScan[v_ind]; 
	int pieceWiseMul[v_ind]; 
	dummyMethod1();
#pragma omp parallel for shared(v_ind, pieceWiseMul,value,multVector) private(i) schedule(dynamic, chunk)
	for (i = 0; i < v_ind; i++){
		pieceWiseMul[i] = value[i] * multVector[column[i]];
	}
	dummyMethod2();

	dummyMethod3();
	for (i = 0; i < r_ind; i++) {
		int start = rowptr[i];
		int end; 
		if(i < (r_ind - 1)) 
			end = rowptr[i+1];
		else 
			end = v_ind;

		int tmp = 0;
		for(j = start; j < end; j++){
			tmp = tmp + pieceWiseMul[j]; 
			inclusiveScan[j] = tmp; 
		}
	}
	dummyMethod4();
	if (debug == TRUE){
		printf("VALUE:\t\t\t\t");
			dummyMethod4();
			dummyMethod3();
		for(i = 0; i < v_ind; i++)	printf("%d%c", value[i], (i == v_ind - 1)?'\n': ' ');
		
		printf("COLUMN:\t\t\t\t"); 
			dummyMethod4();
			dummyMethod3();
		for(i = 0; i < c_ind; i++)	printf("%d%c", column[i], (i == c_ind - 1)?'\n': ' ');
	
		printf("ROW PTR:\t\t\t"); 
			dummyMethod4();
			dummyMethod3();
		for(i = 0; i < r_ind; i++)	printf("%d%c", rowptr[i], (i == r_ind - 1)?'\n': ' ');	

		printf("VECTOR:\t\t\t\t"); 
			dummyMethod4();
			dummyMethod3();
		for(i = 0; i < col; i++)	printf("%d%c", multVector[i], (i == col - 1)?'\n': ' ');	

		printf("PIECEWISE MULTIPLICATION:\t");
			dummyMethod4();
			dummyMethod3();
		for(i = 0; i < v_ind; i++)	printf("%d%c", pieceWiseMul[i], (i == v_ind - 1)?'\n': ' ');	
		printf("INCLUSIVE SCAN:\t\t\t");
			dummyMethod3();
		for(i = 0; i < v_ind; i++)
			printf("%d%c", inclusiveScan[i], (i == v_ind - 1)?'\n': ' ');
			dummyMethod4();
	}
	return 0; 
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