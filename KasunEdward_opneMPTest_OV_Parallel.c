//
// Created by kasun on 7/24/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double matrixMultiply(int n);
void transpose(double** arr,int size);
double* out;
double total;
double final_total;
double sdTotal;
double mean;
int n;
int actualSize;
double val;
double sd;
double result;
double a;

int main(int argc, char* argv[]) {
    n=strtol(argv[1],NULL,10);
    out=(double*) malloc(30 * sizeof(double));
    total=0.0;
    printf("Running code for 30 samples............");
dummyMethod3();
    for(int i=0;i<30;i++){
        out[i]=matrixMultiply(n);
        total+=out[i];
    }
dummyMethod4();

    mean=total/30.0;
    sdTotal=0.0;
							dummyMethod3();
    for(int i=0;i<30;i++){
        sdTotal+=(out[i]-mean)*(out[i]-mean)/29;
    }
							dummyMethod4();
    sd=sqrt(sdTotal);
    val=((100*1.960*sd)/(5*mean))*((100*1.960*sd)/(5*mean));
    actualSize=(int)ceil(val);

    free(out);
    final_total=0.0;

    printf("\nNo. of samples needed: %d",actualSize);
    printf("\nRunning code for %d samples",actualSize);
							dummyMethod3();
    for(int i=1;i<=actualSize;i++){
        final_total+=matrixMultiply(n);
    }
							dummyMethod4();
    result=final_total/actualSize;

    FILE *f= fopen("OV_Parallel_results.csv","a+");
    fprintf(f,"%d,%lf\n",n,result);
    fclose(f);

    printf("\nResult=%lf\n",result);
}
double matrixMultiply(int n){
    int i,j;
    /*get the no of the threads from the command line*/

    double **matA = malloc(sizeof *matA *n);
    if (matA)
    {
															dummyMethod3();
        for (i = 0; i < n; i++)
        {
            matA[i] = malloc(sizeof *matA[i] * n);
        }
															dummyMethod4();
    }
    double **matB = malloc(sizeof *matB *n);
    if (matB)
    {
															dummyMethod3();
        for (i = 0; i < n; i++)
        {
            matB[i] = malloc(sizeof *matB[i] * n);
        }
															dummyMethod4();
    }
    double **matC = malloc(sizeof *matC *n);
    if (matC)
    {
															dummyMethod3();
        for (i = 0; i < n; i++)
        {
            matC[i] = malloc(sizeof *matC[i] * n);
        }
															dummyMethod4();
    }
    srand(time(NULL));
							dummyMethod3();
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a=(double)rand()/1000000;
            matA[i][j]=a;
        }
    }
							dummyMethod4();
							dummyMethod3();
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a=(double)rand()/1000000;
            matB[i][j]=a;
        }
    }
							dummyMethod4();
    double start=omp_get_wtime();
    // time_t start=time(NULL);
    transpose(matB,n);
							dummyMethod1();
#pragma omp parallel for
    for(int i=0;i<n;i++){
#pragma omp parallel for
        for(int j=0;j<n;j++){
            double sum=0.0;
            for(int k=0;k<n;k++){
                sum+=matA[i][k]*matB[j][k];
            }
            matC[i][j]=sum;
        }
    }
							dummyMethod2();
    double end=omp_get_wtime();
    //time_t end=time(NULL);
    double seconds = end - start;
    printf("\n%lf",seconds);
    free(matA);
    free(matB);
    free(matC);
    return seconds;
}
void transpose(double** arr,int size){
							dummyMethod3();
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            double temp=arr[i][j];
            arr[i][j]=arr[j][i];
            arr[j][i]=temp;
        }
    }
							dummyMethod4();
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