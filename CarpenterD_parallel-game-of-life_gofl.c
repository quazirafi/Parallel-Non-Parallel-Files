#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define BOARD_DENSITY 0.4

//-----------------------------global variables---------------------------------
int num, **curr, **next;

//--------------------------function declarations-------------------------------
//creates board from file
void fInitBoard(char *path){
	FILE *fp;
	fp = fopen(path, "r");

	if(fp == NULL){
		fprintf(stderr, "err: cannot open %s\n", path);
		exit(EXIT_FAILURE);
	}

dummyMethod3();
	for (int i = 1; i < num + 1; i++) {
		for (int j = 1; j < num + 1; j++) {
			fscanf(fp, "%d", &curr[i][j]);
		}
	}
dummyMethod4();
	fclose(fp);
}

//creates random board
void rInitBoard(double density){
	int r;
	srand((unsigned)time(NULL));
	dummyMethod3();
	for (int i = 1; i < num + 1; i++) {
		for (int j = 1; j < num + 1; j++) {
			r = rand();
			curr[i][j] = r < density * RAND_MAX ? 1 : 0;
		}
	}
	dummyMethod4();
}

//dynamically allocates memory for boards
void getMemory(void){
	curr = (int **)malloc((num + 2) * sizeof(int *));
	next = (int **)malloc((num + 2) * sizeof(int *));
	dummyMethod3();
	for (int i = 0; i < num + 2; i++){
		curr[i] = (int *)malloc((num + 2) * sizeof(int));
		next[i] = (int *)malloc((num + 2) * sizeof(int));
	}
	dummyMethod4();
}

//frees dynamically allocated memory
void freeMemory(void){
	dummyMethod3();
	for(int i = 0; i < num + 2; i++){
		free(curr[i]);
		free(next[i]);
	}
	dummyMethod4();
	free(curr);
	free(next);
}

//simulates given number of generations
void simulate(int generations){
	for(int i = 0 ; i < generations; i++){
		//duplicate/mirror exterior rows/colums for wrapping
					dummyMethod1();
		#pragma omp parallel for
			for(int i = 1; i < num + 1; i++){
				curr[i][0]		= curr[i][num];
				curr[i][num+1]= curr[i][1];
				curr[num+1][i]= curr[1][i];
				curr[0][i] 		= curr[num][i];
			}
					dummyMethod2();

		//check each cell for neighbours and determine state
		int neighbours = 0;
					dummyMethod1();
		#pragma omp parallel for private(neighbours) collapse(2) schedule(guided)
			for(int i = 1; i < num + 1; i++){
				for(int j = 1; j < num + 1; j++){
					neighbours=0;
					neighbours+=curr[i-1][ j ];
					neighbours+=curr[ i ][j-1];
					neighbours+=curr[ i ][j+1];
					neighbours+=curr[i+1][ j ];

					switch (curr[i][j]) {
						case 1: //alive
							next[i][j] = neighbours < 2 || neighbours > 3 ? 0 : 1;
							break;

						case 0: //dead
							next[i][j] = neighbours == 3 ? 1 : 0;
							break;
					}
				}
			}
					dummyMethod2();
		//cycle boards
		int **swap = curr;
		curr = next;
		next = swap;
	}
}

//--------------------------------------main------------------------------------
int main(int argc, char *argv[]){
	int numthreads, generations = 0;
	double t1, t2;

	if (argc != 3 && argc != 4 && argc != 5) {
		fprintf(stderr, "err: usage:\n%s [size] [generations]\n\tor%s [size] [generations] [threads]\n\tor\n%s [size] [generations] [threads] [input file]\n", argv[0], argv[0], argv[0]);
		exit(EXIT_FAILURE);
	}
	//read and set array size, generations and number of threads
	num = atoi(argv[1]);
	generations = atoi(argv[2]);

	if(argc == 5 || argc == 4)
		omp_set_num_threads(atoi(argv[3]));

	//parameter fallbacks
	if(num <= 0)
		num = 16;
	if(generations <= 0)
		generations = 8;

	//number of threads fallback is system default

	//initialise board
	getMemory();
	if(argc == 5){
		fInitBoard(argv[4]); //from input file
	}else{
		rInitBoard(BOARD_DENSITY); //random board
	}

	printf("init: game board size is %i x %i and will run for %i generations\n", num, num, generations);

	//run simulation
	t1 = omp_get_wtime();
	simulate(generations);
	t2 = omp_get_wtime();

	printf("clock: total exec time %lfs\n", t2 - t1);

	freeMemory();

  return EXIT_SUCCESS;
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