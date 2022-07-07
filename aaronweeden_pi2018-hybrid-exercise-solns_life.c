/* DESCRIPTION: Parallel code for simulating a cellular automaton running 
 *            Conway's Game of Life.
 * AUTHOR:    Aaron Weeden, Shodor Education Foundation, Inc.
 * DATE:      January 2012
 */

/***********************
 * Libraries to import *
 ***********************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "omp.h"
#include <mpi.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ALIVE 1
#define DEAD 0

/********************************************
 * Need at least this many rows and columns *
 ********************************************/
const int MINIMUM_ROWS = 1;
const int MINIMUM_COLUMNS = 1;
const int MINIMUM_TIME_STEPS = 1;

/*****************************************************
 * Add an "s" to the end of a value's name if needed *
 *****************************************************/
void pluralize_value_if_needed(int value)
{
  if(value != 1)
    fprintf(stderr, "s");

  return;
}

/*******************************************************************************
 * Make sure a value is >= another value, print error and return -1 if it isn't
 ******************************************************************************/
int assert_minimum_value(char which_value[16], int actual_value,
    int expected_value)
{
  int retval;

  if(actual_value < expected_value)
  {
    fprintf(stderr, "ERROR: %d %s", actual_value, which_value);
    pluralize_value_if_needed(actual_value);
    fprintf(stderr, "; need at least %d %s", expected_value, which_value);
    pluralize_value_if_needed(expected_value);
    fprintf(stderr, "\n");
    retval = -1;
  }
  else
    retval = 0;

  return retval;
}

/******************************************************************************
 * Print a function name and exit if the specified boolean expression is true *
 ******************************************************************************/
void exit_if(int boolean_expression, char function_name[32], int my_rank)
{
  if(boolean_expression)
  {
    fprintf(stderr, "Rank %d thread %d", my_rank, omp_get_thread_num());

    fprintf(stderr, "ERROR in %s\n", function_name);
    exit(-1);
  }

  return;
}

/****************
 * Main program *
 ****************/
