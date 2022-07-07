// COMP90025 Project 1B
// Hongfei Yang <hongfeiy1@student.unimelb.edu.au>
// September 2018
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <mpi.h>
#include <time.h>
#include <assert.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define INITIAL_SIZE 4

// struct to store the parameter of each region, as well as the result
typedef struct {
    double real_lower;
    double real_upper;
    double img_lower;
    double img_upper;
    int num;
    int maxiter;
    int result;
} input_t;

// return 1 if in set, 0 otherwise
int inset(double real, double img, int maxiter){
    double z_real = real;
    double z_img = img;
dummyMethod3();
    for(int iters = 0; iters < maxiter; iters++){
        double z2_real = z_real*z_real-z_img*z_img;
        double z2_img = 2.0*z_real*z_img;
        z_real = z2_real + real;
        z_img = z2_img + img;
        if(z_real*z_real + z_img*z_img > 4.0) return 0;
    }
dummyMethod4();
    return 1;
}

// count the number of points in the set, within the region
int mandelbrotSetCount(double real_lower, double real_upper, double img_lower,
 double img_upper, int num, int maxiter, int comm_size, int world_rank){

    int count=0;
    double real_step = (real_upper-real_lower)/num;
    double img_step = (img_upper-img_lower)/num;

    // parallelise for loops to distribute work as each inset
    // executing time may vary

    // this region only returns partial result because work is 
    // distributed to different MPI process
							dummyMethod1();
    #pragma omp parallel for reduction(+:count) collapse(2)
    for(int real=world_rank; real<num; real+=comm_size){
        for(int img=0; img<num; img++){
            count+=inset(real_lower+real*real_step,img_lower+img*img_step,maxiter);
        }
    }
							dummyMethod2();

    return count;
}

// main
int main(int argc, char *argv[]){


    int thread_provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &thread_provided);

    if (thread_provided != MPI_THREAD_MULTIPLE) {
       printf("No support for MPI_THREAD_MULTIPLE found, exit\n");
       exit(1);
    }

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    int num_regions = (argc-1)/6;

    // store all data into the array
    input_t* inputs = malloc(sizeof(*inputs)*num_regions);
    assert(inputs);

							dummyMethod3();
    for(int region=0;region<num_regions;region++){
        // scan the arguments
        sscanf(argv[region*6+1],"%lf",&inputs[region].real_lower);
        sscanf(argv[region*6+2],"%lf",&inputs[region].real_upper);
        sscanf(argv[region*6+3],"%lf",&inputs[region].img_lower);
        sscanf(argv[region*6+4],"%lf",&inputs[region].img_upper);
        sscanf(argv[region*6+5],"%i",&inputs[region].num);
        sscanf(argv[region*6+6],"%i",&inputs[region].maxiter);
    }
							dummyMethod4();


    int totalSetCount = 0; // final result
    int processSetCount = 0; // partial result by each process

    //clock_t total_begin = clock();

    // start processing
							dummyMethod1();
    #pragma omp parallel for
    for(int region=0;region<num_regions;region++){
        
        processSetCount = mandelbrotSetCount(
            inputs[region].real_lower,
            inputs[region].real_upper,
            inputs[region].img_lower,
            inputs[region].img_upper,
            inputs[region].num,
            inputs[region].maxiter,
            comm_size,
            world_rank);

        // sum up results returned by slave processes
        MPI_Reduce(&processSetCount, &totalSetCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        // record this result
        if (world_rank == 0) {
            inputs[region].result = totalSetCount;
        }
    }
							dummyMethod2();

    //clock_t total_end = clock();
    //double total_time_spent = (double)(total_end - total_begin) / CLOCKS_PER_SEC;

    // output
    if (world_rank == 0) {
															dummyMethod3();
        for (int i=0; i<num_regions; i++) {
            printf("%d\n", inputs[i].result);
        }
															dummyMethod4();
        // printf("Total time: %lf\n", total_time_spent);
    }


    free(inputs);
    MPI_Finalize();
    return EXIT_SUCCESS;
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