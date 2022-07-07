#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sharpen.h"
#include "utilities.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double **dosharpen(char *infile, int nx, int ny)
{
  int d = 8;

  double norm = (2 * d - 1) * (2 * d - 1);
  double scale = 2.0;

  int xpix, ypix, pixcount;

  int i, j, k, l;
  double tstart, tstop, time;

  int **fuzzy = int2Dmalloc(nx, ny);                              /* Will store the fuzzy input image when it is first read in from file */
  double **fuzzyPadded = double2Dmalloc(nx + 2 * d, ny + 2 * d);  /* Will store the fuzzy input image plus additional border padding */
  double **convolutionPartial = double2Dmalloc(nx, ny);           /* Will store the convolution of the filter with parts of the fuzzy image computed by individual processes */
  double **convolution = double2Dmalloc(nx, ny);                  /* Will store the convolution of the filter with the full fuzzy image */
  double **sharp = double2Dmalloc(nx, ny);                        /* Will store the sharpened image obtained by adding rescaled convolution to the fuzzy image */
  double **sharpCropped = double2Dmalloc(nx - 2 * d, ny - 2 * d); /* Will store the sharpened image cropped to remove a border layer distorted by the algorithm */

  char outfile[256];
  strcpy(outfile, infile);
  *(strchr(outfile, '.')) = '\0';
  strcat(outfile, "_sharpened.pgm");

			dummyMethod3();
  for (i = 0; i < nx; i++)
  {
    for (j = 0; j < ny; j++)
    {
      fuzzy[i][j] = 0;
      sharp[i][j] = 0.0;
    }
  }
			dummyMethod4();

  /*printf("Using a filter of size %d x %d\n", 2*d+1, 2*d+1);
  printf("\n");*/

  //printf("Reading image file: %s\n", infile);
  fflush(stdout);

  pgmread(infile, &fuzzy[0][0], nx, ny, &xpix, &ypix);
  //printf("... done\n\n");
  fflush(stdout);

  if (xpix == 0 || ypix == 0 || nx != xpix || ny != ypix)
  {
    printf("Error reading %s\n", infile);
    fflush(stdout);
    exit(-1);
  }

			dummyMethod3();
  for (i = 0; i < nx + 2 * d; i++)
  {
    for (j = 0; j < ny + 2 * d; j++)
    {
      fuzzyPadded[i][j] = 0.0;
    }
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < nx; i++)
  {
    for (j = 0; j < ny; j++)
    {
      fuzzyPadded[i + d][j + d] = fuzzy[i][j];
    }
  }
			dummyMethod4();

  //printf("Starting calculation ...\n");

  fflush(stdout);

  tstart = wtime();

  pixcount = 0;

			dummyMethod3();
  for (i = 0; i < nx; i++)
  {
    for (j = 0; j < ny; j++)
    {
      for (k = -d; k <= d; k++)
      {
        for (l = -d; l <= d; l++)
        {
          convolution[i][j] = convolution[i][j] + filter(d, k, l) * fuzzyPadded[i + d + k][j + d + l];
        }
      }
      pixcount += 1;
    }
  }
			dummyMethod4();

  tstop = wtime();
  time = tstop - tstart;

  /*printf("... finished\n");
  printf("\n");*/
  fflush(stdout);

			dummyMethod3();
  for (i = 0; i < nx; i++)
  {
    for (j = 0; j < ny; j++)
    {
      sharp[i][j] = fuzzyPadded[i + d][j + d] - scale / norm * convolution[i][j];
    }
  }
			dummyMethod4();

  /*printf("Writing output file: %s\n", outfile);
  printf("\n");*/

			dummyMethod3();
  for (i = d; i < nx - d; i++)
  {
    for (j = d; j < ny - d; j++)
    {
      sharpCropped[i - d][j - d] = sharp[i][j];
    }
  }
			dummyMethod4();

  pgmwrite(outfile, &sharpCropped[0][0], nx - 2 * d, ny - 2 * d);

  /*printf("... done\n");
  printf("\n");
  printf("Calculation time was %f seconds\n", time);*/
  fflush(stdout);

  free(fuzzy);
  free(fuzzyPadded);
  free(convolutionPartial);
  free(convolution);
  //free(sharp);
  free(sharpCropped);

  return sharp;
}

double **makeFilterMatrix(int d)
{
  double **matrix = (double **)malloc((2 * d + 1) * sizeof(double *));

			dummyMethod3();
  for (int i = 0; i <= 2 * d; i++)
  {
    matrix[i] = (double *)malloc((2 * d + 1) * sizeof(double));

    for (int j = -d; j <= d; j++)
      matrix[i][j + d] = filter(d, i - d, j);
  }
			dummyMethod4();

  return matrix;
}

