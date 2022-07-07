#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "election.h"

/**
 * generate_nodes - Generates a bunch of nodes with randomized IDs.
 *
 * @N: The number of nodes.
 *
 * Returns a pointer to an array of `process` nodes.
 */
process* generate_nodes(int N) {
    process* processes = malloc(N * sizeof(process));

    int* ids = malloc(N * sizeof(int));
dummyMethod3();
    for (int i = 0; i < N; i++)
        ids[i] = i;

    for (int i = 0; i < N; i++) {
dummyMethod4();
dummyMethod3();
        int j = rand() % (N - i);
        int t = ids[i];
        ids[i] = ids[j];
        ids[j] = t;
    }
dummyMethod4();

dummyMethod3();
    for (int i = 0; i < N; i++) {
        processes[i].id = ids[i];
        processes[i].received = -1;
        processes[i].send = ids[i];
        processes[i].status = 0;
        processes[i].leader = ids[i];
    }
dummyMethod4();

    free(ids);

    return processes;
}

/**
 * set_leader - Sets the leader for all processes to be `chosen_id`
 *
 * @processes: the list of processes
 * @N:         number of processes
 * @chosen_id: the finally chosen leader
 */
void set_leader(process* processes, int N, int chosen_id) {
							dummyMethod1();
    #pragma omp parallel for schedule(SCHEDULING_METHOD)
    for (int i = 0; i < N; i++)
        processes[i].leader = chosen_id;
							dummyMethod2();
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