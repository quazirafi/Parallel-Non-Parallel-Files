/*
 * COMP90025 Parallel and Multi-core programming, assignment 1
 * Hongfei Yang <hongfeiy1@student.unimelb.edu.au>
 * 25 Aug 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX 20000
#define NOT_CONNECTED -1

int distance[MAX][MAX]; // all pair-wise distance

int nodesCount; // total number of vertices

// initalise distance matrix
void Initialize(){
dummyMethod3();
    for (int i=0;i<MAX;++i){
        for (int j=0;j<MAX;++j){
            distance[i][j]=NOT_CONNECTED;
        }
        distance[i][i]=0;
    }
dummyMethod4();
}

//Floyd-Warshall Tiled algorithm, the input matrix is defined by its
// initial/last row/column number, (i and j), and a range of k, which
// is the 'pitstop' between i and j
void fw(int start_i, int end_i, int start_j, int end_j, int start_k, int end_k) {
    
    int k;

    for (k=start_k;k<=end_k;k++) {

        // k must be shared as i and j depends on k,
        // i and j can be reordered by the system
															dummyMethod1();
        #pragma omp parallel for shared(distance, k) 
        for (int i=start_i;i<=end_i;++i) {

            if (distance[i][k]!=NOT_CONNECTED){

                for (int j=start_j;j<=end_j;++j){

                    if (distance[k][j]!=NOT_CONNECTED && (distance[i][j]==NOT_CONNECTED || distance[i][k]+distance[k][j]<distance[i][j])){
                        distance[i][j]=distance[i][k]+distance[k][j];
                    }
                }
            }
        }
															dummyMethod2();
    }
}


int main(int argc, char** argv){

    if(argc != 2){
        printf("The path to the input file is not specified as a parameter.\n");
        return -1;
    }
    FILE *in_file  = fopen(argv[1], "r");
    if (in_file  == NULL)
    {
        printf("Can't open file for reading.\n");
        return -1;
    }


    Initialize();

    // read graph in to matrix
    fscanf(in_file,"%d", &nodesCount);

    int a, b, c;
    while(fscanf(in_file,"%d %d %d", &a, &b, &c)!= EOF){
        if ( a > nodesCount || b > nodesCount){
            printf("Vertex index out of boundary.");
            return -1;
        }
        distance[a][b]=c;
    }


    double timeBegin, timeEnd;
    timeBegin = omp_get_wtime();

    // set block size of each tile, please note that setting optimal block size
    // requires experimenting, the goal is to keep every processor busy
    // Here block size is set to be the total number of vertices divided by 
    // maximum number of threads
    int block_size = (int)ceil((double)nodesCount / (double)omp_get_max_threads());
    
    int i, j, k, end;

    // iterate through diagonal tiles, then update corresponding row and column,
    // then update the rest
    #pragma omp for schedule(dynamic)
    for (k=1; k<=nodesCount; k+=block_size) {

        // update centre tile
        if (k+block_size-1 > nodesCount) {
            // handle last tile that are less than one block size
            end = nodesCount;
            fw(k, nodesCount, k, nodesCount, k, nodesCount);
        } else {
            // handle normal block size
            end = k+block_size-1;
            fw(k, k+block_size-1, k, k+block_size-1, k, k+block_size-1);
        }

        int _i;

        // update row and columns        
															dummyMethod1();
        #pragma omp parallel for shared(end, k) private(i, j) schedule(dynamic)
        // one loop for row and one loop for column
        for (_i=0; _i<2; _i++) {
            // update each tile of row/column
            for (i=1; i<=nodesCount; i+=block_size) {
                if (i == k) {
                    continue;
                }

                if (_i==1) {
                    // handle column update
                    if (i + block_size - 1 > nodesCount) {
                        fw(k, end, i, nodesCount, k, end);
                    } else {
                        fw(k, end, i, i+block_size-1, k, end);
                    }
                } else {
                    // handle row update
                    if (i + block_size - 1 > nodesCount) {
                        fw(i, nodesCount, k, end, k, end);
                    } else {
                        fw(i, i+block_size-1, k, end, k, end);
                    }
                }
            }
        }
															dummyMethod2();


        // implicit barrier here, now both row and column have been updated,
        // move on to the rest of the matrix, which can be updated freely
        //

        // update rest of the matrix
															dummyMethod1();
        #pragma omp parallel for shared(k, end) private(i, j) schedule(dynamic)

        for (i=1; i<=nodesCount; i+=block_size) {

            if (i==k) {
                // this tile has already been updated
                continue;
            }

            for (j=1; j<=nodesCount; j+=block_size) {

                if (j == k) {
                    // this tile has already been updated
                    continue;
                }


                if (i + block_size - 1 > nodesCount && j + block_size - 1 <= nodesCount) {
                    // handle short row, normal column region
                    fw(i, nodesCount, j, j+block_size-1, k, end);
                } else if (i + block_size - 1 > nodesCount && j + block_size - 1 > nodesCount) {
                    // handle short row, short column region 
                    fw(i, nodesCount, j, nodesCount, k, end);
                } else if (i + block_size - 1 <= nodesCount && j + block_size - 1 > nodesCount) {
                    // handle normal row, short column region
                    fw(i, i+block_size-1, j, nodesCount, k, end);
                } else {
                    // handle normal row, normal column region
                    fw(i, i+block_size-1, j, j+block_size-1, k, end);
                }

            }
        }
															dummyMethod2();

    }

    int diameter=-1;

							dummyMethod1();
    #pragma omp parallel for reduction(max: diameter)
    //look for the most distant pair
    for (int i=1;i<=nodesCount;++i){
        for (int j=1;j<=nodesCount;++j){
            if (diameter<distance[i][j]){
                diameter=distance[i][j];
                //printf("%d-%d-%d\n", i, diameter, j);
            }
        }
    }
							dummyMethod2();

    timeEnd = omp_get_wtime();
    printf("%d %.16g\n", diameter,(timeEnd-timeBegin));   

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