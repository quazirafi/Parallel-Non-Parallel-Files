/*                                                                                                                           
 *  Created on: 4 March 24th 2017                                                                                            
 *  Author: Thomas Diaz, Fotis Tsakiris                                                                                      
 */
#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define n 2000
//#define n 500                                                                                                              
//#define n 1000 /* # of nodes */                                                                                            
//distance[i][j] array is the distance between i & j if it exist, otherwise 0.                                               
int distance[n][n];
//int iterate[n*n];                                                                                                          
/*****************************************/
void printDistance(int x) {
  int i, j;
  printf("   ");
dummyMethod3();
  for (i = 0; i < x; ++i)
    printf("%4c", 'A' + i);
  printf("\n");
dummyMethod4();
dummyMethod3();
  for (i = 0; i < x; ++i) {
    printf("%4c", 'A' + i);
    for (j = 0; j < x; ++j)
      printf("%4d", distance[i][j]);
    printf("\n");
  }
dummyMethod4();
  printf("\n");
}
/*****************************************/
void printE_V_W(int x) {
  int i, j;
  printf("  PATH          Distance \n");
  int count = 1;
			dummyMethod3();
  for(i=0;i<x;++i){
    for(j=0;j<x;++j)
      // printf("%4c  ->%4c   %4d\n",'A'+i,'A'+j,distance[i][j]);                                                            
      printf("%4d to%4d     %4d\n",count+i,count+j,distance[i][j]);
 }
			dummyMethod4();
}
/*****************************************/
//FW_AL: Finds the shortest path, if not will put 0.                                                                         
void FW_Al(int x) {
  int i, j, k;
  //FW_AL(int n){                                                                                                            
  for (k = 0; k < x; ++k)
							dummyMethod1();
#pragma omp parallel for private(i,j)
    for (i = 0; i < x; ++i)
      for (j = 0; j < x; ++j)
        /* 1. If i and j are different nodes and                                                                             
           2. If the paths between i and k and between                                                                       
           k and j exist, then do*/
        if ((distance[i][k] * distance[k][j] != 0) && (i != j))
          /* Check to get a shorter path                                                                                     
             between i and j by placing                                                                                      
             k somewhere on the current path */
          if ((distance[i][k] + distance[k][j] < distance[i][j]) || (distance[i][j] == 0))
            distance[i][j] = distance[i][k] + distance[k][j];
							dummyMethod2();
            // weight[i] += distance[i][j];                                                                                  
            // iterate[n] = k;                                                                                               
}
/*****************************************/
int main(int argc, char *argv[]) {
  /*This method creates a matrix and fills in distance[][]*/
  double start,stop; // time it takes to generate using Floyd’s Algorithm.                                                   
  int i,j,x;

  printf("Please Enter the # of Nodes you'd like to run\n");
  scanf("%d,",&x);

  for (i = 0; i < x; ++i)
    for (j = 0; j < x; ++j)
      if (i==j)
        distance[i][j]=0;
      else
        distance[i][j]= (int)( 11.0 * rand() / ( RAND_MAX + 1.0 ));
  printf("\n");
  printf("Matrix A\n ");
  //  printDistance();// prints the matrix                                                                                   
  printE_V_W(x);
  printf("\n");
  printf("Matrix B | FLOYD's Algorithm\n ");
  start = omp_get_wtime();  // get time                                                                                      
  FW_Al(x); //initializes Floyd’s Algorithm                                                                                  
  stop = omp_get_wtime(); // stop time                                                                                       

  // printDistance();// print the new matrix with shortest paths                                                             
  printE_V_W(x);

  printf("-----------------------------\n");
  printf("Nodes: %d | Time: %f seconds\n",x,stop-start);
  printf("-----------------------------\n");
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