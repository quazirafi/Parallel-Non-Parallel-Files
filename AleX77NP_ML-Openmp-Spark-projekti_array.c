#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define LEN 1000

double *x;
//double sum;
double sv;
int len;

void* array_sum();

int main (int argc, char* argv[]) {

    omp_set_dynamic(0);
    omp_set_num_threads(2); 
    int tNum = 2;

    len = LEN;
    int i;

    //sum = 0;
    sv = 0;

    x = (double*) malloc (tNum * len * sizeof(double));

	dummyMethod1();
    #pragma omp parallel for schedule(static) shared(x) if(len*tNum>1000)
	for (i = 0; i < len * tNum; i++){
		if(i%2 == 0) {
            x[i] = 2;
        } else {
            x[i] = 1;
        }
	}
	dummyMethod2();

    #pragma omp parallel shared(x,len) reduction(+:sv)
	{
	    array_sum();
	}

    printf("Done. SV  =  %f \n", sv);

    free(x);

    return 0;
}

void* array_sum() {
    int i, start, end, myId;
    myId = omp_get_thread_num();
    start = myId * len;
    end  = start + len;
    double sum = 0;

							dummyMethod3();
    for(i=start; i<end; i++) {
        sum += x[i];
    }
							dummyMethod4();

    sv += sum / (2*len);
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