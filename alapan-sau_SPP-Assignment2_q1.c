#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define max(a,b) (a>b?a:b)

void dnc(long long int **c, long long int **a, long long int ** b, int rows1 /*n*/, int cols1 /*m*/, int cols2 /*p*/, int starting_col_c, int starting_col_a, int starting_col_b)
{
    // if( omp_get_thread_num()){
        // fprintf(stderr, "%d\n", omp_get_thread_num());
    // }
    int maxval = max(max(rows1, cols1),cols2);
    if( maxval <= 256){
        //  long long int**  initb = b;
        //  long long int * tempc;
        //  long long int * tempa;
        //  long long int * tempb;

        // #pragma omp parallel for
        // for( int i=0; i<rows1; ++i){
        //     tempa = *a;
        //     tempc = *c;
        //     b = initb;
        //     // #pragma omp parallel for
        //     for ( int k = starting_col_a; k < starting_col_a +cols1; ++k)
        //     {
        //         tempb = *b;
        //         // #pragma omp parallel for
        //         for ( int j = starting_col_c; j < starting_col_c+cols2; ++j)
        //         {
        //             *(tempc+j) += *(tempa+k) *  *(tempb+j);
        //         }
        //         ++b;
        //     }
        //     ++c;
        //     ++a;
        // }
        // #pragma omp parallel for
        // fprintf(stderr, "%d meh\n", omp_get_thread_num());
															dummyMethod1();
        #pragma omp parallel for
        for(int i=0; i<rows1; ++i){
            // fprintf(stderr, "%d meh2\n", omp_get_thread_num());
            // #pragma omp parallel for
            for ( int k = starting_col_a; k < starting_col_a +cols1; ++k){
                #pragma omp simd
                for ( int j = starting_col_c; j < starting_col_c+cols2; ++j){
                    // #pragma omp critical
                    // {
                    // fprintf(stderr, "%d meh3\n", omp_get_thread_num());
                    c[i][j] += a[i][k] * b[k-starting_col_a][j];
                    // }
                }
            }
        }
															dummyMethod2();
        // prlong long intf("Done\n");
        return;
    }
    else if(maxval == rows1){//n
            // a1 = 0;
                int a2;
            a2 = (rows1>>1);
        // #pragma omp parallel
        // {
        //     #pragma omp single
        //     {
            #pragma omp task
            {
            dnc(c, a, b, a2, cols1, cols2, starting_col_c, starting_col_a, starting_col_b);
            }
            #pragma omp task
            {
            dnc(c+a2, a+a2, b, rows1 - a2, cols1, cols2, starting_col_c, starting_col_a, starting_col_b);
            }
            #pragma omp taskwait
        //     }
        // }
    }
    else if(maxval == cols2){//p
         int b2;
        b2 = cols2>>1;
        // #pragma omp parallel
        // {
        //     #pragma omp single
        //     {
            #pragma omp task
            {
            dnc(c, a, b, rows1, cols1, b2, starting_col_c, starting_col_a, starting_col_b);
            }
            #pragma omp task
            {
            dnc(c, a, b, rows1, cols1, cols2 - b2, starting_col_c + b2, starting_col_a, starting_col_b + b2);
            }
            #pragma omp taskwait
        //     }
        // }
    }
    else {//m
         int a2;
        a2 = (cols1>>1);
        // #pragma omp parallel
        // {
        //     #pragma omp single
        //     {
            // #pragma omp task
            // {
            dnc(c, a, b, rows1, a2, cols2, starting_col_c, starting_col_a, starting_col_b);
            // }
            // #pragma omp task
            // {
            dnc(c, a, b+a2, rows1, cols1 - a2, cols2, starting_col_c, starting_col_a + a2, starting_col_b);
            // }
            // c = c+t
        //     }
        // }
    }
}

int main(){

    //struct timeval st, et;
    //gettimeofday(&st,NULL);

    // Take input
    int n;
    scanf("%d", &n);

    long long int** arr[n];
    int dim[n][2];
     int i,j,k;

							dummyMethod3();
    for(i=0;i<n;++i){
        scanf("%d %d", &dim[i][0], &dim[i][1]);
        arr[i] = malloc(dim[i][0] * sizeof(long long int *));

        for(j=0;j<dim[i][0];j++){
            arr[i][j] = malloc(dim[i][1] * sizeof(long long int*));
            for (k = 0; k < dim[i][1]; k++){
                scanf("%lld", &arr[i][j][k]);
            }
        }

    }
							dummyMethod4();

     long long int** prev_prod = arr[0];
     long long int** current_prod = NULL;

     int current_dim_x = dim[0][0];


    omp_set_num_threads(16);
							dummyMethod3();
    for(i=0;i<n-1;++i){

        current_prod = malloc(current_dim_x * sizeof(long long int*));
        for(j=0;j<current_dim_x;j++){
            current_prod[j] = calloc(dim[i+1][1], sizeof(long long int));
        }
        #pragma omp parallel
        {
        #pragma omp single
        {
        dnc(current_prod, prev_prod, arr[i+1], current_dim_x, dim[i+1][0], dim[i+1][1], 0, 0, 0);
        }
        }
        // assign current dims to prev dims

        // assign current value to prev value for next iter
        prev_prod = current_prod;

        // unassign
        // current_prod = NULL;
    }
							dummyMethod4();


    current_dim_x = dim[0][0];
    k = dim[n-1][1];

    printf("%d %d\n", current_dim_x,k);

							dummyMethod3();
    for(i=0;i<current_dim_x;i++){
        for(j=0;j<k;j++){
            printf("%lld ", prev_prod[i][j]);// *(*(prev_prod+i)+j));
        }
        printf("\n");
    }
							dummyMethod4();

    //gettimeofday(&et,NULL);
    //fprintf(stderr, "%ld\n\n", (((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec)) );


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