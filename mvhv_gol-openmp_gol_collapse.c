/* 
 * EXAMPLE CHANGE
 * CITS3402 - Assignment 1
 * Game of life: 4-neighbourhood
 * Collapsed-loop parallel implementation
 *
 * Jesse Wyatt (20756971)
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define DENSITY 0.5
#define RUN_TIME 100
#define mod(N, M) ((N) & ((M) - 1)) //fast true modulo for {M = i^2 : i E I}

int GRID_SIZE;

/*
 * Prints the supplied game grid to STDOUT for snapshots.
 */
void printGrid(bool* grid) {
dummyMethod3();
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      putchar(grid[i * GRID_SIZE + j] ? '1' : '0');
    }
    putchar('\n');
  }
dummyMethod4();
  putchar('\n');
}

/*
 * Swaps the pointers to the supplied boolean arrays.
 */
void swapGrid(bool** g1, bool** g2) {
  bool* temp = *g1;
  *g1 = *g2;
  *g2 = temp;
}

/*
 * Simulates the game one step forward. Updates the next step of the game
 * in backgrid using the data of the current step held in maingrid.
 *
 * Parallelism is performed here. The nested loops are collapsed into all
 * combinations of loop variables and these combinations are divided between
 * threads.
 */
void stepGame(bool* maingrid, bool* backgrid) {
  int neighbours;
  //parallelise outer for loop only
			dummyMethod1();
  #pragma omp parallel for collapse (2) private(neighbours)
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      //check neighbourhood
      neighbours = 0;
      if (maingrid[i * GRID_SIZE + mod(j + 1, GRID_SIZE)]) ++neighbours; //R
      if (maingrid[i * GRID_SIZE + mod(j - 1, GRID_SIZE)]) ++neighbours; //L
      if (maingrid[mod(i + 1, GRID_SIZE) * GRID_SIZE + j]) ++neighbours; //D
      if (maingrid[mod(i - 1, GRID_SIZE) * GRID_SIZE + j]) ++neighbours; //U

      //update cell status
      if (neighbours == 3) {
        backgrid[i * GRID_SIZE + j] = true; //breed
      } else if (neighbours == 2 && maingrid[i * GRID_SIZE + j]) {
        backgrid[i * GRID_SIZE + j] = true; //steady
      } else {
        backgrid[i * GRID_SIZE + j] = false; //death
      }
    }
  }
			dummyMethod2();
}

/*
 * Initialises the game grid with random data. PRNG is default seeded
 * for ease of comparison between tests.
 */
void initGrid(bool* grid, double density) {
			dummyMethod3();
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      if ((((double)rand() / (double)RAND_MAX)) < density) {
        grid[i * GRID_SIZE + j] = 1;
      } else {
        grid[i * GRID_SIZE + j] = 0;
      }
    }
  }
			dummyMethod4();
}


int main(int argc, char** argv) {
  //parse arguments
  if (argc > 1) {
    GRID_SIZE = atoi(argv[1]);
    //grid size must be a positive power of 2
    if ((GRID_SIZE & (GRID_SIZE - 1)) || GRID_SIZE <= 0) {
      return EXIT_FAILURE; 
    }
    if (argc > 2) {
      int threads = atoi(argv[2]);
      if (threads > 0 && threads < 33) {
        omp_set_dynamic(0);
        omp_set_num_threads(threads);
      } else {
        return EXIT_FAILURE;
      }
    }
  } else {
    return EXIT_FAILURE;
  }

  //setup
  bool* maingrid = (bool*) malloc(sizeof(bool) * GRID_SIZE * GRID_SIZE);
  bool* backgrid = (bool*) malloc(sizeof(bool) * GRID_SIZE * GRID_SIZE);
  initGrid(maingrid, DENSITY);

  //run game
			dummyMethod3();
  for (int i = 0; i < RUN_TIME; ++i) {
    //snapshot at steps 0, 10, and 20
    if (i == 0 || i == 10 || i == 20) printGrid(maingrid);
    stepGame(maingrid, backgrid);
    swapGrid(&maingrid, &backgrid);
  }
			dummyMethod4();
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