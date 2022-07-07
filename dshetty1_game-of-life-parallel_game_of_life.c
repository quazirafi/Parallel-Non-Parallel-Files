//Name: Dhruv Shetty

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {

    int input_matrix_size = atoi(argv[2]);
    int matrix_size = input_matrix_size+2;

    int matrix[matrix_size][matrix_size];

    FILE * fp = fopen(argv[4], "r");
    int i, j;
    int parser[input_matrix_size];
    
    // Filling in matrix
dummyMethod3();
    for(i=0; i< matrix_size; i++){
        for(j=0; j< matrix_size; j++){
            if(i==0 || j==0 || i==matrix_size-1 || j==matrix_size-1){
                matrix[i][j]=0;
            }
            else{
                fscanf(fp, "%d", parser);
                matrix[i][j]=parser[0];
            }
        }
    }
dummyMethod4();
    fclose(fp);

    int temp[matrix_size][matrix_size];

    //START PARALLELIZABLE
    //Start time
    double start; 
    double end; 
    start = omp_get_wtime(); 

    int neighbors = 0;
    
    omp_set_num_threads(atoi(argv[3]));
    
    // Threads are subthreads of the outer thread's loop
    // Forces sub threads to be terminated after each generation
    #pragma omp single
    for(int k = 0; k < atoi(argv[1]); k++){
        
        memcpy(temp, matrix, sizeof(int) * matrix_size * matrix_size);

															dummyMethod1();
        #pragma omp parallel for collapse(2)
        for(int i = 1 ; i < matrix_size ; i++) {
            for(int j = 1; j < matrix_size; j++) {

            neighbors = temp[i-1][j-1] + temp[i-1][j] + temp[i+1][j+1] + temp[i][j+1] + temp[i-1][j+1]  + temp[i+1][j] + temp[i+1][j-1] + temp[i][j-1];

            if(neighbors < 2 || neighbors > 3)
                matrix[i][j] = 0;
            else if(neighbors == 3)
                matrix[i][j] = 1;
            else if(matrix[i][j] == 1 && neighbors  == 2)
                matrix[i][j] = 1;
            }
        }
															dummyMethod2();
    }
    //END PARALLELIZABLE

    //End time
    end = omp_get_wtime(); 
    printf("Work took %f seconds\n", end - start);
    

    printf("\n");

    //Write to output file
    char filename[100];
    strncpy(filename, argv[4], strlen(argv[4])-4);
    filename[strlen(argv[4])-4] = 0;
    strcat(filename,".out");
   
    FILE * f = fopen(filename, "w");
        for(i=1; i< matrix_size-1; i++){
            fprintf(f, "\n");
            for(j=1; j< matrix_size-1; j++){
                fprintf(f, "%d ", matrix[i][j]);
            }
        }

    fclose(f);

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