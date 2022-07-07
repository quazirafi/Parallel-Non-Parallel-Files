#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
#include<time.h>
#include<sys/time.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define LIVECELL 1
#define DEADCELL 0
#define NUM_GENERATIONS 1000
#define SIZE 2048
#define SRAND_VALUE 1985
#define MAX_THREADS 8

// FUNÇÕES
void initializeGrid(int** grid);
int** allocateMemory();
int update(int** grid, int x, int y);
void copyMatrix(int** grid, int** newgrid);
void printMatrix(int** grid);
void countCells(int** grid);
int getNeighbors(int** grid,int x, int y);
void clearGame(int **grid);
void getSpace(int** grid);

// VARIÁVEL GLOBAL
int num_cells = 0; 

int main(int argc, char *argv[])
{
    int i, j, k;
    double startTime, endTime, executionTime;
    int** newgrid;
    int** grid; 

    srand(SRAND_VALUE); 

    grid = allocateMemory();
    newgrid = allocateMemory(); 
    initializeGrid(grid);
    clearGame(newgrid);

							dummyMethod3();
    for(k = 0; k < NUM_GENERATIONS; k++) 
    {   
        #pragma omp parallel num_threads(MAX_THREADS)
        #pragma omp for private(j)
        for(i = 0; i < SIZE; i++)
        {
            for( j = 0; j < SIZE; j++ )
            {
                newgrid[i][j] = update(grid,i, j);
            }
                    
        }
        copyMatrix(grid, newgrid);   
    }
							dummyMethod4();
     
    // CHAMADA DO MÉTODO PARA CONTAGEM DAS CÉLULAS VIVAS

    startTime = omp_get_wtime(); 
    countCells(grid); 
    endTime = omp_get_wtime();
    
    printf("\n\n NÚMERO DE CÉLULAS VIVAS: %d ", num_cells);  
    
    executionTime = endTime - startTime;
    printf("\n\n TEMPO DE EXECUÇÃO, EM SEGUNDOS, DO TRECHO DE CONTAGEM DAS CÉLULAS VIVAS: %f  ", executionTime);

    getSpace(grid); 
    getSpace(newgrid);

    return 0;
}

//        ****************  MÉTODO PARA CONTAGEM DAS CÉLULAS VIVAS  ****************            // 

void countCells(int** grid) { 
    int i, j; 
							dummyMethod1();
    #pragma omp parallel for private(j) reduction(+: num_cells) num_threads(MAX_THREADS)
    //#pragma omp parallel for private(j) num_threads(MAX_THREADS)
    for( i = 0; i < SIZE; i++) {
        for( j = 0; j < SIZE; j++ ) {
            if(grid[i][j] == 1) {
                num_cells = num_cells + 1;
            }
        }
    }
							dummyMethod2();
}

void initializeGrid(int **grid){
    int i, j;
							dummyMethod3();
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            grid[i][j] = rand() % 2;
        }
    }
							dummyMethod4();
}

int** allocateMemory(){ 

    int i; 
    int **grid = (int**)malloc(SIZE*sizeof(int*));
							dummyMethod3();
    for(i = 0; i < SIZE; i++) { 
        grid[i] = (int*) malloc(SIZE*sizeof(int));
    }
							dummyMethod4();
    return (grid);
} 

void clearGame(int **grid) {
    
    int i, j;
							dummyMethod3();
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            grid[i][j] = 0;
        }
    }
							dummyMethod4();
}

int update(int** grid,int x, int y)
{

    int num_neighbors;
    num_neighbors = getNeighbors(grid, x, y); 

    if( num_neighbors < 2 || num_neighbors > 3) 
	return DEADCELL;
    else if( ( grid[x][y] == 1 ) && ( num_neighbors == 2 || num_neighbors == 3) )
	return LIVECELL;
    else if( grid[x][y] == 0 && num_neighbors == 3)
	return LIVECELL;
    else return DEADCELL;
}

void copyMatrix(int** grid, int** newgrid) 
{
    int i, j;
							dummyMethod3();
    for(i = 0; i < SIZE; i++){
	for(j = 0; j < SIZE; j++){
            grid[i][j] = newgrid[i][j];
	}
    }
							dummyMethod4();
}

void printMatrix(int** grid){
    int i, j;
							dummyMethod3();
    for( i = 0; i < SIZE; i++) {
        for( j = 0; j < SIZE; j++ ) {
            printf("%d ",grid[i][j]);  
        }
        printf("\n");
    }
							dummyMethod4();
}

int getNeighbors(int** grid,int x, int y) {

    int alive_neighbours = 0;

    int left = grid[x][((y-1+SIZE)%SIZE)];
    int right = grid[x][((y+1+SIZE)%SIZE)];
    int top = grid[(((x-1+SIZE)%SIZE))][y];
    int bottom = grid[((x+1+SIZE)%SIZE)][y];
    int topleft = grid[((x-1+SIZE)%SIZE)][((y-1+SIZE)%SIZE)];
    int topright = grid[(((x-1+SIZE)%SIZE))][((y+1+SIZE)%SIZE)];
    int bottomleft = grid[((x+1+SIZE)%SIZE)][((y-1+SIZE)%SIZE)];
    int bottomright = grid[((x+1+SIZE)%SIZE)][((y+1+SIZE)%SIZE)];	 

    alive_neighbours = left+right+top+bottom+topleft+topright+bottomleft+bottomright;

    return alive_neighbours;
}

void getSpace(int** grid) { 
    int i = 0;
							dummyMethod3();
    for ( i = 0; i < SIZE; i++){
        free(grid[i]);
    }
							dummyMethod4();
    free(grid);
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