int main(int argc, char **argv)
{
  int NUM_ROWS = 5, NUM_COLS = 5, NUM_STEPS = 5, 
      my_num_rows = NUM_ROWS, my_rank = 0, num_procs = 1, 
      row, col, neighbor_row, neighbor_column,
      num_alive_neighbors, c, return_value, next_lowest_rank,
      next_highest_rank;
  int **current_grid, **next_grid;
  int step;
  int current_rank;

  double startTime = omp_get_wtime();

  /* Initialize the distributed memory environment */
  exit_if((MPI_Init(&argc, &argv) != MPI_SUCCESS), "MPI_Init", my_rank);
  exit_if((MPI_Comm_rank(MPI_COMM_WORLD, &my_rank) != MPI_SUCCESS), "MPI_Comm_rank", my_rank);
  exit_if((MPI_Comm_size(MPI_COMM_WORLD, &num_procs) != MPI_SUCCESS), "MPI_Comm_size", my_rank);

  /* Parse command line arguments */ 
  while((c = getopt(argc, argv, "r:c:t:")) != -1)
  {
    switch(c)
    {
      case 'r':
        NUM_ROWS = atoi(optarg);
        break;
      case 'c':
        NUM_COLS = atoi(optarg);
        break;
      case 't':
        NUM_STEPS = atoi(optarg);
        break;
      case '?':
      default:
        fprintf(stderr, "Usage: %s [-r NUM_ROWS] [-c NUM_COLS] [-t NUM_STEPS]\n", argv[0]);
        exit(-1);
    }
  }
  argc -= optind;
  argv += optind;

  /* Make sure we have enough rows, columns, and time steps */
  return_value = assert_minimum_value("row", NUM_ROWS, MINIMUM_ROWS);
  return_value += assert_minimum_value("column", NUM_COLS,
      MINIMUM_COLUMNS);
  return_value += assert_minimum_value("time step", NUM_STEPS,
      MINIMUM_TIME_STEPS);

  /* Exit if we don't */
  if(return_value != 0)
  {
    exit(-1);
  }

  /* Each process determines its number of rows */
  my_num_rows = NUM_ROWS / num_procs;
  /* The last process gets the remainder */
  if(my_rank == num_procs - 1)
  {
    my_num_rows += NUM_ROWS % num_procs;
  }

  /* Allocate enough space in the current grid and next grid for the
   *  number of rows and the number of columns, plus the ghost rows
   *  and columns */
  exit_if(((current_grid = (int**)malloc((my_num_rows + 2) 
            * (NUM_COLS + 2) * sizeof(int))) == NULL),
      "malloc(current_grid)", my_rank);
  exit_if(((next_grid = (int**)malloc((my_num_rows + 2) 
            * (NUM_COLS + 2) * sizeof(int))) == NULL),
      "malloc(next_grid)", my_rank);
			dummyMethod3();
  for(row = 0; row <= my_num_rows + 1; row++)
  {
    exit_if(((current_grid[row]
            = (int*)malloc((NUM_COLS + 2) * sizeof(int))) 
          == NULL), "malloc(current_grid[some_row])", my_rank);
    exit_if(((next_grid[row]
            = (int*)malloc((NUM_COLS + 2) * sizeof(int)))
          == NULL), "malloc(next_grid[some_row])", my_rank);
  }
			dummyMethod4();

  srandom(time(NULL) + my_rank);

  /* Initialize the grid (each cell gets a random state) */
  for(row = 1; row <= my_num_rows; row++)
  {
							dummyMethod1();
#pragma omp parallel for private(col)
    for(col = 1; col <= NUM_COLS; col++)
    {
      current_grid[row][col] = random() % (ALIVE + 1);
    }
							dummyMethod2();
  }

  /* Determine the process with the next-lowest rank */
  if(my_rank == 0)
  {
    next_lowest_rank = num_procs - 1;
  }
  else
  {
    next_lowest_rank = my_rank - 1;
  }

  /* Determine the process with the next-highest rank */
  if(my_rank == num_procs - 1)
  {
    next_highest_rank = 0;
  }
  else
  {
    next_highest_rank = my_rank + 1;
  }

  /* Run the simulation for the specified number of time steps */
  for(step = 0; step <= NUM_STEPS - 1; step++)
  {
    /* Set up the ghost rows */
    /* Send our second-from-the-top row to the process with the
     *  next-lowest rank */
    exit_if((MPI_Send(current_grid[1], NUM_COLS + 2, MPI_INT,
                      next_lowest_rank, 0, MPI_COMM_WORLD) !=
             MPI_SUCCESS), "MPI_Send(top row)", my_rank);

    /* Send our second-from-the-bottom row to the process
     *  with the next-highest rank */
     exit_if((MPI_Send(current_grid[my_num_rows], NUM_COLS + 2,
                       MPI_INT, next_highest_rank, 0,
                       MPI_COMM_WORLD) != MPI_SUCCESS),
             "MPI_Send(bottom row)", my_rank);

    /* Receive our bottom row from the process with the
     *  next-highest rank */
    exit_if((MPI_Recv(current_grid[my_num_rows + 1],
                      NUM_COLS + 2, MPI_INT,
                      next_highest_rank, 0, MPI_COMM_WORLD,
                      MPI_STATUS_IGNORE) != MPI_SUCCESS),
            "MPI_Recv (bottom row)", my_rank);

    /* Receive our top row from the process with the
     *  next-lowest rank */
    exit_if((MPI_Recv(current_grid[0], NUM_COLS + 2,
                      MPI_INT, next_lowest_rank, 0,
                      MPI_COMM_WORLD, MPI_STATUS_IGNORE) !=
             MPI_SUCCESS), "MPI_Recv(top row)", my_rank);

    /* Set up the ghost columns */
    for(row = 0; row <= my_num_rows + 1; row++)
    {
      /* The left ghost column is the same as the farthest-right, non-ghost
         column */
      current_grid[row][0] = current_grid[row][NUM_COLS];

      /* The right ghost column is the same as the farthest-left, non-ghost
         column */
      current_grid[row][NUM_COLS + 1] = current_grid[row][1];
    }

    /* Display the current grid */
    if(my_rank == 0)
    {
      printf("Time Step %d:\n", step);
    }
    for(current_rank = 0; current_rank < num_procs; current_rank++)
    {
      if(current_rank == my_rank)
      {
        for(row = 0; row <= my_num_rows + 1; row++)
        {
          if(my_rank > 0 && row == 0)
          {
            continue;
          }
          if(my_rank < num_procs - 1 && row == my_num_rows + 1)
          {
            continue;
          }
          if(my_rank == 0 && row == 1)
          {
            for(col = 0; col <= NUM_COLS + 1 + 2; col++)
            {
              printf("- ");
            }
            printf("\n");
          }

          for(col = 0; col <= NUM_COLS + 1; col++)
          {
            if(col == 1)
            {
              printf("| ");
            }

            printf("%d ", current_grid[row][col]);

            if(col == NUM_COLS)
            {
              printf("| ");
            }
          }
          printf("\n");

          if(my_rank == num_procs - 1 && row == my_num_rows)
          {
            for(col = 0; col <= NUM_COLS + 1 + 2; col++)
            {
              printf("- ");
            }
            printf("\n");
          }
        }
      }

      MPI_Barrier(MPI_COMM_WORLD);
    }

    /* Determine the next grid -- for each row, do the following: */
    for(row = 1; row <= my_num_rows; row++)
    {
      /* For each column, spawn threads to do the following: */
											dummyMethod1();
#pragma omp parallel for private(col, neighbor_row, neighbor_column, num_alive_neighbors)
      for(col = 1; col <= NUM_COLS; col++)
      {
        /* Initialize the count of ALIVE neighbors to 0 */
        num_alive_neighbors = 0;

        /* For each row of the cell's neighbors, do the following: */
        for(neighbor_row = row - 1; neighbor_row <= row + 1; neighbor_row++)
        {
          /* For each column of the cell's neighbors, do the following: */
          for(neighbor_column = col - 1; neighbor_column <= col + 1;
              neighbor_column++)
          {
            /* If the neighbor is not the cell itself, and the neighbor is
               ALIVE, do the following: */
            if((neighbor_row != row || neighbor_column != col) &&
               (current_grid[neighbor_row][neighbor_column] == ALIVE))
            {
              /* Add 1 to the count of the number of ALIVE neighbors */
              num_alive_neighbors++;
            }
          }
        }

        /* Apply Rule 1 of Conway's Game of Life */
        if(num_alive_neighbors < 2)
        {
          next_grid[row][col] = DEAD;
        }

        /* Apply Rule 2 of Conway's Game of Life */
        else if(current_grid[row][col] == ALIVE &&
           (num_alive_neighbors == 2 || num_alive_neighbors == 3))
        {
          next_grid[row][col] = ALIVE;
        }

        /* Apply Rule 3 of Conway's Game of Life */
        else if(num_alive_neighbors > 3)
        {
          next_grid[row][col] = DEAD;
        }

        /* Apply Rule 4 of Conway's Game of Life */
        else if(current_grid[row][col] == DEAD && num_alive_neighbors == 3)
        {
          next_grid[row][col] = ALIVE;
        }

        /* No rule applies; keep the same state */
        else
        {
          next_grid[row][col] = current_grid[row][col];
        }
      }
											dummyMethod2();
    }

    /* Spawn threads to copy the next grid into the current grid */
    for(row = 1; row <= my_num_rows; row++)
    {
											dummyMethod1();
#pragma omp parallel for private(col)
      for(col = 1; col <= NUM_COLS; col++)
      {
        current_grid[row][col] = next_grid[row][col];
      }
											dummyMethod2();
    }
  }

  /* Deallocate data structures */
  for(row = my_num_rows + 1; row >= 0; row--)
  {
    free(next_grid[row]);
    free(current_grid[row]);
  }
  free(next_grid);
  free(current_grid);

  /* Stop the timer */
  if (my_rank == 0)
  {
    printf("Runtime: %f seconds\n", omp_get_wtime() - startTime);
  }

  /* Finalize the distributed memory environment */
  exit_if((MPI_Finalize() != MPI_SUCCESS), "MPI_Finalize", my_rank);

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