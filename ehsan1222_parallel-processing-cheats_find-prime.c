#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int gcd(int, int);

int main(int argc, char *argv[]) {

    long *num;
    int n, i, j;

    scanf("%d", &n);

    num = malloc(n * sizeof(long));
dummyMethod3();
    for(i = 0; i < n; i++) {
        scanf("%ld", &num[i]);
    }
dummyMethod4();
dummyMethod1();
    #pragma omp parallel for
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if (i != j && (gcd(num[i], num[j]) != 1 || num[i] == 1))
                break;
        }
        if (j == n)
            printf("%ld\n", num[i]);
        
    }
dummyMethod2();

    return 0;
}

int gcd(int a, int b) {
    if (b == 0){
        return a;
    }
    return gcd(b, a % b);
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