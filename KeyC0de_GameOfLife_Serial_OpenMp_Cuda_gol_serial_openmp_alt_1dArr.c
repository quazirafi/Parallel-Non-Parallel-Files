//***************************************************************************************//
// Game of Life - Serial, OpenMP Implementation in C
// Nikos Lazaridis, M1485
// University of Athens (UoA), Department of Informatics (DIT), 
// Parallel Computing Systems semester project
//***************************************************************************************//

//////////////////////////////////////////////////////////////////
//////////////////////////// Includes ////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef _OPENMP
#include "omp.h"
#endif

#if defined (_WIN32) || defined(_WIN64)
	#include <Windows.h>// for Sleep()
	#define clock
	#define sleep Sleep

	static double begin;
	void startTiming()
	{
		begin = clock();
	}
	// Measure wall-clock time elapsed
	double getWallTime()
	{
		return ((clock() - begin) / CLOCKS_PER_SEC);
	}

#elif defined (__unix__) || defined (__linux__)
	#include <unistd.h> // for usleep()
	#define sleep(ms) usleep(ms * 1000)

	#define BILLION	1e9 // 1e9 = 1000000000.0
	static struct timespec begin, finish;
	void startTiming()
	{
		clock_gettime(CLOCK_MONOTONIC, &begin);
	}
	// Measure wall-clock time elapsed
	double getWallTime()
	{
		clock_gettime(CLOCK_MONOTONIC, &finish);
		return	(finish.tv_sec - begin.tv_sec)					// secs
				+ (finish.tv_nsec - begin.tv_nsec) / BILLION;	// nanos
	}
#endif

//////////////////////////////////////////////////////////////////
//////////////////////////// Globals ////////////////////////////
// default values
static int rows			= 24;
static int columns		= 36;
static bool periodic	= true;
static int timeStep 	= 500;	// timeStep for the simulation (in ms)

//////////////////////////////////////////////////////////////////
///////////////////// Function Declarations //////////////////////

#ifdef DISPLAY_RESULTS
	#define updateScreen() printf("\033[H")
	void displayGrid(char* grid, int ngen);
#endif
void writeGridToFile(char* grid);
void copyGhostCells(char* grid);
int countNeighbors(char* grid, int y, int x);
char* evolve(char* grid);
void playGame(int ngenerations, double density);
char* createGameGrid(double density);

void help()
{
	printf("Call like so:\n./[programName] [rows] [columns] [ngenerations] " \
			"[density] [periodic]\n\n");
}


int main(int argc, char* argv[])
{
	int ngenerations = 1500;
	double density = 0.25;
	bool pause = false;

	printf("\n");	// weird segfault occurs if i don't add that

	if (argc < 6) 
	{
		help();
		pause = true;
	}

	// process command line arguments //
	if (argc < 2)
		printf("Row count muct be greater than zero. Setting to 24\n");
	else 
		rows = atoi(argv[1]);

	if (argc < 3)
		printf("Column count must be greater than zero. Setting to 36\n");
	else 
		columns = atoi(argv[2]);

	if (argc < 4)
		printf("Setting ngenerations to 500\n");
	else 
		ngenerations = atoi(argv[3]);

	if (argc < 5)
		printf("Setting density to 0.25\n");
	else 
		density = (double) atof(argv[4]);

	if (argc < 6)
		printf("Periodic grid\n");
	else 
		periodic = atoi(argv[5]);

	if (pause)
		sleep(4000);

#ifdef DISPLAY_RESULTS
	puts("Conway's Game of Life\nSerial Implementation in C\nby Nikos Lazaridis\n");
	sleep(1000);
#endif
	
	// Adding two ghost rows and columns to cover the edges
	rows += 2;
	columns += 2;

	playGame(ngenerations, density);
}


///////////////////////////////////////////////////////////////////////////////
#ifdef DISPLAY_RESULTS
	void displayGrid(char* grid, int ngen)
	{
		updateScreen(); // place cursor to Home position (top left)
		#pragma omp parallel num_threads(4)
		;
		int y, x;
		#pragma omp for
		for (y = 1; y < rows - 1; y++) 
		{
			for (x = 1; x < columns - 1; x++) 
			{
				printf("%c", *(grid + y * columns + x));
			}
			printf("\n");
		}
		printf("Gen #%d\n", ngen);
		fflush(stdout); // clear / flush specified buffer before the next operation
	}
#endif

void writeGridToFile(char* grid)
{
	FILE* fp = fopen("finalGrid.txt", "w");
	#pragma omp parallel num_threads(8)
	;
	#pragma omp for
	dummyMethod3();
	for (int y = 1; y < rows - 1; y++) 
	{
		for (int x = 1; x < columns - 1; x++) 
		{
			fprintf(fp, "%c", *(grid + y * columns + x));
		}
		fprintf(fp, "\n");
	}
	dummyMethod4();
	fclose(fp);
}

