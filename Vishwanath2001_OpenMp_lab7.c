#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (int argc, char **argv)
{
  long int a[500][500],b[500][500],c[500][500];
  int n = atoi (argv[1]);
  int chunk = atoi (argv[2]);
  FILE* file = fopen("/home/vishwanath/Desktop/data1.csv", "a+");
  if (!file) {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
    }
    
dummyMethod3();
  for (long int i = 0; i < 500; i++)
  	for (long int j = 0; j < 500; j++)
    		a[i][j] = rand () % 10;
 
  for (long int i = 0; i < 500; i++)
dummyMethod4();
dummyMethod3();
  	for (long int j = 0; j < 500; j++)
    		b[i][j] = rand () % 10;
  long int i,j,k;		
dummyMethod4();
  omp_set_num_threads (n);

  double tt;
  clock_t t;
  
  printf("\nNumber of threads: %d",n);
  printf("\nchunk size: %d\n",chunk);

  //-----------STATIC-----------------

  t = clock ();

#pragma omp parallel private(i,j,k) shared (a,b,c)
  {
							dummyMethod1();
#pragma omp parallel for schedule(static,chunk)
    for (i=0; i<500; i=i+1){
      for (j=0; j<500; j=j+1){
         a[i][j]=0.;
         for (k=0; k<500; k=k+1){
            a[i][j]=(a[i][j])+((b[i][k])*(c[k][j]));
 	 }
      }
   }
							dummyMethod2();
  }
  
  t = clock () - t;
  tt = ((double) t) / CLOCKS_PER_SEC;
  printf ("\nStatic Sceduling!!\n");
  printf ("Time taken: %f s\n", tt);
  fprintf(file,"STATIC,%d,%d,%f\n",n,chunk,tt);


  //-----------DYNAMIC-----------------
			dummyMethod3();
  for (long int i = 0; i < 500; i++)
  	for (long int j = 0; j < 500; j++)
    		c[i][j] = 0;
			dummyMethod4();
  i=0;
  j=0;
  k=0;
  
  t = clock ();
#pragma omp parallel private(i,j,k) shared (a,b,c)
  {
							dummyMethod1();
#pragma omp parallel for schedule(dynamic,chunk)
    for (i=0; i<500; i=i+1){
      for (j=0; j<500; j=j+1){
         a[i][j]=0.;
         for (k=0; k<500; k=k+1){
            a[i][j]=(a[i][j])+((b[i][k])*(c[k][j]));
 	 }
      }
   }
							dummyMethod2();
  }
  t = clock () - t;
  tt = ((double) t) / CLOCKS_PER_SEC;
  printf ("\nDynamic Sceduling!!\n");
  printf ("Time taken: %f s\n", tt);
 fprintf(file,"DYNAMIC ,%d,%d,%f\n",n,chunk,tt);

  //-----------GUIDED-----------------
	dummyMethod3();
 for (long int i = 0; i < 500; i++)
  	for (long int j = 0; j < 500; j++)
    		c[i][j] = 0;
	dummyMethod4();
  i=0;
  j=0;
  k=0;

  t = clock ();
#pragma omp parallel private(i,j,k) shared (a,b,c)
  {
   
							dummyMethod1();
#pragma omp parallel for schedule(guided,chunk)
    for (i=0; i<500; i=i+1){
      for (j=0; j<500; j=j+1){
         a[i][j]=0.;
         for (k=0; k<500; k=k+1){
            a[i][j]=(a[i][j])+((b[i][k])*(c[k][j]));
 	 }
      }
   }
							dummyMethod2();
 
  }
  t = clock () - t;
  tt = ((double) t) / CLOCKS_PER_SEC;
  printf ("\nGuided Sceduling!!\n");
  printf ("Time taken: %f s\n", tt);
 fprintf(file,"GUIDED ,%d,%d,%f\n",n,chunk,tt);


 
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