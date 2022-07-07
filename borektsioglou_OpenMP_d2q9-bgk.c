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
**          ^       cols(jj)
**          |  ----- ----- -----
**          | | ... | ... | etc |
**          |  ----- ----- -----
** rows(ii) | | 1,0 | 1,1 | 1,2 |
**          |  ----- ----- -----
**          | | 0,0 | 0,1 | 0,2 |
**          |  ----- ----- -----
**          ----------------------> nx
**
** Note the names of the input parameter and obstacle files
** are passed on the command line, e.g.:
**
**   d2q9-bgk.exe input.params obstacles.dat
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

#define NSPEEDS         9
#define FINALSTATEFILE  "final_state.dat"
#define AVVELSFILE      "av_vels.dat"

/* struct to hold the parameter values */
typedef struct
{
  int    nx;            /* no. of cells in x-direction */
  int    ny;            /* no. of cells in y-direction */
  int    maxIters;      /* no. of iterations */
  int    tot_cells;
  int    reynolds_dim;  /* dimension for Reynolds number */
  double density;       /* density per link */
  double accel;         /* density redistribution */
  double omega;         /* relaxation parameter */
} t_param;

/* struct to hold the 'speed' values */
typedef struct
{
  double speeds[NSPEEDS];
} t_speed;

/*
** function prototypes
*/

/* load params, allocate memory, load obstacles & initialise fluid particle densities */
int initialise(const char* paramfile, const char* obstaclefile,
               t_param* params, t_speed** cells_ptr, t_speed** tmp_cells_ptr,
               int** obstacles_ptr, double** av_vels_ptr);

/*
** The main calculation methods.
** timestep calls, in order, the functions:
** accelerate_flow(), propagate(), rebound() & collision()
*/
double timestep(const t_param params, t_speed* cells, t_speed* tmp_cells, int* obstacles);
int accelerate_flow(const t_param params, t_speed* cells, int* obstacles);
int propagate(const t_param params, t_speed* cells, t_speed* tmp_cells);
int rebound(const t_param params, t_speed* cells, t_speed* tmp_cells, int* obstacles);
double collision(const t_param params, t_speed* cells, t_speed* tmp_cells, int* obstacles);
int write_values(const t_param params, t_speed* cells, int* obstacles, double* av_vels);

/* finalise, including freeing up allocated memory */
int finalise(const t_param* params, t_speed** cells_ptr, t_speed** tmp_cells_ptr,
             int** obstacles_ptr, double** av_vels_ptr);

/* Sum all the densities in the grid.
** The total should remain constant from one timestep to the next. */
double total_density(const t_param params, t_speed* cells);

/* compute average velocity */
double av_velocity(const t_param params, t_speed* cells, int* obstacles, int ii);

/* calculate Reynolds number */
double calc_reynolds(const t_param params, t_speed* cells, int* obstacles);

/* utility functions */
void die(const char* message, const int line, const char* file);
void usage(const char* exe);

