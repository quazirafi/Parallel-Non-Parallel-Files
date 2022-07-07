/* Ordenación de un vector
 * 
 * Compilación: gcc -W OrdenaVectorOMP.c -o OrdenaVectorOMP -fopenmp
 * Ejecución: ./OrdenaVectorOMP	
*/
/*
* Authors: 
*  Josue Carlos Zenteno Yave : Intel Core i7-8750H  -  12 cores
*  Sergio Silvestre Pavón : Intel Core i5-7200U  -  4 cores
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


#define M 100			// ==> Rango de valores de los componentes: [0, M[
#define VECT_SIZE 200000 /// 50000	// N.º componentes del vector que se quiere ordenar
#define NM 4			// N.º de métodos de ordenación que se llamarán desde el programa principal
#define min(a,b) ((a)<(b)? a:b)
#define FALSE 0
#define TRUE 1

// Variables globales
float vini[VECT_SIZE], vord0[VECT_SIZE], vord[VECT_SIZE];	// vector desordenado y vector que se ordenará, respectivamente

void copiarVector(float Vdest[], float V[], int size)
{
	int i,np;
	np = omp_get_num_procs();
			dummyMethod1();
	#pragma omp parallel for num_threads(np)
		for (i = 0; i < size; ++i){	
			Vdest[i] = V[i];
		}
			dummyMethod2();
}

void printVector(float vector[], int size)
{
	/**********************************************************************************************
	*NON PARALLELIZABLE FOR LOOP 
	As we cannot set an order of execution for the threads, the previous and the ordered vector 
	are printed randomly depending on the 'speed' of each thread printing each value.
	***********************************************************************************************/
	dummyMethod4();
	dummyMethod3();
	for (int i = 0; i < size; ++i) printf("%0.4f\t", vector[i]);
	printf("\n\n");
}

int estaOrdenado(float vector[], int size)
{
  int i=0;
  do i++; while ((vector[i-1]<=vector[i])&&(i<size-1));
  
  return ((i==size-1)&&(vector[i-1]<=vector[i]));	// TRUE (1) si el vector está ordenado y FALSE (0) en caso contrario
}

int vectoresIguales(float vecta[], float vectb[], int size)
{
	int i, ini, fin, iguales = TRUE, np = omp_get_num_procs();	// número de núcleos del microprocesador
	#pragma omp parallel for num_threads(np) private(ini, fin, i) shared(iguales)
			dummyMethod3();
		for (i=0; i<np; i++)
		{
			ini = i*size/np;	fin =(i+1)*size/np;
			int j=ini;
			while ((vecta[j] == vectb[j]) && (j<fin)) j++;
			
			#pragma omp critical
			iguales = iguales && (j==fin);
		}
			dummyMethod4();
	return iguales;
}


/* Función que mezcla dos fragmentos ordenados contiguos de un vector en un solo fragmento ordenado
 * Fragmentos ordenados de entrada: (vector[ini1]... vector[ini2-1]),		(vector[ini2]... vector[fin2])
 * Fragmento ordenado que contiene el resultado:	(vector[ini1]... vector[ini2-1], vector[ini2]... vector[fin2]) 
*/
void mezcla_ordenada(float vector[], int ini1, int ini2, int fin2)
{
	int i, j, k, terminado = 0; float temp;
	i = ini1; j = ini2;
	do
		{	// vector[ini1] <=...<= vector[j-1] AND vector[j] <=...<= vector[fin2] AND i < j
			while ((vector[i] <= vector[j]) && (i < j-1)) i++;
			if (vector[i] > vector[j])
				{
					/* Rotamos vector[i], vector[i+1], ...,vector[j-1], vector[j]
					 * para que vector[j] pase a la posición i y el resto se desplace una posición a la derecha */
					temp = vector[j];
					/**********************************************************************************************
					*NON PARALLELIZABLE FOR LOOP
					The following for loop cannot be parallelized, as, for example in the iteration k=3
					we will be reading vector[3-1] and writing this value in vector[3] then in the next iteration
					we will reading vector[2-1] and writing in vector[2] that is the same memory position where we
					were reading in the previous iteration, so there exist a Write after Read dependecy (WAR) and 
					as we cannot set an order of execution for the threads, this loop cannot be parallelized.

					[There are WAR dependences in the whole loop unless it is the first iteration where there will 
					be only one thread]
					***********************************************************************************************/
									dummyMethod4();
									dummyMethod3();
					for (k=j; k>i ; k--) vector[k] = vector[k-1];
					vector[i] = temp;
					if (j==fin2) terminado = 1;
						// Hemos colocado en su posición el último elemento del segundo fragmento
					else {j++; i++;}
				}
			// vector[ini1] <=...<= vector[j-1] AND vector[j] <=...<= vector[fin2] AND i < j
			else terminado = 1;
				 /* i == j-1 AND vector[i] <= vector[j], 
				 * luego vector[j-1] <= vector[j] y todo queda ordenado*/
		}
	while (!terminado) ;
}

