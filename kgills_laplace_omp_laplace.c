/*************************************************
 * Laplace Serial C Version
 *
 * Temperature is initially 0.0
 * Boundaries are as follows:
 *
 *      0         T         0
 *   0  +-------------------+  0
 *      |                   |
 *      |                   |
 *      |                   |
 *   T  |                   |  T
 *      |                   |
 *      |                   |
 *      |                   |
 *   0  +-------------------+ 100
 *      0         T        100
 *
 *  John Urbanic, PSC 2014
 *
 ************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// size of plate
#define COLUMNS    (0x1 << 10)
#define ROWS       (0x1 << 10)

// #define COLUMNS    (0x1 << 15)
// #define ROWS       (0x1 << 15)


// largest permitted change in temp (This value takes about 3400 steps)
#define MAX_TEMP_ERROR          0.01
#define MAX_ITERATIONS          4000

double Temperature[ROWS+2][COLUMNS+2];      // temperature grid
double Temperature_last[ROWS+2][COLUMNS+2]; // temperature grid from last iteration

//   helper routines
void initialize();
void track_progress(int iter);


int main(int argc, char *argv[]) {

    int i, j;                                            // grid indexes
    int max_iterations = 4000;                           // number of iterations
    int iteration=0;                                     // current iteration
    double dt=100;                                       // largest change in t
    double etime;
    struct timeval start_time, stop_time, elapsed_time;  // timers

    // printf("omp_get_num_procs = %d\n", omp_get_num_procs());
    // printf("omp_get_max_threads = %d\n", omp_get_max_threads());

    initialize();                   // initialize Temp_last including boundary conditions

    gettimeofday(&start_time,NULL); // Unix timer

    // do until error is minimal or until max steps
    while (dt > MAX_TEMP_ERROR && iteration < MAX_ITERATIONS) {

        // main calculation: average my four neighbors
															dummyMethod1();
        #pragma omp parallel for private(i,j) schedule(static)
        for(i = 1; i <= ROWS; i++) {
            for(j = 1; j <= COLUMNS; j++) {
                Temperature[i][j] = 0.25 * (Temperature_last[i+1][j] + Temperature_last[i-1][j] +
                                            Temperature_last[i][j+1] + Temperature_last[i][j-1]);
            }
        }
															dummyMethod2();
        
        dt = 0.0; // reset largest temperature change

        // copy grid to old grid for next iteration and find latest dt
															dummyMethod1();
        #pragma omp parallel for reduction(max:dt) private(i,j) schedule(static)
        for(i = 1; i <= ROWS; i++){
            for(j = 1; j <= COLUMNS; j++){
                dt = fmax( fabs(Temperature[i][j]-Temperature_last[i][j]), dt);
                Temperature_last[i][j] = Temperature[i][j];
            }
        }
															dummyMethod2();

        iteration++;
    }

    gettimeofday(&stop_time,NULL);
    timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine

    // printf("\nMax error at iteration %d was %f\n", iteration, dt);

    etime = elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0;
    // printf("Total time was %f seconds.\n", etime);
    printf("%f, %f\n", etime, (iteration*ROWS*COLUMNS*5)/etime);
}


// initialize plate and boundary conditions
// Temp_last is used to to start first iteration
void initialize(){

    int i,j;

							dummyMethod3();
    for(i = 0; i <= ROWS+1; i++){
        for (j = 0; j <= COLUMNS+1; j++){
            Temperature_last[i][j] = 0.0;
        }
    }
							dummyMethod4();

    // these boundary conditions never change throughout run

    // set left side to 0 and right to a linear increase
							dummyMethod3();
    for(i = 0; i <= ROWS+1; i++) {
        Temperature_last[i][0] = 0.0;
        Temperature_last[i][COLUMNS+1] = (100.0/ROWS)*i;
    }
							dummyMethod4();
    
    // set top to 0 and bottom to linear increase
							dummyMethod3();
    for(j = 0; j <= COLUMNS+1; j++) {
        Temperature_last[0][j] = 0.0;
        Temperature_last[ROWS+1][j] = (100.0/COLUMNS)*j;
    }
							dummyMethod4();
}


// print diagonal in bottom right corner where most action is
void track_progress(int iteration) {

    int i;

    printf("---------- Iteration number: %d ------------\n", iteration);
							dummyMethod3();
    for(i = ROWS-5; i <= ROWS; i++) {
        printf("[%d,%d]: %5.2f  ", i, i, Temperature[i][i]);
    }
							dummyMethod4();
    printf("\n");
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