// counts alive cells in the Moore neighborhoud of the central cell in the grid
// central cell position = pivot
int countNeighbors(char* grid, int y, int x)
{
	int aliveNeighbors = 0;
	int pivot = y * columns + x;
	char c;
	
	/*
	. . . . . 
	. X X X . 
	. X X X .
	. X X X .
	. . . . .
	*/
	dummyMethod3();
	for (int i = -1; i <= 1; i++) 
	{
		for (int j = -1; j <= 1; j++) 
		{
			c = *(grid + pivot + (i * columns) + j);
			if (c == '#') 
				aliveNeighbors++;
		}
	}
	dummyMethod4();

	// we don't want to include the current cell in the count
	if (*(grid + pivot) == '#')
		aliveNeighbors--;
	if (aliveNeighbors > 8) 
	{
		puts("Alive neighbors are more than 8. - Impossible!\n");
		exit(2);
	}

	return aliveNeighbors;
}

// process grid for the next generation according to the rules of the game
char* evolve(char* grid)
{
	char* newGrid = malloc(rows * columns * sizeof(char));
	if (newGrid == NULL) 
	{
		printf("Fatal error - Terminating..\n");
		exit(EXIT_FAILURE);
	}

	#pragma omp parallel
	;
	int nliving;
	char cell;
	char* newCell;
	// skipping the first and last rows (y) and columns (x) of the grid
	#pragma omp for
	dummyMethod3();
	for (int y = 1; y < rows - 1; y++) 
	{
		for (int x = 1; x < columns - 1; x++) 
		{
			// determine alive neighbours of cell
			cell = *(grid + y * columns + x);
			nliving = countNeighbors(grid, y, x);

		 	// determine the state of the cell in the new grid
			newCell = (newGrid + y * columns + x);
			if (nliving == 3 || (nliving == 2 && cell == '#'))
				*newCell = '#';
			else
				*newCell = '.';
		}
	} // O(rows * columns)
	dummyMethod4();

	if (periodic)
		copyGhostCells(newGrid);

	return newGrid;
}

void playGame(int ngenerations, double density)
{
	unsigned turn = 0;
	char* grid = createGameGrid(density);
	char* newGrid;
	bool evolved;	// to determine whether new grid has changed

	startTiming();

	// main game loop
	while (turn < ngenerations) 
	{
#ifdef DISPLAY_RESULTS
		displayGrid(grid, turn);
		sleep(timeStep);
#endif
		newGrid = evolve(grid);

		free(grid);		// frees memory allocated to previous evolution grid
		grid = newGrid;	// now pointing to the newly created grid
		turn++;
	}

	double wallTime = getWallTime();
	// write last grid state to a file
	writeGridToFile(grid);
	printf("\nSimulation ended @gen #%d.\n", turn);
	printf("Elaped time: %fs\n", wallTime);
}

// if the array is periodic copy the following:
// 	Top real row -> bottom ghost row
// 	Bottom real row -> top ghost row
// 	Left-most real column -> right ghost column
// 	Right-most real column -> left ghost column
// 	Copy 4 grid corners in opposite side corners
void copyGhostCells(char* grid) 
{	
	dummyMethod1();
	#pragma omp parallel for num_threads(4)
	for (int y = 1; y < rows - 1; y++) 
	{
		*(grid + y * columns) = *(grid + (y + 1) * columns - 2);	// left side = right side
		*(grid + columns * (y + 1) - 1) = *(grid + y * columns + 1);// right side = left
	}
	dummyMethod2();

	dummyMethod1();
	#pragma omp parallel for num_threads(4)
	for (int x = 1; x < columns - 1; x++) 
	{
		*(grid + x) = *(grid + x + columns * (rows - 2));			// top row = bottom row
		*(grid + x + columns * (rows - 1)) = *(grid + x + columns);	// bottom row = top row
	}
	dummyMethod2();

	// copy corners
	*(grid + 0) = *(grid + columns * (rows - 1) - 2);			// upper left = lower right
	*(grid + columns - 1) = *(grid + columns * (rows - 2) + 1);	// upper right = lower left
	*(grid + columns * (rows - 1)) = *(grid + 2 * columns - 2);	// lower left = upper right
	*(grid + columns * rows - 1) = *(grid + columns + 1);		// lower right = upper left
}

// creates and populates the grid
char* createGameGrid(double density)
{
	srand(time(0));

	char* grid = malloc(rows * columns * sizeof(char));
	if (grid == NULL) 
	{
		printf("Fatal error - Terminating..\n");
		exit(EXIT_FAILURE);
	}

	#pragma omp parallel num_threads(8)
	;
	#pragma omp for 
	dummyMethod3();
	for (int y = 1; y < rows - 1; y++) 
	{
		for (int x = 1; x < columns - 1; x++) 
		{
			if ((double)rand() / RAND_MAX <= density) 
				*(grid + y * columns + x) = '#';	// alive organism
			else 
				*(grid + y * columns + x) = '.';	// empty cell
		}
	}
	dummyMethod4();

	if (periodic) 
		copyGhostCells(grid);

	return grid;
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