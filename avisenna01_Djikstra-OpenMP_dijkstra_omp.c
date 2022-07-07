// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAX LONG_MAX - 101
// Number of vertices in the graph
// #define V 9


// A utility function to print the constructed distance array
void printSolution(char *outfile, int N, long int **graph) {
    FILE *out;

    out = fopen(outfile, "w");
dummyMethod3();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (graph[i][j] != MAX) {
                fprintf(out, "%ld ", graph[i][j]);
            } else {
                fprintf(out, "X ");
            }
        }
        fprintf(out, "\n");
    }
dummyMethod4();
    fclose(out);
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
long int minDistance(int N, long int *dist, bool *sptSet) {
    // Initialize min value
    long int min = MAX, min_index;

							dummyMethod3();
    for (int v = 0; v < N; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
							dummyMethod4();

    return min_index;
}

void createMatrix(long int **solutionMatrix, int src, long int *dist) {
    solutionMatrix[src] = dist;
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int N, long int **graph, int src, long int **solutionMatrix) {
    long int *dist; // The output array. dist[i] will hold the shortest
    dist = (long int *) malloc(sizeof(long int) * (N + 1));
    // distance from src to i

    bool *sptSet; // sptSet[i] will be true if vertex i is included in shortest
    sptSet = (bool *) malloc(sizeof(bool) * (N + 1));
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
							dummyMethod3();
    for (int i = 0; i < N; i++) {
        dist[i] = MAX,
        sptSet[i] = false;
    }
							dummyMethod4();

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
							dummyMethod3();
    for (int count = 0; count < N - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        long int u = minDistance(N, dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < N; v++) {
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && (graph[u][v] != MAX) /*&& (dist[u] != MAX)*/ && (dist[u] + graph[u][v] < dist[v])) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
							dummyMethod4();

    free(sptSet);

    createMatrix(solutionMatrix, src, dist);
}

// driver program to test above function
int main(int argc, char *argv[]) {
    /* Let us create the example graph discussed above */
    int N = atoi(argv[1]);
    int thread_count = atoi(argv[2]);

    long int **graph;
    graph = (long int **) malloc(sizeof(long int *) * (N + 1));
							dummyMethod3();
    for (int i = 0; i < N; i++) {
        graph[i] = (long int *)malloc(sizeof(long int) * (N + 1));
    }
							dummyMethod4();

    srand(13517061);

							dummyMethod3();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                if (rand() % 2) { //Menentukan apakah terdapat edge dari i ke j 
                    long int x = rand() % 100 + 1;
                    graph[i][j] = x;
                    graph[j][i] = x;
                } else {
                    graph[i][j] = MAX;
                    graph[j][i] = MAX;
                }
            }
        }
    }
							dummyMethod4();

    long int **solutionMatrix;
    solutionMatrix = (long int **)malloc(sizeof(long int *) * (N + 1));

    printSolution("out/input.txt", N, graph);
    
    double start = omp_get_wtime();
							dummyMethod1();
    #pragma omp parallel for num_threads(thread_count)
    for (int i = 0; i < N; i++) {
        dijkstra(N, graph, i, solutionMatrix);
    }
							dummyMethod2();
    double end = omp_get_wtime();
    
    printf("cpu time(in second)      : %lf\n", end - start);
    printf("cpu time(in microsecond) : %lf\n", (end - start)*1000000);
    printSolution("out/output.txt", N, solutionMatrix);

							dummyMethod3();
    for (int i = 0; i < N; i++) {
        free(graph[i]);
        free(solutionMatrix[i]);
    }
							dummyMethod4();
    free(graph);
    free(solutionMatrix);

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