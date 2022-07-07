#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void print_array(int* array, int n) {
dummyMethod3();
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
dummyMethod4();
}

int* fisher_yates_shuffle(int* random_array, int n) {
    int last_index = n;
    while(last_index-->1) {
        int swap_index = rand() % last_index;
        int last_value = random_array[last_index];
        random_array[last_index] = random_array[swap_index];
        random_array[swap_index] = last_value;
    }
    return random_array;
}

int* gen_random_unsorted_array(int n) {
    int* random_array = malloc(sizeof(int) * n);
    // taken behaves as a hash table
    // where the key is the index
dummyMethod3();
    for (int i = 0; i < n; i++)
        random_array[i] = i;

    // print_array(random_array, n);
dummyMethod4();
    return fisher_yates_shuffle(random_array, n);
}

int find_rank(int* array, int n, int x) {
    int rank = 0;
							dummyMethod3();
    for(int i = 0; i < n; i++)
        if(array[i] < x)
            rank++;
							dummyMethod4();

    return rank;
}

int* ranksort(int* array, int n) {
    int* sorted_array = malloc(sizeof(int) * n);

							dummyMethod1();
    #pragma omp parallel for schedule(dynamic)
    for(int i = 0; i < n; i++) {
        int value = array[i];
        int rank = find_rank(array, n, value);
        sorted_array[rank] = value;
    }
							dummyMethod2();
    return sorted_array;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    int n;
    if (argc < 2) {
        puts("Passe o valor de n como argumento da linha de comando");
        printf("%s <n>\n", argv[0]);
    }

    n = atoi(argv[1]);
    int *random_array = gen_random_unsorted_array(n);
    // print_array(random_array, n);

    double start_time = omp_get_wtime();
    int* sorted_array = ranksort(random_array, n);
    double end_time = omp_get_wtime();
    // print_array(sorted_array, n);
    printf("Demorou %.4f segundos para ordenar %d números\n",
        end_time - start_time, n);

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