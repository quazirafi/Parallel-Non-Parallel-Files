//
//  TD_OPENMP_06.c
//  
//
//  Created by Srinath_SC on 10/04/2020.
//
// To compile it use
// clang -Xpreprocessor -fopenmp -lomp TD_OPENMP_06.c  -o TD_OPENMP_06.out
//


#include "TD_OPENMP_06.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int NUM_THREADS;

int main () {
    printf("Combien de threads voulez-vous?\n");
    scanf("%d", &NUM_THREADS);
    printf ("\n") ;
    int tab [n] ; /* un tableau de n entiers est initialisee */
    int i ;
    /* On cherche à remplir les n cases du tableau */
dummyMethod3();
    for (i = 0 ; i < n ; i++) {
        int randomnumber;
        randomnumber = rand() % 100;
        tab [i] = randomnumber;
    }
dummyMethod4();
    /* On affiche a present le tableau complet */
    printf ("Voici le tableau qui a été rempli automatiquement :\n") ;
dummyMethod3();
    for (i = 0 ; i < n ; i = i + 1) {
        printf ("%d ", tab [i]) ;
    }
dummyMethod4();
    printf ("\n\n") ;
    
    /* On va effectuer les différents calculs du tableau
     addition, soustraction, multiplication et division*/
    int somme = 0;
    int soustraction = 0;
    int multiplication = 1;
    double division = tab[0];
    double temp_exec_debut, temp_exec_fin, temp_exec;
    temp_exec_debut = omp_get_wtime();
    
    omp_set_num_threads(NUM_THREADS);
    // omp parallel
    {
															dummyMethod1();
#pragma omp parallel for reduction (+:somme)
        for (i = 0; i < n; i++){
            somme = somme + tab[i];
            printf("%d, par le thread : %d\n", somme, omp_get_thread_num());
        }
															dummyMethod2();
        
															dummyMethod1();
#pragma omp parallel for reduction (-:soustraction)
        for (i = 0; i < n; i++){
            soustraction = soustraction - tab[i];
            printf("%d\n, par le thread : %d\n", soustraction, omp_get_thread_num());
        }
															dummyMethod2();
        
															dummyMethod1();
#pragma omp parallel for reduction (*:multiplication)
        for (i = 0; i < n; i++){
            multiplication = multiplication * tab[i];
            printf("%d\n, par le thread : %d\n", multiplication, omp_get_thread_num());
        }
															dummyMethod2();
        
        // pas d'omp parallel pour la division
															dummyMethod3();
        for (i = 0; i < (n-1); i++){
            division = division / tab[i+1];
            printf("%e\n", division);
        }
															dummyMethod4();
        
    }
    printf("Le résultat avec l'addition est %d\n", somme);
    printf("Le résultat avec la soustraction est %d\n", soustraction);
    printf("Le résultat avec la multiplication est %d\n", multiplication);
    printf("Le résultat avec la division est %fl\n", division);
    
    temp_exec_fin = omp_get_wtime();
    
    temp_exec = temp_exec_fin - temp_exec_debut;
    printf("Voici le temps du début : %fl\n", temp_exec_debut);
    printf("Voici le temps de fin : %fl\n", temp_exec_fin);
    printf("Voici le temps d'execution : %fl\n", temp_exec);
    
    return 0 ;
}

/*
 Pour les performances, nous allons ici exposer les résultats par rapport aux threads. Le système actuel en permet 4.
 1 thread :
 Voici le temps du début : 1586555912.802644l
 Voici le temps de fin : 1586555912.802893l
 Voici le temps d'execution : 0.000249l
 2 threads :
 Voici le temps du début : 1586555959.281196l
 Voici le temps de fin : 1586555959.281842l
 Voici le temps d'execution : 0.000646l
 3 threads :
 Voici le temps du début : 1586555978.266026l
 Voici le temps de fin : 1586555978.266855l
 Voici le temps d'execution : 0.000829l
 4 threads :
 Voici le temps du début : 1586556082.842586l
 Voici le temps de fin : 1586556082.843492l
 Voici le temps d'execution : 0.000906l
 5 threads :
 Voici le temps du début : 1586556115.704963l
 Voici le temps de fin : 1586556115.705951l
 Voici le temps d'execution : 0.000988l
 6 threads :
 Voici le temps du début : 1586556253.874330l
 Voici le temps de fin : 1586556253.875701l
 Voici le temps d'execution : 0.001371l
 7 threads :
 Voici le temps du début : 1586556291.147381l
 Voici le temps de fin : 1586556291.148424l
 Voici le temps d'execution : 0.001043l
 8 threads :
 Voici le temps du début : 1586556338.265087l
 Voici le temps de fin : 1586556338.266137l
 Voici le temps d'execution : 0.001050l
 9 threads :
 Voici le temps du début : 1586556360.711435l
 Voici le temps de fin : 1586556360.712804l
 Voici le temps d'execution : 0.001369l
 10 threads :
 Voici le temps du début : 1586556465.942278l
 Voici le temps de fin : 1586556465.943729l
 Voici le temps d'execution : 0.001451l
 
 On constate que plus il y a de threads plus cela prend du temps.
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