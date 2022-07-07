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

    return 0;
}

/******************************************************************************/
/*  Your changes here */
#include "omp.h"

typedef struct Distance {
    int value;
    struct Distance *next;
} LinkList;

LinkList minDistance[MAX][MAX];

omp_lock_t lock[MAX][MAX];
int localNodesCount, tmpLocalMinDistance;

#pragma omp threadprivate(localNodesCount, tmpLocalMinDistance)

int diameter(int distance[MAX][MAX], int nodesCount) {
    int i, j, k;

    //initialize min distances chain table
    localNodesCount = nodesCount;
							dummyMethod1();
#pragma omp parallel for
    for (int l = 0; l < nodesCount; ++l) {
        for (int m = 0; m < nodesCount; ++m) {
            minDistance[l][m].value = INT_MAX;
        }
    }
							dummyMethod2();

							dummyMethod1();
#pragma omp parallel for
    for (int k = 0; k < nodesCount; ++k) {
        int tmp;
        for (int i = 0; i < nodesCount; ++i) {
//            omp_set_lock(&lock[i][k]);

            if (distance[i][k] != NOT_CONNECTED) {
                for (int j = 0; j < nodesCount; ++j) {
                    if (distance[k][j] != NOT_CONNECTED) {

                        omp_set_lock(&lock[k][j]);
                        tmp = distance[i][k] + distance[k][j];
                        omp_unset_lock(&lock[k][j]);

                        omp_set_lock(&lock[i][j]);
                        if ((distance[i][j] == NOT_CONNECTED || tmp < distance[i][j])) {
                            distance[i][j] = tmp;
                        }
                        omp_unset_lock(&lock[i][j]);
                    }
                }
            }
//            omp_unset_lock(&lock[i][k]);

        }
    }
							dummyMethod2();
//    }

							dummyMethod3();
    for (int n = 0; n < nodesCount; ++n) {
        for (int l = 0; l < nodesCount; ++l) {
            if (distance[n][l] != INT_MAX) {
                printf("%2d ", distance[n][l]);

            } else {
                printf("%2d ", 0);

            }
        }
        printf("\n");
    }
							dummyMethod4();
    int diameter = -1;

    /* look for the most distant pair */
							dummyMethod3();
    for (int i = 0; i < nodesCount; ++i) {
        for (int j = 0; j < nodesCount; ++j) {
            if (distance[i][j] != NOT_CONNECTED && diameter < distance[i][j]) {
                diameter = distance[i][j];
            }
        }
    }
							dummyMethod4();

    return (diameter);
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