/*
 * parmerge_tester.c
 *
 *  Created on: Mar 12, 2019
 *      Author: sascha
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"
#include "parmergesort.h"

static int verbose = 0;

static int cmpfunc(const void * a, const void * b) {
  return (*(array_t*) a - *(array_t*) b);
}

int is_verbose() {
  return verbose;
}

void usage(const char *prog_name)
{
    fprintf(stderr, "usage: %s -n <n> -p <p> -v -c -h\n"
        "-n number elements in array\n"
        "-p number threads\n"
        "-c check results\n"
        "-v verbose mode\n"
        "-h print this help message\n"
        , prog_name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

  int tok;
  long i;
  long n = 1, nset=0;
  int p = 1, pset=0;
  array_t *a;
  double time_start, time_end;
  int check = 0;
  int help = 0;

  opterr = 0;

  while ((tok = getopt(argc, argv, "n:m:p:vch")) != -1) {
    switch (tok) {
    case 'n':
      n = atol(optarg);
      nset = 1;
      break;
    case 'p':
      p = atoi(optarg);
      pset = 1;
      break;
    case 'v':
      verbose = 1;
      break;
    case 'h':
      help = 1;
      break;
    case 'c':
      check = 1;
      break;
    default:
      fprintf(stderr, "unknown parameter\n");
      exit(1);
    }
  }

  if( (nset + pset < 2) || help == 1 ) {
    usage(basename(argv[0]));
  }


  a = (array_t*)malloc(n * sizeof(array_t));

  omp_set_dynamic(0);
  omp_set_num_threads(p);

			dummyMethod1();
#pragma omp parallel for
  for(i=0; i<n; i++) {
    a[i] = n-i;
  }
			dummyMethod2();

  if(is_verbose()) {
    printf("a:");
							dummyMethod3();
    for(i=0; i<n; i++) {
      printf(" %g", a[i]);
    }
							dummyMethod4();
    printf("\n");
  }

  time_start = omp_get_wtime();
  par_mergesort(a, n);
  time_end = omp_get_wtime();

  printf("%d,%ld,%.6f\n", p, n, time_end-time_start);

  if(is_verbose()) {
    printf("sorted:");
							dummyMethod3();
    for(i=0; i<n; i++) {
      printf(" %g", a[i]);
    }
							dummyMethod4();
    printf("\n");
  }


  if( check == 1 ) {
    int ok = 1;

    array_t *res = (array_t*)calloc(n, sizeof(array_t));
							dummyMethod3();
    for(i=0; i<n; i++) {
      res[i] = n-i;
    }
							dummyMethod4();

    // now sort this array
    qsort(res, n, sizeof(array_t), cmpfunc);

    if(is_verbose()) {
      printf("res:");
											dummyMethod3();
      for(i=0; i<n; i++) {
        printf(" %g", res[i]);
      }
											dummyMethod4();
      printf("\n");
    }


    // now check elem per elem
							dummyMethod3();
    for(i=0; i<n; i++) {
      if( res[i] != a[i] ) {
        ok = 0;
        fprintf(stderr, "ERROR: position %ld should be %g but is %g\n", i, res[i], a[i]);
        break;
      }
    }
							dummyMethod4();

    if( ok == 1 ) {
      fprintf(stderr, "PASSED\n");
    }
  }

  free(a);

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