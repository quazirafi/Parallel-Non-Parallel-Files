#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include "bmp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

const int image_width = 512;
const int image_height = 512;
const int image_size = 512*512;
const int color_depth = 255;

int main(int argc, char** argv){

    if(argc != 3){
        printf("Useage: %s image n_threads\n", argv[0]);
        exit(-1);
    }
    int n_threads = atoi(argv[2]);

    unsigned char* image = read_bmp(argv[1]);
    unsigned char* output_image = malloc(sizeof(unsigned char) * image_size);


    int* histogram = (int*)calloc(sizeof(int), color_depth);
#pragma omp parallel for num_threads(n_threads)
dummyMethod3();
    for(int i = 0; i < image_size; i++){
        int image_val = image[i]; 
#pragma omp critical
dummyMethod4();
        histogram[image_val]++;
    }


    float* transfer_function = (float*)calloc(sizeof(float), color_depth);
    
							dummyMethod1();
#pragma omp parallel for num_threads(n_threads) schedule(static,1)
    for(int i = 0; i < color_depth; i++){
        for(int j = 0; j < i+1; j++){
            transfer_function[i] += color_depth*((float)histogram[j])/(image_size);
        }
    }
							dummyMethod2();


							dummyMethod1();
#pragma omp parallel for num_threads(n_threads)
    for(int i = 0; i < image_size; i++){
        output_image[i] = transfer_function[image[i]];
    }
							dummyMethod2();

    write_bmp(output_image, image_width, image_height);
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