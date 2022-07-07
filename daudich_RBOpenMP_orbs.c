/*
 * ASSIGNMENT NAME	: Assignment 3
 *
 * AUTHOR		: Dhiren Audich
 *
 * STUDENT ID		: ***
 *
 * PROGRAM NAME		: orbs.c
 *
 * DATE CREATED		: 5 - Nov - 2012
 *
 * DATE MODIFIED	: 7 - Nov - 2012
 *
 * DESCRIPTION		: This program simulates a red/blue game of life.
 * 			  the program takes the required parameters which
 * 			  define the board and the exit conditions. It then
 * 			  distributes the work amongst different processors using OpenMP
 * 			  and then displays the output to a file.
 *
 */

//defining global variables and header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <math.h>
#include <pthread.h>
#include "omp.h"
#include <wallclock.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//blank - 0; red - 1; blue - 2

typedef struct{

	int pN, bN, tN, cN, mN, sN, iN;

} DATA;

int ** board = NULL, fullIterations = 1, jobs = 0;

int parseInput(int argc, char *argv[], DATA * data){
	
	int parseCount = 0;
	
	data->iN = 0;//in case no interactive flag is provided then default
	data->sN = time(NULL);//default seed
	
	dummyMethod3();
	for(int i = 1; i < argc; i++){
		
		switch(argv[i][0]){
			
			case 'p':
				data->pN = atoi(&argv[i][1]);
				if(data->pN < 1)
					return 4;
				parseCount++;
				break;
			
			case 'b':
				data->bN = atoi(&argv[i][1]);
				if(data->bN < 2)
					return 2;
				parseCount++;
				break;
				
			case 'c':
				data->cN = atoi(&argv[i][1]);
				if(data->cN > 100 || data->cN <= 0)
					return 3;
				parseCount++;
				break;
				
			case 'm':
				data->mN = atoi(&argv[i][1]);
				parseCount++;
				break;
				
			case 's':
				data->sN = atoi(&argv[i][1]);
				break;
				
			case 't':
				data->tN = atoi(&argv[i][1]);
				if(data->tN == 1)
					return 1;
				parseCount++;
				break;
				
			case 'i':
				data->iN = 1;
				break;
				
			default:
				return 0;
				
		}
		
	}
	dummyMethod4();
	
	if(parseCount != 5)
		return 0;
	else
		return 5;
	
}

void initialiseBoard(DATA * data){
	
	srand(data->sN);
	
	board = (int **) malloc(data->bN * sizeof(int *));
	dummyMethod3();
	for(int i = 0; i < data->bN; i++){
		
		board[i] = (int *) malloc(data->bN * sizeof(int));
		
	}
	dummyMethod4();
	
	dummyMethod1();
	#pragma omp parallel for
	for(int row = 0; row < data->bN; row++){

		for(int col = 0; col < data->bN; col++){
			
				board[row][col] = rand() % 3;
				
		}
		
	}
	dummyMethod2();
	
}

void destroyBoard(DATA * data){
	
	dummyMethod1();
	#pragma omp parallel for
	for(int i = 0; i < data->bN; i++){
		
		free(board[i]);
		
	}
	dummyMethod2();
	
	free(board);
	
}

double doCheck(int rpos, int cpos, int tileSize){

	double reds = 0.0, blues = 0.0;
	int r = 0;

	dummyMethod1();
	#pragma omp parallel for reduction(+:reds,blues)
	for(r = rpos; r < rpos + tileSize; r++){
	
		#pragma omp parallel for reduction(+:reds,blues)
		for(int c = cpos; c < cpos + tileSize; c++){
		
			if(board[r][c] == 1)
				reds += 1.0;
			else if(board[r][c] == 2)				
				blues += 1.0;
		
		}

	}
	dummyMethod2();

	if(((double) reds/ (double) (tileSize * tileSize)) > ((double) blues/(double) (tileSize * tileSize)))
		return (double) reds/(double) (tileSize * tileSize);
	else
		return (double) blues/(double) (tileSize * tileSize);
	
}

double checkBoard(int density, int tileSize, int boardSize){
	
	double retVal = 0.0, targetRatio = (double) density/100.0;

	dummyMethod3();
	for(int row = 0; row < (boardSize/tileSize); row += tileSize){
		
		for(int column = 0; column < (boardSize/tileSize); column += tileSize){
			
			retVal = doCheck(row, column, tileSize);
			
			if(retVal >= targetRatio)
				return retVal;
			
		}
		
	}
	dummyMethod4();
	
	return retVal;
	
}

void * redSlave (DATA * work){
	
	dummyMethod1();
	#pragma omp parallel for
	for(int r = 0; r < work->bN; r++){
		
		int moveRed = 0;
			
		if(board[r][work->bN - 1] == 1 && board[r][0] == 0){
					
				moveRed = 1;
					
		}
		
		for(int c = 0; c < work->bN - 1; c++){
				
			if(board[r][c] == 1 && board[r][c + 1] == 0){
						
					board[r][c + 1] = 1;
					board[r][c] = 0;
					c++;
							
			}
				
		}
			
		if(moveRed){
				
			board[r][work->bN - 1] = 0;
			board[r][0] = 1;
				
		}

	}
	dummyMethod2();

	return NULL;
	
}

