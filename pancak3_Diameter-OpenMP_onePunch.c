#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX 10000
#define NOT_CONNECTED (INT_MAX)

int diameter(int distance[MAX][MAX], int nodesCount);

int distance[MAX][MAX];

/* initialize all distances to */
void Initialize() {
dummyMethod3();
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            distance[i][j] = NOT_CONNECTED;
        }
        distance[i][i] = 0;
    }
dummyMethod4();
}

uint64_t GetTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * (uint64_t) 1000000 + tv.tv_usec;
}

int main() {
    /* number of nodes */
    int nodeCount;

    /* Number of edges */
    int m;

    Initialize();

    /* get the node count */
    if (scanf("%d", &nodeCount) < 1) {
        fprintf(stderr, "Error reading node count\n");
        exit(1);
    }
    if (nodeCount < 1 || nodeCount > MAX) {
        fprintf(stderr, "Invalid number of nodes, %d.  Must be 1 to %d\n",
                nodeCount, MAX);
        exit(1);
    }

    /* edge count */
    if (scanf("%d", &m) < 1) {
        fprintf(stderr, "Error reading edge count\n");
        exit(1);
    }
    if (m < nodeCount - 1 || m > nodeCount * (nodeCount - 1)) {
        fprintf(stderr, "Invalid number of edges, %d.  Must be %d to %d\n",
                m, nodeCount - 1, nodeCount * (nodeCount - 1));
        exit(1);
    }

    while (m--) {
        /* nodes - let the indexation begin from 0 */
        int a, b;

        /* edge weight */
        int c;

        if (scanf("%d %d %d", &a, &b, &c) < 3) {
            fprintf(stderr, "Error reading edge\n");
            exit(1);
        }
        if (a < 0 || a >= nodeCount || b < 0 || b >= nodeCount || c <= 0) {
            fprintf(stderr, "Invalid edge: from %d to %d weight %d\n", a, b, c);
            exit(1);
        }
        distance[a][b] = c;
    }

    uint64_t start = GetTimeStamp();

    printf("Diameter %d\n", diameter(distance, nodeCount));

    printf("Time: %ld us\n", (uint64_t) (GetTimeStamp() - start));
//
    return 0;
}

/******************************************************************************/
/*  Your changes here */

#include "omp.h"

int localVertexCount;
//int localDistance[MAX][MAX];
//#pragma omp threadprivate(localVertexCount,localDistance)
#pragma omp threadprivate(localVertexCount)

int *Dijkstra(int fromVertex, int vertexCount, int graph[MAX][MAX]);

int diameter(int givenDistance[MAX][MAX], int vertexCount) {

    int *distancesTable[vertexCount];
    localVertexCount = vertexCount;

							dummyMethod1();
#pragma omp parallel for copyin(localVertexCount)
    for (int fromVertex = 0; fromVertex < vertexCount; ++fromVertex) {
        distancesTable[fromVertex] = Dijkstra(fromVertex, localVertexCount, givenDistance);
    }
							dummyMethod2();


    int diameter = -1;

							dummyMethod3();
    for (int i = 0; i < vertexCount; ++i) {

        int maxDistance = 0;
        for (int j = 0; j < localVertexCount; ++j) {
            if (*(distancesTable[i] + j) > maxDistance && *(distancesTable[i] + j) != NOT_CONNECTED)
                maxDistance = *(distancesTable[i] + j);
        }
        if (maxDistance > diameter) {
            diameter = maxDistance;
        }

    }
							dummyMethod4();



    return diameter;
}

int *Dijkstra(int fromVertex, int vertexCount, int graph[MAX][MAX]) {
    int visitedVertex[vertexCount];
//    int distancesOfThisVertex[vertexCount];
    int *distancesOfThisVertex = malloc(vertexCount * sizeof(int));

    int minEdge, vertex = 0, searchedEdgesCount = 0;
    visitedVertex[fromVertex] = 1;

							dummyMethod3();
    for (int i = 0; i < vertexCount; ++i) {
        visitedVertex[i] = 0;
        distancesOfThisVertex[i] = graph[fromVertex][i];

    }
							dummyMethod4();


    distancesOfThisVertex[fromVertex] = 0;

    while (searchedEdgesCount < vertexCount - 1) {
        searchedEdgesCount++;
        minEdge = NOT_CONNECTED;

															dummyMethod3();
        for (int i = 0; i < vertexCount; ++i) {
            if (visitedVertex[i] == 0 && minEdge > distancesOfThisVertex[i]) {
                vertex = i;
                minEdge = distancesOfThisVertex[i];
            }
        }
															dummyMethod4();

        visitedVertex[vertex] = 1;

															dummyMethod3();
        for (int i = 0; i < vertexCount; ++i) {
            if (visitedVertex[i] == 0 && graph[vertex][i] != NOT_CONNECTED &&
                distancesOfThisVertex[vertex] != NOT_CONNECTED &&
                distancesOfThisVertex[vertex] + graph[vertex][i] < distancesOfThisVertex[i]) {
                distancesOfThisVertex[i] = distancesOfThisVertex[vertex] + graph[vertex][i];
            }
        }
															dummyMethod4();

    }
    return distancesOfThisVertex;
}
/* The following is the exact command used to compile this code */
/* g++ -O2 graph-diameter.cpp -o graph-diameter */
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