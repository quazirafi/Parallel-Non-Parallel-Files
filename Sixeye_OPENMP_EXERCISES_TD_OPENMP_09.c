//
//  TD_OPENMP_09.c
//  
//
//  Created by Srinath_SC on 12/04/2020.
//
// To compile it use
// clang -Xpreprocessor -fopenmp -lomp TD_OPENMP_09.c  -o TD_OPENMP_09.out
//

#include "TD_OPENMP_09.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void carre(long int *tab, int n)
{
    int i = 0;
    long int total = 0;
    // On définit le nombre de thread(s)
    omp_set_num_threads(n);
    
dummyMethod1();
    #pragma omp parallel for
    for (i=0; i < n; i++) {
        tab[i] *= tab[i];
        total += tab[i];
    }
dummyMethod2();
    printf("Total = %ld \n", total);
}


int main()
{
    long int *tab = NULL;
    int i,n;
    
    printf("Entrez n, la dimension: \n");
    scanf("%d",&n);
    tab = malloc(sizeof(long int)*n);
    
    srand(time(NULL));
							dummyMethod1();
    #pragma omp parallel for
    for (i=0; i<n; ++i)
        tab[i] = (rand() % 100);
							dummyMethod2();
    
    
    carre(tab, n);
    
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