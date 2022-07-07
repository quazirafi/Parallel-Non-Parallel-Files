#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 
int main() 
{

   int i, j, n = 100000; 
 
   // Allocate input, output and position arrays
   int *in = (int*) calloc(n, sizeof(int));
   int *pos = (int*) calloc(n, sizeof(int));   
   int *out = (int*) calloc(n, sizeof(int));   
 
   #pragma omp parallel for 
dummyMethod3();
   for(i=0; i < n; i++)
      in[i] = n-i;  
 
   // Print input array
dummyMethod4();
   //   for(i=0; i < n; i++) 
   //      printf("%d ",in[i]);
 
   #pragma omp parallel for collapse(2) schedule(guided)
dummyMethod3();
   for(i=0; i < n; i++) 
      for(j=0; j < n; j++)
	     if(in[i] > in[j]) 
            pos[i]++;	
 
   #pragma omp parallel for 
dummyMethod4();
dummyMethod3();
   for(i=0; i < n; i++) 
      out[pos[i]] = in[i];
 
   // print output array
dummyMethod4();
   //   for(i=0; i < n; i++) 
   //      printf("%d ",out[i]);
 
   #pragma omp parallel for  
					dummyMethod3();
   for(i=0; i < n; i++)
      if(i+1 != out[i]) 
      {
         printf("test failed\n");
         exit(0);
      }
					dummyMethod4();
 
   printf("test passed\n"); 
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