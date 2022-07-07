/*
** Code to implement a d2q9-bgk lattice boltzmann scheme.
** 'd2' inidates a 2-dimensional grid, and
** 'q9' indicates 9 velocities per grid cell.
** 'bgk' refers to the Bhatnagar-Gross-Krook collision step.
**
** The 'speeds' in each cell are numbered as follows:
**
** 6 2 5
**  \|/
** 3-0-1
**  /|\
** 7 4 8
**
** A 2D grid:
**
**           cols
**       --- --- ---
**      | D | E | F |
** rows  --- --- ---
**      | A | B | C |
**       --- --- ---
**
** 'unwrapped' in row major order to give a 1D array:
**
**  --- --- --- --- --- ---
** | A | B | C | D | E | F |
**  --- --- --- --- --- ---
**
** Grid indicies are:
**
**          ny
**          ^       cols(ii)
**          |  ----- ----- -----
**          | | ... | ... | etc |
**          |  ----- ----- -----
** rows(jj) | | 1,0 | 1,1 | 1,2 |
**          |  ----- ----- -----
**          | | 0,0 | 0,1 | 0,2 |
**          |  ----- ----- -----
**          ----------------------> nx
**
** Note the names of the input parameter and obstacle files
** are passed on the command line, e.g.:
**
**   ./d2q9-bgk input.params obstacles.dat
**
** Be sure to adjust the grid dimensions in the parameter file
** if you choose a different obstacle file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NSPEEDS 9
#define FINALSTATEFILE "final_state.dat"
#define AVVELSFILE "av_vels.dat"

#define C_SQ (1.f / 3.f) /* square of speed of sound */
#define W0 (4.f / 9.f)   /* weighting factor */
#define W1 (1.f / 9.f)   /* weighting factor */
#define W2 (1.f / 36.f)  /* weighting factor */
#define C1_5 1.5f
#define C1_ 1.f
#define C4_5 4.5f

/* struct to hold the parameter values */
typedef struct
{
  int nx;           /* no. of cells in x-direction */
  int ny;           /* no. of cells in y-direction */
  int maxIters;     /* no. of iterations */
  int reynolds_dim; /* dimension for Reynolds number */
  float density;    /* density per link */
  float accel;      /* density redistribution */
  float omega;      /* relaxation parameter */
} t_param;

/* struct to hold the 'speed' values */
typedef struct
{
  float *speeds[NSPEEDS];
} t_speed;

/*
** function prototypes
*/

/* load params, allocate memory, load obstacles & initialise fluid particle densities */
int initialise(const char *paramfile, const char *obstaclefile,
               t_param *params, t_speed **cells_ptr, t_speed **tmp_cells_ptr,
               int **obstacles_ptr, float **av_vels_ptr);

/*
** The main calculation methods.
** timestep calls, in order, the functions:
** accelerate_flow(), propagate(), rebound() & collision()
*/
int timestep(const t_param params, t_speed *cells, t_speed *tmp_cells, int *obstacles);
int accelerate_flow(const t_param params, t_speed *cells, const int *obstacles);
int collision(const t_param params, t_speed *cells, t_speed *tmp_cells, const int *obstacles);
int write_values(const t_param params, t_speed *cells, int *obstacles, float *av_vels);

/* finalise, including freeing up allocated memory */
int finalise(const t_param *params, t_speed **cells_ptr, t_speed **tmp_cells_ptr,
             int **obstacles_ptr, float **av_vels_ptr);

/* Sum all the densities in the grid.
** The total should remain constant from one timestep to the next. */
float total_density(const t_param params, t_speed *cells);

/* compute average velocity */
float av_velocity(const t_param params, t_speed *cells, int *obstacles);

/* calculate Reynolds number */
float calc_reynolds(const t_param params, t_speed *cells, int *obstacles);

/* utility functions */
void die(const char *message, const int line, const char *file);
void usage(const char *exe);

