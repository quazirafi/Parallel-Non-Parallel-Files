//Exercice 9 , Axel Houdayer et Florian Simon-Rouquie IATIC 4

#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//omp_lock_t lock;
//int calcul(int * array, int length);
void carre(int * tab, int taille);
void affichage(int * tab, int taille);
void addreel(int* tab, int taille);
void addSecCritique(int* tab,int taille);
void addReduction(int* tab,int taille);
void addAtomique(int* tab,int taille);
int main(int argc, char ** argv) {

    omp_set_num_threads(5); //Permet de parametrer le nombre de threads

    srand(time(NULL));

    int * tab;
    //int total;
    int i,taille=10;

    if(argc!=1){
        taille = atoi(argv[1]);// a) permet de lire la taille du tableau sur la ligne de commande
    }

    // remplit le tableau en parallele :
    tab = (int*) malloc(sizeof(int) * taille);

							dummyMethod1();
    #pragma omp parallel for
    for(i = 0; i<taille; i++) {
        tab[i] = rand()%20;
        //printf("Nombre de thread  crées par OpenMP: %d \n ",omp_get_num_threads());
    }
							dummyMethod2();

    //affichage(tab, taille);
    //carre(tab, taille);
    addreel(tab,taille);
    addSecCritique(tab,taille);
    addReduction(tab,taille);
    addAtomique(tab,taille);
    // omp_init_lock(&lock);
    // total=calcul(tab,taille);
    // omp_destroy_lock(&lock);
    //Affichage du résultat :
    //affichage(tab, taille);

}


void carre(int * tab, int taille) {
    int i;
    //parallèlisation de la boucle for
    int total=0;
							dummyMethod1();
    #pragma omp parallel for
    for(i = 0; i<taille; i++) {
        //total+=tab[i];
        tab[i] = tab[i] * tab[i];

    }
							dummyMethod2();
    printf("Total = %d\n",total);
}

//Fonction qui permet d'afficher les valeurs du tableau
void affichage(int * tab,int taille) {
							dummyMethod3();
    for(int i = 0; i<taille; i++) {
        printf("%d\t", tab[i]);
    }
							dummyMethod4();
    printf("\n");

}
//Fonction témoin pour vérifier la valeur réelle de la somme des éléments
void addreel(int* tab, int taille){
    double T0 = omp_get_wtime(); //Temps d'execution
    int total=0;
							dummyMethod3();
    for(int i=0;i<taille;i++){
        total+=tab[i];
    }
							dummyMethod4();
printf("total réel : %d\n",total);
printf("[sequentiel] Prends %f ms en temps d'execution\n", (omp_get_wtime() - T0) * 1000);
}

void addSecCritique(int * tab, int taille) {
    double T0 = omp_get_wtime(); //Temps d'execution
    int i;
    int total=0;
        #pragma omp parallel for
															dummyMethod3();
        for(i = 0; i<taille; i++) {
            #pragma omp critical
                total+=tab[i];
        }
															dummyMethod4();
    printf("Total section critique = %d\n",total);
    printf("[secCritique] Prends %f ms en temps d'execution\n", (omp_get_wtime() - T0) * 1000);
}
void addAtomique(int * tab, int taille) {
    double T0 = omp_get_wtime(); //Temps d'execution
    int i;
    int total=0;
    #pragma omp parallel for
							dummyMethod3();
    for(i = 0; i<taille; i++) {
        #pragma omp atomic
            total+=tab[i];
    }
							dummyMethod4();
    printf("Total atomique = %d\n",total);
    printf("[atomique] Prends %f ms en temps d'execution\n", (omp_get_wtime() - T0) * 1000);
}

void addReduction(int * tab, int taille) {
    double T0 = omp_get_wtime(); //Temps d'execution
    int i;
    int total=0;
															dummyMethod1();
    #pragma omp parallel for reduction(+:total)
        for(i = 0; i<taille; i++) {
            total+=tab[i];
        }
															dummyMethod2();
        printf("Total reduction  = %d\n",total);
        printf("[reduction] Prends %f ms en temps d'execution\n", (omp_get_wtime() - T0) * 1000);
    }

