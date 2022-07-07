/******************************************************************************
* FILE: array_loops.c
* DESCRIPTION:
*   Initialize array of size 64 in parallel, then add 3*i to each element,
*   then counts amount of odd values in array
* AUTHOR: David Nguyen
* CONTACT: david@knytes.com
* LAST REVISED: 07/03/2020 14:17:30 GMT-8
******************************************************************************/
#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define     DESIRED_ARR_SIZE    64
#define     DESIRED_NUM_THREADS 8

int main (int nargs , char ** args) {
    int     array[DESIRED_ARR_SIZE], // array to hold values
            i, // for loop iterator
            sum = 0, // master odd count sum
            oddCount; // local odd count sum

    // Sets omp threads to DESIRED_NUM_THREADS if not already
    omp_set_num_threads(DESIRED_NUM_THREADS);

    // Populate array with all zeros
dummyMethod1();
    #pragma omp parallel for private(i)
        for (i = 0; i < DESIRED_ARR_SIZE; i++){
            array[i] = 0;
            printf("ZERO_SETTING: Thread %d set index %d to %d\n",omp_get_thread_num(), i, array[i]);
        }
dummyMethod2();

    // Add 3*i to each element of array
															dummyMethod1();
    #pragma omp parallel for private(i)
        for (i = 0; i < DESIRED_ARR_SIZE; i++){
            array[i] += 3*i;
            printf("ADDITION_3*I: Thread %d added %d to index %d\n",omp_get_thread_num(), array[i], i);
        }
															dummyMethod2();

    #pragma omp parallel private(oddCount, i) shared(sum)
    {
        int t_id = omp_get_thread_num();

        // set oddCount to 0. Fixes memory corruption issue.
        oddCount = 0;

															dummyMethod3();
        for (i = t_id; i < DESIRED_ARR_SIZE; i += DESIRED_NUM_THREADS){
            printf("SEARCHING: Thread %d is peeking index %d\n", t_id, i); // this print affects odd count
            if(array[i]%2 != 0){
                oddCount += 1;
                printf("FOUND: Thread %d found odd value %d at index %d\n",t_id, array[i], i); // this print affects odd count
            }
        }
															dummyMethod4();

        printf("Thread %d found %d odd values\n",t_id, oddCount);
        
        #pragma omp critical
        sum += oddCount;
    }

    // Print number of odd numbers
    printf("Count of odd numbers: %d\n", sum);

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