#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//global input vars
int N, t;

//find prime numbers and print time taken
void compute(int arr[]) {
    int i, curr = 0;
    double tstart = omp_get_wtime();
dummyMethod1();
    #pragma omp parallel for num_threads(t) private(curr)
    for (curr = 2; curr < N; curr++) {  
        if (arr[curr] == 1) {
            #pragma omp parallel for num_threads(t) private(i)
            for (i = (2*curr); i < N; i += curr) {
                arr[i] = 0;
            }
        }
    }
dummyMethod2();
    double ttaken = omp_get_wtime() - tstart;
    printf("Time taken for the main part: %f\n", ttaken);
}

//create output file
void output(int arr[], char* outputFile) {
    FILE * filePointer = fopen(outputFile, "w");
    
    int rank = 1;
    int previous = 2;
    int interval = 0;
    int i;
							dummyMethod3();
    for (i = 2; i < N; i++) {
        if (arr[i] != 0) {
            interval = (i - previous);
            previous = i;
            fprintf(filePointer, "%d , %d, %d\n", rank++, i, interval);
        }
    }
							dummyMethod4();

    fclose(filePointer);
}

int main(int argc, char *argv[]) {
   //tests that input is valid
    if (argc != 3) 
    {
        printf("Invalid input.\n");
        exit(1);
    }
    N = atoi(argv[1]);
    t = strtol(argv[2], NULL, 10);
    if (N <= 2 || N > 100000)
    {
        printf("Invalid input.\n");
        exit(0);
    }

    //populates initial array
    int arr[N + 1];
							dummyMethod3();
    for (int i = 2; i <= N; i++) {
        arr[i] = 1;
    }
							dummyMethod4();

    //creates output file
    char * outputFile[10];
    sprintf(outputFile, "%d.txt", N);

    //calls methods to find primes and write to output
    compute(arr);
    output(arr, outputFile);
    exit(0);
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