//
//  TD_OPENMP_10.c
//  
//
//  Created by Srinath_SC on 12/04/2020.
//
// To compile it use
// clang -Xpreprocessor -fopenmp -lomp TD_OPENMP_10.c  -o TD_OPENMP_10.out
//

#include "TD_OPENMP_10.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
omp_lock_t lock;
double calcul(double*array, int length)
{
    double total = 0.0;
    double temp_exec_debut, temp_exec_fin, temp_exec;
    
    temp_exec_debut = omp_get_wtime();
dummyMethod1();
    #pragma omp parallel for
    for (int i=0; i<length; i++)
    {
        omp_set_lock(&lock);
        total +=array[i];
        omp_unset_lock(&lock);
        
    }
dummyMethod2();
    printf("Total = %2f \n", total);
    temp_exec_fin = omp_get_wtime();
    temp_exec = temp_exec_fin - temp_exec_debut;
    printf("Voici le temps du début : %fl\n", temp_exec_debut);
    printf("Voici le temps de fin : %fl\n", temp_exec_fin);
    printf("Voici le temps d'execution : %fl\n", temp_exec);
    return total;
}

int main()
{
    double array[1024];
    omp_init_lock(&lock);
    calcul(array,1024);
    omp_destroy_lock(&lock);
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