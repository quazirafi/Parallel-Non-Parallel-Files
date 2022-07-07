/* =============================================================================
 * main.c     Main file, contains entry point and core calculation functions
 * =============================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "omp.h"
#include <mpi.h>
#include "helper.h"
#include "io.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int rank, size;
MPI_Comm comm = MPI_COMM_WORLD;

/* Populate matrix of shortest paths between all pairs of nodes.
 *  Use Floyd-Warshall algorithm for O(|V|^3) time with simple implementation.
 * Parameters:
 *          graph - the graph in question
 * Return:
 *          A matrix containing the length of the shortest paths
 *          between all nodes.
 */
int** all_pair_shortest_path(Graph* graph) {
    // Partition by rows since C is row-major.
    int start, end;
    set_partition(rank, size, graph->nodeCount, &start, &end);

    // Use full matrix instead of half for simpler access
    // RAM use isn't the bottleneck in any case
    int** dist = malloc(graph->nodeCount * sizeof(int*));
							dummyMethod3();
    for (int i = 0; i < graph->nodeCount; i++) {
        dist[i] = malloc(graph->nodeCount * sizeof(int));
        for (int j = 0; j < graph->nodeCount; j++) {
            dist[i][j] = graph->connections[i][j];
        }
    }
							dummyMethod4();

    double startTime = MPI_Wtime();
    double com = 0;
    // Loop over each intermediate node
    for (int k = 0; k < graph->nodeCount; k++) {
        double _startTime = MPI_Wtime();
        if (size > 1) {
            // Synchronize k-th row and column, since we'll be querying it.
            MPI_Bcast(dist[k], graph->nodeCount, MPI_INT, 
                    get_partition(k, size, graph->nodeCount), comm);
            for (int i = 0; i < size; i++) {
                int otherStart, otherEnd;
                set_partition(i, size, graph->nodeCount, &otherStart, &otherEnd);
                // Create single buffer containing i-th node's piece of the 
                // column, for single broadcast as opposed to many 
                int* kCol = malloc((otherEnd - otherStart + 1) * sizeof(int));
                for (int j = otherStart, c=0; j <= otherEnd; j++, c++) {
                    kCol[c] = dist[j][k];
                }
                MPI_Bcast(kCol, otherEnd - otherStart + 1, MPI_INT, i, comm);
                for (int j = otherStart, c=0; j <= otherEnd; j++, c++) {
                    dist[j][k] = kCol[c];
                }
                free(kCol);
            }
        }
        com += MPI_Wtime() - _startTime;

        // Loop over each pair of nodes
        for (int i = start; i <= end; i++) {
            // Extract loop invariant access
            int distIK = dist[i][k];
            // Skipping the lower half was causing problems, and would make 
            // dividing the workload for parallelisation harder, so I got
            // rid of it for now. This means approx doubling the runtime.
																							dummyMethod1();
            #pragma omp parallel for
            for (int j = 0; j < graph->nodeCount; j++) {
                // If path through intermediate node exists and is shorter than 
                // direct path or if direct path doesn't exist, use path 
                // through intermediate node
                // Check if path exists and short-circuit otherwise
                if (distIK != INT_MAX && dist[k][j] != INT_MAX 
                        && dist[i][j] > distIK + dist[k][j]) {
                    if (i == j && distIK + dist[k][j] < 0) {
                        printf("Negative cycle detected, min path undefined\n");
                        exit(1); 
                    }
                    dist[i][j] = distIK + dist[k][j];
                }
            }
																							dummyMethod2();
        }
    }

    startTime = MPI_Wtime();
    // Collect on rank 0 only since we only need to process once.
    if (size == 1) {
        printf("%f,", com);
        return dist;
    }
    if (rank == 0) {
        for (int i = end+1; i < graph->nodeCount; i++) {
            MPI_Recv(dist[i], graph->nodeCount, MPI_INT, MPI_ANY_SOURCE, i, 
                    comm, NULL);
        }
        printf("%f,", com);
    } else {
        for (int i = start; i <= end; i++) {
            MPI_Send(dist[i], graph->nodeCount, MPI_INT, 0, i, comm);
        }
    }

    return dist;
}

