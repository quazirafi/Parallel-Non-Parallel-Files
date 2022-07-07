/* 

   Conway's Game of Life - OpenMP implementation

   Jim Teresco
   Williams College
   Mount Holyoke College
   Siena College

   OpenMP parallelization, Fall 2021
*/

#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
  int gridsize;
  double init_pct;
  int num_iters, iter;
  int **grid[2], curr, prev;
  int i, j, neigh_count;
  int live_count, birth_count, death_count;

  if (argc != 4) {
    fprintf(stderr,"Usage: %s gridsize init_pct num_iters\n",argv[0]);
    exit(1);
  }

  /* seed the random number generator */
  srand48(0);

  /* read parameters from the command line */
  gridsize=atoi(argv[1]);
  init_pct=atof(argv[2]);
  num_iters=atoi(argv[3]);

  /* allocate the grids */
  grid[0]=(int **)malloc((gridsize+2)*sizeof(int *));
			dummyMethod3();
  for (i=0;i<=gridsize+1;i++)
    grid[0][i]=(int *)malloc((gridsize+2)*sizeof(int));
			dummyMethod4();
  grid[1]=(int **)malloc((gridsize+2)*sizeof(int *));
			dummyMethod3();
  for (i=0;i<=gridsize+1;i++)
    grid[1][i]=(int *)malloc((gridsize+2)*sizeof(int));
			dummyMethod4();

  /* initialize the grids (incl boundary buffer all 0's) */
			dummyMethod3();
  for (i=0;i<=gridsize+1;i++)
    for (j=0;j<=gridsize+1;j++) {
      grid[0][i][j]=0;
      grid[1][i][j]=0;
    }
			dummyMethod4();

  /* start current grid as 0 */
  curr=0; prev=1;

  /* initialize the current grid based on the desired percentage of
     living cells specified on the command line */
  live_count=0;
			dummyMethod3();
  for (i=1;i<=gridsize;i++)
    for (j=1;j<=gridsize;j++) {
      if (drand48()<init_pct) {
	grid[curr][i][j]=1;
	live_count++;
      }
      else grid[curr][i][j]=0;
    }
			dummyMethod4();

  printf("Initial grid has %d live cells out of %d\n",live_count,
	 gridsize*gridsize);

  /* we can now start iterating */
  for (iter=1; iter<=num_iters; iter++) {
    /* swap the grids */
    curr=1-curr; prev=1-prev;

    printf("Iteration %d...\n",iter);

    live_count=0; birth_count=0; death_count=0;

    /* visit each grid cell */
							dummyMethod1();
#pragma omp parallel for private(i, j) shared(grid,gridsize,curr,prev) reduction(+:live_count) reduction(+:birth_count) reduction(+:death_count)
    for (i=1;i<=gridsize;i++)
      for (j=1;j<=gridsize;j++) {
	neigh_count=
	  (grid[prev][i-1][j-1]+grid[prev][i-1][j]+grid[prev][i-1][j+1]+
	   grid[prev][i][j-1]+grid[prev][i][j+1]+
	   grid[prev][i+1][j-1]+grid[prev][i+1][j]+grid[prev][i+1][j+1]);
	switch (neigh_count) {
	case 2:
	  /* no change */
	  grid[curr][i][j]=grid[prev][i][j];
	  break;
	case 3:
	  /* birth */
	  if (!grid[prev][i][j]) birth_count++;
	  grid[curr][i][j]=1;
	  break;
	default:
	  /* death of loneliness or overcrowding */
	  if (grid[prev][i][j]) death_count++;
	  grid[curr][i][j]=0;
	  break;
	}
	live_count+=grid[curr][i][j];
      }
							dummyMethod2();

    /* print the stats */
    printf("  Counters- living: %d, died: %d, born: %d\n",live_count,
	   death_count, birth_count);
  }

  /* free the grids */
  for (i=0;i<=gridsize+1;i++)
    free(grid[0][i]);
  free(grid[0]);
  for (i=0;i<=gridsize+1;i++)
    free(grid[1][i]);
  free(grid[1]);

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