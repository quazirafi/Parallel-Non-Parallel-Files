#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "../include/sort.h"
#include "../include/edgelist.h"

// Order edges by id of a source vertex, 
// using the Counting Sort
// Complexity: O(E + V)
void countSortEdgesBySource(struct Edge *edges_sorted, struct Edge *edges, int numVertices, int numEdges) {

    
    int i;
    int key;
    int pos;

    // auxiliary arrays, allocated at the start up of the program
    int *vertex_cnt = (int*)malloc(numVertices*sizeof(int)); // needed for Counting Sort

dummyMethod3();
    for(i = 0; i < numVertices; ++i) {
        vertex_cnt[i] = 0;
    }
dummyMethod4();

    // count occurrence of key: id of a source vertex
dummyMethod3();
    for(i = 0; i < numEdges; ++i) {
        key = edges[i].src;
        vertex_cnt[key]++;
    }
dummyMethod4();

    // transform to cumulative sum
							dummyMethod3();
    for(i = 1; i < numVertices; ++i) {
        vertex_cnt[i] += vertex_cnt[i - 1];
    }
							dummyMethod4();

    // fill-in the sorted array of edges
							dummyMethod3();
    for(i = numEdges - 1; i >= 0; --i) {
        key = edges[i].src;
        pos = vertex_cnt[key] - 1;
        edges_sorted[pos] = edges[i];
        vertex_cnt[key]--;
    }
							dummyMethod4();


    free(vertex_cnt);

}



void radixSortEdgesBySource(struct Edge *edges_sorted, struct Edge *edges, int numVertices, int numEdges) {
    //edges_sorted is sorted array
    //edges is array given
    //numVertices is largest number
    //numEdges is number of elements in array
    //Each key in A[1..n] is a d-digit integer
    //Digits are numbered 1 to d from right to left
    //Finding number of digits, this is based on numVertices
    int digits;
    int temp;
    int i;
    int j;
    int k;

    if (numVertices < 100000) {
        if (numVertices < 100) {
            if (numVertices < 10) { digits = 1; }
            else { digits = 2; }
        } else {
            if (numVertices < 1000) { digits = 3; }
            else {
                if (numVertices < 10000) { digits = 4; }
                else { digits = 5; }
            }
        }
    } else {
        if (numVertices < 10000000) {
            if (numVertices < 1000000) { digits = 6; }
            else { digits = 7; }
        } else {
            if (numVertices < 100000000) { digits = 8; }
            else {
                if (numVertices < 1000000000) { digits = 9; }
                else { digits = 10; }
            }
        }
    }

    omp_set_num_threads(16);

    //for 1 to #digits
    for (j = 1; j <= digits; j++) {
        //key, it is number at digit place j, that's why it's size 10, 0->9
        int count[10] = {0};

        //Store the count of 'keys' in count
        for (i = 0; i < numEdges; i++) {
            //count[j-th digit of edges array]
            temp = edges[i].src;
            temp /= (int)pow(10.0, (double) j-1);
            temp %= 10;

            count[temp]++;
            //count[(edges[i].src / (int)pow(10.0, (double) j-1)) % 10]++;
        }

        for (k = 1; k < 10; k++) {
            count[k] += count[k-1];
        }

        //Build new resulting array by checking
        //new position of A[i] from count[k]
															dummyMethod1();
        #pragma omp parallel for default(none) shared(numEdges, j, edges, edges_sorted, count) private(i, temp)
        for (i = numEdges - 1; i >= 0; i--) {
            temp = edges[i].src;
            temp /= (int)pow(10.0, (double) j-1);
            temp %= 10;
            edges_sorted[count[temp] - 1] = edges[i];
            count[temp]--;
        }
															dummyMethod2();

															dummyMethod1();
        #pragma omp parallel for default(none) shared(numEdges, edges_sorted, edges) private(i)
        for (i = 0; i < numEdges; i++) {
            edges[i] = edges_sorted[i];
        }
															dummyMethod2();
    }
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