/*
** main program:
** initialise, timestep loop, finalise
*/
int main(int argc, char* argv[])
{
  char*    paramfile = NULL;    /* name of the input parameter file */
  char*    obstaclefile = NULL; /* name of a the input obstacle file */
  t_param  params;              /* struct to hold parameter values */
  t_speed* cells     = NULL;    /* grid containing fluid densities */
  t_speed* tmp_cells = NULL;    /* scratch space */
  int*     obstacles = NULL;    /* grid indicating which cells are blocked */
  double* av_vels   = NULL;     /* a record of the av. velocity computed for each timestep */
  struct timeval timstr;        /* structure to hold elapsed time */
  struct rusage ru;             /* structure to hold CPU time--system and user */
  double tic, toc;              /* floating point numbers to calculate elapsed wallclock time */
  double usrtim;                /* floating point number to record elapsed user CPU time */
  double systim;                /* floating point number to record elapsed system CPU time */
  double tot_u;

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
      //prob with tot_cells
      tot_u = timestep(params, cells, tmp_cells, obstacles);
      av_vels[tt] = tot_u/(double)params.tot_cells;
      
      
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

double timestep(const t_param params, t_speed* cells, t_speed* tmp_cells, int* obstacles)
{
  double tot_u; 
  #pragma omp parallel proc_bind(master) num_threads(16)
  {
    accelerate_flow(params, cells, obstacles);
    propagate(params, cells, tmp_cells);
    rebound(params, cells, tmp_cells, obstacles);
  }
  tot_u = collision(params, cells, tmp_cells, obstacles);
  
  return tot_u;
}

int accelerate_flow(const t_param params, t_speed* cells, int* obstacles)
{
  /* compute weighting factors */
  double w1 = params.density * params.accel / 9.0;
  double w2 = params.density * params.accel / 36.0;

  /* modify the 2nd row of the grid */
  int ii = params.ny - 2;

  #pragma omp for
			dummyMethod3();
  for (int jj = 0; jj < params.nx; jj++)
  {

    /* if the cell is not occupied and
    ** we don't send a negative density */
    if (!obstacles[ii * params.nx + jj]
        && (cells[ii * params.nx + jj].speeds[3] - w1) > 0.0
        && (cells[ii * params.nx + jj].speeds[6] - w2) > 0.0
        && (cells[ii * params.nx + jj].speeds[7] - w2) > 0.0)
    {
      /* increase 'east-side' densities */
      cells[ii * params.nx + jj].speeds[1] += w1;
      cells[ii * params.nx + jj].speeds[5] += w2;
      cells[ii * params.nx + jj].speeds[8] += w2;
      /* decrease 'west-side' densities */
      cells[ii * params.nx + jj].speeds[3] -= w1;
      cells[ii * params.nx + jj].speeds[6] -= w2;
      cells[ii * params.nx + jj].speeds[7] -= w2;
    }
  }
			dummyMethod4();

  return EXIT_SUCCESS;
}



int propagate(const t_param params, t_speed* cells, t_speed* tmp_cells)
{
  /* loop over _all_ cells */
  #pragma omp for
			dummyMethod3();
  for (int ii = 0; ii < params.ny; ii++)
  {
    int y_n,y_s;
    y_n = (ii + 1) % params.ny;
    y_s = (ii != 0) ?  (ii - 1) : (ii + params.ny - 1);

    for (int jj = 0; jj < params.nx; jj++)
    {
      int x_e,x_w;
      /* determine indices of axis-direction neighbours
      ** respecting periodic boundary conditions (wrap around) */        
        x_e = (jj + 1) % params.nx;
        x_w = (jj != 0) ?  (jj - 1) : (jj + params.nx - 1);

      /* propagate densities to neighbouring cells, following
      ** appropriate directions of travel and writing into
      ** scratch space grid */
      tmp_cells[ii * params.nx + jj].speeds[0]  = cells[ii * params.nx + jj].speeds[0]; /* central cell, no movement */
      tmp_cells[ii * params.nx + x_e].speeds[1] = cells[ii * params.nx + jj].speeds[1]; /* east */
      tmp_cells[y_n * params.nx + jj].speeds[2]  = cells[ii * params.nx + jj].speeds[2]; /* north */
      tmp_cells[ii * params.nx + x_w].speeds[3] = cells[ii * params.nx + jj].speeds[3]; /* west */
      tmp_cells[y_s * params.nx + jj].speeds[4]  = cells[ii * params.nx + jj].speeds[4]; /* south */
      tmp_cells[y_n * params.nx + x_e].speeds[5] = cells[ii * params.nx + jj].speeds[5]; /* north-east */
      tmp_cells[y_n * params.nx + x_w].speeds[6] = cells[ii * params.nx + jj].speeds[6]; /* north-west */
      tmp_cells[y_s * params.nx + x_w].speeds[7] = cells[ii * params.nx + jj].speeds[7]; /* south-west */
      tmp_cells[y_s * params.nx + x_e].speeds[8] = cells[ii * params.nx + jj].speeds[8]; /* south-east */
    }
  }
			dummyMethod4();

  return EXIT_SUCCESS;
}



int rebound(const t_param params, t_speed* cells, t_speed* tmp_cells, int* obstacles)
{
  /* loop over the cells in the grid */
  #pragma omp for nowait
			dummyMethod3();
  for (int ii = 0; ii < params.ny; ii++)
  {
    for (int jj = 0; jj < params.nx; jj++)
    {
      /* if the cell contains an obstacle */
      if (obstacles[ii * params.nx + jj])
      {
        /* called after propagate, so taking values from scratch space
        ** mirroring, and writing into main grid */
        cells[ii * params.nx + jj].speeds[1] = tmp_cells[ii * params.nx + jj].speeds[3];
        cells[ii * params.nx + jj].speeds[2] = tmp_cells[ii * params.nx + jj].speeds[4];
        cells[ii * params.nx + jj].speeds[3] = tmp_cells[ii * params.nx + jj].speeds[1];
        cells[ii * params.nx + jj].speeds[4] = tmp_cells[ii * params.nx + jj].speeds[2];
        cells[ii * params.nx + jj].speeds[5] = tmp_cells[ii * params.nx + jj].speeds[7];
        cells[ii * params.nx + jj].speeds[6] = tmp_cells[ii * params.nx + jj].speeds[8];
        cells[ii * params.nx + jj].speeds[7] = tmp_cells[ii * params.nx + jj].speeds[5];
        cells[ii * params.nx + jj].speeds[8] = tmp_cells[ii * params.nx + jj].speeds[6];
      }
    }
  }
			dummyMethod4();

  return EXIT_SUCCESS;
}


double collision(const t_param params, t_speed* cells, t_speed* tmp_cells, int* obstacles)
{
  const double c_sq = 1.0 / 3.0;   /* square of speed of sound*/
  const double inv_c_sq = 3.0 / 1.0; /* inverse of square of speed of sound */
  const double w0 = 4.0 / 9.0;  /* weighting factor */
  const double w1 = 1.0 / 9.0;  /* weighting factor */
  const double w2 = 1.0 / 36.0; /* weighting factor */
  const double inv_double_c_sq = 1.0/(2.0 * c_sq); /*double of square of speed*/
  const double inv_sq_c_sq = 1.0/(2.0 * c_sq * c_sq); 
  double temp_u = 0.0;

  /* loop over the cells in the grid
  ** NB the collision step is called after
  ** the propagate step and so values of interest
  ** are in the scratch-space grid */
			dummyMethod1();
  #pragma omp parallel for reduction(+:temp_u)
  for (int ii = 0; ii < params.ny; ii++)
  {

    for (int jj = 0; jj < params.nx; jj++)
    {
      /* don't consider occupied cells */
      if (!obstacles[ii * params.nx + jj])
      {
        /* compute local density total */
        double local_density = 0.0;

        for (int kk = 0; kk < NSPEEDS; kk++)
        {
          local_density += tmp_cells[ii * params.nx + jj].speeds[kk];
        }
	      double inv_local_density = 1.0 / local_density;
        /* compute x velocity component */
        double u_x = (tmp_cells[ii * params.nx + jj].speeds[1]
                      + tmp_cells[ii * params.nx + jj].speeds[5]
                      + tmp_cells[ii * params.nx + jj].speeds[8]
                      - (tmp_cells[ii * params.nx + jj].speeds[3]
                         + tmp_cells[ii * params.nx + jj].speeds[6]
                         + tmp_cells[ii * params.nx + jj].speeds[7]))
                     * inv_local_density;
        /* compute y velocity component */
        double u_y = (tmp_cells[ii * params.nx + jj].speeds[2]
                      + tmp_cells[ii * params.nx + jj].speeds[5]
                      + tmp_cells[ii * params.nx + jj].speeds[6]
                      - (tmp_cells[ii * params.nx + jj].speeds[4]
                         + tmp_cells[ii * params.nx + jj].speeds[7]
                         + tmp_cells[ii * params.nx + jj].speeds[8]))
                     * inv_local_density;

        /* velocity squared */
        double u_sq = u_x * u_x + u_y * u_y;
        //velocity
        temp_u += sqrt(u_sq);
        /* directional velocity components */
        double u[NSPEEDS];
        u[1] =   u_x;        /* east */
        u[2] =         u_y;  /* north */
        u[3] = - u_x;        /* west */
        u[4] =       - u_y;  /* south */
        u[5] =   u_x + u_y;  /* north-east */
        u[6] = - u_x + u_y;  /* north-west */
        u[7] = - u_x - u_y;  /* south-west */
        u[8] =   u_x - u_y;  /* south-east */

        /* equilibrium densities */
        double d_equ;
        /* zero velocity density: weight w0 */
        d_equ = w0 * local_density
                   * (1.0 - u_sq * inv_double_c_sq);
        cells[ii * params.nx + jj].speeds[0] = tmp_cells[ii * params.nx + jj].speeds[0]
                                                  + params.omega
                                                  * (d_equ - tmp_cells[ii * params.nx + jj].speeds[0]);

        /* axis speeds: weight w1 */
        for(int kk = 1; kk < 5; kk++){
          d_equ = w1 * local_density * (1.0 + u[kk] * inv_c_sq
                                           + (u[kk] * u[kk]) * inv_sq_c_sq
                                           - u_sq * inv_double_c_sq);
          cells[ii * params.nx + jj].speeds[kk] = tmp_cells[ii * params.nx + jj].speeds[kk]
                                                    + params.omega
                                                    * (d_equ - tmp_cells[ii * params.nx + jj].speeds[kk]);
        }                                 

        /* diagonal speeds: weight w2 */
        for(int kk = 5; kk < 9; kk++){
          d_equ = w2 * local_density * (1.0 + u[kk] * inv_c_sq
                                           + (u[kk] * u[kk]) * inv_sq_c_sq
                                           - u_sq * inv_double_c_sq);
          cells[ii * params.nx + jj].speeds[kk] = tmp_cells[ii * params.nx + jj].speeds[kk]
                                                    + params.omega
                                                    * (d_equ - tmp_cells[ii * params.nx + jj].speeds[kk]);
        }
      }
    }
  }
			dummyMethod2();
  return temp_u;
}

double av_velocity(const t_param params, t_speed* cells, int* obstacles, int k)
{
  int    tot_cells = 0;  /* no. of cells used in calculation */
  double tot_u;          /* accumulated magnitudes of velocity for each cell */

  /* initialise */
  tot_u = 0.0;

  /* loop over all non-blocked cells */
			dummyMethod3();
  for (int ii = 0; ii < params.ny; ii++)
  {
    for (int jj = 0; jj < params.nx; jj++)
    {
      /* ignore occupied cells */
      if (!obstacles[ii * params.nx + jj])
      {
        /* local density total */
        double local_density = 0.0;

        for (int kk = 0; kk < NSPEEDS; kk++)
        {
          local_density += cells[ii * params.nx + jj].speeds[kk];
        }

        /* x-component of velocity */
        double u_x = (cells[ii * params.nx + jj].speeds[1]
                      + cells[ii * params.nx + jj].speeds[5]
                      + cells[ii * params.nx + jj].speeds[8]
                      - (cells[ii * params.nx + jj].speeds[3]
                         + cells[ii * params.nx + jj].speeds[6]
                         + cells[ii * params.nx + jj].speeds[7]))
                     / local_density;
        /* compute y velocity component */
        double u_y = (cells[ii * params.nx + jj].speeds[2]
                      + cells[ii * params.nx + jj].speeds[5]
                      + cells[ii * params.nx + jj].speeds[6]
                      - (cells[ii * params.nx + jj].speeds[4]
                         + cells[ii * params.nx + jj].speeds[7]
                         + cells[ii * params.nx + jj].speeds[8]))
                     / local_density;

        /* accumulate the norm of x- and y- velocity components */
        tot_u += sqrt((u_x * u_x) + (u_y * u_y));
        /* increase counter of inspected cells */
        ++tot_cells;
      }
    }

  }
			dummyMethod4();

  return tot_u / (double)tot_cells;
}

int initialise(const char* paramfile, const char* obstaclefile,
               t_param* params, t_speed** cells_ptr, t_speed** tmp_cells_ptr,
               int** obstacles_ptr, double** av_vels_ptr)
{
  char   message[1024];  /* message buffer */
  FILE*   fp;            /* file pointer */
  int    xx, yy;         /* generic array indices */
  int    blocked;        /* indicates whether a cell is blocked by an obstacle */
  int    retval;         /* to hold return value for checking */

  /* open the parameter file */
  fp = fopen(paramfile, "r");

  if (fp == NULL)
  {
    sprintf(message, "could not open input parameter file: %s", paramfile);
    die(message, __LINE__, __FILE__);
  }

  /* read in the parameter values */
  retval = fscanf(fp, "%d\n", &(params->nx));

  if (retval != 1) die("could not read param file: nx", __LINE__, __FILE__);

  retval = fscanf(fp, "%d\n", &(params->ny));

  if (retval != 1) die("could not read param file: ny", __LINE__, __FILE__);

  retval = fscanf(fp, "%d\n", &(params->maxIters));

  if (retval != 1) die("could not read param file: maxIters", __LINE__, __FILE__);

  retval = fscanf(fp, "%d\n", &(params->reynolds_dim));

  if (retval != 1) die("could not read param file: reynolds_dim", __LINE__, __FILE__);

  retval = fscanf(fp, "%lf\n", &(params->density));

  if (retval != 1) die("could not read param file: density", __LINE__, __FILE__);

  retval = fscanf(fp, "%lf\n", &(params->accel));

  if (retval != 1) die("could not read param file: accel", __LINE__, __FILE__);

  retval = fscanf(fp, "%lf\n", &(params->omega));

  if (retval != 1) die("could not read param file: omega", __LINE__, __FILE__);

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
  *cells_ptr = (t_speed*)malloc(sizeof(t_speed) * (params->ny * params->nx));

  if (*cells_ptr == NULL) die("cannot allocate memory for cells", __LINE__, __FILE__);

  /* 'helper' grid, used as scratch space */
  *tmp_cells_ptr = (t_speed*)malloc(sizeof(t_speed) * (params->ny * params->nx));

  if (*tmp_cells_ptr == NULL) die("cannot allocate memory for tmp_cells", __LINE__, __FILE__);

  /* the map of obstacles */
  *obstacles_ptr = malloc(sizeof(int) * (params->ny * params->nx));

  if (*obstacles_ptr == NULL) die("cannot allocate column memory for obstacles", __LINE__, __FILE__);

  /* initialise densities */
  double w0 = params->density * 4.0 / 9.0;
  double w1 = params->density      / 9.0;
  double w2 = params->density      / 36.0;

			dummyMethod3();
  for (int ii = 0; ii < params->ny; ii++)
  {
    for (int jj = 0; jj < params->nx; jj++)
    {
      /* centre */
      (*cells_ptr)[ii * params->nx + jj].speeds[0] = w0;
      /* axis directions */
      (*cells_ptr)[ii * params->nx + jj].speeds[1] = w1;
      (*cells_ptr)[ii * params->nx + jj].speeds[2] = w1;
      (*cells_ptr)[ii * params->nx + jj].speeds[3] = w1;
      (*cells_ptr)[ii * params->nx + jj].speeds[4] = w1;
      /* diagonals */
      (*cells_ptr)[ii * params->nx + jj].speeds[5] = w2;
      (*cells_ptr)[ii * params->nx + jj].speeds[6] = w2;
      (*cells_ptr)[ii * params->nx + jj].speeds[7] = w2;
      (*cells_ptr)[ii * params->nx + jj].speeds[8] = w2;
    }
  }
			dummyMethod4();

  /* first set all cells in obstacle array to zero */
			dummyMethod3();
  for (int ii = 0; ii < params->ny; ii++)
  {
    for (int jj = 0; jj < params->nx; jj++)
    {
      (*obstacles_ptr)[ii * params->nx + jj] = 0;
    }
  }
			dummyMethod4();

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
    if (retval != 3) die("expected 3 values per line in obstacle file", __LINE__, __FILE__);

    if (xx < 0 || xx > params->nx - 1) die("obstacle x-coord out of range", __LINE__, __FILE__);

    if (yy < 0 || yy > params->ny - 1) die("obstacle y-coord out of range", __LINE__, __FILE__);

    if (blocked != 1) die("obstacle blocked value should be 1", __LINE__, __FILE__);

    /* assign to array */
    (*obstacles_ptr)[yy * params->nx + xx] = blocked;
    //params->tot_cells--;
  }
  params->tot_cells = 0;
			dummyMethod3();
  for(int ii = 0; ii < params->nx*params->ny; ii++)
    if(!(*obstacles_ptr)[ii])
      params->tot_cells++;
			dummyMethod4();
  
  /* and close the file */
  fclose(fp);

  /*
  ** allocate space to hold a record of the avarage velocities computed
  ** at each timestep
  */
  *av_vels_ptr = (double*)malloc(sizeof(double) * params->maxIters);

  return EXIT_SUCCESS;
}

