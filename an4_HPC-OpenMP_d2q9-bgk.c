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

#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef DEBUG
#include "/usr/include/opencv/cxcore.h"
#include "/usr/include/opencv/cv.h"
#include "/usr/include/opencv/highgui.h"
#endif

#define FINALSTATEFILE  "final_state.dat"
#define AVVELSFILE      "av_vels.dat"

/* struct to hold the parameter values */
typedef struct {
  int    nx;            /* no. of cells in x-direction */
  int    ny;            /* no. of cells in y-direction */
  int    maxIters;      /* no. of iterations */
  int    reynolds_dim;  /* dimension for Reynolds number */
  float  density;       /* density per link */
  float  accel;         /* density redistribution */
  float  omega;         /* relaxation parameter */
} t_param;

/* struct to hold the 'speed' values */
typedef struct {
  float speeds[9];
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
int timestep(const t_param params, t_speed* cells, t_speed* tmp_cells, int* obstacles);
int accelerate_flow(const t_param params, t_speed* cells, int* obstacles);
int propagate(const t_param params, t_speed* cells, t_speed* tmp_cells);
double collision(const t_param params, t_speed* cells, t_speed* tmp_cells, int* obstacles);
int write_values(const t_param params, t_speed* cells, int* obstacles, double* av_vels);

/* finalise, including freeing up allocated memory */
int finalise(const t_param* params, t_speed** cells_ptr, t_speed** tmp_cells_ptr,
	     int** obstacles_ptr, double** av_vels_ptr);

/* Sum all the densities in the grid.
** The total should remain constant from one timestep to the next. */
double total_density(const t_param params, t_speed* cells);

/* compute average velocity */
double av_velocity(const t_param params, t_speed* cells, int* obstacles);

/* calculate Reynolds number */
double calc_reynolds(const t_param params, t_speed* cells, int* obstacles);

/* utility functions */
void die(const char* message, const int line, const char *file);
void usage(const char* exe);

#ifdef DEBUG

void add_frame(const t_param params, t_speed* cells, int* obstacles, cv::VideoWriter* vw)
{
    // Create image
    cv::Mat image = cv::Mat(params.ny, params.nx, CV_8UC3);
    
    // Add frame to scene
    for(int i=0; i < params.ny; ++i)
    {
        for(int j = 0; j<params.nx; ++j) 
        {
            int cell = params.nx * i + j;

            //Values between 0.097430 and 0.110866
            float local_density = 0.0f;

            for(int kk=0;kk<9;kk++) {
              local_density += cells[cell].speeds[kk];
            }

            if(obstacles[cell]) { 
                image.at<cv::Vec3b>(i,j)[0] = 255;
                image.at<cv::Vec3b>(i,j)[1] = 255;
                image.at<cv::Vec3b>(i,j)[2] = 255;
            } else if(local_density > 0.101f) {
                image.at<cv::Vec3b>(i,j)[0] = 0;
                image.at<cv::Vec3b>(i,j)[1] = 0;
                image.at<cv::Vec3b>(i,j)[2] = 255;
            } else if(local_density > 0.1005f) {
                image.at<cv::Vec3b>(i,j)[0] = 0;
                image.at<cv::Vec3b>(i,j)[1] = 128;
                image.at<cv::Vec3b>(i,j)[2] = 255;
            } else if(local_density > 0.1001f) {
                image.at<cv::Vec3b>(i,j)[0] = 0;
                image.at<cv::Vec3b>(i,j)[1] = 255;
                image.at<cv::Vec3b>(i,j)[2] = 255;
            } else if(local_density > 0.10005f) { 
                image.at<cv::Vec3b>(i,j)[0] = 0;
                image.at<cv::Vec3b>(i,j)[1] = 255;
                image.at<cv::Vec3b>(i,j)[2] = 128;
            } else if(local_density >0.1f) { 
                image.at<cv::Vec3b>(i,j)[0] = 0;
                image.at<cv::Vec3b>(i,j)[1] = 255;
                image.at<cv::Vec3b>(i,j)[2] = 0;
            } else if(local_density > 0.09995f) {
                image.at<cv::Vec3b>(i,j)[0] = 128;
                image.at<cv::Vec3b>(i,j)[1] = 255;
                image.at<cv::Vec3b>(i,j)[2] = 0;
            } else if(local_density > 0.0999f) {
                image.at<cv::Vec3b>(i,j)[0] = 255;
                image.at<cv::Vec3b>(i,j)[1] = 255;
                image.at<cv::Vec3b>(i,j)[2] = 0;
            } else if(local_density > 0.0995f) {
                image.at<cv::Vec3b>(i,j)[0] = 255;
                image.at<cv::Vec3b>(i,j)[1] = 128;
                image.at<cv::Vec3b>(i,j)[2] = 0;
            } else {
                image.at<cv::Vec3b>(i,j)[0] = 255;
                image.at<cv::Vec3b>(i,j)[1] = 0;
                image.at<cv::Vec3b>(i,j)[2] = 0;
            }
        }
    }

    // Add frame to the sequence
    vw->write(image);
}

#endif 

/*
** main program:
** initialise, timestep loop, finalise
*/
int main(int argc, char* argv[])
{
  char*    paramfile = NULL;    /* name of the input parameter file */
  char*    obstaclefile = NULL; /* name of a the input obstacle file */
  t_param  params;              /* struct to hold parameter values */
  t_speed* cells     = NULL;    /* grid containing fluid denfsities */
  t_speed* tmp_cells = NULL;    /* scratch space */
  int*     obstacles = NULL;    /* grid indicating which cells are blocked */
  double*  av_vels   = NULL;    /* a record of the av. velocity computed for each timestep */
  int      ii;                  /* generic counter */
  struct timeval timstr;        /* structure to hold elapsed time */
  struct rusage ru;             /* structure to hold CPU time--system and user */
  double tic,toc;               /* floating point numbers to calculate elapsed wallclock time */
  double usrtim;                /* floating point number to record elapsed user CPU time */
  double systim;                /* floating point number to record elapsed system CPU time */

  /* parse the command line */
  if(argc != 3) {
    usage(argv[0]);
  }
  else{
    paramfile = argv[1];
    obstaclefile = argv[2];
  }

  /* initialise our data structures and load values from file */
  initialise(paramfile, obstaclefile, &params, &cells, &tmp_cells, &obstacles, &av_vels);

  /* iterate for maxIters timesteps */
  gettimeofday(&timstr,NULL);
  tic=timstr.tv_sec+(timstr.tv_usec/1000000.0);

  #ifdef DEBUG
    cv::VideoWriter *vw = new cv::VideoWriter(
      "video.avi", // filename
      CV_FOURCC('P','I','M','1'), // codec
      200.0, // fps
      cv::Size(params.nx, params.ny), // size
      true); // isColor
  #endif

			dummyMethod3();
  for (ii=0;ii<params.maxIters;ii++) {
    accelerate_flow(params,cells,obstacles);
    propagate(params,cells,tmp_cells);
    av_vels[ii] = collision(params,cells,tmp_cells,obstacles);
#ifdef DEBUG
    add_frame(params, cells, obstacles, vw);    
    //printf("==timestep: %d==\n",ii);
    //printf("av velocity: %.12E\n", av_vels[ii]);
    //printf("tot density: %.12E\n",total_density(params,cells));
#endif
  }
			dummyMethod4();


  #ifdef DEBUG
    if(vw != NULL) {
      delete vw;
      vw = NULL;
    }
  #endif


  gettimeofday(&timstr,NULL);
  toc=timstr.tv_sec+(timstr.tv_usec/1000000.0);
  getrusage(RUSAGE_SELF, &ru);
  timstr=ru.ru_utime;        
  usrtim=timstr.tv_sec+(timstr.tv_usec/1000000.0);
  timstr=ru.ru_stime;        
  systim=timstr.tv_sec+(timstr.tv_usec/1000000.0);

  /* write final values and free memory */
  printf("==done==\n");
  printf("Reynolds number:\t\t%.12E\n",calc_reynolds(params,cells,obstacles));
  printf("Elapsed time:\t\t\t%.6lf (s)\n", toc-tic);
  printf("Elapsed user CPU time:\t\t%.6lf (s)\n", usrtim);
  printf("Elapsed system CPU time:\t%.6lf (s)\n", systim);
  write_values(params,cells,obstacles,av_vels);
  finalise(&params, &cells, &tmp_cells, &obstacles, &av_vels);
  
  return EXIT_SUCCESS;
}

int accelerate_flow(const t_param params, t_speed* cells, int* obstacles)
{
  int ii,jj;     /* generic counters */
  
  /* compute weighting factors */
  float w1 = params.density * params.accel / 9.0;
  float w2 = params.density * params.accel / 36.0;

  /* modify the 2nd row of the grid */
  ii=(params.ny - 2)*params.nx;
			dummyMethod1();
  #pragma omp parallel for
  for(jj=ii;jj<ii+params.nx;++jj) {
    /* if the cell is not occupied and
    ** we don't send a density negative */
    if( !obstacles[jj] && 
	(cells[jj].speeds[3] - w1) > 0.0 &&
	(cells[jj].speeds[6] - w2) > 0.0 &&
	(cells[jj].speeds[7] - w2) > 0.0 ) {
      /* increase 'east-side' densities */
      cells[jj].speeds[1] += w1;
      cells[jj].speeds[5] += w2;
      cells[jj].speeds[8] += w2;
      /* decrease 'west-side' densities */
      cells[jj].speeds[3] -= w1;
      cells[jj].speeds[6] -= w2;
      cells[jj].speeds[7] -= w2;
    }
  }
			dummyMethod2();

  return EXIT_SUCCESS;
}

int propagate(const t_param params, t_speed* cells, t_speed* tmp_cells)
{
  int ii;            /* generic counters */

  /* loop over _all_ cells */
			dummyMethod1();
  #pragma omp parallel for
  for(ii=0;ii<params.ny;++ii) {
    int jj=0;
    for(;jj<params.nx;++jj) {
      /* determine indices of axis-direction neighbours
      ** respectingav periodic boundary conditions (wrap around) */
      int y_n = (ii + 1 == params.ny) ? 0 : (ii+1);
      int x_e = (jj + 1 == params.nx) ? 0 : (jj+1);
      int y_s = (ii == 0) ? (params.ny - 1) : (ii - 1);
      int x_w = (jj == 0) ? (params.nx - 1) : (jj - 1);
      /* propagate densities to neighbouring cells, following
      ** appropriate directions of travel and writing into
      ** scratch space grid */
      int kk = ii*params.nx + jj;
      tmp_cells[kk].speeds[0]  = cells[kk].speeds[0]; /* central cell, */
                                                                                     /* no movement   */
      tmp_cells[ii *params.nx + x_e].speeds[1] = cells[kk].speeds[1]; /* east */
      tmp_cells[y_n*params.nx + jj].speeds[2]  = cells[kk].speeds[2]; /* north */
      tmp_cells[ii *params.nx + x_w].speeds[3] = cells[kk].speeds[3]; /* west */
      tmp_cells[y_s*params.nx + jj].speeds[4]  = cells[kk].speeds[4]; /* south */
      tmp_cells[y_n*params.nx + x_e].speeds[5] = cells[kk].speeds[5]; /* north-east */
      tmp_cells[y_n*params.nx + x_w].speeds[6] = cells[kk].speeds[6]; /* north-west */
      tmp_cells[y_s*params.nx + x_w].speeds[7] = cells[kk].speeds[7]; /* south-west */      
      tmp_cells[y_s*params.nx + x_e].speeds[8] = cells[kk].speeds[8]; /* south-east */      
    }
  }
			dummyMethod2();

  return EXIT_SUCCESS;
}

double collision(const t_param params, t_speed* cells, t_speed* tmp_cells, int* obstacles)
{
  int ii;                    /* generic counters */
  int    tot_cells = 0;         /* no. of cells used in calculation */                   
  float  tot_u = 0.0;           /* accumulated magnitudes of velocity for each cell */
  
  /* loop over the cells in the grid
  ** NB the collision step is called after
  ** the propagate step and so values of interest
  ** are in the scratch-space grid */
			dummyMethod1();
  #pragma omp parallel for reduction(+:tot_cells,tot_u)
  for(ii=0;ii<params.ny*params.nx;++ii) {
      /* don't consider occupied cells */
      if(!obstacles[ii]) {
	    /* compute local density total */
	    float local_density = 0.0;
	    int kk=8;
	    for(;kk>=0;kk--) {
	      local_density += tmp_cells[ii].speeds[kk];
	    }                 
	    /* compute x velocity component */
	    float u_x = (tmp_cells[ii].speeds[1] + 
	           tmp_cells[ii].speeds[5] + 
	           tmp_cells[ii].speeds[8]
	           - (tmp_cells[ii].speeds[3] + 
		      tmp_cells[ii].speeds[6] + 
		      tmp_cells[ii].speeds[7]))
	      / local_density;
	    /* compute y velocity component */
	    float u_y = (tmp_cells[ii].speeds[2] + 
	           tmp_cells[ii].speeds[5] + 
	           tmp_cells[ii].speeds[6]
	           - (tmp_cells[ii].speeds[4] + 
		      tmp_cells[ii].speeds[7] + 
		      tmp_cells[ii].speeds[8]))
	      / local_density;
	    
	    /* accumulate the norm of x- and y- velocity components */
		tot_u += sqrt((u_x * u_x) + (u_y * u_y));
		/* increase counter of inspected cells */
		++tot_cells;
		
	    /* velocity squared */ 
	    float u_sq = u_x * u_x + u_y * u_y;
	    /* directional velocity components */
	    float u[9]; 
	    u[1] =   u_x;        /* east */
	    u[2] =         u_y;  /* north */
	    u[3] = - u_x;        /* west */
	    u[4] =       - u_y;  /* south */
	    u[5] =   u_x + u_y;  /* north-east */
	    u[6] = - u_x + u_y;  /* north-west */
	    u[7] = - u_x - u_y;  /* south-west */
	    u[8] =   u_x - u_y;  /* south-east */
	    /* equilibrium densities */
	    float d_equ[9];
	    /* zero velocity density: weight w0=0.44444444444 */
	    d_equ[0] = 0.44444444444 * local_density * (1.0 - u_sq * 1.5);
	    /* axis speeds: weight w1=0.11111111111 */
	    d_equ[1] = 0.11111111111 * local_density * (1.0 + u[1] * 3.0
					     + (u[1] * u[1]) * 4.5
					     - u_sq * 1.5);
	    d_equ[2] = 0.11111111111 * local_density * (1.0 + u[2] * 3.0
					     + (u[2] * u[2]) * 4.5
					     - u_sq * 1.5);
	    d_equ[3] = 0.11111111111 * local_density * (1.0 + u[3] * 3.0
					     + (u[3] * u[3]) * 4.5
					     - u_sq * 1.5);
	    d_equ[4] = 0.11111111111* local_density * (1.0 + u[4] * 3.0
					     + (u[4] * u[4]) * 4.5
					     - u_sq * 1.5);
	    /* diagonal speeds: weight w2=0.02777777777 */
	    d_equ[5] = 0.02777777777 * local_density * (1.0 + u[5] * 3.0
					     + (u[5] * u[5]) * 4.5
					     - u_sq * 1.5);
	    d_equ[6] = 0.02777777777 * local_density * (1.0 + u[6] * 3.0
					     + (u[6] * u[6]) * 4.5
					     - u_sq * 1.5);
	    d_equ[7] = 0.02777777777 * local_density * (1.0 + u[7] * 3.0
					     + (u[7] * u[7]) * 4.5
					     - u_sq * 1.5);
	    d_equ[8] = 0.02777777777 * local_density * (1.0 + u[8] * 3.0
					     + (u[8] * u[8]) * 4.5
					     - u_sq * 1.5);
	    /* relaxation step */
	    for(kk=8;kk>=0;kk--) {
	      cells[ii].speeds[kk] = (tmp_cells[ii].speeds[kk]
						     + params.omega * 
						     (d_equ[kk] - tmp_cells[ii].speeds[kk]));
	    }
      } else {
      //rebound
        cells[ii].speeds[1] = tmp_cells[ii].speeds[3];
        cells[ii].speeds[2] = tmp_cells[ii].speeds[4];
        cells[ii].speeds[3] = tmp_cells[ii].speeds[1];
        cells[ii].speeds[4] = tmp_cells[ii].speeds[2];
        cells[ii].speeds[5] = tmp_cells[ii].speeds[7];
        cells[ii].speeds[6] = tmp_cells[ii].speeds[8];
        cells[ii].speeds[7] = tmp_cells[ii].speeds[5];
        cells[ii].speeds[8] = tmp_cells[ii].speeds[6];
      }
  }
			dummyMethod2();

  return tot_u / (double)tot_cells; 
}

int initialise(const char* paramfile, const char* obstaclefile,
	       t_param* params, t_speed** cells_ptr, t_speed** tmp_cells_ptr, 
	       int** obstacles_ptr, double** av_vels_ptr)
{
  char   message[1024];  /* message buffer */
  FILE   *fp;            /* file pointer */
  int    ii;             /* generic counters */
  int    xx,yy;          /* generic array indices */
  int    blocked;        /* indicates whether a cell is blocked by an obstacle */ 
  int    retval;         /* to hold return value for checking */
  double w0,w1,w2;       /* weighting factors */

  /* open the parameter file */
  fp = fopen(paramfile,"r");
  if (fp == NULL) {
    sprintf(message,"could not open input parameter file: %s", paramfile);
    die(message,__LINE__,__FILE__);
  }

  /* read in the parameter values */
  retval = fscanf(fp,"%d\n",&(params->nx));
  if(retval != 1) die ("could not read param file: nx",__LINE__,__FILE__);
  retval = fscanf(fp,"%d\n",&(params->ny));
  if(retval != 1) die ("could not read param file: ny",__LINE__,__FILE__);
  retval = fscanf(fp,"%d\n",&(params->maxIters));
  if(retval != 1) die ("could not read param file: maxIters",__LINE__,__FILE__);
  retval = fscanf(fp,"%d\n",&(params->reynolds_dim));
  if(retval != 1) die ("could not read param file: reynolds_dim",__LINE__,__FILE__);
  retval = fscanf(fp,"%f\n",&(params->density));
  if(retval != 1) die ("could not read param file: density",__LINE__,__FILE__);
  retval = fscanf(fp,"%f\n",&(params->accel));
  if(retval != 1) die ("could not read param file: accel",__LINE__,__FILE__);
  retval = fscanf(fp,"%f\n",&(params->omega));
  if(retval != 1) die ("could not read param file: omega",__LINE__,__FILE__);

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
  *cells_ptr = (t_speed*)malloc(sizeof(t_speed)*(params->ny*params->nx));
  if (*cells_ptr == NULL) 
    die("cannot allocate memory for cells",__LINE__,__FILE__);

  /* 'helper' grid, used as scratch space */
  *tmp_cells_ptr = (t_speed*)malloc(sizeof(t_speed)*(params->ny*params->nx));
  if (*tmp_cells_ptr == NULL) 
    die("cannot allocate memory for tmp_cells",__LINE__,__FILE__);
  
  /* the map of obstacles */
  *obstacles_ptr = (int*)malloc(sizeof(int)*(params->ny*params->nx));
  if (*obstacles_ptr == NULL) 
    die("cannot allocate column memory for obstacles",__LINE__,__FILE__);

  /* initialise densities */
  w0 = params->density * 4.0/9.0;
  w1 = params->density      /9.0;
  w2 = params->density      /36.0;

			dummyMethod3();
  for(ii=0;ii<params->ny*params->nx;++ii) {
      /* centre */
      (*cells_ptr)[ii].speeds[0] = w0;
      /* axis directions */
      (*cells_ptr)[ii].speeds[1] = w1;
      (*cells_ptr)[ii].speeds[2] = w1;
      (*cells_ptr)[ii].speeds[3] = w1;
      (*cells_ptr)[ii].speeds[4] = w1;
      /* diagonals */
      (*cells_ptr)[ii].speeds[5] = w2;
      (*cells_ptr)[ii].speeds[6] = w2;
      (*cells_ptr)[ii].speeds[7] = w2;
      (*cells_ptr)[ii].speeds[8] = w2;
  }
			dummyMethod4();

  /* first set all cells in obstacle array to zero */ 
			dummyMethod3();
  for(ii=0;ii<params->ny*params->nx;++ii) {
      (*obstacles_ptr)[ii] = 0;
  }
			dummyMethod4();

  /* open the obstacle data file */
  fp = fopen(obstaclefile,"r");
  if (fp == NULL) {
    sprintf(message,"could not open input obstacles file: %s", obstaclefile);
    die(message,__LINE__,__FILE__);
  }

  /* read-in the blocked cells list */
  while( (retval = fscanf(fp,"%d %d %d\n", &xx, &yy, &blocked)) != EOF) {
    /* some checks */
    if ( retval != 3)
      die("expected 3 values per line in obstacle file",__LINE__,__FILE__);
    if ( xx<0 || xx>params->nx-1 )
      die("obstacle x-coord out of range",__LINE__,__FILE__);
    if ( yy<0 || yy>params->ny-1 )
      die("obstacle y-coord out of range",__LINE__,__FILE__);
    if ( blocked != 1 ) 
      die("obstacle blocked value should be 1",__LINE__,__FILE__);
    /* assign to array */
    (*obstacles_ptr)[yy*params->nx + xx] = blocked;
  }
  
  /* and close the file */
  fclose(fp);

  /* 
  ** allocate space to hold a record of the avarage velocities computed 
  ** at each timestep
  */
  *av_vels_ptr = (double*)malloc(sizeof(double)*params->maxIters);

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

double av_velocity(const t_param params, t_speed* cells, int* obstacles)
{
  int    ii,kk;       /* generic counters */
  int    tot_cells = 0;  /* no. of cells used in calculation */                   
  double tot_u = 0.0;    /* accumulated magnitudes of velocity for each cell */

			dummyMethod1();
  #pragma omp parallel for reduction(+:tot_u,tot_cells)
  /* loop over all non-blocked cells */
  for(ii=0;ii<params.ny*params.nx;++ii) {
	/* ignore occupied cells */
	if(!obstacles[ii]) {
		/* local density total */
		float local_density = 0.0;
		for(kk=0;kk<9;kk++) {
			local_density += cells[ii].speeds[kk];
		}
		/* x-component of velocity for current cell */
		float u_x = (cells[ii].speeds[1] + 
		cells[ii].speeds[5] + 
		cells[ii].speeds[8]
		- (cells[ii].speeds[3] + 
		cells[ii].speeds[6] + 
		cells[ii].speeds[7])) / 
		local_density;
		/* y-component of velocity for current cell */
		float u_y = (cells[ii].speeds[2] + 
		cells[ii].speeds[5] + 
		cells[ii].speeds[6]
		- (cells[ii].speeds[4] + 
		cells[ii].speeds[7] + 
		cells[ii].speeds[8])) /
		local_density;
		/* accumulate the norm of x- and y- velocity components */
		tot_u += sqrt((u_x * u_x) + (u_y * u_y));
		/* increase counter of inspected cells */
		++tot_cells;
	}
  }
			dummyMethod2();

  return tot_u / (double)tot_cells;
}

double calc_reynolds(const t_param params, t_speed* cells, int* obstacles)
{
  const double viscosity = 1.0 / 6.0 * (2.0 / params.omega - 1.0);
  
  return av_velocity(params,cells,obstacles) * params.reynolds_dim / viscosity;
}

double total_density(const t_param params, t_speed* cells)
{
  int ii,jj,kk;        /* generic counters */
  double total = 0.0;  /* accumulator */

			dummyMethod3();
  for(ii=0;ii<params.ny;ii++) {
    for(jj=0;jj<params.nx;jj++) {
      for(kk=0;kk<9;kk++) {
	total += cells[ii*params.nx + jj].speeds[kk];
      }
    }
  }
			dummyMethod4();
  
  return total;
}

int write_values(const t_param params, t_speed* cells, int* obstacles, double* av_vels)
{
  FILE* fp;                     /* file pointer */
  int ii,jj,kk;                 /* generic counters */
  const double c_sq = 1.0/3.0;  /* sq. of speed of sound */
  double local_density;         /* per grid cell sum of densities */
  double pressure;              /* fluid pressure in grid cell */
  double u_x;                   /* x-component of velocity in grid cell */
  double u_y;                   /* y-component of velocity in grid cell */
  double u;                     /* norm--root of summed squares--of u_x and u_y */

  fp = fopen(FINALSTATEFILE,"w");
  if (fp == NULL) {
    die("could not open file output file",__LINE__,__FILE__);
  }

			dummyMethod3();
  for(ii=0;ii<params.ny;ii++) {
    for(jj=0;jj<params.nx;jj++) {
      /* an occupied cell */
      if(obstacles[ii*params.nx + jj]) {
	u_x = u_y = u = 0.0;
	pressure = params.density * c_sq;
      }
      /* no obstacle */
      else {
	local_density = 0.0;
	for(kk=0;kk<9;kk++) {
	  local_density += cells[ii*params.nx + jj].speeds[kk];
	}
	/* compute x velocity component */
	u_x = (cells[ii*params.nx + jj].speeds[1] + 
	       cells[ii*params.nx + jj].speeds[5] +
	       cells[ii*params.nx + jj].speeds[8]
	       - (cells[ii*params.nx + jj].speeds[3] + 
		  cells[ii*params.nx + jj].speeds[6] + 
		  cells[ii*params.nx + jj].speeds[7]))
	  / local_density;
	/* compute y velocity component */
	u_y = (cells[ii*params.nx + jj].speeds[2] + 
	       cells[ii*params.nx + jj].speeds[5] + 
	       cells[ii*params.nx + jj].speeds[6]
	       - (cells[ii*params.nx + jj].speeds[4] + 
		  cells[ii*params.nx + jj].speeds[7] + 
		  cells[ii*params.nx + jj].speeds[8]))
	  / local_density;
	/* compute norm of velocity */
	u = sqrt((u_x * u_x) + (u_y * u_y));
	/* compute pressure */
	pressure = local_density * c_sq;
      }
      /* write to file */
      fprintf(fp,"%d %d %.12E %.12E %.12E %.12E %d\n",jj,ii,u_x,u_y,u,pressure,obstacles[ii*params.nx + jj]);
    }
  }
			dummyMethod4();

  fclose(fp);

  fp = fopen(AVVELSFILE,"w");
  if (fp == NULL) {
    die("could not open file output file",__LINE__,__FILE__);
  }
			dummyMethod3();
  for (ii=0;ii<params.maxIters;ii++) {
    fprintf(fp,"%d:\t%.12E\n", ii, av_vels[ii]);
  }
			dummyMethod4();

  fclose(fp);

  return EXIT_SUCCESS;
}

void die(const char* message, const int line, const char *file)
{
  fprintf(stderr, "Error at line %d of file %s:\n", line, file);
  fprintf(stderr, "%s\n",message);
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