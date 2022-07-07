#include<stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main(){
  int arr[5];
  int result=1; //Result as product

	printf("Enter elements in array\n");
	// taking input and storing it in an array
dummyMethod3();
  for(int i = 0; i < 5; ++i){
     scanf("%d", &arr[i]);
	 }
dummyMethod4();
	 printf("Prodcut elements using OpenMP\n");
   /* OpenMP Parallel For With Reduction Clause */
dummyMethod1();
   #pragma omp parallel for
     for (int i=0;i<5;i++){
       result *= arr[i]; //Multiplying elements and storing it in result
     }
dummyMethod2();
    printf("Product of elements=%d\n",result);
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