// Funciones que ordenan los size primeros elementos de un vector

void ord_parA(float vector[], int size)
{
	int incr, i, fin2,np;
	np = omp_get_num_procs();
	/**********************************************************************************************
	*NON PARALLELIZABLE FOR LOOP
	As all the threads will be executing at the same time one thread can be ordering the vector by
	pair of 2 values, other can be ordering the vector by sets of 4 and so on so on.

	[Parallelizing this has no sense as we will be repeating the work in every thread.]
	***********************************************************************************************/
	for (incr = 2; incr < 2*size; incr = 2*incr){
					dummyMethod1();
		#pragma omp parallel for num_threads(np) private (fin2, i) shared(vector,size,incr)
			for (i = 0; i < (size-incr/2); i += incr)		// (i+incr/2) < size
			{	fin2 = min(size-1,i+incr-1);
				mezcla_ordenada(vector,i,i+incr/2,fin2);	
				/* Quedan ordenados incr componentes consecutivos del vector (índices i,i+1,...i+incr-1)
				* (el último trozo ordenado puede ser menor: índices i, i+1,...size-1)
				*/
			}
					dummyMethod2();
		/* El último valor de incr cumple size <= incr < 2*size. 
		 * Esto conlleva que está ordenado todo el vector, al ser size <= incr */
	}
}	// Fin de ord_secA


void ord_secB(float vector[], int size)
{
  int i,j; float x;
  /**********************************************************************************************
	*NON PARALLELIZABLE FOR LOOP
	The following for loop cannot be parallelized, as, for example in the iteration i = 2, j will
	be j = 1, so in the while loop we read vector[1] checking the condition, then inside this loop
	we assign to vector[2] the value of vector[1]. Then in the next iteration i = 3, j will be
	j = 2 and then in the while loop we will be reading vector[2] which was written in the previous
	iteration. For theis reason we have a Read after Write dependency (RAW).

	[There are RAW dependences in the whole loop unless it is the first iteration.]
	***********************************************************************************************/  
  for (int i = 1; i < size; i++)
  {
	 x = vector[i]; j = i-1;
	 while ((x<vector[j])&&(0<=j))
	 {
		 vector[j+1]=vector[j]; j--;
	 }
	 vector[j+1]=x;
  }
}	// Fin de ord_secB

void ord_secC(float vector[], int size)
{
   int list_length, i; float temp;
   /**********************************************************************************************
	*NON PARALLELIZABLE FOR LOOP
	As we cannot set an order of execution for the threads we cannot assure that the algorithm will
	work properly a 100% of the times, as in some cases (with the example of the assignment) if one
	thread is executing the algorithm with a lenght of 6 and then it comes another one executing 
	the algorithm with a lenght of 7. Therefore 32 will be set in the second to last position and it 
	will not be accesible for any other thread. This leads the algorithm to fail.

	[Take into account that this cannot be fixed by protecting the shared variables]
	***********************************************************************************************/
   for (list_length = size; list_length >= 2; list_length--)
   /* El siguiente for no se puede paralelizar ya que, por ejemplo, en la iteración i=0 
    * puede que haya que escribir en vector[1] y en la iteración siguiente (i=1) hay que leer vector[1].
    * Así pues, si se cumple la condición del "if" hay una dependencia leer después de escribir (RAW)
    * entre la iteración 0 y la 1.
    * [ En general, hay una dependencia RAW entre cualquier iteración, i=k,
    * (que no sea la última) y la siguiente respecto al operando vector[k+1], si se cumple la condición
    * del "if", cosa que puede ocurrir o no dependiendo de los datos de entrada).] 	*/
      for (i = 0; i < list_length-1; i++)
         if (vector[i] > vector[i+1])
         {
            temp = vector[i];
            vector[i] = vector[i+1];
            vector[i+1] = temp;
         }

}  // Fin de ord_secC

void ord_parD(float vector[], int size)
{
   int phase, i; float temp;
   /* El siguiente for no se puede paralelizar ya que entre una fase y la siguiente hay dependencias RAW:
    * por ejemplo, un fase puede escribir en vector[1] y la siguiente lee vector[1]*/
   for (phase = 0; phase < size; phase++) 
      if (phase % 2 == 0)
      { // Fase par
																	dummyMethod1();
		 #pragma omp parallel for private (temp)
         for (i = 1; i < size; i += 2) 
            if (vector[i-1] > vector[i])
            {
               temp = vector[i];
               vector[i] = vector[i-1];
               vector[i-1] = temp;
            }
																	dummyMethod2();
      } else
      { // Fase impar
																	dummyMethod1();
		 #pragma omp parallel for private(temp)
         for (i = 1; i < size-1; i += 2)
            if (vector[i] > vector[i+1])
            {
               temp = vector[i];
               vector[i] = vector[i+1];
               vector[i+1] = temp;
            }
																	dummyMethod2();
      }
}  // Fin de ord_parD