/*
** main program:
** initialise, timestep loop, finalise
*/
int main(int argc, char *argv[])
{
  char *paramfile = NULL;    /* name of the input parameter file */
  char *obstaclefile = NULL; /* name of a the input obstacle file */
  t_param params;            /* struct to hold parameter values */
  t_speed *cells = NULL;     /* grid containing fluid densities */
  t_speed *tmp_cells = NULL; /* scratch space */
  t_speed *swp_cells = NULL;
  int *obstacles = NULL; /* grid indicating which cells are blocked */
  float *av_vels = NULL; /* a record of the av. velocity computed for each timestep */
  struct timeval timstr; /* structure to hold elapsed time */
  struct rusage ru;      /* structure to hold CPU time--system and user */
  double tic, toc;       /* floating point numbers to calculate elapsed wallclock time */
  double usrtim;         /* floating point number to record elapsed user CPU time */
  double systim;         /* floating point number to record elapsed system CPU time */


  /* parse the command line */
  if (argc != 3)
  {
    usage(argv[0]);
  }
  else
  {
    paramfile = argv[1];
    obstaclefile = argv[2];
  }

  /* initialise our data structures and load values from file */
  initialise(paramfile, obstaclefile, &params, &cells, &tmp_cells, &obstacles, &av_vels);

  /* iterate for maxIters timesteps */
  gettimeofday(&timstr, NULL);
  tic = timstr.tv_sec + (timstr.tv_usec / 1000000.0);

			dummyMethod3();
  for (int tt = 0; tt < params.maxIters; tt++)
  {
    timestep(params, cells, tmp_cells, obstacles);
    swp_cells = cells;
    cells = tmp_cells;
    tmp_cells = swp_cells;
    av_vels[tt] = av_velocity(params, cells, obstacles);
#ifdef DEBUG
    printf("==timestep: %d==\n", tt);
    printf("av velocity: %.12E\n", av_vels[tt]);
    printf("tot density: %.12E\n", total_density(params, cells));
#endif
  }
			dummyMethod4();

  gettimeofday(&timstr, NULL);
  toc = timstr.tv_sec + (timstr.tv_usec / 1000000.0);
  getrusage(RUSAGE_SELF, &ru);
  timstr = ru.ru_utime;
  usrtim = timstr.tv_sec + (timstr.tv_usec / 1000000.0);
  timstr = ru.ru_stime;
  systim = timstr.tv_sec + (timstr.tv_usec / 1000000.0);

  /* write final values and free memory */
  printf("==done==\n");
  printf("Reynolds number:\t\t%.12E\n", calc_reynolds(params, cells, obstacles));
  printf("Elapsed time:\t\t\t%.6lf (s)\n", toc - tic);
  printf("Elapsed user CPU time:\t\t%.6lf (s)\n", usrtim);
  printf("Elapsed system CPU time:\t%.6lf (s)\n", systim);
  write_values(params, cells, obstacles, av_vels);
  finalise(&params, &cells, &tmp_cells, &obstacles, &av_vels);

  return EXIT_SUCCESS;
}

int timestep(const t_param params, t_speed *restrict cells, t_speed *restrict tmp_cells, int *obstacles)
{
  accelerate_flow(params, cells, obstacles);
  collision(params, cells, tmp_cells, obstacles);
  return EXIT_SUCCESS;
}

