#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//#include "Python.h"
#include "omp.h"
#include<unistd.h>

#define SETUP 11
#define SETUPSIZE 5
#define MAX_BUFFER_SIZE 256
#define SOURCE 0
#define WORKFINISH 13

int *setup_message(int rank, int splits, int input_size) {
    static int message[SETUPSIZE];
    message[0] = splits * rank;//start_position
    message[1] = (splits * rank + splits > input_size) ? splits * rank + splits - input_size
                                                       : splits;//How many sentences
    message[2] = 0;//char count start
    message[3] = input_size;//char count end --- only vertical partitioning
    message[4] = input_size;

    return message;
}

static char alphabet[2] = {'0', '1'};

int do_work(int *setup_msg, int rank, int num_procs) {
	double start_time = MPI_Wtime(); 
    int res = -1;
							dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < 2; ++i) {
        char out_string[MAX_BUFFER_SIZE];

        sprintf(out_string,
                "python3 SuffixTreeCreate.py %d %d %d %d %c %d data/%d.txt run%d_R%d",
                setup_msg[0], setup_msg[1],
                setup_msg[2], setup_msg[3], alphabet[i], setup_msg[4], setup_msg[4],  num_procs,rank);
        printf("%s\n", out_string);
        res = system(out_string);
    }
							dummyMethod2();
	double 	stop_time = MPI_Wtime();
    printf("Work time (sec): %f\n", stop_time - start_time);
    return res;
}

int main(int argc, char *argv[]) {
    // Declare process-related vars
    // and initialize MPI
    int my_rank;
    int num_procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //grab this process's rank
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); //grab the total num of processes
    MPI_Status status;
	double start_time; // use these for timing
    double stop_time;
    int *setup_msg;
    int finish = -1;
    if (my_rank == 0) {
        printf("Number of processes: %d\n", num_procs);
        int input_size = atoi(argv[1]);
        int splits = (int) ceil(input_size / num_procs);

															dummyMethod3();
        for (int i = 1; i < num_procs; ++i) {
            setup_msg = setup_message(i, splits, input_size);
//            int *message = setup_message(i, splits, input_size);
            MPI_Send(setup_msg, SETUPSIZE, MPI_INT, i, SETUP, MPI_COMM_WORLD);
        }
															dummyMethod4();
        setup_msg = setup_message(0, splits, input_size);

        finish = do_work(setup_msg, my_rank, num_procs);

															dummyMethod3();
        for (int i = 1; i < num_procs; ++i) {
            MPI_Recv(&finish, 1, MPI_INT, i, WORKFINISH, MPI_COMM_WORLD, &status);
            if (finish < 0)
                printf("Did not finish %d!", i);
        }
															dummyMethod4();
        //merge call from master
		start_time = MPI_Wtime(); 
															dummyMethod1();
#pragma omp parallel for
        for (int i = 0; i < 2; ++i) {
            char out_string[MAX_BUFFER_SIZE];
            sprintf(out_string, "python3 SuffixTreeMerge.py run%d %c merge_master", num_procs, alphabet[i]);
            printf("%s\n", out_string);

            system(out_string);
        }
															dummyMethod2();
		stop_time = MPI_Wtime();
        printf("Merge time (sec): %f\n", stop_time - start_time);

    } else {
        setup_msg = (int *) malloc(SETUPSIZE * sizeof(int));
        MPI_Recv(setup_msg, SETUPSIZE, MPI_INT, 0, SETUP, MPI_COMM_WORLD, &status);
//        printf("Process %d received %d \n", my_rank, setup_msg[0]);
//        printf("Process %d received %d %d %d %d %d\n", my_rank, setup_msg[0], setup_msg[1], setup_msg[2], setup_msg[3],
//               setup_msg[4]);



        finish = do_work(setup_msg, my_rank, num_procs);
//        printf("status %d\n", finish);
        MPI_Send(&finish, 1, MPI_INT, SOURCE, WORKFINISH, MPI_COMM_WORLD);
//        printf("finish %d\n", finish);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if (my_rank == 0) {
        printf("\nExiting gracefully\n");
    }
//    free(setup_msg);

//

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