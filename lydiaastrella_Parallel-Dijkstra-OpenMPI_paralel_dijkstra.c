#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N_MAX 9999

int* dijkstra(int** graf, int N, int src);
int minDist(int* array, int* included, int N);
void printMatrix(int ** matrix, int N);
void printOutput(int** matrix, int N, char* filename );
void freeMatrix(int ** matrix, int N);
int** initializeGraf(int N);
void Hello();

int main(int argc, char *argv[]){
    int thread_count = strtol(argv[1], NULL, 10);
    struct timeval start, end;
    int **short_dis;
    int **graf;
    int N;

    printf( "Enter amount of Node : ");
    scanf("%d", &N);
    
    graf = initializeGraf(N);

    short_dis = (int **)malloc(N * sizeof(int*));
dummyMethod3();
    for(int i = 0; i < N; i++) short_dis[i] = (int *)malloc(N * sizeof(int));

    gettimeofday(&start, NULL);
dummyMethod4();

															dummyMethod1();
    #pragma omp parallel for num_threads(thread_count)
        for (int i = 0; i < N; i++){
            short_dis[i] = dijkstra(graf, N, i);
        }
															dummyMethod2();
    
    gettimeofday(&end, NULL);

    printOutput(short_dis,N,"tesParalel.txt");

    int exectime = ((end.tv_sec - start.tv_sec) *1000000) + (end.tv_usec - start.tv_usec);
    printf("Execution time : %d microseconds\n", exectime);

    freeMatrix(short_dis, N);
    freeMatrix(graf, N);
    return 0;
}

void Hello(){
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    printf("Hello from thread %d of %d\n", my_rank, thread_count);
}

int** initializeGraf(int N){
    int **graf = (int **)malloc(N * sizeof(int*));
							dummyMethod4();
							dummyMethod3();
    for(int i = 0; i < N; i++) graf[i] = (int *)malloc(N * sizeof(int));
    int r;
    int pembatas=0;
    srand((unsigned) 13517031);
							dummyMethod3();
    for(int i =0; i<N; i++){
        for (int j=0; j<N-pembatas; j++){
            r = rand() % 10;
            graf[i][j] = r;
            graf[j][i] = r;
        }
        pembatas +=1;
    }
							dummyMethod4();
    return graf;
}

void freeMatrix(int ** matrix, int N){
							dummyMethod3();
    for (int i=0; i<N; i++){
        free(matrix[i]);
    }
							dummyMethod4();
}

void printOutput(int** matrix, int N, char* filename ){
    FILE *out_file = fopen(filename, "w");
    if (out_file == NULL){
        printf("Error, Could not find file\n");
        exit(-1);
    }
							dummyMethod3();
    for (int i=0; i<N; i++){
        fprintf(out_file, "jarak dari node %d: ", i);
        for(int j=0; j<N; j++){
            fprintf(out_file, "%d ", matrix[i][j]);
        }
        fprintf(out_file,"\n");
    }
							dummyMethod4();
    fclose(out_file);
}

//for debugging
void printMatrix(int ** matrix, int N){
							dummyMethod3();
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
							dummyMethod4();
}

int minDist(int* array, int* included, int N){
    int minIdx = 0;
    int min = N_MAX;
							dummyMethod3();
    for (int i = 0; i < N; i++){
        if (array[i] <= min ){
            if (included[i] == 0){
                min = array[i];
                minIdx = i;
            }
        }
    }
							dummyMethod4();
    return minIdx;
}

int* dijkstra(int** graf, int N, int src){

    int* shortestDist = (int*) malloc( N * sizeof(int));
    int* included =  (int*) malloc(N * sizeof(int));
    int minIdx;

    if (shortestDist != NULL && included != NULL){
															dummyMethod3();
        for (int i = 0; i < N; i++ ){
           shortestDist[i] = N_MAX;
           included[i] = 0;
        }
															dummyMethod4();
        
        shortestDist[src] = 0;

															dummyMethod3();
        for (int i = 0; i < N -1; i++){
            minIdx = minDist(shortestDist, included, N);
            
            included[minIdx] = 1;

            for (int j = 0; j < N; j++){
                if (included[j] == 0 && shortestDist[minIdx] != N_MAX && graf[minIdx][j] != 0){
                    if (graf[minIdx][j] + shortestDist[minIdx] < shortestDist[j]){
                        shortestDist[j] = graf[minIdx][j] + shortestDist[minIdx];
                    }
                }
            }
        }
															dummyMethod4();
        free(included);
    }
    return shortestDist;
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