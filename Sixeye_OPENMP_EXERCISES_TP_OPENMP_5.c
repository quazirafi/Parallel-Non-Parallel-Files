//
//  TP_OPENMP5.c
//  
//
//  Created by Srinath_SC on 05/04/2020.
//
// To compile it use
// clang -Xpreprocessor -fopenmp -lomp TP_OPENMP_5.c  -o TP_OPENMP_5.out
//

#include "TP_OPENMP_5.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//Element pour la question b
void carre(int*tab_param, int tailleTabParam){
    omp_set_num_threads(NB_THREADS);
#pragma omp parallel
    {
        int j = 0;
        printf("Le valeur de nb dans carre est %d\n", tailleTabParam);
dummyMethod1();
#pragma omp parallel for
        for(j = 0; j<tailleTabParam; j++){
            tab_param[j] = tab_param[j]*tab_param[j];
        }
dummyMethod2();
    }
}

int main(int argc, char *argv[]){
    
    int timeDeb, timeFin;
    
    timeDeb = time(NULL);
    
    int nb = atoi(argv[1]);
    // This function returns the converted integral number as an int value. If no valid conversion could be performed, it returns zero.
    srand(time(NULL)); //Random num generator
    int tab[nb]; //initializing the array
    int i=0;
    
    printf("Le valeur de la variable nb est %d\n", nb);
    omp_set_num_threads(NB_THREADS);
#pragma omp parallel
    {
															dummyMethod1();
#pragma omp parallel for
        for(i=0;i<nb;i++){
            tab[i]=rand()%(nb-1)+1;
        }
															dummyMethod2();
    }
    
							dummyMethod3();
    for(i=0;i<nb;i++){
        printf("tab[%d] : %d\n",i,tab[i]);
    }
							dummyMethod4();
    
    carre(tab,nb);
    
    printf("Voici l'affichage suite a l'appel de la fonction carre\n");
    
							dummyMethod3();
    for(i=0;i<nb;i++){
        printf("tab[%d] : %d\n",i,tab[i]);
    }
							dummyMethod4();
    
    
    
    timeFin= time(NULL);
    printf("Le temps d'execution est de  %d ms\n", (timeFin-timeDeb)*1000);
    
    return 0;
}


/* Element pour la question c
 */
// "#pragma omp parallele for" avant boucle for

// On a les résultats suivants avec 1, 5 et 10 :
//  =>    taille tab = 1000000 nb thread = 01 temps = 10000 ms
//  =>    taille tab = 1000000 nb thread = 05 temps = 11000 ms
//  =>    taille tab = 1000000 nb thread = 10 temps = 10000 ms
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