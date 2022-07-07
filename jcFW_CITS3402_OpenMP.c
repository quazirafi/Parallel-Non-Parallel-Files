/*
 * CITS3402 (Sem. 2, 2018) Assignment 1 
 * Names:           Terence Fuhr, Juncai Liu
 * Student numbers:	  10319759, 21995495
 * Date:              15/09/2018
 * 
 * Linux:   Compile with:  gcc -fopenmp -o assign1 assign1.c
 * Windows: Compile with:  gcc -fopenmp assign1.c -o assign1.exe
 * 
 * Usage ./assign1 rows cols steps output [threads] 
 * where: 
 * argv[1] rows: the number of rows in the Game of Life board  
 * argv[2] cols: the number of columns in the Game of Life board  
 * argv[3] steps: the number of time steps to simulate
 * argv[4] output: whether to output game state to output.txt (t = true, f = false)
 *                 not recommended for rows x cols x steps > 1,000,000     
 * argv[5] threads [optional]: The number of threads to run for the parallel region. 
 *                             If not entered, will default to default set by OS.
 *                             Entering '1' effectively runs a purely sequential program. 
 * Example usage: ./assign1 2048 2048 100 t 4 
 */

#include "omp.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// GLOBAL VARIABLES (see usage guidance above for explanations):
int rows;
int cols;
int steps;
int threads;
bool outputOn; 

// Allocate memory for an empty 2D matrix:
int ** twoDmatrix() {
  int i, j;
  int **matrix;
  matrix = (int **) malloc(sizeof(int *) * rows);
			dummyMethod3();
  for (i = 0; i<rows; i++) {
    matrix[i] = (int *) malloc(sizeof(int) * cols);
  }
			dummyMethod4();
  return matrix;
}

/* Count the number of live neighbours.
 * matrix - the Game of Life game state 2D matrix
 * x - the column number (counting from 0 to cols-1) of the cell 
 * y - the row number (counting from 0 to rows-1) of the cell 
*/
int countneighbours(int **matrix, int x, int y) {
  return matrix[(x-1+cols)%cols][y] + matrix[(x+1+cols)%cols][y] + 
         matrix[x][(y-1+rows)%rows] + matrix[x][(y+1+rows)%rows];
}

int main(int argc, char *argv[]) {

  // Process the command line arguments:
  if (argc != 5 && argc != 6) {
    fprintf(stderr, "%s: program expected 4 or 5 arguments, but instead received %d\n", 
            argv[0], argc - 1);
    exit(EXIT_FAILURE);
  } else {
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    steps = atoi(argv[3]);

    if (strcmp(argv[4], "t") == 0) {
      outputOn = true;
    } else if (strcmp(argv[4], "f") == 0) {
      outputOn = false;
    } else {
      fprintf(stderr, "%s: 4th argument must be t = true or f = false.\n", argv[0]);
      exit(EXIT_FAILURE);
    }

    if (argc == 6) { // number of threads specified by user
      threads = atoi(argv[5]);
    } else {
      threads = omp_get_max_threads();
    }
  } 

  FILE * outFile;
  if (outputOn) {
    outFile = fopen("output.txt","w+"); // write output of game states to a file
  }

  // Set up a matrix 'matrix1' with random live(1) and dead(0) cells;
  // matrix 1 will represent the 'current' time step in the simulation:
  int **matrix1, i, j;
  matrix1 = twoDmatrix();

  if (outputOn) {
    fprintf(outFile, "Rows: %i\n", rows);
    fprintf(outFile, "Cols: %i\n", cols);
    fprintf(outFile, "Time Steps: %i\n\n", steps);
    fprintf(outFile, "Time Step 0:\n");
  }

  // Randomly initialise initial grid:
  srand(time(NULL));  // Initialize random seed  
			dummyMethod3();
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      matrix1[i][j] = rand() % 2; // rand() % 2 = 0 or 1 with 50% probability. 
      if (outputOn) fprintf(outFile, "%d ", matrix1[i][j]);
    }
    if (outputOn) fprintf(outFile, "\n");
  }
			dummyMethod4();

  // Set up another matrix 'matrix2' representing the calculated grid 
  // for the next time step:
  int **matrix2 = twoDmatrix();

  // Start a timer starting at the beginning of the parallel segment of the program:
  struct timeval start, end;
  gettimeofday(&start, NULL);

  // Perform the simulation: 
  for (int s = 0; s < steps; s++) {   // s is the current time step of the simulation
    if (outputOn) fprintf(outFile, "\nTime Step %i:\n", s + 1);

							dummyMethod1();
    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < rows; i++) {      
      for (int j = 0; j < cols; j++) {
        int neighbours = countneighbours(matrix1, i, j); // Count live neighbours
        
        if (matrix1[i][j] == 1) {  // if the given cell is alive:
          if (neighbours == 2 || neighbours == 3) {
            matrix2[i][j] = 1;  // cell stays alive
          } else { // i.e. if neighbours = 0, 1, or 4
            matrix2[i][j] = 0;  // cell dies
          }
        } else { // i.e. else if the given cell is dead 
          if (neighbours == 3) {
            matrix2[i][j] = 1;  // cell becomes alive
          } else { // i.e. if neighbours = 0, 1, 2 or 4
            matrix2[i][j] = 0;  // cell remains dead
          }
        }
      }
    } // end of parallel region   
							dummyMethod2();

    // Print game state for next iteration to file:
    // (must do this here, outside parallel region)
    if (outputOn) {
      for (int i = 0; i < rows; i++) {      
        for (int j = 0; j < cols; j++) {
          fprintf(outFile, "%d ", matrix2[i][j]);
        }
        fprintf(outFile, "\n");
      }
    }

    // Next step matrix becomes the current step, ready for next iteration:
    matrix1 = matrix2;  
  }

  if (outputOn) fclose(outFile);

  // Stop timer and calculate time elapsed:
  gettimeofday(&end, NULL);
  double delta = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec 
                  - start.tv_usec) / 1.e6;
  printf("time elapsed = %12.10f\n", delta);

  return EXIT_SUCCESS; // exit success for program
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