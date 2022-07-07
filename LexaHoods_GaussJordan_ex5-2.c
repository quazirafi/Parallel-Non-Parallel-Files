#include <stdio.h> 
#include "omp.h"
#include <time.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void carre(double *tab,int taille);
void print_tab(double *tab,int taille);

int main(int argc, char **argv){   
    
    FILE* fichier = fopen("perf5-2.csv", "w");
    
    srand(time(NULL));
    int nbr_thread=4;
    omp_set_num_threads(nbr_thread);
   
    int i,j,taille = 10;
    
    double debut,fin;
    
    printf("\nTaille variable, Nbr de threas fixe: %d\n",nbr_thread);
    fprintf(fichier,"Taille;Temps;");
    for(taille=10;taille<10000000;taille*=10){
        
        double *tab=(double *) malloc(sizeof(double)*taille);
        
        debut = omp_get_wtime();
        
        double somme;
        
															dummyMethod1();
        #pragma omp parallel for
        for(i=0;i<taille;i++){
            tab[i]=rand();
        }
															dummyMethod2();
       
															dummyMethod1();
        #pragma omp parallel for reduction(+:somme)
        for(i=0;i<taille;i++){
            somme+=tab[i];
            //printf("Thread: %d s: %11.0f i: %11.0f\n",omp_get_thread_num(),somme,tab[i]);
        }
															dummyMethod2();
        fin=omp_get_wtime();
        printf("temps: %3.6f s | taille: %d\n",fin-debut,taille);
        fprintf(fichier,"\n%d;%f;",taille,fin-debut);
        //printf("Somme finale: %11.0f\n",somme);
        
        free(tab);;
    }
    printf("\nNbr de threas variable, taille fixe: %d\n",taille);
    fprintf(fichier,"\nNbr de threas ;Temps;");
    taille=1000000;
    double *tab=(double *) malloc(sizeof(double)*taille);
    
    for(j=1;j<100;j+=20){
        
        omp_set_num_threads(j);
        
        double somme;
        
        debut = omp_get_wtime();
        
															dummyMethod1();
        #pragma omp parallel for
        for(i=0;i<taille;i++){
            tab[i]=rand();
        }
															dummyMethod2();
       
															dummyMethod1();
        #pragma omp parallel for reduction(+:somme)
        for(i=0;i<taille;i++){
            somme+=tab[i];
            //printf("Thread: %d s: %11.0f i: %11.0f\n",omp_get_thread_num(),somme,tab[i]);
        }
															dummyMethod2();
        fin =omp_get_wtime();
        printf("temps: %3.6f s | nbr Threads: %d \n",fin-debut,j);
        fprintf(fichier,"\n%d;%f;",j,fin-debut);
        //printf("Somme finale: %11.0f\n",somme);
    }
    free(tab);
    
    fclose(fichier);
}


/*

Les courbes de performances sont en annexes 

Pour afficher les sommes partielles et totales, il faut decommenter 
les lignes 39,44, 69 et 74

Jeu de test :
gcc -fopenmp -Werror ex5-2.c -o ex5-2.out
./ex5-2.out 
ou bien
make 5-2

Taille variable, Nbr de threas fixe: 4
temps: 0.000420 s | taille: 10
temps: 0.000062 s | taille: 100
temps: 0.001131 s | taille: 1000
temps: 0.026808 s | taille: 10000
temps: 0.060773 s | taille: 100000
temps: 0.112253 s | taille: 1000000

Nbr de threas variable, taille fixe: 10000000
temps: 0.043156 s | nbr Threads: 1 
temps: 0.143510 s | nbr Threads: 21 
temps: 0.155096 s | nbr Threads: 41 
temps: 0.181844 s | nbr Threads: 61 
temps: 0.167035 s | nbr Threads: 81 


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