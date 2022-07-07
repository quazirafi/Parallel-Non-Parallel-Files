#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
void reduction(int * array, int size);
void affichage(int * array, int size);

int main(int argc, char ** argv) {
    omp_set_num_threads(5); //Permet de parametrer le nombre de threads
    srand(time(NULL));

    int * tab;

    int taille = atoi(argv[1]); //  permet de lire la taille du tableau sur la ligne de commande
    int i;

    // remplit le tableau en parallele :
    tab = (int*) malloc(sizeof(int) * taille);

dummyMethod1();
    #pragma omp parallel for
    for(i = 0; i<taille; i++) {
        tab[i] = rand()%20;
        //printf("Nombre de thread  crées par OpenMP: %d \n ",omp_get_num_threads());
    }
dummyMethod2();

    affichage(tab, taille);
    reduction(tab,taille);
    return 0;
}
//Fonction qui permet d'afficher les valeurs du tableau
void affichage(int * tab,int taille) {
							dummyMethod3();
    for(int i = 0; i<taille; i++) {
        printf("%d ", tab[i]);
    }
							dummyMethod4();
    printf("\n");

}
void reduction(int * tab,int taille){
    //a) Réduction avec l'opération + :
    int i,j,k;
    int result = 0;
    double T0 = omp_get_wtime(); //Temps d'execution
    //parallèlisation de la boucle for
							dummyMethod1();
    #pragma omp parallel for reduction(+:result)
    for(i = 0; i<taille; i++) {
        result+=tab[i];
    }
							dummyMethod2();
    printf("Pour l'opération + : result = %d\n",result);
    printf("Prends %f ms en temps d'execution pour l'operation +\n", (omp_get_wtime() - T0) * 1000);
    //b) Réduction avec l'opération * :
    result = 1;
    T0 = omp_get_wtime(); //Temps d'execution
							dummyMethod1();
    #pragma omp parallel for reduction(*:result)
    for(j = 0; j<taille; j++) {
        result=result*tab[j];
    }
							dummyMethod2();
    printf("Pour l'opération * : result = %d\n",result);
    printf("Prends %f ms en temps d'execution pour l'operation *\n", (omp_get_wtime() - T0) * 1000);
    //c) Réduction avec l'opération - :
    result = tab[0];
    T0 = omp_get_wtime(); //Temps d'execution
							dummyMethod1();
    #pragma omp parallel for reduction(-:result)
    for(k = 1; k<taille; k++) {
            result-=tab[k];
    }
							dummyMethod2();
    printf("Pour l'opération - : result = %d\n",result);
    printf("Prends %f ms en temps d'execution pour l'operation -\n", (omp_get_wtime() - T0) * 1000);
    //d) Réduction avec l'opération min :
    result = tab[0];
    T0 = omp_get_wtime(); //Temps d'execution
							dummyMethod1();
    #pragma omp parallel for reduction(min:result)
    for(k = 0; k<taille; k++) {
            result=min(result,tab[k]);
    }
							dummyMethod2();
    printf("Pour l'opération min : result = %d\n",result);
    printf("Prends %f ms en temps d'execution pour l'operation min\n", (omp_get_wtime() - T0) * 1000);
    //e) Réduction avec l'opération max :
    result = tab[0];
    T0 = omp_get_wtime(); //Temps d'execution
							dummyMethod1();
    #pragma omp parallel for reduction(max:result)
    for(k = 0; k<taille; k++) {
            result=max(result,tab[k]);
    }
							dummyMethod2();
    printf("Pour l'opération max : result = %d\n",result);
    printf("Prends %f ms en temps d'execution pour l'operation max\n", (omp_get_wtime() - T0) * 1000);

}

/* b) Evaluation performance  + jeux de tests :
gcc Exo6.c -0 Exo6 -fopenmp
./Exo6 3 :
13 	12 	18
Pour l'opération + : result = 43
Prends 0.216821 ms en temps d'execution pour l'operation +
Pour l'opération * : result = 2808
Prends 0.114910 ms en temps d'execution pour l'operation *
Pour l'opération - : result = -17
Prends 0.072242 ms en temps d'execution pour l'operation -
Pour l'opération min : result = 12
Prends 0.066558 ms en temps d'execution pour l'operation min
Pour l'opération max : result = 18
Prends 0.058415 ms en temps d'execution pour l'operation max

./Exo6 50 :
10 8 8 0 13 4 7 12 14 15 1 5 10 15 6 7 8 8 16 12 0
5 16 9 16 14 11 9 16 15 18 6 9 2 18 15 9 6 16 5 11
6 6 0 6 1 10 11 0 11

Pour l'opération + : result = 456
Prends 0.070786 ms en temps d'execution pour l'operation +
Pour l'opération * : result = 0
Prends 0.072410 ms en temps d'execution pour l'operation *
Pour l'opération - : result = -436
Prends 0.073492 ms en temps d'execution pour l'operation -
Pour l'opération min : result = 0
Prends 0.042382 ms en temps d'execution pour l'operation min
Pour l'opération max : result = 18
Prends 0.047221 ms en temps d'execution pour l'operation max

./Exo6 100 :

8 6 6 14 7 1 12 3 1 1 6 0 12 1 15 5 6 17 10 19 10 18 5 13 1 5 18 5 4
1 16 1 13 1 14 18 16 8 8 10 18 14 18 13 14 10 10 8 7 10 19 15 10 3 19
5 3 7 2 19 18 19 15 3 1 13 2 4 13 9 15 4 0 12 17 13 17 7 10 13 17 12
 5 1 13 3 14 10 14 18 11 12 12 1 18 7 11 8 7 18
Pour l'opération + : result = 976
Prends 0.185969 ms en temps d'execution pour l'operation +
Pour l'opération * : result = 0
Prends 0.151339 ms en temps d'execution pour l'operation *
Pour l'opération - : result = -960
Prends 0.156601 ms en temps d'execution pour l'operation -
Pour l'opération min : result = 0
Prends 0.097676 ms en temps d'execution pour l'operation min
Pour l'opération max : result = 19
Prends 0.093386 ms en temps d'execution pour l'operation max

On remarque que l'opération min et max sont les plus rapide
en terme d'execution.
Les 3 autres opérations se suivent de près.

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