int finalise(const t_param* params, t_speed** cells_ptr, t_speed** tmp_cells_ptr,
             int** obstacles_ptr, double** av_vels_ptr)
{
  /*
  ** free up allocated memory
  */
  free(*cells_ptr);
  *cells_ptr = NULL;

  free(*tmp_cells_ptr);
  *tmp_cells_ptr = NULL;

  free(*obstacles_ptr);
  *obstacles_ptr = NULL;

  free(*av_vels_ptr);
  *av_vels_ptr = NULL;

  return EXIT_SUCCESS;
}


double calc_reynolds(const t_param params, t_speed* cells, int* obstacles)
{
  const double viscosity = 1.0 / 6.0 * (2.0 / params.omega - 1.0);
  double av_vel = 0;
  // for(int ii = 0; ii < params.ny*params.nx; ii++)
    av_vel = av_velocity(params, cells, obstacles, 0);
  return  av_vel * params.reynolds_dim / viscosity;
}

double total_density(const t_param params, t_speed* cells)
{
  double total = 0.0;  /* accumulator */

			dummyMethod3();
  for (int ii = 0; ii < params.ny; ii++)
  {
    for (int jj = 0; jj < params.nx; jj++)
    {
      for (int kk = 0; kk < NSPEEDS; kk++)
      {
        total += cells[ii * params.nx + jj].speeds[kk];
      }
    }
  }
			dummyMethod4();

  return total;
}