int accelerate_flow(const t_param params, t_speed *restrict cells, const int *obstacles)
{
  __assume_aligned(cells->speeds[0], 64);
  __assume_aligned(cells->speeds[1], 64);
  __assume_aligned(cells->speeds[2], 64);
  __assume_aligned(cells->speeds[3], 64);
  __assume_aligned(cells->speeds[4], 64);
  __assume_aligned(cells->speeds[5], 64);
  __assume_aligned(cells->speeds[6], 64);
  __assume_aligned(cells->speeds[7], 64);
  __assume_aligned(cells->speeds[8], 64);

  /* compute weighting factors */
  float w1 = params.density * params.accel / 9.f;
  float w2 = params.density * params.accel / 36.f;

  /* modify the 2nd row of the grid */
  int jj = params.ny - 2;

#pragma omp simd
			dummyMethod3();
  for (int ii = 0; ii < params.nx; ii++)
  {
    int index = ii + jj * params.nx;
    /* if the cell is not occupied and
    ** we don't send a negative density */
    if (!obstacles[index] && ((cells->speeds[3])[index] - w1) > 0.f && ((cells->speeds[6])[index] - w2) > 0.f && ((cells->speeds[7])[index] - w2) > 0.f)
    {
      /* increase 'east-side' densities */
      (cells->speeds[1])[index] += w1;
      (cells->speeds[5])[index] += w2;
      (cells->speeds[8])[index] += w2;
      /* decrease 'west-side' densities */
      (cells->speeds[3])[index] -= w1;
      (cells->speeds[6])[index] -= w2;
      (cells->speeds[7])[index] -= w2;
    }
  }
			dummyMethod4();

  return EXIT_SUCCESS;
}


