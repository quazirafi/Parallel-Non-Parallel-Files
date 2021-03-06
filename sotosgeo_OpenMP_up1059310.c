/*
This program estimates the value of pi, by using a Monte Carlo area simulation.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif
#include <limits.h>


int main(int argc, char *argv[]) {


    int thread_count;   
    unsigned long long int total_throws, current_throw, throws_in_circle;
    double x_pos,y_pos,sum_of_squares;
    thread_count = 4;
    total_throws = 1e6;

    //Generating a seed with time
    srand (time (NULL));

    if (argc > 1) {
        thread_count = atoi(argv[1]);
    }
    if (argc > 2) {
        total_throws = atol(argv[2]);
    }

    
    //----Serial Solution----
    //Uncomment line below to remove serial
    //*
    throws_in_circle = 0;
    double t0 = omp_get_wtime();
							dummyMethod3();
    for (current_throw = 0; current_throw < total_throws; current_throw++) {
        x_pos = (double)rand()/RAND_MAX*2.0-1.0;
        y_pos = (double)rand()/RAND_MAX*2.0-1.0;
        sum_of_squares = x_pos * x_pos + y_pos * y_pos;
        if (sum_of_squares <= 1) throws_in_circle ++;
    }
							dummyMethod4();
    double serial_pi_approx = 4.0 * throws_in_circle / ((double) total_throws);
    double t1 = omp_get_wtime();
    //*/


    //----Parallel Solution----
    throws_in_circle = 0;
    double t2 = omp_get_wtime();    
							dummyMethod1();
    #pragma omp parallel for num_threads(thread_count) \
            default(none) \
            shared(total_throws) private(x_pos,y_pos, sum_of_squares,current_throw) \
            reduction(+ : throws_in_circle) 
    for (current_throw = 0; current_throw < total_throws; current_throw++) {
        //Generating 2 random numbers between -1 and 1
        x_pos = (double)rand()/RAND_MAX*2.0-1.0;
        y_pos = (double)rand()/RAND_MAX*2.0-1.0;
        sum_of_squares = x_pos * x_pos + y_pos * y_pos;
        if (sum_of_squares <= 1) throws_in_circle ++;
    }
							dummyMethod2();
    double parallel_pi_approx = 4.0 * throws_in_circle / ((double) total_throws);
    double t3 = omp_get_wtime();



    //----Output----
    printf("\nTotal darts n = %llu \n", total_throws);
    //Uncomment line below to remove serial
    //*
    
    printf("//----Serial----//\n");
    printf("Serial estimate of pi = %.14f\n", serial_pi_approx);
    printf("The error from the actual M_PI value is: %.14f\n", M_PI - serial_pi_approx);  
    printf("Serial time = %.3f sec\n\n", t1 - t0);
    //*/
    printf("//----Parallel----//\n");
    printf("Number of threads = %d \n", thread_count);
    printf("Parallel estimate of pi = %.14f\n", parallel_pi_approx);
    printf("The error from the actual M_PI value is: %.14f\n", M_PI - parallel_pi_approx);  
    printf("Parallel time = %.3f sec\n", t3 - t2);

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