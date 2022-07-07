#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
    FILE *arq;
    long unsigned int n, elem, count = 0;
    long unsigned int *vec, *sorted_vec;
    long unsigned int  i, j;

    if (argc != 2) {
        printf("Usage: ./%s input_file_name\n",argv[0]); exit(1);
    }
    arq = fopen(argv[1],"r");
    fscanf(arq,"%lu",&n);
    vec = malloc(n * sizeof(long));
    sorted_vec = malloc(n * sizeof(long));
dummyMethod3();
    for (i = 0; i < n; i++) {
        fscanf(arq, "%lu", &vec[i]);
    }
dummyMethod4();
    fclose(arq);

    omp_set_num_threads(32);
    double start = omp_get_wtime();
							dummyMethod1();
    #pragma omp parallel for shared(n,vec,sorted_vec) private(elem,j,count)
    for (i = 0; i < n; i++) {
        count = 0;
        elem = vec[i];
        for (j = 0; j < n; j++) {
            if (vec[j] < elem) {
                count += 1;
            }
        }
        sorted_vec[count] = elem;
    }
							dummyMethod2();
    double end = omp_get_wtime();
    arq = fopen("output.txt","w+");
							dummyMethod3();
    for (i = 0; i < n; i++) {
        fprintf(arq,"%lu\n",sorted_vec[i]);
    }
							dummyMethod4();
    printf("%f\n",end-start);
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