int collision(const t_param params, t_speed *restrict cells, t_speed *restrict tmp_cells, const int *obstacles)
{
  __assume_aligned(cells->speeds[0], 64);
  __assume_aligned(cells->speeds[1], 64);
  __assume_aligned(cells->speeds[2], 64);
  __assume_aligned(cells->speeds[3], 64);
  __assume_aligned(cells->speeds[4], 64);
  __assume_aligned(cells->speeds[5], 64);
  __assume_aligned(cells->speeds[6], 64);
  __assume_aligned(cells->speeds[7], 64);
  __assume_aligned(cells->speeds[8], 64);

  __assume_aligned(tmp_cells->speeds[0], 64);
  __assume_aligned(tmp_cells->speeds[1], 64);
  __assume_aligned(tmp_cells->speeds[2], 64);
  __assume_aligned(tmp_cells->speeds[3], 64);
  __assume_aligned(tmp_cells->speeds[4], 64);
  __assume_aligned(tmp_cells->speeds[5], 64);
  __assume_aligned(tmp_cells->speeds[6], 64);
  __assume_aligned(tmp_cells->speeds[7], 64);
  __assume_aligned(tmp_cells->speeds[8], 64);

  /* loop over the cells in the grid
  ** NB the collision step is called after
  ** the propagate step and so values of interest
  ** are in the scratch-space grid */

			dummyMethod1();
#pragma omp parallel for shared(cells, tmp_cells, obstacles)
  for (int jj = 0; jj < params.ny; jj++)
  {
    #pragma omp simd
    for (int ii = 0; ii < params.nx; ii++)
    {
      float tp[NSPEEDS];

      int y_n = (jj + 1) % params.ny;
      int x_e = (ii + 1) % params.nx;
      int y_s = (jj == 0) ? (jj + params.ny - 1) : (jj - 1);
      int x_w = (ii == 0) ? (ii + params.nx - 1) : (ii - 1);

      tp[0] = cells->speeds[0][ii + jj * params.nx];
      tp[1] = cells->speeds[1][x_w + jj * params.nx];
      tp[2] = cells->speeds[2][ii + y_s * params.nx];
      tp[3] = cells->speeds[3][x_e + jj * params.nx];
      tp[4] = cells->speeds[4][ii + y_n * params.nx];
      tp[5] = cells->speeds[5][x_w + y_s * params.nx];
      tp[6] = cells->speeds[6][x_e + y_s * params.nx];
      tp[7] = cells->speeds[7][x_e + y_n * params.nx];
      tp[8] = cells->speeds[8][x_w + y_n * params.nx];

      /* compute local density total */
      float local_density = tp[0]
                          + tp[1]
                          + tp[2]
                          + tp[3]
                          + tp[4]
                          + tp[5]
                          + tp[6]
                          + tp[7]
                          + tp[8];

      /* compute x velocity component */
      float u_x = (tp[1] + tp[5] + tp[8] - (tp[3] + tp[6] + tp[7])) / local_density;
      /* compute y velocity component */
      float u_y = (tp[2] + tp[5] + tp[6] - (tp[4] + tp[7] + tp[8])) / local_density;

      /* velocity squared */
      float u_sq = u_x * u_x + u_y * u_y;

      /* directional velocity components */
      float u[NSPEEDS];
      u[0] = 0;
      u[1] = u_x;        /* east */
      u[2] = u_y;        /* north */
      u[3] = -u_x;       /* west */
      u[4] = -u_y;       /* south */
      u[5] = u_x + u_y;  /* north-east */
      u[6] = -u_x + u_y; /* north-west */
      u[7] = -u_x - u_y; /* south-west */
      u[8] = u_x - u_y;  /* south-east */

      (tmp_cells->speeds[0])[ii + jj * params.nx] = (obstacles[jj * params.nx + ii]) ? tp[0] : tp[0] + params.omega * ((W0 * local_density * (C1_ - C1_5 * u_sq)) - tp[0]);
      (tmp_cells->speeds[1])[ii + jj * params.nx] = (obstacles[jj * params.nx + ii]) ? tp[3] : tp[1] + params.omega * ((W1 * local_density * (C1_ + 3 * u[1] + C4_5 * (u[1] * u[1]) - C1_5 * u_sq)) - tp[1]);
      (tmp_cells->speeds[2])[ii + jj * params.nx] = (obstacles[jj * params.nx + ii]) ? tp[4] : tp[2] + params.omega * ((W1 * local_density * (C1_ + 3 * u[2] + C4_5 * (u[2] * u[2]) - C1_5 * u_sq)) - tp[2]);
      (tmp_cells->speeds[3])[ii + jj * params.nx] = (obstacles[jj * params.nx + ii]) ? tp[1] : tp[3] + params.omega * ((W1 * local_density * (C1_ + 3 * u[3] + C4_5 * (u[3] * u[3]) - C1_5 * u_sq)) - tp[3]);
      (tmp_cells->speeds[4])[ii + jj * params.nx] = (obstacles[jj * params.nx + ii]) ? tp[2] : tp[4] + params.omega * ((W1 * local_density * (C1_ + 3 * u[4] + C4_5 * (u[4] * u[4]) - C1_5 * u_sq)) - tp[4]);
      (tmp_cells->speeds[5])[ii + jj * params.nx] = (obstacles[jj * params.nx + ii]) ? tp[7] : tp[5] + params.omega * ((W2 * local_density * (C1_ + 3 * u[5] + C4_5 * (u[5] * u[5]) - C1_5 * u_sq)) - tp[5]);
      (tmp_cells->speeds[6])[ii + jj * params.nx] = (obstacles[jj * params.nx + ii]) ? tp[8] : tp[6] + params.omega * ((W2 * local_density * (C1_ + 3 * u[6] + C4_5 * (u[6] * u[6]) - C1_5 * u_sq)) - tp[6]);
      (tmp_cells->speeds[7])[ii + jj * params.nx] = (obstacles[jj * params.nx + ii]) ? tp[5] : tp[7] + params.omega * ((W2 * local_density * (C1_ + 3 * u[7] + C4_5 * (u[7] * u[7]) - C1_5 * u_sq)) - tp[7]);
      (tmp_cells->speeds[8])[ii + jj * params.nx] = (obstacles[jj * params.nx + ii]) ? tp[6] : tp[8] + params.omega * ((W2 * local_density * (C1_ + 3 * u[8] + C4_5 * (u[8] * u[8]) - C1_5 * u_sq)) - tp[8]);

    

    }
  }
			dummyMethod2();

  return EXIT_SUCCESS;
}

