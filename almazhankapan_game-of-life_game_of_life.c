#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int isCorner(int num,int bound);
int countN(int **array,int i,int j);
void swap(int ***array1,int ***array2);

int main(int argc, char* argv[]) {

    int *ptr1=NULL;
    int *ptr2=NULL;
    int **array1;
    int **array2;
    double start=0.0;
    double end=0.0;
    int thread_count,dimension,generations,size,i,j; 
    char filename[100] = ""; // the file name
    FILE *fp,*inputf;

    //create output file
    strcpy(filename, argv[4]);
    strcat(filename, ".out");

    //read input file - assume correct inputs
    inputf = fopen(argv[4], "r");
    if (inputf == NULL) {
        printf("cannot open input file");
        exit(1);
    }
    generations = atoi(argv[1]);
    dimension = atoi(argv[2]);
    thread_count = atoi(argv[3]);
    size=dimension+2;
        
    omp_set_num_threads(thread_count);

    //create array1 to store the original board   
    array1 = malloc(size * sizeof(int *));
    if (array1==NULL){
        printf("memory allocation error");
        exit(1);
    }

							dummyMethod3();
    for (i = 0; i < size; ++i, ptr1+=size) {
        array1[i] = malloc(size * size * sizeof(int));
        if (array1[i]==NULL){ exit(1);}
    }
							dummyMethod4();
    
    //read the input matrix - assume correct input
							dummyMethod3();
    for (i = 1; i <= dimension; ++i) {
        for (j = 1; j <= dimension; ++j) {
            fscanf(inputf, "%d", &array1[i][j]);
        }
    }
							dummyMethod4();
    //clear the extra corner cells 
							dummyMethod3();
    for (i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(isCorner(i,size-1) || isCorner(j,size-1)) {   
                array1[i][j]=0;
            }
        }
    }
							dummyMethod4();
    
    fclose(inputf);

    //create array2 to store the updated board   
    array2 = malloc(size* sizeof(int *));
    if (array2==NULL){
        printf("malloc error"); exit(1);
    }

							dummyMethod3();
    for (i = 0; i < size; ++i, ptr2+=size) {
        array2[i] = malloc(size * size * sizeof(int));
        if (array2[i]==NULL){ exit(1);}
    }
							dummyMethod4();
    
    //clear cells not used in array2
							dummyMethod3();
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            if(isCorner(i,size-1) || isCorner(j,size-1)) {   
                array2[i][j]=0;
            }
        }
    }
							dummyMethod4();
    start = omp_get_wtime();
    //populate array2 and process the cells
    for (int gen = 0; gen < generations; ++gen) {
        int i, j;
															dummyMethod1();
      #pragma omp parallel for private(j) schedule(static) 
        for (i = 1; i <= dimension; ++i) {
            for (j = 1; j <= dimension; ++j) {
                int count = countN(array1,i,j);
                int current_cell=array1[i][j];
                if (current_cell==1 && (count==2 ||count==3)){
                    array2[i][j] = 1;
                }
                else if (current_cell==0 && count==3){
                    array2[i][j] = 1;
                } else{
                    array2[i][j] = 0;
                }
            }
        }
															dummyMethod2();
       
       //swap the arrays
       swap(&array1,&array2);
    }
    end = omp_get_wtime();
    //additionally printout the time and number of threads
    printf("time: %f\n", end - start);
    printf("number of threads %d\n", thread_count);
    if (!(fp = fopen(filename, "w+t"))) {
        printf("cannot create file %s\n", filename);
        exit(1);
    }
    //write to the output file
    for (int i = 1; i <= dimension; ++i) {
        for (int j = 1; j <= dimension; ++j) {
            char s[40];
            sprintf(s, "%d ", array1[i][j]);
            fprintf(fp,"%s",s);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    //free the memory
    for(int i = 0; i < size; i++){
        free(array1[i]);
        free(array2[i]);
    }
    free(array1);
    free(array2);
    exit(0);
}



int isCorner(int s,int lim){
        if (s==0 || s==lim){
            return 1;
        } else{
            return 0;
        }
}

int countN(int **array,int i,int j){
    int r,c,count;
    count=0;
    for (r = i - 1; r <= i+1; ++r) { 
        for (c = j - 1; c <= j+1; ++c) {
            if (!(r == i && c == j) ) {
                count += array[r][c];
               if (count>3){
                   return count;
                }
            }
        }
    }
    return count;
}

void swap(int ***a, int ***b) {
  int ** t = *a;
  *a = *b;
  *b = t;
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