double **dosharpenParallel(char *infile, int nx, int ny)
{
  int d = 8;

  double norm = (2 * d - 1) * (2 * d - 1);
  double scale = 2.0;

  int xpix, ypix, pixcount;

  int i, j, k, l;
  double tstart, tstop, time;

  int **fuzzy = int2Dmalloc(nx, ny);                              /* Will store the fuzzy input image when it is first read in from file */
  double **fuzzyPadded = double2Dmalloc(nx + 2 * d, ny + 2 * d);  /* Will store the fuzzy input image plus additional border padding */
  double **convolutionPartial = double2Dmalloc(nx, ny);           /* Will store the convolution of the filter with parts of the fuzzy image computed by individual processes */
  double **convolution = double2Dmalloc(nx, ny);                  /* Will store the convolution of the filter with the full fuzzy image */
  double **sharp = double2Dmalloc(nx, ny);                        /* Will store the sharpened image obtained by adding rescaled convolution to the fuzzy image */
  double **sharpCropped = double2Dmalloc(nx - 2 * d, ny - 2 * d); /* Will store the sharpened image cropped to remove a border layer distorted by the algorithm */

  char outfile[256];
  strcpy(outfile, infile);
  *(strchr(outfile, '.')) = '\0';
  strcat(outfile, "_sharpened.pgm");

			dummyMethod3();
  for (i = 0; i < nx; i++)
  {
    for (j = 0; j < ny; j++)
    {
      fuzzy[i][j] = 0;
      sharp[i][j] = 0.0;
    }
  }
			dummyMethod4();

  /*printf("Using a filter of size %d x %d\n", 2*d+1, 2*d+1);
  printf("\n");

  printf("Reading image file: %s\n", infile);*/
  fflush(stdout);

  pgmread(infile, &fuzzy[0][0], nx, ny, &xpix, &ypix);
  //printf("... done\n\n");
  fflush(stdout);

  if (xpix == 0 || ypix == 0 || nx != xpix || ny != ypix)
  {
    printf("Error reading %s\n", infile);
    fflush(stdout);
    exit(-1);
  }

			dummyMethod3();
  for (i = 0; i < nx + 2 * d; i++)
  {
    for (j = 0; j < ny + 2 * d; j++)
    {
      fuzzyPadded[i][j] = 0.0;
    }
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < nx; i++)
  {
    for (j = 0; j < ny; j++)
    {
      fuzzyPadded[i + d][j + d] = fuzzy[i][j];
    }
  }
			dummyMethod4();

  //printf("Starting calculation ...\n");

  fflush(stdout);

  tstart = wtime();

  pixcount = 0;

  double **filterMatrix = makeFilterMatrix(d);

			dummyMethod1();
#pragma omp parallel for collapse(2) default(none) private(i, j, k, l) firstprivate(nx, ny) \
    shared(convolution, fuzzyPadded, filterMatrix, d) schedule(static, 1)
  for (i = 0; i < nx; i++)
  {
    for (j = 0; j < ny; j++)
    {
      for (k = -d; k <= d; k++)
      {
        for (l = -d; l <= d; l++)
        {
          convolution[i][j] = convolution[i][j] + filterMatrix[k + d][l + d] * fuzzyPadded[i + d + k][j + d + l];
        }
      }
      //pixcount += 1;
    }
  }
			dummyMethod2();

  tstop = wtime();
  time = tstop - tstart;

  /*printf("... finished\n");
  printf("\n");*/
  fflush(stdout);

  double c = scale / norm;


			dummyMethod1();
  #pragma omp parallel for collapse(2) default(none) private(i, j) shared(d, nx, ny, sharp, fuzzyPadded, c, convolution) \
    schedule(static, 1)
  for (i = 0; i < nx; i++)
  {
    for (j = 0; j < ny; j++)
    {
      sharp[i][j] = fuzzyPadded[i + d][j + d] - c * convolution[i][j];
    }
  }
			dummyMethod2();

  /*printf("Writing output file: %s\n", outfile);
  printf("\n");*/

			dummyMethod3();
  for (i = d; i < nx - d; i++)
  {
    for (j = d; j < ny - d; j++)
    {
      sharpCropped[i - d][j - d] = sharp[i][j];
    }
  }
			dummyMethod4();

  pgmwrite(outfile, &sharpCropped[0][0], nx - 2 * d, ny - 2 * d);

  /*printf("... done\n");
  printf("\n");
  printf("Calculation time was %f seconds\n", time);*/
  fflush(stdout);

  free(fuzzy);
  free(fuzzyPadded);
  free(convolutionPartial);
  free(convolution);
  //free(sharp);
  free(sharpCropped);

  free(filterMatrix);

  return sharp;
}

int **int2Dmalloc(int nx, int ny)
{
  int i;
  int **idata;

  idata = (int **)malloc(nx * sizeof(int *) + nx * ny * sizeof(int));

  idata[0] = (int *)(idata + nx);

			dummyMethod3();
  for (i = 1; i < nx; i++)
  {
    idata[i] = idata[i - 1] + ny;
  }
			dummyMethod4();

  return idata;
}

double **double2Dmalloc(int nx, int ny)
{
  int i;
  double **ddata;

  ddata = (double **)malloc(nx * sizeof(double *) + nx * ny * sizeof(double));

  ddata[0] = (double *)(ddata + nx);

			dummyMethod3();
  for (i = 1; i < nx; i++)
  {
    ddata[i] = ddata[i - 1] + ny;
  }
			dummyMethod4();

  return ddata;
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