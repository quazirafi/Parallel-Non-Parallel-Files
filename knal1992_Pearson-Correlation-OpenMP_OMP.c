//
//  OMP.c
//  C
//
//  Created by Krzysztof Nalborski on 05/11/2016.
//  Copyright © 2016 Krzysztof Nalborski. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();



//Global Variables
const int n = 5000000;

int i;

double parallel_time;

double serial_time;

//Methods
void SerialPCC();
void ParallelPCC();

//Main Method
int main(void) {

SerialPCC();

ParallelPCC();
}

//Serial Method

void SerialPCC() {

double *a= malloc(n * sizeof(a));
    
double *b= malloc(n * sizeof(b));

double sum_a= 0; //variable to hold the result of sum of array a

double sum_b= 0; //variable to hold the result of sum of array b

double mean_a= 0; //variable to hold the result of mean- array a

double mean_b= 0; //variable to hold the result of mean- array b

double sd_asum= 0; //variable to hold the result of the sum of (a1-mean_a)^2 + (a2-mean_a)^2...

double SD_a= 0; //variable to hold SD for array a

double sd_bsum= 0; //variable to hold the result of the sum of (b1-mean_b)^2 + (b2-mean_b)^2...

double SD_b= 0; //variable to hold SD for array b

double sum_r= 0; //sum of (a[1]-mean_a) * (b[1]-mean_b)...+ (a[n]-mean_a) * (b[n]-mean_b)

double r= 0; //variable to hold the result of Pearson Correlation Coefficient

double sts= 0; //time starts

double ends= 0; //time ends

sts= omp_get_wtime();

//Initializing Arrays

dummyMethod3();
for(i= 0; i < n; i++) {

a[i]= sin(i);
b[i]= sin(i +2);
}
dummyMethod4();
    
//Computing sum of array a and b

dummyMethod3();
for(i= 0; i < n; i++) {
    
    sum_a= sum_a + a[i];
    sum_b= sum_b + b[i];
    
}
dummyMethod4();

//Computing mean

mean_a= sum_a/ n;
mean_b= (sum_b/ n);


//Computing standard deviation of array a and b

dummyMethod3();
for(i= 0; i < n; i++) {
    
    
sd_asum= sd_asum + (a[i] - mean_a) * (a[i] - mean_a);
sd_bsum= sd_bsum + (b[i] - mean_b) * (b[i] - mean_b);

}
dummyMethod4();

SD_a= sqrt(sd_asum/n);
SD_b= sqrt(sd_bsum/n);

//Computing Pearson Correlation between the two arrays

dummyMethod3();
for(i= 0; i < n; i++) {
    
sum_r= sum_r + (a[i] - mean_a) * (b[i] - mean_b);
    
}
dummyMethod4();

r= (sum_r / n) / (SD_a * SD_b);

ends= omp_get_wtime();
    
serial_time = (double)(ends - sts);

printf("\n##########     Serial Algorithm Results:     ##########\n");

printf("\n     mean_a= %lf    mean_b= %lf\n", mean_a, mean_b);

printf("\n     SD_a= %lf    SD_b= %lf\n", SD_a, SD_b);

printf("\n     Pearson Correlation Coefficient = %lf\n", r);

printf("\n     Execution time (including array initialization) is %lf s\n", serial_time);
}

//Parallel Method

void ParallelPCC() {

double *a= malloc(n * sizeof(a));

double *b= malloc(n * sizeof(b));

double sum_a= 0;

double sum_b= 0;

double mean_a= 0;

double mean_b= 0;

double sd_asum= 0;

double sd_bsum= 0;

double SD_a= 0;

double SD_b= 0;

double sum_r= 0;

double r= 0;

double st= 0; //time starts

double end= 0; //time ends

st= omp_get_wtime();

dummyMethod1();
#pragma omp parallel for reduction(+:sum_a) reduction(+:sum_b) num_threads(8)
for (i= 0; i < n; i++) {

a[i]=sin(i);
b[i]= sin(i + 2);

sum_a= sum_a + a[i]; ////calculating sum of array a
sum_b= sum_b + b[i]; //calculating sum of array b
}
dummyMethod2();

#pragma omp parallel sections num_threads(2)
{

#pragma omp section
{
mean_a = sum_a / n; //calculating mean of array a
}

#pragma omp section
{
mean_b = sum_b / n; //calculating mean of array b
}

}

dummyMethod1();
#pragma omp parallel for reduction(+:sd_asum) reduction(+:sd_bsum) reduction(+:sum_r) num_threads(8)
for (i= 0; i < n; i++) {

sd_asum += (a[i] - mean_a) * (a[i] - mean_a) ; //sum of (a1-mean_a)^2 + (a2-mean_a)^2...
sd_bsum += (b[i] - mean_b) * (b[i] - mean_b) ; //sum of (b1-mean_b)^2 + (b2-mean_b)^2...
sum_r += (a[i] - mean_a) * (b[i] - mean_b); ////sum of (a[1]-mean_a) * (b[1]-mean_b)...+ (a[n]-mean_a) * (b[n]-mean_b)
}
dummyMethod2();

#pragma omp parallel sections num_threads(2)
{

#pragma omp section
{
SD_a= sqrt(sd_asum/n); //calculating SD of a
}

#pragma omp section
{
SD_b = sqrt(sd_bsum/n); //calculating SD of b
}

}

r= (sum_r / n) / (SD_a * SD_b); //calculating Pearson Correlation Coefficient

end= omp_get_wtime();

parallel_time= (double)(end - st);

printf("\n##########     OpenMP Parallel Algorithm     ##########\n");

printf("\n     mean_a= %lf     mean_b= %lf\n", mean_a, mean_b);

printf("\n     SD_a= %lf       SD_b= %lf\n", SD_a, SD_b);

printf("\n     Pearson Correlation Coefficient = %lf\n", r);

printf("\n     Execution time (including array initialization) is %lf s\n", parallel_time);

printf("\n     Speedup Achieved = %lf\n", (serial_time/parallel_time));

printf("\n     Percentage Speedup Achieved = %0.2lf%%\n\n", (1-(parallel_time/serial_time))*100);

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