/* Find the centre of the graph defined by closeness.
 *  That is, find the node(s) such that the sum of shortest paths to every other
 *  node is minimised.
 * Parameters:
 *          graph - the graph in question
 * Return:
 *          The id of the centre node.
 */
ListNode* min_total_centres(int** dist, Graph* graph) {
    int champ = INT_MAX;
    ListNode* centres = malloc(sizeof(ListNode));
    centres->next = NULL;
    // Iterate backwards so that list is in appearance order
    for (int i = graph->nodeCount - 1; i >= 0; i--) {
        int sum = 0;
        // Sum over row of pairwise distance matrix to get total distance
        for (int j = 0; j < graph->nodeCount; j++) {
            if (dist[i][j] == INT_MAX) {
                printf("Disconnected subgraph detected, solution undefined\n");
                exit(1); 
            }
            sum += dist[i][j];
        } 
        if (sum < champ) {
            champ = sum;
            centres->value = i;
            centres->length = 1;
            // Clear linked list
            if (centres->next != NULL) {
                free_list(centres->next);
                centres->next = NULL;
            }
        } else if (sum == champ) {
            // Append at head of linked list
            ListNode* next = malloc(sizeof(ListNode));
            next->value = i;
            next->next = centres;
            next->length = centres->length + 1;
            centres = next;
        }
    }
    return centres; 
}

/* Find the centre of the graph defined by minimum maximum distance.
 *  That is, find the node(s) such that the longest distance to any other node 
 *  (along the shortest path) is minimised.
 * Parameters:
 *          graph - the graph in question
 * Return:
 *          The id of the centre node.
 */
ListNode* min_max_centres(int** dist, Graph* graph) {
    int champ = INT_MAX;
    ListNode* centres = malloc(sizeof(ListNode));
    centres->next = NULL;
    // Iterate backwards so that list is in appearance order
    for (int i = graph->nodeCount - 1; i >= 0; i--) {
        // Take max of row of pairwise distance matrix to get largest distance
        int maxDistance = max_val(dist[i], graph->nodeCount);
        if (maxDistance < champ) {
            champ = maxDistance;
            centres->value = i;
            centres->length = 1;
            // Clear linked list
            if (centres->next != NULL) {
                free_list(centres->next);
                centres->next = NULL;
            }
        } else if (maxDistance == champ) {
            // Append at head of linked list
            ListNode* next = malloc(sizeof(ListNode));
            next->value = i;
            next->next = centres;
            next->length = centres->length + 1;
            centres = next;
        }
    }
    return centres; 
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);

    Graph* graph = read_file(argv[1]);

    double startTime = MPI_Wtime();

    int** shortestPathsMatrix = all_pair_shortest_path(graph);

    if (rank == 0) {
        printf("%i\n", (int) (MPI_Wtime() - startTime));
    }

    // Only calculate centres on rank 0, since only it has full distance matrix
    if (rank != 0) {
        MPI_Finalize();
        return 0;
    }
    
    // Find centres by minimum total distance
    ListNode* minTotalCentres = min_total_centres(shortestPathsMatrix, graph);
    char* minTotalFilename = malloc((strlen(argv[1]) + 20) * sizeof(char));
    sprintf(minTotalFilename, "%s-min_total", argv[1]);
    write_file(minTotalFilename, minTotalCentres, graph);
    
    // Find centres by minimum maximum distance
    ListNode* minMaxCentres = min_max_centres(shortestPathsMatrix, graph);
    char* minMaxFilename = malloc((strlen(argv[1]) + 20) * sizeof(char));
    sprintf(minMaxFilename, "%s-min_max", argv[1]);
    write_file(minMaxFilename, minMaxCentres, graph);

    MPI_Finalize();
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