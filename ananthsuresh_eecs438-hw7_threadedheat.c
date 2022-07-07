#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//Ananth Suresh//
//axs1264//
//HW 6 Resubmission//
//MultiThreaded Version//
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <omp.h> 
# include <sys/time.h>

int COLUMNS;
int ROWS;

//   helper routine
void track_progress(int iteration, double* Temperature, int COLUMNS, int ROWS);

int main(int argc, char *argv[]) {
    COLUMNS = atoi(argv[1]);
    ROWS = atoi(argv[2]);                                      // grid indexes
    int max_iterations = 300;                              // number of iterations
    int iteration;                                   // current iteration
    int i,j;
    int testing = 1;
    double* Temperature = (double*)malloc(sizeof(double) * (COLUMNS + 2) * (ROWS + 2));
    double* Temperature_last = (double*)malloc(sizeof(double) * (COLUMNS + 2) * (ROWS + 2));

    //initialize
dummyMethod3();
    for(i = 0; i <= ROWS+1; i++){
     for (j = 0; j <= COLUMNS+1; j++){
            Temperature_last[i * (COLUMNS + 2) + j] = 0.0;
        }
    }
dummyMethod4();

    // these boundary conditions never change throughout run
    // set left side to 0 and right to a linear increase
							dummyMethod3();
    for(i = 0; i <= ROWS+1; i++) {
        Temperature_last[i * (COLUMNS + 2) ] = 0.0;
        Temperature_last[i * (COLUMNS + 2) + COLUMNS + 1] = (100.0/ROWS)*i;
    }
							dummyMethod4();
    // set top to 0 and bottom to linear increase
							dummyMethod3();
    for(j = 0; j <= COLUMNS+1; j++) {
        Temperature_last[j] = 0.0;
        Temperature_last[(ROWS+1) * (COLUMNS + 2) + j] = (100.0/COLUMNS)*j;
    }       
							dummyMethod4();
   
    
    //Prints initial Grid
    if(testing == 1){
        printf("Initial Grid");
															dummyMethod3();
        for (i = 0; i < COLUMNS + 2; i++) {
            for (j = 0; j < ROWS + 2; j++){
                printf("%.1f ", Temperature_last[i*(COLUMNS + 2)+j]);
            }
            printf("\n");
        }
															dummyMethod4();
    }

    struct timeval start_time, stop_time, elapsed_time;  // timers
    gettimeofday(&start_time,NULL); // Unix timer
    // do until error is minimal or until max steps
    for (iteration = 1; iteration <= max_iterations; iteration++) {
       
       // main calculation: average my four neighbors
        omp_set_num_threads(2);
															dummyMethod1();
        #pragma omp parallel for
        for(i = 1; i <= ROWS; i++) {
            int j;
            for(j = 1; j <= COLUMNS; j++) {
                Temperature[i * (COLUMNS + 2) + j] = 0.25 * (Temperature_last[(i+1) * (COLUMNS + 2) + j] +
                                            Temperature_last[(i-1) * (COLUMNS + 2) + j] +
                                            Temperature_last[i * (COLUMNS + 2) + j+1] +
                                            Temperature_last[i * (COLUMNS + 2) + j-1]);
            }
        }
															dummyMethod2();

        // copy grid to old grid for next iteration and find latest dt
        omp_set_num_threads(2);
															dummyMethod1();
        #pragma omp parallel for
        for(i = 1; i <= ROWS; i++){
            int j;
            for(j = 1; j <= COLUMNS; j++){
              Temperature_last[i * (COLUMNS + 2) + j] = Temperature[i * (COLUMNS + 2) + j];
            }
        }
															dummyMethod2();

        // periodically print test values
        if(testing == 1){
            int iteration_jump = 10; // Use to print fewer snapshots
            if((iteration % iteration_jump) == 0) {
                track_progress(iteration, Temperature, COLUMNS, ROWS);
            }
        }
    }
    gettimeofday(&stop_time,NULL);
    timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
    fflush(stdout);
    printf("\n%f seconds\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);

    //Prints final Grid
    if(testing == 1){
        printf("Final Grid");
        for (i = 0; i < COLUMNS + 2; i++) {
            for (j = 0; j < ROWS + 2; j++){
                printf("%.1f ", Temperature_last[i*(COLUMNS + 2)+j]);
            }
            printf("\n");
        }
    }
}


// print diagonal in bottom right corner where most action is
void track_progress(int iteration, double* Temperature, int COLUMNS, int ROWS) {
    int i,j;
    printf("---------- Iteration number: %d ------------\n", iteration);
    for(i = ROWS-3; i <= ROWS; i++) {
        printf("[%d,%d]: %5.2f  ", i, i, Temperature[i * (COLUMNS + 2) + i]);
    }
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