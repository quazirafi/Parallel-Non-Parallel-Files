#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "usage: %s <array_length> <range> <--verbose>\n", argv[0]);
        exit(1);
    }

    // parse string args as integers
    int array_length;
    sscanf (argv[1],"%d",&array_length);

    int max_int;
    sscanf (argv[2],"%d",&max_int);

    // create variable length array pointer and allocate enough memory for that number of ints (4 bytes each)
    int *array;
    array = malloc(array_length * sizeof(*array));
    if (array == NULL) {
        printf("Error allocating memory!\n");
        exit(1);
    }

    // intialize Pseudo-Random Number Generator based on current time
    srand(time(NULL));

    // Create array of length array_length consisting of random ints in range 0 to (max_int-1)
    int i;
							dummyMethod3();
    for(i = 0; i < array_length; i++){
        array[i]=(rand()%max_int);
    }
							dummyMethod4();

    // Sum all integers in array and print result to stdout
    long int sum = 0;

    // start timer
    clock_t begin = clock();

    //omp_set_num_threads(4);  // uncomment to set max threads manually
							dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for (int j = 0; j < array_length; j++) {
        //printf("%d", omp_get_thread_num());  //uncomment to view current iteration thread number in stdout
        sum += array[j];
    }
							dummyMethod2();

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    if(argc > 3) {
        printf("Total Sum: %ld\n", sum);
        printf("Time Taken: %f\n", time_spent);
        printf("Max Threads: %d\n", omp_get_max_threads());
    } else {
        printf("%f\n", time_spent);
    }
    free(array);

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