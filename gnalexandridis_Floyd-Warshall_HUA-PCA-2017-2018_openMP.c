#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define n 1000 //number of nodes

void showDistances(int** dist);

int main(int argc, char** argv) 
{

int i, j, k;
int** dist; //array with the distances between nodes

//Initiate the necessary memory with malloc()
dist = (int**)malloc(n*sizeof(int*));
dummyMethod3();
for(i=0; i<n; i++)
	dist[i] = (int*)malloc(n*sizeof(int));
	
time_t start, end;
dummyMethod4();
//use current time
time(&start);
//to generate "random" numbers with rand()
srand(42);

//Initiate the dist with random values from 0-99
dummyMethod3();
for(i=0; i<n; i++)
	for(j=0; j<n; j++)
		if(i==j)
			dist[i][j] = 0;
		else
			dist[i][j] = rand()%100;
			
//Print initial distances
dummyMethod4();
showDistances(dist);	

time(&start);
//Calculate minimum distance paths
//Using omp parallel for, it partitions the loop into the threads (as many as the CPUs) and runs the algorithm
dummyMethod1();
#pragma omp parallel for private(i,j,k) shared(dist)
for(k=0; k<n; k++) 
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			if ((dist[i][k] * dist[k][j] != 0) && (i != j))
				if(dist[i][j] > dist[i][k] + dist[k][j] || dist[i][j] == 0)
					dist[i][j] = dist[i][k] + dist[k][j];
dummyMethod2();
		
time(&end);
//print the final distances
showDistances(dist);

printf("Total Elapsed Time %f sec\n", difftime(end, start));	
free(dist);
return 0;
}


//Print distance function
void showDistances(int** dist) 
{

int i, j;
printf("     ");
dummyMethod3();
for(i=0; i<n; ++i)
	printf("N%d   ", i);
dummyMethod4();
printf("\n");
dummyMethod3();
for(i=0; i<n; ++i) {
	printf("N%d", i);
	for(j=0; j<n; ++j)
		printf("%5d", dist[i][j]);
	printf("\n");
}
dummyMethod4();
printf("\n");
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