float av_velocity(const t_param params, t_speed *restrict cells, int *obstacles)
{
  __assume_aligned(cells->speeds[0], 64);
  __assume_aligned(cells->speeds[1], 64);
  __assume_aligned(cells->speeds[2], 64);
  __assume_aligned(cells->speeds[3], 64);
  __assume_aligned(cells->speeds[4], 64);
  __assume_aligned(cells->speeds[5], 64);
  __assume_aligned(cells->speeds[6], 64);
  __assume_aligned(cells->speeds[7], 64);
  __assume_aligned(cells->speeds[8], 64);

  int tot_cells = 0; /* no. of cells used in calculation */
  float tot_u;       /* accumulated magnitudes of velocity for each cell */

  /* initialise */
  tot_u = 0.f;

  /* loop over all non-blocked cells */
			dummyMethod1();
#pragma omp parallel for reduction(+ : tot_cells, tot_u)
  for (int jj = 0; jj < params.ny; jj++)
  {
#pragma ivdep
    for (int ii = 0; ii < params.nx; ii++)
    {
      /* ignore occupied cells */
      if (!obstacles[ii + jj * params.nx])
      {
        /* local density total */
        float local_density = (cells->speeds[0])[ii + jj * params.nx]
                            + (cells->speeds[1])[ii + jj * params.nx]
                            + (cells->speeds[2])[ii + jj * params.nx]
                            + (cells->speeds[3])[ii + jj * params.nx]
                            + (cells->speeds[4])[ii + jj * params.nx]
                            + (cells->speeds[5])[ii + jj * params.nx]
                            + (cells->speeds[6])[ii + jj * params.nx]
                            + (cells->speeds[7])[ii + jj * params.nx]
                            + (cells->speeds[8])[ii + jj * params.nx];
                          

        /* x-component of velocity */
        float u_x = ((cells->speeds[1])[ii + jj * params.nx] + (cells->speeds[5])[ii + jj * params.nx] + (cells->speeds[8])[ii + jj * params.nx] - ((cells->speeds[3])[ii + jj * params.nx] + (cells->speeds[6])[ii + jj * params.nx] + (cells->speeds[7])[ii + jj * params.nx])) / local_density;
        /* compute y velocity component */
        float u_y = ((cells->speeds[2])[ii + jj * params.nx] + (cells->speeds[5])[ii + jj * params.nx] + (cells->speeds[6])[ii + jj * params.nx] - ((cells->speeds[4])[ii + jj * params.nx] + (cells->speeds[7])[ii + jj * params.nx] + (cells->speeds[8])[ii + jj * params.nx])) / local_density;
        /* accumulate the norm of x- and y- velocity components */
        tot_u += sqrtf((u_x * u_x) + (u_y * u_y));
        /* increase counter of inspected cells */
        ++tot_cells;
      }
    }
  }
			dummyMethod2();

  return tot_u / (float)tot_cells;
}

