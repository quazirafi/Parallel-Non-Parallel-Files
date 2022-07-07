//Exercice 10 , Axel Houdayer et Florian Simon-Rouquie IATIC 4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
omp_lock_t lock;

double calcul(double* array, int length);
void remplissage(double* array, int length);
void affichage(double * array, int size);
int main()
{
    srand(time(NULL));
    double array[1024],total;
    remplissage(array,1024);
    affichage(array,5); // affiche les 5 premières valeurs du tableau
    omp_init_lock(&lock);
    total=calcul(array,1024);
    omp_destroy_lock(&lock);
    printf("Total = %f\n",total);

}
void remplissage(double* array, int length){
dummyMethod1();
    #pragma omp parallel for
    for(int i = 0; i<length; i++) {
        array[i] = rand()%20;
    }
dummyMethod2();
}
double calcul(double* array, int length){
    double T0 = omp_get_wtime();
    double total = 0.0;
															dummyMethod1();
    #pragma omp parallel for
        for(int i = 0; i < length; i++) {
            omp_set_lock(&lock);
            total+=array[i];
            omp_unset_lock(&lock);

    }
															dummyMethod2();
    printf("[Calcul] Prends %f ms en temps d'execution\n", (omp_get_wtime() - T0) * 1000);

    return total;
}
void affichage(double * tab,int taille) {
							dummyMethod3();
    for(int i = 0; i<taille; i++) {
        printf("%f ", tab[i]);
    }
							dummyMethod4();
    printf("\n");

}
/*
total réel : 948769
[sequentiel] Prends 0.394182 ms en temps d'execution
Total section critique = 948769
[secCritique] Prends 11.937348 ms en temps d'execution
Total reduction  = 948769
[reduction] Prends 0.207221 ms en temps d'execution
Total atomique = 948769
[atomique] Prends 3.532368 ms en temps d'execution

make 10 100 000
[Calcul] Prends 10.902220 ms en temps d'execution

On remarque que le programme prends presque autant de temps
que l'addition avec la section critique.
Il a donc des mauvais résultat pour le calcul.
(Test effectué dans l'exercice 9 pour comparer sur les mêmes valeurs)
*/
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