/*    int calcul(int* array, int length){
        double T0 = omp_get_wtime();
        int total = 0;
        #pragma omp parallel for
            for(int i = 0; i < length; i++) {
                omp_set_lock(&lock);
                total+=array[i];
                omp_unset_lock(&lock);

        }
        printf("Prends %f ms en temps d'execution pour le calcul\n", (omp_get_wtime() - T0) * 1000);

        return total;
    }   */

/*


Jeu de test :
(gcc exo9.c -o exo9 -fopenmp)
./exo9 110 ou make exo9 x=110
6;18;14;11;12;7;13;18;17;19;8;7;10;11;6;4;1;17;17;19;16;7;18;8;15;8;13;16;19;10;10;
11;0;1;10;15;1;3;6;8;13;14;10;12;5;14;10;9;10;10;8;1;2;10;10;13;2;7;1;11;0;19;8;11;19;
10;3;7;18;14;17;14;1;8;8;15;0;14;18;3;17;3;5;4;4;8;16;15;8;0;4;8;16;11;18;10;5;9;13;8;
18;4;11;0;4;14;18;11;2;12;
Total = 1075
total réel : 1085

18	10	12	19	3	3	18	18	18	10	12	17	4	15	8	13	9
7	14	9	17	11	16	5	2	9	2	4	2	12	617	18	16	2
17	1	11	6	3	2	12	13	19	2	3	11	9	2	7	8	8
17	17	5	19	6	8	15	0	12	13	215	8	9	15	4	9	19
9	19	1	11	12	13	14	15	3	5	13	13	9	10	17	16	10
2	6	10	16	7	19	19	14	7	0	9	3	2	0	13	1	14
16	5	7	11	1	10
Total = 1060
total réel : 1085

a) On remarque grâce à notre fonction témoin que le total diffère par rapport au total réel
des éléments du tableau.
Ceci est du aux collisions puisque nous avons pas protégé correctement la somme.

make 9 x=110
3	6	16	3	14	8	4	12	16	10	415	11	11	16	13	10	11
9	0	9	16	2	8	0	12	9	18	16	14	0	18	1	6	1
10	19	3	3	18	18	619	3	16	15	11	1	16	15	15	12	44
12	5	3	4	7	7	2	6	7	18	11	0	13	2	3	7	16
2	7	213	0	10	14	19	4	7	1	6	16	612	7	14	17	17
8	0	7	11	15	416	17	19	3	5	1	10	7	14	10	17	0
13	19
Total = 0
total réel : 1023
b) On remarque que la valeur total est toujours égal à la valeur initial(ici 0) puisqu'on l'a
mit en private(total) la valeur total n'est pas modifié à la fin de la région parallèle, cette clause privatise
la variable total et est persistant.

c) make 9 10000 :
total réel : 94092
Total section critique = 94092
[secCritique] Prends 1.097334 ms en temps d'execution
Total reduction  = 94092
[reduction] Prends 0.208341 ms en temps d'execution
Total atomique = 94092
[atomique] Prends 0.341346 ms en temps d'execution

On remarque qu'en terme de performance la somme par section critique est la pire, en effet elle met plus de temps
que la clause atomique ou reduction pour réaliser la même opération.

d) On constate que la clause atomique est au moins 3 fois plus rapide par rapport à la clause critique, on peut donc
dire qu'elle est plus performante.
e) La clause réduction est la plus performante des 3, et permet d'éviter les collisions simplement.
Elle peut aussi gérer plusieurs autres opérations tel que la multiplication, la soustraction ..


******** Exo 10 ***
pour comparer les résultats décommenter les lignes 7, 8, 22 , 44 à 46 et 122 à 135
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