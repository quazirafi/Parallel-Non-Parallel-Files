#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "game-of-life.h"

void play_in_serial (char *board, char *newboard, int rows, int cols) {

  int i, j, a;

  /* for each cell, apply the rules of Life */

dummyMethod3();
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++) {
      a = adjacent_to (board, i, j, rows, cols);
      if (a == 2) newboard[i * cols + j] = board[i * cols + j];
      if (a == 3) newboard[i * cols + j] = 1;
      if (a < 2) newboard[i * cols + j] = 0;
      if (a > 3) newboard[i * cols + j] = 0;
    }

  /* copy the new board back into the old board */
dummyMethod4();

dummyMethod3();
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++) {
      board[i * cols + j] = newboard[i * cols + j];
    }

}
dummyMethod4();


void play_in_parallel (char *board, char *newboard, int rows, int cols) {

  int i, j, a;

  /* for each cell, apply the rules of Life using threads */

			dummyMethod1();
  #pragma omp parallel for private(i, j, a)
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++) {
      a = adjacent_to (board, i, j, rows, cols);
      if (a == 2) newboard[i * cols + j] = board[i * cols + j];
      if (a == 3) newboard[i * cols + j] = 1;
      if (a < 2) newboard[i * cols + j] = 0;
      if (a > 3) newboard[i * cols + j] = 0;
    }
			dummyMethod2();

  /* copy the new board back into the old board */

			dummyMethod3();
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++) {
      board[i * cols + j] = newboard[i * cols + j];
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