int initialise(const char *paramfile, const char *obstaclefile,
               t_param *params, t_speed **cells_ptr, t_speed **tmp_cells_ptr,
               int **obstacles_ptr, float **av_vels_ptr)
{
  char message[1024]; /* message buffer */
  FILE *fp;           /* file pointer */
  int xx, yy;         /* generic array indices */
  int blocked;        /* indicates whether a cell is blocked by an obstacle */
  int retval;         /* to hold return value for checking */

  /* open the parameter file */
  fp = fopen(paramfile, "r");

  if (fp == NULL)
  {
    sprintf(message, "could not open input parameter file: %s", paramfile);
    die(message, __LINE__, __FILE__);
  }

  /* read in the parameter values */
  retval = fscanf(fp, "%d\n", &(params->nx));

  if (retval != 1)
    die("could not read param file: nx", __LINE__, __FILE__);

  retval = fscanf(fp, "%d\n", &(params->ny));

  if (retval != 1)
    die("could not read param file: ny", __LINE__, __FILE__);

  retval = fscanf(fp, "%d\n", &(params->maxIters));

  if (retval != 1)
    die("could not read param file: maxIters", __LINE__, __FILE__);

  retval = fscanf(fp, "%d\n", &(params->reynolds_dim));

  if (retval != 1)
    die("could not read param file: reynolds_dim", __LINE__, __FILE__);

  retval = fscanf(fp, "%f\n", &(params->density));

  if (retval != 1)
    die("could not read param file: density", __LINE__, __FILE__);

  retval = fscanf(fp, "%f\n", &(params->accel));

  if (retval != 1)
    die("could not read param file: accel", __LINE__, __FILE__);

  retval = fscanf(fp, "%f\n", &(params->omega));

  if (retval != 1)
    die("could not read param file: omega", __LINE__, __FILE__);

  /* and close up the file */
  fclose(fp);

  /*
  ** Allocate memory.
  **
  ** Remember C is pass-by-value, so we need to
  ** pass pointers into the initialise function.
  **
  ** NB we are allocating a 1D array, so that the
  ** memory will be contiguous.  We still want to
  ** index this memory as if it were a (row major
  ** ordered) 2D array, however.  We will perform
  ** some arithmetic using the row and column
  ** coordinates, inside the square brackets, when
  ** we want to access elements of this array.
  **
  ** Note also that we are using a structure to
  ** hold an array of 'speeds'.  We will allocate
  ** a 1D array of these structs.
  */

  /* main grid */
  *cells_ptr = (t_speed *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);

  if (*cells_ptr == NULL)
    die("cannot allocate memory for cells", __LINE__, __FILE__);

  (*cells_ptr)->speeds[0] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*cells_ptr)->speeds[1] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*cells_ptr)->speeds[2] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*cells_ptr)->speeds[3] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*cells_ptr)->speeds[4] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*cells_ptr)->speeds[5] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*cells_ptr)->speeds[6] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*cells_ptr)->speeds[7] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*cells_ptr)->speeds[8] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);

  /* 'helper' grid, used as scratch space */
  *tmp_cells_ptr = (t_speed *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);

  if (*tmp_cells_ptr == NULL)
    die("cannot allocate memory for tmp_cells", __LINE__, __FILE__);

  (*tmp_cells_ptr)->speeds[0] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*tmp_cells_ptr)->speeds[1] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*tmp_cells_ptr)->speeds[2] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*tmp_cells_ptr)->speeds[3] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*tmp_cells_ptr)->speeds[4] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*tmp_cells_ptr)->speeds[5] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*tmp_cells_ptr)->speeds[6] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*tmp_cells_ptr)->speeds[7] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);
  (*tmp_cells_ptr)->speeds[8] = (float *)_mm_malloc(sizeof(float) * params->nx * params->ny, 64);

  /* the map of obstacles */
  *obstacles_ptr = _mm_malloc(sizeof(int) * (params->ny * params->nx), 64);

  if (*obstacles_ptr == NULL)
    die("cannot allocate column memory for obstacles", __LINE__, __FILE__);

  /* initialise densities */
  float w0 = params->density * 4.f / 9.f;
  float w1 = params->density / 9.f;
  float w2 = params->density / 36.f;

			dummyMethod1();
