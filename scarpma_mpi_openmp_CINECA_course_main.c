#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv)
{
   int n;
   int i, j, k;

   if(argc != 2) {
      fprintf(stderr,"Usage: %s  matrix size\n", argv[0]);
      exit(EXIT_FAILURE);
    }

   n = atoi(argv[1]);
   if ( n > 0) {
     printf("Matrix size is %d\n",n);
   }
   else {
     fprintf(stderr,"Error, matrix size is %d \n", n);
     exit(EXIT_FAILURE);
   }

   double (*a)[n] =  malloc(sizeof(double[n][n]));
   double (*b)[n] =  malloc(sizeof(double[n][n]));
   double (*c)[n] =  malloc(sizeof(double[n][n]));

   if ( a == NULL || b == NULL || c == NULL) {
       fprintf(stderr, "Not enough memory!\n");
       exit(EXIT_FAILURE);
    }

					dummyMethod3();
   for (i=0; i<n; i++) 
      for (j=0; j<n; j++) {
         a[i][j] = ((double)rand())/((double)RAND_MAX);
         b[i][j] = ((double)rand())/((double)RAND_MAX);
         c[i][j] = 0.0;
      }
					dummyMethod4();

					dummyMethod1();
#pragma omp parallel for private(k,j)
   for (i=0; i<n; i++) 
     for (k=0; k<n; k++)  
        for (j=0; j<n; j++) 
          c[i][j] += a[i][k]*b[k][j];
					dummyMethod2();

   //check a random element
   i = rand()%n;
   j = rand()%n;
   double d = 0.0;
					dummyMethod3();
   for (k=0; k<n; k++)
      d += a[i][k]*b[k][j];
					dummyMethod4();

   printf("Check on a random element: %18.9lE\n", fabs(d-c[i][j]));

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