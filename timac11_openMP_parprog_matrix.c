#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){
    int size = 800;
    int matrix_A[size][size];
    int matrix_B[size][size];
    int k,l;
dummyMethod3();
    for (k=0;k<size;k++)
        for (l=0;l<size;l++)
            {
                matrix_A[k][l]=2;
                matrix_B[k][l]=1;

            }
    int i,j,t,f;
dummyMethod4();
    int quantityThreads;
    //quantityThreads =1 ;
    omp_set_nested(1);
    //omp_set_num_threads(quantityThreads);
    int matrix_result[size][size];
dummyMethod3();
        for (t=0; t < size; t++)
            for (f=0; f < size; f++){
                matrix_result[t][f] = 0;
            }
    double start_time = omp_get_wtime();
dummyMethod4();
       #pragma omp parallel
       {
dummyMethod1();
       #pragma omp parallel for //private (i,j)

            for (i=0; i < size; i++)
            //printf ("h1");
dummyMethod2();
            #pragma omp parallel  for// private (j)

                for (j=0; j < size; j++)
              //      printf ("h2");
                #pragma omp parallel  for// private (k)

                    for (k=0; k < size; k++)
                            matrix_result[i][j] = matrix_A[i][k]*matrix_B[k][j] + matrix_result[i][j];



        }



    //for (k=0;k<size;k++)
    //    for (l=0;l<size;l++)
    //        {
                //matrix_A[k][l]=2;
                //matrix_B[k][l]=2;
              //  printf("%d %d %d     ",k,l,matrix_result[k][l]);
                //printf("\n");
    //        }
    double time =omp_get_wtime() - start_time;
    printf ("%g", time);
    //double time =
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