#pragma omp parallel for collapse(2)
  for (int jj = 0; jj < params->ny; jj++)
  {
    for (int ii = 0; ii < params->nx; ii++)
    {
      /* centre */
      ((*cells_ptr)->speeds[0])[ii + jj * params->nx] = w0;
      /* axis directions */
      ((*cells_ptr)->speeds[1])[ii + jj * params->nx] = w1;

      ((*cells_ptr)->speeds[2])[ii + jj * params->nx] = w1;
      ((*cells_ptr)->speeds[3])[ii + jj * params->nx] = w1;
      ((*cells_ptr)->speeds[4])[ii + jj * params->nx] = w1;
      /* diagonals */
      ((*cells_ptr)->speeds[5])[ii + jj * params->nx] = w2;
      ((*cells_ptr)->speeds[6])[ii + jj * params->nx] = w2;
      ((*cells_ptr)->speeds[7])[ii + jj * params->nx] = w2;
      ((*cells_ptr)->speeds[8])[ii + jj * params->nx] = w2;
    }
  }
			dummyMethod2();

  /* first set all cells in obstacle array to zero */
			dummyMethod1();
#pragma omp parallel for collapse(2)
  for (int jj = 0; jj < params->ny; jj++)
  {
    for (int ii = 0; ii < params->nx; ii++)
    {
      (*obstacles_ptr)[ii + jj * params->nx] = 0;
    }
  }
			dummyMethod2();

  /* open the obstacle data file */
  fp = fopen(obstaclefile, "r");

  if (fp == NULL)
  {
    sprintf(message, "could not open input obstacles file: %s", obstaclefile);
    die(message, __LINE__, __FILE__);
  }

  /* read-in the blocked cells list */
  while ((retval = fscanf(fp, "%d %d %d\n", &xx, &yy, &blocked)) != EOF)
  {
    /* some checks */
    if (retval != 3)
      die("expected 3 values per line in obstacle file", __LINE__, __FILE__);

    if (xx < 0 || xx > params->nx - 1)
      die("obstacle x-coord out of range", __LINE__, __FILE__);

    if (yy < 0 || yy > params->ny - 1)
      die("obstacle y-coord out of range", __LINE__, __FILE__);

    if (blocked != 1)
      die("obstacle blocked value should be 1", __LINE__, __FILE__);

    /* assign to array */
    (*obstacles_ptr)[xx + yy * params->nx] = blocked;
  }

  /* and close the file */
  fclose(fp);

  /*
  ** allocate space to hold a record of the avarage velocities computed
  ** at each timestep
  */
  *av_vels_ptr = (float *)malloc(sizeof(float) * params->maxIters);

  return EXIT_SUCCESS;
}

int finalise(const t_param *params, t_speed **cells_ptr, t_speed **tmp_cells_ptr,
             int **obstacles_ptr, float **av_vels_ptr)
{
  /*
  ** free up allocated memory
  */
  _mm_free(*cells_ptr);
  *cells_ptr = NULL;

  _mm_free(*tmp_cells_ptr);
  *tmp_cells_ptr = NULL;

  _mm_free(*obstacles_ptr);
  *obstacles_ptr = NULL;

  _mm_free(*av_vels_ptr);
  *av_vels_ptr = NULL;

  return EXIT_SUCCESS;
}

float calc_reynolds(const t_param params, t_speed *cells, int *obstacles)
{
  const float viscosity = C1_ / 6.f * (2.f / params.omega - C1_);

  return av_velocity(params, cells, obstacles) * params.reynolds_dim / viscosity;
}

float total_density(const t_param params, t_speed *cells)
{
  float total = 0.f; /* accumulator */

			dummyMethod3();
  for (int jj = 0; jj < params.ny; jj++)
  {
    for (int ii = 0; ii < params.nx; ii++)
    {
      total += (cells->speeds[0])[ii + jj * params.nx];
      total += (cells->speeds[1])[ii + jj * params.nx];
      total += (cells->speeds[2])[ii + jj * params.nx];
      total += (cells->speeds[3])[ii + jj * params.nx];
      total += (cells->speeds[4])[ii + jj * params.nx];
      total += (cells->speeds[5])[ii + jj * params.nx];
      total += (cells->speeds[6])[ii + jj * params.nx];
      total += (cells->speeds[7])[ii + jj * params.nx];
      total += (cells->speeds[8])[ii + jj * params.nx];
    }
  }
			dummyMethod4();

  return total;
}

