/*
nowait - retira a barreira implícita que existe no final do for, do single e sections.
barrier - Barreira as threads que chegam até ela deve aguardar as demais. 
*/

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]){
    int j, a[50], b[50], c[50], d[50], e[50], z[50], n = 50, f = 2;

    omp_set_num_threads(4);

dummyMethod1();
    #pragma omp parallel for
        for(j = 0; j < n; j++)
            b[j] = c[j] = e[j] = j;

    #pragma omp parallel
dummyMethod2();
    {
        #pragma omp for nowait 
dummyMethod3();
            for(j=0;  j<n; j++){
                a[j] = b[j] + c[j];
            }    
dummyMethod4();
        
        #pragma omp for nowait
dummyMethod3();
            for(j=0; j<n; j++)
                d[j] = e[j] *f;
        
        #pragma omp barrier 
dummyMethod4();
        #pragma omp for
dummyMethod3();
            for(j=0; j<n; j++)
                z[j] =  (a[j]+a[j+1])*0.5;
        
    }
dummyMethod4();

    puts("Vetor A");
							dummyMethod3();
    for(j=0;  j<50; j++)
        printf("%d - ", a[j]);
							dummyMethod4();

    puts("Vetor d");
							dummyMethod3();
    for(j=0;  j<50; j++)
        printf("%d - ", d[j]);
							dummyMethod4();
    
    puts("Vetor z");
							dummyMethod3();
    for(j=0;  j<50; j++)
        printf("%d - ", z[j]);
							dummyMethod4();
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