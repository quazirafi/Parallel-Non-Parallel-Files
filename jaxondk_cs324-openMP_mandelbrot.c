/*
  This program is an adaptation of the Mandelbrot program
  from the Programming Rosetta Stone, see
  http://rosettacode.org/wiki/Mandelbrot_set
  Compile the program with:
  gcc -o mandelbrot -O4 mandelbrot.c
  Usage:

  ./mandelbrot <xmin> <xmax> <ymin> <ymax> <maxiter> <xres> <out.ppm>
  Example:
  ./mandelbrot 0.27085 0.27100 0.004640 0.004810 1000 1024 pic.ppm
  The interior of Mandelbrot set is black, the levels are gray.
  If you have very many levels, the picture is likely going to be quite
  dark. You can postprocess it to fix the palette. For instance,
  with ImageMagick you can do (assuming the picture was saved to pic.ppm):
  convert -normalize pic.ppm pic.png
  The resulting pic.png is still gray, but the levels will be nicer. You
  can also add colors, for instance:
  convert -negate -normalize -fill blue -tint 100 pic.ppm pic.png
  See http://www.imagemagick.org/Usage/color_mods/ for what ImageMagick
  can do. It can do a lot.
*/


/* COMPUTATION TIMES - each time is the average of 10 iterations
    1 thread: 28.714
    2 threads: 14.784
    4 threads: 7.812
    8 threads: 7.839

    If you want to run it, just make the desired number of threads the last argument
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double When()
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

int main(int argc, char* argv[])
{
  /* Parse the command line arguments. */
  if (argc != 8 && argc != 9) {
    printf("Usage:   %s <xmin> <xmax> <ymin> <ymax> <maxiter> <xres> <out.ppm> [<nthreads>]\n", argv[0]);
    printf("Example: %s 0.27085 0.27100 0.004640 0.004810 1000 1024 pic.ppm 8\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* The window in the plane. */
  const double xmin = atof(argv[1]);
  const double xmax = atof(argv[2]);
  const double ymin = atof(argv[3]);
  const double ymax = atof(argv[4]);

  /* Maximum number of iterations, at most 65535. */
  const uint16_t maxiter = (unsigned short)atoi(argv[5]);

  /* Image size, width is given, height is computed. */
  const int xres = atoi(argv[6]);
  const int yres = (xres*(ymax-ymin))/(xmax-xmin);

  /* The output file name */
  const char* filename = argv[7];

  /* Open the file and write the header. */
  FILE * fp = fopen(filename,"wb");
  char *comment="# Mandelbrot set";/* comment should start with # */

  /*write ASCII header to the file*/
  fprintf(fp,
          "P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n",
          xmin, xmax, ymin, ymax, maxiter, xres, yres, (maxiter < 256 ? 256 : maxiter));

  /* Precompute pixel width and height. */
  double dx=(xmax-xmin)/xres;
  double dy=(ymax-ymin)/yres;

  double x, y; /* Coordinates of the current point in the complex plane. */
  double u, v; /* Coordinates of the iterated point. */
  int i,j; /* Pixel counters */
  int k; /* Iteration counter */

  //Initialize result array
  int **result = (int**)malloc(xres*sizeof(int*));
			dummyMethod3();
  for (int i = 0; i < xres; i++) {
      result[i] = (int*)malloc(yres*sizeof(int));
  }
			dummyMethod4();

  if((argc == 9))
    omp_set_num_threads(atoi(argv[8]));

  double start = When();
  // for (size_t i = 0; i < 10; i++) { //for calculating times with different number of threads
			dummyMethod1();
  #pragma omp parallel for private(i,j,k,y,x,u,v) schedule(dynamic,4)
  for (j = 0; j < yres; j++) {
    y = ymax - j * dy;
    for(i = 0; i < xres; i++) {
      double u = 0.0;
      double v= 0.0;
      double u2 = u * u;
      double v2 = v*v;
      x = xmin + i * dx;
      /* iterate the point */
      for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++) {
            v = 2 * u * v + y;
            u = u2 - v2 + x;
            u2 = u * u;
            v2 = v * v;
      };


      result[i][j] = k;
    }
  }
			dummyMethod2();
  // }
  double stop = When();
  // printf("Average Computation time for %s threads: %f\n", argv[8], (stop - start)/10);
  printf("Computation time %f\n", stop - start);

  //write result to file
  const unsigned char black[] = {0, 0, 0, 0, 0, 0};
  unsigned char color[6];
			dummyMethod3();
  for(int j = 0; j < yres; j++) {
      for (int i = 0; i < xres; i++) {
          if (k >= maxiter) {
              fwrite(black, 6, 1, fp);
          }
          else {
              color[0] = result[i][j] >> 8;
              color[1] = result[i][j] & 255;
              color[2] = result[i][j] >> 8;
              color[3] = result[i][j] & 255;
              color[4] = result[i][j] >> 8;
              color[5] = result[i][j] & 255;
              fwrite(color, 6, 1, fp);
          }
      }
  }
			dummyMethod4();
  fclose(fp);
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