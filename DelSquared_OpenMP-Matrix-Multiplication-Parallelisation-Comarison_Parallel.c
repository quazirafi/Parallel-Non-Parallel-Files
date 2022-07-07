#include <stdio.h>
#include "omp.h"
#include <unistd.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//This is the code using OpenMP to parallelise the code on all (4) cores of the CPU then appending the time it took to the txt file
//uncomment the comments below to also have it print the result to the console

int main(){

    int n = 416; //matrices are 416x416 in order to stress test the code and is a multiple of 4
    

    int a[n][n];
    int b[n][n];
    int c[n][n]; //declairing arrays
    int i,j,k; //ideclairing indices

dummyMethod3();
    for (i=0;i<n;i++){ //initialising arrays
        for (j=0;j<n;j++){
            a[i][j]=rand()%50;
            b[i][j]=rand()%50;
            c[i][j]=0;
        }
    }
dummyMethod4();
    clock_t begin = clock(); //begin clock
							dummyMethod1();
    #pragma omp parallel for private(k) //making sure k is not parallelised
    for (i=0;i<n;i++){
        #pragma omp parallel for private(k)
        for (j=0;j<n;j++){
            for (k=0;k<n;k++){
                c[i][j] += a[i][k]*b[k][j];
            }
        }
    }
							dummyMethod2();
    clock_t end = clock(); //end clock and work out time
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    
    //printf("Time spent: %lf\n",time_spent);

    FILE * fp; //Writing to the file. The extra comma after the last entry will give us a NaN element in the python array that will be ignored
    fp = fopen ("par.txt","a");
    fprintf (fp, "%lf,",time_spent);
    fclose (fp);
    
    //system("pause");

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