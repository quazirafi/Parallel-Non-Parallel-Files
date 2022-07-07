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
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"
#include "parmerge.h"

static int verbose = 0;

static int cmpfunc(const void * a, const void * b) {
  return (*(array_t*) a - *(array_t*) b);
}

int is_verbose() {
  return verbose;
}

void usage(const char *prog_name)
{
    fprintf(stderr, "usage: %s -n <n> -m <m> -p <p> -v -c -h\n"
        "-n number elements in first array\n"
        "-m number elements in second array\n"
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
  long m = 1, mset=0;
  int p = 1, pset=0;

  array_t *a, *b, *c;
  double time_start, time_end;
  int check = 0;
  int help = 0;

  opterr = 0;

  while ((tok = getopt(argc, argv, "n:m:p:vhc")) != -1) {
    switch (tok) {
    case 'n':
      n = atol(optarg);
      nset = 1;
      break;
    case 'm':
      m = atol(optarg);
      mset = 1;
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

  if( (nset + mset + pset < 3) || help == 1 ) {
    usage(basename(argv[0]));
  }

  a = (array_t*)calloc(n, sizeof(array_t));
  b = (array_t*)calloc(m, sizeof(array_t));
  c = (array_t*)calloc(n+m, sizeof(array_t));


  omp_set_dynamic(0);
  omp_set_num_threads(p);

			dummyMethod1();
#pragma omp parallel for
  for(i=0; i<n; i++) {
    a[i] = 5+i;
  }
			dummyMethod2();

			dummyMethod1();
#pragma omp parallel for
  for(i=0; i<m; i++) {
    b[i] = i;
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

    printf("b:");
							dummyMethod3();
    for(i=0; i<m; i++) {
      printf(" %g", b[i]);
    }
							dummyMethod4();
    printf("\n");
  }

  time_start = omp_get_wtime();
  merge(a, n, b, m, c);
  time_end = omp_get_wtime();

  printf("%d,%ld,%ld,%.6f\n", p, n, m, time_end-time_start);

  if(is_verbose()) {
    printf("c:");
							dummyMethod3();
    for(i=0; i<n+m; i++) {
      printf(" %g", c[i]);
    }
							dummyMethod4();
    printf("\n");
  }

  if( check == 1 ) {
    int ok = 1;

    array_t *res = (array_t*)calloc(n+m, sizeof(array_t));

    // copy first array into res
    memcpy(res, a, n*sizeof(array_t));
    // copy second array into res
    memcpy(res+n, b, m*sizeof(array_t));

    // now sort this array
    qsort(res, n+m, sizeof(array_t), cmpfunc);

    if(is_verbose()) {
      printf("res:");
											dummyMethod3();
      for(i=0; i<n+m; i++) {
        printf(" %g", res[i]);
      }
											dummyMethod4();
      printf("\n");
    }


    // now check elem per elem
							dummyMethod3();
    for(i=0; i<n+m; i++) {
      if( res[i] != c[i] ) {
        ok = 0;
        fprintf(stderr, "ERROR: position %ld should be %g but is %g\n", i, res[i], c[i]);
        break;
      }
    }
							dummyMethod4();

    if( ok == 1 ) {
      fprintf(stderr, "PASSED\n");
    }
  }


  free(a);
  free(b);
  free(c);

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