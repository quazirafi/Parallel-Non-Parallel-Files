/* Approximate pi using a Left Riemann Sum under a quarter unit circle. */

/* Author: Aaron Weeden, Shodor, 2015 */

#include <float.h>   /* DBL_EPSILON, DBL_DIG */
#include <unistd.h>  /* getopt(), optarg */
#include "omp.h"
#include <math.h>    /* sqrt() */
#include <mpi.h>     /* MPI_Init(), etc. */
#include <stdbool.h> /* bool type */
#include <stdio.h>   /* fprintf(), printf() */
#include <stdlib.h>  /* atoi(), atof(), exit(), EXIT_FAILURE */
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Define default number of rectangles per process */
#define RECTS_PER_PROC_DEFAULT 10

/* Define description of input parameter for number of rectangles per process */
#define RECTS_PER_PROC_DESCR \
  "This many rectangles will be used per process (positive integer)"

/* Define character used on the command line to change the number of
   rectangles per process */
#define RECTS_PER_PROC_CHAR 'r'

/* Define rank of process who has unique work to do */
#define BOSS 0

/* Define options string used by getopt() - a colon after the character means
   the parameter's value is specified by the user */
char const GETOPT_STRING[] = {
  RECTS_PER_PROC_CHAR, ':'
};

int main(int argc, char **argv) {
  /* Start the timer */
  double startTime = omp_get_wtime();
  bool isError = false;

  /* Start MPI */
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /* Get user options for number of rectangles per process */
  unsigned long long int rectsPerProc = RECTS_PER_PROC_DEFAULT;
  char c;
  while ((c = getopt(argc, argv, GETOPT_STRING)) != -1) {
    switch(c) {
      /* The user has chosen to change the number of rectangles per process */
      case RECTS_PER_PROC_CHAR:
        /* Get integer value */
        rectsPerProc = strtoull(optarg, NULL, 10);
        /* Make sure positive and equal to floating point value */
        if (rectsPerProc < 1 || atof(optarg) != rectsPerProc) {
          fprintf(stderr, "ERROR: value for -%c must be positive integer\n",
                  RECTS_PER_PROC_CHAR);
          isError = true;
        }
        break;
        /* The user has chosen an unknown option */
      default:
        isError = true;
    }
  }

  /* If there was an error in input, print a usage message and exit early */
  if (isError) {
    fprintf(stderr, "Usage: ");
    fprintf(stderr, "%s [OPTIONS]\n", argv[0]);
    fprintf(stderr, "Where OPTIONS can be any of the following:\n");
    fprintf(stderr, "-%c : \n\t%s\n\tdefault: %d\n", RECTS_PER_PROC_CHAR,
            RECTS_PER_PROC_DESCR, RECTS_PER_PROC_DEFAULT);
    exit(EXIT_FAILURE);
  }

  /* Calculate the width of each rectangle */
  double const width = (double)1 / (rectsPerProc * size);

  /* Sum areas of all rectangles */
  double myAreaSum = 0.0;
			dummyMethod1();
#pragma omp parallel for reduction(+:myAreaSum)
  for (int i = 0; i < rectsPerProc; i++) {
    /* Calculate the x-coordinate of the rectangle's left side */
    double const x = (rank * rectsPerProc + i) * width;

    /* Use the circle equation to calculate the rectangle's height squared */
    double const heightSq = 1.0 - x * x;

    /* If the height squared is so close to zero that the sqrt() function would
       return -inf, do not call the sqrt() function, just set the height to zero
       */
    double const height = (heightSq < DBL_EPSILON) ? 0.0 : sqrt(heightSq);

    /* Calculate the area of the rectangle and add it to the total */
    myAreaSum += width * height;
  }
			dummyMethod2();

  /* Reduce all the process' sums into a single sum */
  double areaSum;
  if (MPI_Reduce(&myAreaSum, /* send buffer */
                   &areaSum, /* receive buffer (destination process only) */
                          1, /* count */
                 MPI_DOUBLE, /* type */
                    MPI_SUM, /* operation */
                       BOSS, /* rank of destination process */
             MPI_COMM_WORLD) != MPI_SUCCESS) {
    /* Exit if the reduction failed */
    fprintf(stderr, "ERROR: MPI_Reduce() failed\n");
    exit(EXIT_FAILURE);
  }

  if (rank == BOSS) {
    /* Calculate pi and print it */
    printf("%.*f\n", DBL_DIG, 4.0 * areaSum);
    printf("Value of pi from math.h is %.*f\n", DBL_DIG, M_PI);

    /* Stop the timer, print the total elapsed time */
    printf("Runtime: %f seconds\n",
      omp_get_wtime() - startTime);
  }

  /* Stop MPI */
  MPI_Finalize();

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