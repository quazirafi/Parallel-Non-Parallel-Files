#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(void){

	int i = 0;
dummyMethod1();
 	#pragma omp parallel for 
 	for(i = 0; i < 10; i++){
 		printf("%i %i\n",i, omp_get_thread_num());
 	}
dummyMethod2();


 	printf("Hello, world.\n");
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