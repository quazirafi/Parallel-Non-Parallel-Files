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
    
    srand(time(NULL));
   
    
    int i,j;
    int nl=10,nc=10; //attention <1000
    double debut,fin;
    
    if(argc==3){
        nl = atoi(argv[1]);
        nc = atoi(argv[2]);
    }
    
    printf("\nTableau statique \n");
    double t[nl][nc];
    
    debut = omp_get_wtime();
    
							dummyMethod1();
    #pragma omp parallel for private(i,j)
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
            printf("Thread: %d Charge: %d-%d \n",omp_get_thread_num(),i,j);
            t[i][j]=rand();
        }
    }
							dummyMethod2();
    fin = omp_get_wtime();
    
    printf("temps: %3.6f s\n",fin-debut);
    
    
    printf("\nTableau dynamique\n");
    
    double **tab=(double **) malloc(sizeof(double*)*nl);
							dummyMethod3();
    for(i=0;i<nl;i++){
        tab[i]=(double *) malloc(sizeof(double)*nc);
    }
							dummyMethod4();
    
    debut = omp_get_wtime();
    
							dummyMethod1();
    #pragma omp parallel for private(i,j)
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
            printf("Thread: %d Charge: %d-%d \n",omp_get_thread_num(),i,j);
            tab[i][j]=rand();
        }
    }
							dummyMethod2();
    
    fin = omp_get_wtime();
    
    printf("temps: %3.6f s\n",fin-debut);
    
							dummyMethod3();
    for(i=0;i<nl;i++){
        free(tab[i]);
    }
							dummyMethod4();
    free(tab);
        
    return 0;
}
/*
gcc -fopenmp -Werror ex5-3.c -o ex5-3.out
./ex5-3.out 3
Ou bien 
make 5-3 x=3

Tableau statique 
Thread: 0 Charge: 0-0 
Thread: 0 Charge: 0-1 
Thread: 0 Charge: 0-2 
Thread: 1 Charge: 1-0 
Thread: 1 Charge: 1-1 
Thread: 1 Charge: 1-2 
Thread: 2 Charge: 2-0 
Thread: 2 Charge: 2-1 
Thread: 2 Charge: 2-2 
temps: 0.001922 s

Tableau dynamique
Thread: 1 Charge: 1-0 
Thread: 1 Charge: 1-1 
Thread: 1 Charge: 1-2 
Thread: 2 Charge: 2-0 
Thread: 2 Charge: 2-1 
Thread: 2 Charge: 2-2 
Thread: 0 Charge: 0-0 
Thread: 0 Charge: 0-1 
Thread: 0 Charge: 0-2 
temps: 0.000258 s
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