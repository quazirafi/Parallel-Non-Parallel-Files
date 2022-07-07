#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void getInput(int*, int*);

void main(int arc, char* argv) {
    omp_set_num_threads(4);
    double begin,end;
    double sequential_time, parallel_time;
    int iteration, i, j, current, next, N, T;

    getInput(&N, &T);

    //initaialize the array
    double h[2][N][N];
    double g[2][N][N];

    // Initialize both arrays to all 0s
dummyMethod3();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            h[0][i][j] = 0;
            h[1][i][j] = 0;
            g[0][i][j] = 0;
            g[1][i][j] = 0;
        }
    }
dummyMethod4();

    // Set all the walls to 20C degrees
							dummyMethod3();
    for(i = 0; i < N; i++) {
        h[0][0][i] = 20.0;
        h[0][i][0] = 20.0;
        h[0][N-1][i] = 20.0;
        h[0][i][N-1] = 20.0;
        g[0][0][i] = 20.0;
        g[0][i][0] = 20.0;
        g[0][N-1][i] = 20.0;
        g[0][i][N-1] = 20.0;
    }
							dummyMethod4();

    // Set the starting point and the ending point of the fireplace
    double fp_start, fp_end;
    fp_start = 0.3 * N;
    fp_end = (0.7 * N);

    // Initialize the values of the location of the fireplacee to 100C
							dummyMethod3();
    for(i = fp_start; i < fp_end; i++) {
        h[0][0][i] = 100.0;
        g[0][0][i] = 100.0;
    }
							dummyMethod4();

    // Get the start time of the program
    begin = omp_get_wtime();

    /**
     * Begin the sequential calculation section
     */
    current = 0;
    next = 1;
							dummyMethod3();
    for (iteration = 0; iteration < T; iteration++) {
        for( i = 1; i < N-1; i++) {
            for( j = 1; j < N-1; j++) {
                h[next][i][j] = 0.25 * (h[current][i-1][j] + h[current][i+1][j] + h[current][i][j-1] + h[current][i][j+1]);
            }
        }
        current = next;
        next = (current + 1) % 2;
    }
							dummyMethod4();
    // Calculate time spent
    end = omp_get_wtime();
    sequential_time = end-begin;

    // Print an 8x8 array the N/8 x N/8 positions of the room.
							dummyMethod3();
    for(i = 0; i < N; i+= N/8) {
        for(j = 0; j < N; j+= N/8) {
            printf("%.2f ", h[current][i][j]);
        }
        printf("\n");
    }
							dummyMethod4();
    printf("\n");


    /**
     * Begin Parallel section
     */
    begin = omp_get_wtime();
    for (iteration = 0; iteration < T; iteration++) {
															dummyMethod1();
        #pragma omp parallel for private(i, j)
        for( i = 1; i < N-1; i++) {
            for( j = 1; j < N-1; j++) {
                g[next][i][j] = 0.25 * (g[current][i-1][j] + g[current][i+1][j]+ g[current][i][j-1] + g[current][i][j+1]);
            }
        }
															dummyMethod2();
        current = next;
        next = (current + 1) % 2;
    }
    // Calculate the time spent
    end = omp_get_wtime();
    parallel_time = end - begin;

    // Print an 8x8 array the N/8 x N/8 positions of the room.
    for(i = 0; i < N; i+= N/8) {
        for(j = 0; j < N; j+= N/8) {
            printf("%.2f ", g[0][i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Check to see if the two arrays match
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if(g[0][i][j] != h[current][i][j]) {
                printf("2 arrays do not match\n");
                exit(1);
            }
        }
    }

    // Print the time in seconds that the program took to run
    printf("Parallel: %f\nSequential: %f\nDifference: %f\n", parallel_time, sequential_time, sequential_time - parallel_time);
    printf("Speedup factor: %f\n", sequential_time/parallel_time);

}

/**
 * Function to get the input from the user
 * Params: int* N - A pointer to the number 'N' of the NxN matrix
 *         int* T - A pointer to the number of iterations
 */
void getInput(int* N, int* T) {
    // Get the size of the matrix
    int valid = 0;
    while(!valid) {
        printf("Please enter matrix size(NxN): ");
        scanf("%d", N);
        if(N) {
            valid = 1;
        }
    }

    // Get the number of iterations
    valid = 0;
    while(!valid) {
        printf("Please enter the number of iterations: ");
        scanf("%d", T);
        if(N) {
            valid = 1;
        }
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