int write_values(const t_param params, t_speed* cells, int* obstacles, double* av_vels)
{
  FILE* fp;                     /* file pointer */
  const double c_sq = 1.0 / 3.0; /* sq. of speed of sound */
  double local_density;         /* per grid cell sum of densities */
  double pressure;              /* fluid pressure in grid cell */
  double u_x;                   /* x-component of velocity in grid cell */
  double u_y;                   /* y-component of velocity in grid cell */
  double u;                     /* norm--root of summed squares--of u_x and u_y */

  fp = fopen(FINALSTATEFILE, "w");

  if (fp == NULL)
  {
    die("could not open file output file", __LINE__, __FILE__);
  }

			dummyMethod3();
  for (int ii = 0; ii < params.ny; ii++)
  {
    for (int jj = 0; jj < params.nx; jj++)
    {
      /* an occupied cell */
      if (obstacles[ii * params.nx + jj])
      {
        u_x = u_y = u = 0.0;
        pressure = params.density * c_sq;
      }
      /* no obstacle */
      else
      {
        local_density = 0.0;

        for (int kk = 0; kk < NSPEEDS; kk++)
        {
          local_density += cells[ii * params.nx + jj].speeds[kk];
        }

        /* compute x velocity component */
        u_x = (cells[ii * params.nx + jj].speeds[1]
               + cells[ii * params.nx + jj].speeds[5]
               + cells[ii * params.nx + jj].speeds[8]
               - (cells[ii * params.nx + jj].speeds[3]
                  + cells[ii * params.nx + jj].speeds[6]
                  + cells[ii * params.nx + jj].speeds[7]))
              / local_density;
        /* compute y velocity component */
        u_y = (cells[ii * params.nx + jj].speeds[2]
               + cells[ii * params.nx + jj].speeds[5]
               + cells[ii * params.nx + jj].speeds[6]
               - (cells[ii * params.nx + jj].speeds[4]
                  + cells[ii * params.nx + jj].speeds[7]
                  + cells[ii * params.nx + jj].speeds[8]))
              / local_density;
        /* compute norm of velocity */
        u = sqrt((u_x * u_x) + (u_y * u_y));
        /* compute pressure */
        pressure = local_density * c_sq;
      }

      /* write to file */
      fprintf(fp, "%d %d %.12E %.12E %.12E %.12E %d\n", jj, ii, u_x, u_y, u, pressure, obstacles[ii * params.nx + jj]);
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

void die(const char* message, const int line, const char* file)
{
  fprintf(stderr, "Error at line %d of file %s:\n", line, file);
  fprintf(stderr, "%s\n", message);
  fflush(stderr);
  exit(EXIT_FAILURE);
}

void usage(const char* exe)
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