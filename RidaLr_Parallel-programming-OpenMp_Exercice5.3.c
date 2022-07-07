#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NL 1100  //NL => number of lignes 
#define NC 900  //NC => number of columns 



/* This fuction allocate a 2 dimension table dynamically*/
double **alloc_tab2D(int nl,int nc)
{	
	double **tab=(double**)malloc(nl*sizeof(double *));
dummyMethod3();
	for( int i=0;i<nl;i++)
	{
		tab[i]=(double*)malloc(nc*sizeof(double));
	}
dummyMethod4();
	return tab;
}

void desalloc_tab2D(double **tab,int nl,int nc)
{
dummyMethod3();
	for(int i=0;i<=nl;i++)
	{
		free(tab[i]);
	}
dummyMethod4();
	free(tab);
}

int main()
{
	
	srand(time(NULL));
	omp_set_num_threads(100);
	int nb_threads = omp_get_max_threads();
	
	/****************************Allocation dynamique*****************************/
	double **T2D = alloc_tab2D(NL,NC);
	double temps_debut = clock(); //initial time
	
			dummyMethod1();
	#pragma omp parallel for 
		for(int i = 0 ; i < NL ; i++ )
		{
			for(int j = 0 ; j < NC ; j++ )
			{
				T2D[i][j] = (double)rand()/3.33;
				printf("Thread number %d fill this portion [%d][%d] of T2D ( Dynamic) \n",omp_get_thread_num(),i,j);
			}
		}
			dummyMethod2();
	desalloc_tab2D(T2D,NL,NC);
	double timedynamic = (clock() - temps_debut) / (double)CLOCKS_PER_SEC;
	
	/*****************************Allocation static******************************/
	double temps_debut2 = clock(); //initial time
	double TA2D[NL][NC];
			dummyMethod1();
	#pragma omp parallel for 
		for(int i = 0 ; i < NL ; i++ )
		{
			for(int j = 0 ; j < NC ; j++ )
			{
				TA2D[i][j] = (double)rand()/3.33;
				printf("Thread number %d fill this portion [%d][%d] of T2D (static) \n",omp_get_thread_num(),i,j);
			}
		} 
			dummyMethod2();
	double timestatic = (clock() - temps_debut2) / (double)CLOCKS_PER_SEC;
	printf("%d",nb_threads);
	// Show execution results.
	fprintf(stdout, "\n\n"
	  "   Nombre de lignes      : %d sec \n"
	  "   Nombre de colonnes    : %d sec \n"
	  "   Temps d'exécution (Tab statique) : %f sec \n"
	  "   Temps d'exécution (Tab dynamique) : %f sec \n"
	  "   La charge des threads (Statique)  : %f.\n"
	  "   La charge des threads (dynamique)  : %f.\n"
	  "   La charge des processeurs (statique)  : %f.\n"
	  "   La charge des processeurs (dynamique)  : %f.\n",
	  NL,NC,timestatic, timedynamic, (timestatic/100), (timedynamic/100), (timestatic/omp_get_num_procs()), (timedynamic/omp_get_num_procs()));

	return 0;
}

/****
 * 
 *  1)- Après l'exécution du programme on a eu les résultats ci-dessous , on constate d'après ces derniers que 
 *    la version (tableau dynamique) est plus efficace que la version avec un tableau statique, en temps d'execution. 
 * 
 *
 * 
 *                   ---------------------------------------------------------------------------------------------------------------
 *                  |                        STATIQUES                      |				      DYNAMIQUES                        |
 * 					 ---------------------------------------------------------------------------------------------------------------
 *  				|   Charges                      | Temps d'exécution    |   Charges                      | Temps d'exécution	|
 *	--------------------------------------------------------------------------------------------------------------------------------
 * |    NL = 700    | charges threads =0.125499      | time = 0.291166 sec  |  charges threads =  0.151083   | time = 0.257982 sec  |
 * |    NC = 560    | charges processeurs =6.533054  |                      |  charges processeurs =7.225250 |      				|
 * |--------------------------------------------------------------------------------------------------------------------------------|
 * |    NL = 1000   | charges threads =	0.276374     | time = 0.378257 sec  |  charges threads = 0.264953    | time = 0.360686 sec  |
 * |    NC = 800    | charges processeurs = 13.818709|                      |  charges processeurs =13.247638| 					    |
 *  --------------------------------------------------------------------------------------------------------------------------------
 * |    NL = 1100   | charges threads =	0.323663     | time = 0.555118 sec  |  charges threads = 0.318080    | time = 0.505309 sec  |
 * |    Nc = 900    | charges processeurs =16.183152 |                      |  charges processeurs =15.903982|     				    |
 *  --------------------------------------------------------------------------------------------------------------------------------
 * 
 * *****/
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