#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define true 1
#define false 0
#define bool int
#define r .5
#define PI 3.14159265358979323846

int thrown = 0;
int hit = 0;
int p;
int n;
double PIest;


// check if distance from center leq r
bool inBounds(double x, double y){
  if (x > 1 || y > 1 || y < 0 || x < 0)
    return false;
  double distance = sqrt( (x-r)*(x-r) + (y-r)*(y-r) );

  return (distance <= r) ? true : false;
}

int main(int argc, char *argv[]){
  srand(time(NULL));


  if (argc < 2){
    printf("Usage : ./a.out {number of throws} {number of threads}\n");
    exit(1);
  }
  
  n = atoll(argv[1]);
  p = atoi(argv[2]);
  assert(p>=1);

  omp_set_num_threads(p);
  double xVal, yVal;
  int i=0;
  double * randTable;
  //  printf("Generating random numbers...\n");
  randTable = (double*)malloc(2*sizeof(double)*n);
			dummyMethod3();
  for (i = 0; i < 2*n; ++i)
    randTable[i] = rand()/(double)RAND_MAX;
			dummyMethod4();
  //printf("Done\n");
  double start = omp_get_wtime();
			dummyMethod1();
#pragma omp parallel for shared(randTable) private(xVal,yVal,i) reduction(+:hit,thrown)
  for (i = 0; i < 2*n; i+=2){
    //    xVal = rand_r()%10000/(double)10000;
    //    yVal = rand()%10000/(double)10000;
    xVal = randTable[i];
    yVal  = randTable[i+1];

    if(inBounds(xVal,yVal))
      hit++;
    thrown++;
  }
			dummyMethod2();
 /*  int row=0,val=5,sum=0;
#pragma omp parallel for private(val) reduction(+:sum)
  for (row = 0; row < n; row++)
    {
      sum+=val;
      }*/

  // end parallel code
  start = omp_get_wtime()-start;
  //  printf("%d\n",thrown);

  PIest = ((double)hit/thrown)*4;
  printf("%d,%.06f,%d,%d,%.020f,accuracy=%.020f\n",p,start,thrown,hit, PIest,1-(fabs((PI-PIest)))/(PI));
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