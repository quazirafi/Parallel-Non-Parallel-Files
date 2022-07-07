#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
#include<unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

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

    int res = -1;
							dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < 2; ++i) {
        char out_string[MAX_BUFFER_SIZE];

        sprintf(out_string,
                "python3 SuffixTreeCreate.py %d %d %d %d %c %d data/%d.txt run%d_R%d",
                setup_msg[0], setup_msg[1],
                setup_msg[2], setup_msg[3], alphabet[i], setup_msg[4], setup_msg[4], num_procs, rank);
        printf("%s\n", out_string);
        res = system(out_string);
    }
							dummyMethod2();
    return res;
}

int main(int argc, char *argv[]) {
    // Declare process-related vars
    // and initialize MPI


    int input_size = atoi(argv[1]);
    omp_set_num_threads(atoi(argv[2]));
    int num_procs;
            //just checking number of threads
#pragma omp parallel
    {
        num_procs = omp_get_num_threads();

    }
    printf("num threads %d\n", num_procs);
    int splits = (int) (input_size / num_procs);
							dummyMethod1();
#pragma omp parallel for
    for (int rank = 0; rank < num_procs; ++rank) {
        int* setup_msg = setup_message(rank, splits, input_size);
        do_work(setup_msg, rank, num_procs);
    }
							dummyMethod2();

//    finish = do_work(setup_msg, my_rank, num_procs);
//
//
//    //merge call from master
							dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < 2; ++i) {
        char out_string[MAX_BUFFER_SIZE];
        sprintf(out_string, "python3 SuffixTreeMerge.py run%d %c merge_master", num_procs, alphabet[i]);
        printf("%s\n", out_string);

        system(out_string);
    }
							dummyMethod2();


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