int write_values(const t_param params, t_speed *cells, int *obstacles, float *av_vels)
{
  FILE *fp;                     /* file pointer */
  const float c_sq = C1_ / 3.f; /* sq. of speed of sound */
  float local_density;          /* per grid cell sum of densities */
  float pressure;               /* fluid pressure in grid cell */
  float u_x;                    /* x-component of velocity in grid cell */
  float u_y;                    /* y-component of velocity in grid cell */
  float u;                      /* norm--root of summed squares--of u_x and u_y */

  fp = fopen(FINALSTATEFILE, "w");

  if (fp == NULL)
  {
    die("could not open file output file", __LINE__, __FILE__);
  }

			dummyMethod3();
  for (int jj = 0; jj < params.ny; jj++)
  {
    for (int ii = 0; ii < params.nx; ii++)
    {
      /* an occupied cell */
      if (obstacles[ii + jj * params.nx])
      {
        u_x = u_y = u = 0.f;
        pressure = params.density * c_sq;
      }
      /* no obstacle */
      else
      {
        local_density = 0.f;

        local_density += (cells->speeds[0])[ii + jj * params.nx];
        local_density += (cells->speeds[1])[ii + jj * params.nx];
        local_density += (cells->speeds[2])[ii + jj * params.nx];
        local_density += (cells->speeds[3])[ii + jj * params.nx];
        local_density += (cells->speeds[4])[ii + jj * params.nx];
        local_density += (cells->speeds[5])[ii + jj * params.nx];
        local_density += (cells->speeds[6])[ii + jj * params.nx];
        local_density += (cells->speeds[7])[ii + jj * params.nx];
        local_density += (cells->speeds[8])[ii + jj * params.nx];

        /* compute x velocity component */
        u_x = ((cells->speeds[1])[ii + jj * params.nx] + (cells->speeds[5])[ii + jj * params.nx] + (cells->speeds[8])[ii + jj * params.nx] - ((cells->speeds[3])[ii + jj * params.nx] + (cells->speeds[6])[ii + jj * params.nx] + (cells->speeds[7])[ii + jj * params.nx])) / local_density;
        /* compute y velocity component */
        u_y = ((cells->speeds[2])[ii + jj * params.nx] + (cells->speeds[5])[ii + jj * params.nx] + (cells->speeds[6])[ii + jj * params.nx] - ((cells->speeds[4])[ii + jj * params.nx] + (cells->speeds[7])[ii + jj * params.nx] + (cells->speeds[8])[ii + jj * params.nx])) / local_density;
        /* compute norm of velocity */
        u = sqrtf((u_x * u_x) + (u_y * u_y));
        /* compute pressure */
        pressure = local_density * c_sq;
      }

      /* write to file */
      fprintf(fp, "%d %d %.12E %.12E %.12E %.12E %d\n", ii, jj, u_x, u_y, u, pressure, obstacles[ii * params.nx + jj]);
    }
  }
			dummyMethod4();

  fclose(fp);

  fp = fopen(AVVELSFILE, "w");

  if (fp == NULL)
  {
    die("could not open file output file", __LINE__, __FILE__);
  }

			dummyMethod3();
  for (int ii = 0; ii < params.maxIters; ii++)
  {
    fprintf(fp, "%d:\t%.12E\n", ii, av_vels[ii]);
  }
			dummyMethod4();

  fclose(fp);

  return EXIT_SUCCESS;
}

void die(const char *message, const int line, const char *file)
{
  fprintf(stderr, "Error at line %d of file %s:\n", line, file);
  fprintf(stderr, "%s\n", message);
  fflush(stderr);
  exit(EXIT_FAILURE);
}

void usage(const char *exe)
{
  fprintf(stderr, "Usage: %s <paramfile> <obstaclefile>\n", exe);
  exit(EXIT_FAILURE);
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