int main()
{
	int i, np; double t;
	
	// 1. Dar valores aleatorios al vector en el intervalo [0, M[
	srand((unsigned)time(NULL));
	float faux;
	np = omp_get_num_procs();
			dummyMethod1();
	#pragma omp parallel for num_threads(np) shared(vini) private(i,faux)
		for (i=0; i < VECT_SIZE; i++){
			faux = (float)(rand()%RAND_MAX)/RAND_MAX;
			// faux se distribuye con igual probabilidad a lo largo del intervalo [0,1[
			vini[i] = M *faux;
		}
			dummyMethod2();
		
	// 2. Imprimir vector desordenado (solo si el número de componentes no es muy grande)
	if (VECT_SIZE <= 400)	{
		printf("\nVector antes de ser ordenado: \n");
		printVector(vini,VECT_SIZE);
	}
	
	// 3. Para el primer método de ordenación, copiar vini en vord0, ordenar vord0 y comprobar que el vector queda ordenado
	//	  Para el resto de métodos, copiar vini en vord, ordendar vord y comprobar que vord queda igual que vord0
	//	  Para todos los métodos medir e imprimir el tiempo de copiar y ordenar el vector

	/**********************************************************************************************
	*NON PARALLELIZABLE FOR LOOP
	As the program has been made in a way that we have to wait for the algorithm A to be executed 
	to compare its result with the other Algorithm results and then print if those have been ordered
	correctly too. 

	For that reason as we will have all the threads executing at the same time if the thread responsible
	of executing the algorithm A is not the very first ending its execution and saving it in vord0, 
	then all the other threads will finish before and also checking their results with an old 
	version of vord0, printing that they are not correct. But they, in fact, are ordered.

	[Take into account that we cannot use barriers as the threads will execute a different part of code
	due to the switch.]
	***********************************************************************************************/
	for (i=0; i<NM; i++)
	{
		t = omp_get_wtime();
		printf("=================================================================\n");
		switch (i)
		{
			case	0:
				copiarVector(vord0, vini, VECT_SIZE);	// vord0 <-- vini
				printf("Ordenando por el método paralelo A\n");
				ord_parA(vord0,VECT_SIZE);
				printf("\nTiempo empleado por método paralelo A: %0.8f milisegundos\n",1000*(omp_get_wtime()-t));
				if (estaOrdenado(vord0,VECT_SIZE)) printf("\nEl vector obtenido por el método paralelo A está ordenado\n");
				else printf("\nEl vector obtenido por el método paralelo A no está ordenado\n");
				break;
			case	1:
				copiarVector(vord, vini, VECT_SIZE);	// vord <-- vini
				printf("Ordenando por el método secuencial B\n");
				ord_secB(vord,VECT_SIZE);
				printf("\nTiempo empleado por método secuencial B: %0.8f milisegundos\n",1000*(omp_get_wtime()-t));
				if (vectoresIguales(vord0, vord, VECT_SIZE))
					printf("\nEl vector obtenido por el método secuencial B coincide con el del método secuencial A\n");
				else printf("\nEl vector obtenido por el método secuencial B no coincide con el del método secuencial A\n");			
				break;
			case	2:
				copiarVector(vord, vini, VECT_SIZE);	// vord <-- vini			
				printf("Ordenando por el método secuencial C\n");
				ord_secC(vord,VECT_SIZE);
				printf("\nTiempo empleado por método secuencial C: %0.8f milisegundos\n",1000*(omp_get_wtime()-t));
				if (vectoresIguales(vord0, vord, VECT_SIZE))
					printf("\nEl vector obtenido por el método secuencial C coincide con el del método secuencial A\n");
				else printf("\nEl vector obtenido por el método secuencial C no coincide con el del método secuencial A\n");
				break;
			case	3:
				copiarVector(vord, vini, VECT_SIZE);	// vord <-- vini			
				printf("Ordenando por el método paralelo D\n");
				ord_parD(vord,VECT_SIZE);
				printf("\nTiempo empleado por método paralelo D: %0.8f milisegundos\n",1000*(omp_get_wtime()-t));
				if (vectoresIguales(vord0, vord, VECT_SIZE))
					printf("\nEl vector obtenido por el método paralelo D coincide con el del método paralelo A\n");
				else printf("\nEl vector obtenido por el método paralelo D no coincide con el del método paralelo A\n");			
				break;				
		}
	}

	
	// 4. Imprimir vector ordenado (solo si el número de componentes no es muy grande)
	printf("=================================================================\n");
	if (VECT_SIZE <= 400)	{
		printf("\nVector ordenado: \n");
		printVector(vord,VECT_SIZE);
	}
	printf("\n");
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