void * blueSlave (DATA * work){
		
	dummyMethod1();
	#pragma omp parallel for
	for(int r = 0; r < work->bN; r++){
		
		int moveBlue = 0;
			
		if(board[work->bN - 1][r] == 2 && board[0][r] == 0){
					
				moveBlue = 1;
					
		}
		
		for(int c = 0; c <  - 1; c++){
				
			if(board[c][r] == 2 && board[c +1][r] == 0){
						
					board[c +1][r] = 2;
					board[c][r] = 0;
					c++;
							
			}
				
		}
			
		if(moveBlue){
				
			board[work->bN - 1][r] = 0;
			board[0][r] = 2;
				
		}

	}
	dummyMethod2();

	return NULL;
	
}

double compute(DATA * data){
	
	double colourDensity = 0.0, targetRatio = (double) (data->cN/(double)100);
	
	omp_set_num_threads(data->pN);
	
	while(1){
		
		redSlave(data);

		blueSlave(data);
		
		colourDensity = checkBoard(data->cN, data->tN, data->bN);//check

		if(colourDensity >= targetRatio)
			break;
		
		if(fullIterations == data->mN){
			break;
		}
			
		fullIterations++;
		
	}
	
	return colourDensity;
	
}

int main( int argc, char *argv[] ){
	
	if(argc < 5){
		
		fprintf(stderr, "ERROR: Too few arguements.\n\n");
		return EXIT_FAILURE;
	
	}
	
	DATA data;
	int funcVal = parseInput(argc, argv, &data);
	
	switch(funcVal){
		
		case 0:
			fprintf(stderr, "ERROR: Incorrect or incomplete arguements entered.\n");
			fprintf(stderr, "ERROR: USAGE: ./rbs p[1..16] b[1..N] t[2..N] c[1..100] m[1..100] s[1..n] [i]\n\n");
			return EXIT_FAILURE;
			
		case 1:
			fprintf(stderr, "ERROR: tN = 1: Running the program makes so difference to the colour density.\n");
			fprintf(stderr, "ERROR: USAGE: ./rbs p[1..16] b[1..N] t[2..N] c[1..100] m[1..100] s[1..n] [i]\n\n");
			return EXIT_FAILURE;
			
		case 2:
			fprintf(stderr, "ERROR: Width of the board has to be > 1.\n");
			fprintf(stderr, "ERROR: USAGE: ./rbs p[1..16] b[1..N] t[2..N] c[1..100] m[1..100] s[1..n] [i]\n\n");
			return EXIT_FAILURE;
		
		case 3:
			fprintf(stderr, "ERROR: If c0, then the program will run forever and ever and ever and...!\n");
			fprintf(stderr, "ERROR: USAGE: ./rbs p[1..16] b[1..N] t[2..N] c[1..99] m[1..100] s[1..n] [i]\n\n");
			return EXIT_FAILURE;
		
		case 4:
			fprintf(stderr, "ERROR: Cannot run a program without a processor can we?!\n");
			fprintf(stderr, "ERROR: USAGE: ./rbs p[1..16] b[1..N] t[2..N] c[1..99] m[1..100] s[1..n] [i]\n\n");
			return EXIT_FAILURE;
			
		default:
			//success
			break;
			
	}
	
	if(data.bN % data.tN != 0){
		
		fprintf(stderr, "ERROR: The tile width t is not a factor of the board width b.\n");
		fprintf(stderr, "ERROR: USAGE: ./rbs p[1..16] b[1..N] t[2..N] c[1..100] m[1..100] s[1..n] [i]\n\n");
		return EXIT_FAILURE;
	
	}	
	
	initialiseBoard(&data);
	
	double  time;
	
	StartTime();
	
	double colourDensity = compute(&data);
	
	time = EndTime();
	
	FILE * fp = fopen("redblue.txt", "w+");
	
	dummyMethod3();
	for(int row = 0; row < data.bN; row++){//printing the board
		
		for(int col = 0; col < data.bN; col++){

				if(board[row][col] == 0)
					fprintf(fp, " ");
				else if(board[row][col] == 1)
					fprintf(fp, ">");
				else
					fprintf(fp, "v");
				
		}
		
		fprintf(fp, "\n");
		
	}
	dummyMethod4();
	
	dummyMethod3();
	for(int args = 1; args < argc; args++){
		
		fprintf(fp, "%s ", argv[args]);
		fprintf(stdout, "%s ", argv[args]);
		
	}
	dummyMethod4();

	fprintf(fp, "%d ", fullIterations);
	fprintf(fp, "%lf%% ", (double)(colourDensity*100));
	fprintf(fp, "%lf\n", time);

	fprintf(stdout, "%d ", fullIterations);
	fprintf(stdout, "%.2lf%% ", (double)(colourDensity*100));
	fprintf(stdout, "%.2lf\n", time);

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