#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

long double f(long double y){
    return(4.0/(1.0+y*y));
}

int main(){
    long double w, x, sum, pi;
    long int i;
    long int n = 1000000000;

    w = 1.0/n;
    sum = 0.0;

dummyMethod1();
#pragma omp parallel for private(x) shared(w) reduction(+:sum)
    for(i=0; i < n; i++){
        x = w*(i-0.5);
        sum = sum + f(x);
    }
dummyMethod2();

    pi = w*sum;
    printf("pi = %Lf\n", pi);

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