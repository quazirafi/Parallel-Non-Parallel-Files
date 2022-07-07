#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int compare_exchange(int *a, int *b) {
    int tmp;

    if (*a > *b) {
        tmp = *a;
        *a = *b;
        *b = tmp;
        return 1;
    } else {
        return 0;
    }
}

void bubble_sort(int n, int *a){

    int flag;

dummyMethod3();
    for (int i = n; i > 1; i--) {
        flag = 0;
        for (int j = 0; j < i; j++) {
            if (compare_exchange(&a[j], &a[j+1])) {
                flag = 1;
            }
        }
        if (!flag) break;
    }
dummyMethod4();

}

void para_oddeven_sort(int n, int* a) {

    //#pragma omp parallel num_threads(6)

    for (size_t i = 0; i < n; i++) {
        if (i%2) {

																							dummyMethod1();
            #pragma omp parallel for
            for (int j = 0; j < n/2; j++) {
                compare_exchange(&a[2*j+1], &a[2*j+2]);
            }
																							dummyMethod2();
        } else {
																							dummyMethod1();
            #pragma omp parallel for
            for (int j = 0; j < n/2; j++) {
                compare_exchange(&a[2*j], &a[2*j+1]);
            }
																							dummyMethod2();
        }
    }

    printf("Sorted odd/even:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }

}


// void para_matvec(int n, double **A, double* x, double* y){
//
//     int num_procs;
//     int my_rank;
//
//     MPI_Init()
//     MPI_Comm_size (MPI_COMM_WORLD, &mnum_procs);
//     MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
//
//
//     if (my_rank == 0) {
//         MPI_Bcast(x, n, MPI_)
//     }
//
//
//
// }

int main(int argc, char const *argv[]) {

    int n = 10;
    int a[10] = {2,1,6,14,25,16,27,8,10,9};



    bubble_sort(n, a);
    //para_oddeven_sort(n, a);

    printf("Sorted:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }

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