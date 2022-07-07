#include "../headers/gamma.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX 255

void gamma_correct(int* pixels, int size, float a, float gamma){
	int i, pixel;
dummyMethod1();
	#pragma omp parallel for private(i)
	for (i=0; i<size; i++){
		pixel = (int) ( a * ( pow( (double)pixels[i], (double)gamma )));
		if(pixel > MAX){
			pixels[i] = MAX;
		}else{
			pixels[i] = pixel;
		}
	}
dummyMethod2();
}

void single_gamma(int* value, float a, float gamma){
	int max;
	max = (int) ( a * ( pow( (double)(*(value)), (double)gamma )));
	if(max > MAX){
		*(value) = MAX;
	}else{
		*(value) = max;
	}
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