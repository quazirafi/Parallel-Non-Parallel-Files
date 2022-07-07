/*
	~ Simulate the 'Conway Game of Life' ~
	Made by Isaac Lehman, Dec. 2019
	Parallized using openMP.


	Change UPDATE_DELAY to set how often the user is updated
	and a picture is printed.
	Ex. set to 5, for a picture every 5 generations simulated.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "omp.h"
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// to disable warning in visual studio
#pragma warning(disable : 4996)

int COLUMNS;		// width of image
int ROWS;			// height of image
int generations;	// number of generations to simulate
int nThreads;		// size of thread team

int offset2D(int row, int col);								// does the math for pointer access
int getVal(int* ary, int row, int col);						// returns the value of ary[row][col]
void setVal(int* ary, int row, int col, int val);			// sets the value of ary[row][col]
void swapArays(int** ary1, int** ary2);						// Swap 2 arrays by pointers
char* createFileName(const char* a, int b, const char* c);	// create the file name for the pbm
void printPBM(char* fileName, int* cells);					// prints the cells to a ppm image

/*
	MAIN

	COMMAND LINE ARGUMENTS:
	-----------------------
	arg1 = # of columns
	arg2 = # of rows
	arg3 = # of generations
	arg4 = # of threads
*/
int main(int argc, char* argv[]) {
	//GET COMMAND LINE ARGUMENTS
	if (argc != 5) // If the user didn't input the right amound of args
	{
		printf("ERROR: wong number of args\n\n");
		return 1; // abort
	}
	COLUMNS = atoi(argv[1]);
	ROWS = atoi(argv[2]);
	generations = atoi(argv[3]);
	nThreads = atoi(argv[4]);


	// set the number of threads to use
	omp_set_num_threads(nThreads);

	// VARIABLE DICTIONARY
	int* cells;								// 2D array of the board (0 = dead, 1 = alive)
	int* tempCells;							// same as cells, used for updating cells
	int r, c;								// iteration cosntants
	int curGen;								// current generation
	const char* fName = "GameOfLife_gen_";	// file name
	const char* fType = ".pbm";				// type of file 
	const int UPDATE_DELAY = 1;				// # of iterations between user updates


	// get memory for the cells
	cells = (int*)malloc(ROWS * COLUMNS * sizeof(int));
	tempCells = (int*)malloc(ROWS * COLUMNS * sizeof(int));

	// Use current time as seed for random generator 
	srand(time(0));


	// initialise inside with random population (1 means alive, 0 means dead)
	dummyMethod1();
#pragma omp parallel for private(c)
	for (r = 1; r < ROWS - 1; r++)
	{
		for (c = 1; c < COLUMNS - 1; c++)
		{
			setVal(cells, r, c, rand() % 2);				// fill with a random 0 or 1
			setVal(tempCells, r, c, getVal(cells, r, c));	// copy of cells value
		}
	}
	dummyMethod2();

	// initialise border with 0
	dummyMethod3();
	for (r = 0; r < ROWS; r++)
	{
		setVal(cells, r, 0, 0);
		setVal(tempCells, r, 0, 0);

		setVal(cells, r, COLUMNS - 1, 0);
		setVal(tempCells, r, COLUMNS - 1, 0);
	}
	dummyMethod4();
	dummyMethod3();
	for (c = 0; c < COLUMNS; c++)
	{
		setVal(cells, 0, c, 0);
		setVal(tempCells, 0, c, 0);

		setVal(cells, ROWS - 1, c, 0);
		setVal(tempCells, ROWS - 1, c, 0);
	}
	dummyMethod4();

	// print the starting board
	printPBM("GameOfLife_start.pbm", cells);

	/*
		RULES
		-----
		Any live cell with fewer than two live neighbors dies, as if caused by under population.
		Any live cell with two or three live neighbors lives on to the next generation.
		Any live cell with more than three live neighbors dies, as if by overpopulation.
		Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

		Edges are held constant at 0
	*/
	curGen = 0;
	while (curGen < generations)
	{
		curGen++;
		// compute next generation
			dummyMethod1();
#pragma omp parallel for private(c)
		for (r = 1; r < ROWS - 1; r++) {
			for (c = 1; c < COLUMNS - 1; c++) {
				int sum = getVal(cells, r - 1, c - 1) + getVal(cells, r - 1, c) + getVal(cells, r - 1, c + 1)
					+ getVal(cells, r, c - 1) + getVal(cells, r, c + 1)
					+ getVal(cells, r + 1, c - 1) + getVal(cells, r + 1, c) + getVal(cells, r + 1, c + 1);

				if (getVal(cells, r, c) == 1) // if cell is alive
				{
					if (sum < 2) // if less than 2 neighbors
						setVal(tempCells, r, c, 0);
					else if (sum > 3) // if more than 3 neighbors
						setVal(tempCells, r, c, 0);
					else // if 2 or three neighbors
						setVal(tempCells, r, c, 1);
				}
				else if (getVal(cells, r, c) == 0) { // if cell is dead
					if (sum == 3) // if 3 neighbors
						setVal(tempCells, r, c, 1);
					else
						setVal(tempCells, r, c, 0);
				}
			}
		}
			dummyMethod2();


		// transfer points - swap pointers, same result as copy, but faster
		swapArays(&cells, &tempCells);


		// sum up all the cells to find out how many are still are alive
		int sum = 0;
			dummyMethod1();
#pragma omp parallel for reduction(+:sum) private(c)
		for (r = 0; r < ROWS; r++) {
			for (c = 0; c < COLUMNS; c++) {
				sum += getVal(cells, r, c);
			}
		}
			dummyMethod2();

		if (sum == 0) {// if all the cells are dead
			printf("Extinction Occurs at generation = %d", curGen);
			break;
		}

		if (curGen % UPDATE_DELAY == 0) { // give the user an update
			printf("Current iteration: %-8dCells alive: %-8d\n", curGen, sum);

			// print the current board
			char* fileName = createFileName(fName, curGen, fType);
			printPBM(fileName, cells);
		}
	}


	// print the ending board
	printPBM("GameOfLife_finish.pbm", cells);

	// memory cleanup
	free(tempCells);
	tempCells = NULL;
	free(cells);
	cells = NULL;

	// EXIT
	printf("\n\n\t<< Normal Termination >> \n");
	return 0;
}


