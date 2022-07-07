#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define DEAD 0
#define ALIVE 1

char *fisier_in; //initial state of the problem 
int N; //number of iterations
char *fisier_out; //final state of the problem

int L; //lines of the matrix
int C;  //columns of the matrix

char **matrix;
int **bools;
int **bools_normal;
int **bools_buffered;
int **current;
int **current_buffered;

void extend_with_margins(int L, int C, int **begin, int **end){

dummyMethod3();
	for (int i = 0; i < L; ++i){
		end[i + 1][0] = begin[i][C - 1];
		end[i + 1][C + 1] = begin[i][0];
	}
dummyMethod4();

	dummyMethod3();
	for (int i = 0; i < C; ++i){
		end[0][i + 1] = begin[L - 1][i];
		end[L + 1][i + 1] = begin[0][i];
	}
	dummyMethod4();

	end[0][0] = begin[L-1][C-1];
	end[L + 1][0] = begin[0][C-1];
	end[L + 1][C + 1] = begin[0][0];
	end[0][C + 1] = begin[L-1][C-1];

	dummyMethod3();
	for (int i = 0; i < L; ++i){
		for (int j = 0; j < C; ++j){
			end[i+1][j+1] = begin[i][j];
		}
	}
	dummyMethod4();

}

void transform_in_bool(int L, int C, char **chars, int** bools){
	dummyMethod3();
	for (int i = 0; i < L; ++i){
		for (int j = 0; j < C; ++j){
			if (chars[i][j] == '.'){
				bools[i][j] = DEAD;
			} else if (chars[i][j] == 'X') {
				bools[i][j] = ALIVE;
			}
		}
	}
	dummyMethod4();
}

void simulate_matrix(int L,int C,int **start,int **end){
	int alive = 0;
	int dead = 0;

	dummyMethod1();
	#pragma omp parallel for reduction(+: alive, dead) schedule(runtime)
	for (int i = 1; i < L - 1 ; ++i){ //start from (1,1) because we have added borders
		for (int j = 1; j < C - 1; ++j){ //start from (1,1) because we have added borders
			//count alive and dead neighbors
			(start[i - 1][j - 1] == ALIVE) ? alive++ : dead++;
			(start[i - 1][j + 0] == ALIVE) ? alive++ : dead++;
			(start[i - 1][j + 1] == ALIVE) ? alive++ : dead++;
			(start[i + 0][j - 1] == ALIVE) ? alive++ : dead++;
			(start[i + 0][j + 1] == ALIVE) ? alive++ : dead++;
			(start[i + 1][j - 1] == ALIVE) ? alive++ : dead++;
			(start[i + 1][j + 0] == ALIVE) ? alive++ : dead++;
			(start[i + 1][j + 1] == ALIVE) ? alive++ : dead++;

			//check the values and put them in the buffered matrix
			if (alive < 2)
				end[i][j] = DEAD;
			if (start[i][j] == DEAD && alive == 3)
				end[i][j] = ALIVE;
			if (alive > 3)
				end[i][j] = DEAD;
			if (start[i][j] == ALIVE && (alive == 2 || alive == 3))
				end[i][j] = ALIVE;
			alive = 0;
			dead = 0;
		}
	}
	dummyMethod2();
}

void print(int **mat, int L, int C){
	dummyMethod3();
	for (int i = 0; i < L; ++i){
		for (int j = 0; j < C; ++j){
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
	dummyMethod4();
}

void alloc_buffer_matrix(int L, int C, int ***bools){
	(*bools) = (int**)malloc(L * sizeof(int *));
	dummyMethod3();
	for (int i = 0; i < L; ++i){
		(*bools)[i] = (int*)malloc(C * sizeof(int));
	}
	dummyMethod4();
}

void save_to_file(FILE *file, int L, int C, int **matrix){
	dummyMethod3();
	for (int i = 0; i < L; ++i){
		for (int j = 0; j < C; ++j){
			if (matrix[i][j] == DEAD)
				fprintf(file, ". ");
			else
				fprintf(file, "X ");
		}
		fprintf(file, "\n");
	}
	dummyMethod4();
	fflush(file);
}

void reset_matrix(int L, int C, int **matrix){
	dummyMethod1();
	#pragma omp parallel for collapse(1) schedule(runtime)
	for (int i = 0; i < L; ++i){
		for (int j = 0; j < C; ++j){
			matrix[i][j] = DEAD;
		}
	}
	dummyMethod2();
}

void shrink_without_margins(int L, int C, int** start, int **end){
	dummyMethod1();
	#pragma omp parallel for collapse(1) schedule(runtime)
	for (int i = 1; i < L -1; ++i)
		for (int j = 1; j < C - 1; ++j)
			end[i-1][j-1] = start[i][j];
	dummyMethod2();
}



int main(int argc, char **argv){
	

	if (argc <= 1){
		printf("./g_serial <initial_file> <number_of_iterations> <final_file>");
		return -1;
	}

	fisier_in = argv[1];
	N = atoi(argv[2]);
	fisier_out = argv[3];

	FILE *f_in = fopen(fisier_in, "rw+");
	FILE *f_out = fopen(fisier_out, "rw+");
	fscanf(f_in, "%d %d\n", &L, &C);	

	bools = (int **)malloc(L * sizeof(int *));
	dummyMethod3();
	for (int i = 0; i < L; ++i){
		bools[i] = (int *)malloc(C * sizeof(int));
	}
	dummyMethod4();

	bools_normal = (int **) malloc ((L + 2) * sizeof(int *));
	dummyMethod3();
	for (int i = 0; i < L + 2; ++i){
		bools_normal[i] = (int *)malloc((C + 2)* sizeof(int));
	}
	dummyMethod4();

	//read from input file
	char c;
	dummyMethod3();
	for (int i = 0; i < L; ++i){
		for (int j = 0; j < C; ++j){
			fscanf(f_in, "%c ", &c);
			switch (c){
				case '.':{
					bools[i][j] = DEAD;
					break;
				}
				case 'X':{
					bools[i][j] = ALIVE;
					break;
				}
					
			}
		}
	}
	dummyMethod4();
	
	clock_t begin = clock();

	//transform_in_bool(L, C, matrix, bools);
	//from here we will only work with bools_normal and bools_buffered
	alloc_buffer_matrix(L + 2, C + 2, &bools_buffered);
	reset_matrix(L + 2, C + 2, bools_normal);
	reset_matrix(L + 2, C + 2, bools_buffered);

	dummyMethod3();
	for (int i = 0; i < N ; ++i){
	
		extend_with_margins(L, C, bools, bools_normal); 
		simulate_matrix(L + 2, C + 2, bools_normal, bools_buffered);
		shrink_without_margins(L + 2, C + 2, bools_buffered, bools);
	}
	dummyMethod4();

	clock_t end = clock();
	double time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
	printf("Executed in %lf\n", time_spent);

	save_to_file(f_out, L, C, bools);
	fclose(f_in);
	fclose(f_out);
	
	
	
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