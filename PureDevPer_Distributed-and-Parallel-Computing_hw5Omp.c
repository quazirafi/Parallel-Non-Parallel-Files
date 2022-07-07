// Wooseok Kim
// Homework #5

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "omp.h"
#include "timing.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double getRand(double min, double max);

int main(int argc, char*argv[])
{
	if(argc<3)
  {
    perror("\nUsage ./generateInput <squareMatrixSize>\n");
    exit(-1);
  }

  int matrixSize = atoi(argv[1]);
  int nThreads = atoi(argv[2]);
  
  int i, j, k;
  
  // Time measurement start
  timing_start();

  // fp - inputMatrix
  // fp1 - inputMatrix1
  // fp2 - outputMatrix
  FILE *fp, *fp1, *fp2;
  double min=0.00001, max=100000;;
  char comma[2];
  fp = fopen("inputMatrix.csv", "w");
  fp1 = fopen("inputMatrix1.csv", "w");
  fp2 = fopen("outputMatrix.csv", "w");
  srand(time(NULL));
  fprintf(fp, "%d\n", matrixSize);
  fprintf(fp1, "%d\n", matrixSize);
  fprintf(fp2, "%d\n", matrixSize);

  // inputMatrix
  double array[matrixSize][matrixSize];
  // inputMatrix 1
  double array2[matrixSize][matrixSize];
  // ouputMatrix
  double array4[matrixSize][matrixSize];

  // Array creation which has random values 
  // (Used generateSquareMatrix file)


{
// Open MP 
// All arrays are shared
// i,j, and k have independent values which means that the values are not shared
// Creation of Threads
			dummyMethod1();
#pragma omp parallel for shared(array, array2, array4) private( i, j, k) num_threads(nThreads)
  for(i=0;i<matrixSize;i++)
  {
    sprintf(comma, "%s", "");
    for(j=0;j<matrixSize;j++)
    {
      double d = getRand(min, max);
      array[i][j] = d;
      double d1 = getRand(min, max);
      array4[i][j] = d1;
      fprintf(fp, "%s%f",comma,d);
      fprintf(fp1, "%s%f",comma,d1);
      sprintf(comma, "%s", ",");

      array2[i][j] = 0;
    }
      fprintf(fp, "\n");
      fprintf(fp1, "\n");
  }
			dummyMethod2();

  fclose(fp);
  fclose(fp1);

  // Move columns in order to speed up
  int r;

							dummyMethod1();
#pragma omp parallel for shared(array, array2, array4) private(i, j, k) num_threads(nThreads) 
    for(k=0;k<matrixSize;++k){
      for(i=0;i<matrixSize;++i){
        r = array[i][k];
        for(j=0;j<matrixSize;++j){
          array2[i][j] += r*array4[k][j];
        }
    }
  }
							dummyMethod2();
}
  // End of time measurement
  timing_stop();
  print_timing();

  // Write outputMatrix
			dummyMethod3();
  for(i=0;i<matrixSize;++i){
  	sprintf(comma, "%s", "");
  	for(j=0;j<matrixSize;++j){
  		fprintf(fp2, "%s%f",comma,array2[i][j]);
  		sprintf(comma, "%s", ",");
  	}
  	fprintf(fp2, "\n");
  }
			dummyMethod4();

  fclose(fp2);

  return 0;
}


double getRand(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
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