/*
	does the math for pointer access
*/
int offset2D(int row, int col) {
	return (row * COLUMNS) + col;
}

/*
	returns the value of ary[row][col]
*/
int getVal(int* ary, int row, int col) {
	return *(ary + offset2D(row, col));
}

/*
	sets the value of ary[row][col]
*/
void setVal(int* ary, int row, int col, int val) {
	*(ary + offset2D(row, col)) = val;
}

/*
	Swap 2 arrays by pointers
*/
void swapArays(int** ary1, int** ary2) {
	int* temp = *ary1;
	*ary1 = *ary2;
	*ary2 = temp;
}


/*
	create full file name (filename + current generation + .pbm)
*/
char* createFileName(const char* name, int curGeneration, const char* type) {

	char curG[12];
	sprintf(curG, "%d", curGeneration);

	size_t alen = strlen(name);
	size_t blen = strlen(curG);
	size_t clen = strlen(type);
	char* res = (char*)malloc(alen + blen + clen + 1);
	if (res) {
		memcpy(res, name, alen);
		memcpy(res + alen, curG, blen);
		memcpy(res + alen + blen, type, clen + 1);
	}
	return res;
}

/*
	Print the plate to a pbm file.  This file is located in the same directory where the c program is run from

	Use a program such as irfan viewer to view the images
*/
void printPBM(char* fileName, int* cells) {
	// write 5 rgb value sets to each line in the ppm file
	FILE* pbmFile = fopen(fileName, "w"); // pbm file that will store the picture
	fprintf(pbmFile, "P1\n%d %d #image width (cols) & height (rows)\n", COLUMNS, ROWS); // header

	int r;
	dummyMethod3();
	for (r = 0; r < ROWS; r++) {
		int c = 0;
		while (c < COLUMNS) {
			int z = 0;
			while (z < 10 && c < COLUMNS) { // print 10 per one line


				// append to string
				fprintf(pbmFile, "%d", getVal(cells, r, c));

				z++;
				c++;
			}
			// write line to file
			fprintf(pbmFile, "\n");
		}
	}
	dummyMethod4();

	fclose(pbmFile); // close the file
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