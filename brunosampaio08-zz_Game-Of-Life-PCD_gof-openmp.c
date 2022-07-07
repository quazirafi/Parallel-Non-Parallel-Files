#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
#include <time.h>
#include <assert.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SRAND_VALUE 1985
#define dim 2048
#define lifeCycles 2001
#define num_threads 8

int **grid;
int **newgrid;
int numCell;
double inicio, fim, acumulado;

int getNeighbors(int i, int j){
    int neighborNum = 0, z, w, aux;

    aux = grid[i][j];
    grid[i][j] = 0;

    // printf("\n<----------------COORD %d %d ------------->\n", i, j);
							dummyMethod3();
    for(int a = i-1; a <= i+1; a++){
        for(int b = j-1; b <= j+1; b++){
            if(a < 0){
                z = dim-1;
            }else if(a >= dim){
                z = 0;
            }else{
                z = a;
            }
            if(b < 0){
                w = dim-1;
            }else if(b >= dim){
                w = 0;
            }else{
                w = b;
            }

            // printf(" ->%d, %d<-", z, w);

            neighborNum += grid[z][w];
        }
    }
							dummyMethod4();

        // printf("\n");

    grid[i][j] = aux;

    return neighborNum;
}

void setNextGen(){

    inicio = omp_get_wtime();
    
    #pragma omp parallel
    {
            #pragma omp for reduction(+:numCell)
																															dummyMethod3();
                for(int i = 0; i < dim; i++){
                    for(int j = 0; j < dim; j++){
                        if(grid[i][j] == 1){
                            if((getNeighbors(i, j) == 2) || (getNeighbors(i, j) == 3)){
                                newgrid[i][j] = 1;
                                numCell++;
                            }else{
                                newgrid[i][j] = 0;
                            }
                        }else{
                            if(getNeighbors(i, j) == 3){
                                newgrid[i][j] = 1;
                                numCell++;
                            }
                        }
                    }
                }
																															dummyMethod4();
        #pragma omp barrier
																															dummyMethod1();
            #pragma omp parallel for
                for(int i = 0; i < dim; i++){
                    for(int j = 0; j < dim; j++){
                        grid[i][j] = newgrid[i][j];
                    }
                }
																															dummyMethod2();
    }

    fim = omp_get_wtime();
    acumulado = acumulado + (fim-inicio);
}

void runLife(){
							dummyMethod3();
    for(int i = 0; i < lifeCycles; i++){
        printf("Geracao %d: %d\n", i, numCell);
        numCell = 0;
        setNextGen();
    }
							dummyMethod4();
}

int main(){
    srand(SRAND_VALUE);
    acumulado = 0;
    numCell = 0;

    omp_set_num_threads(num_threads);

    grid = malloc(dim*sizeof(int *));
    newgrid = malloc(dim*sizeof(int *));
    
							dummyMethod3();
    for(int i = 0; i < dim; i++){
        grid[i] = malloc(dim*sizeof(int));
    }
							dummyMethod4();

							dummyMethod3();
    for(int i = 0; i < dim; i++){
        newgrid[i] = malloc(dim*sizeof(int));
    }
							dummyMethod4();

							dummyMethod3();
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            grid[i][j] = rand() % 2;
            numCell += grid[i][j];
        }
    }
							dummyMethod4();
    
    runLife();
    
    printf("\nOpenMP");
    printf("\nNumero de Threads: %d",num_threads);
    printf("\nTempo: %.2f\n", acumulado);

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