#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mpi.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "../include/imagen.h"
#include "../include/ga.h"
#include "../include/derivados_mpi.h"

#define PRINT 1

static int aleatorio(int max)
{
	return (rand() % (max + 1));
}

void init_imagen_aleatoria(RGB *imagen, int max, int total)
{
dummyMethod3();
	for (int i = 0; i < total; i++)
	{
		imagen[i].r = aleatorio(max);
		imagen[i].g = aleatorio(max);
		imagen[i].b = aleatorio(max);
	}
dummyMethod4();
}

RGB *imagen_aleatoria(int max, int total)
{
	RGB *imagen = (RGB *)malloc(total * sizeof(RGB));
	assert(imagen);

	init_imagen_aleatoria(imagen, max, total);
	return imagen;
}

static int comp_fitness(const void *a, const void *b)
{
	/* qsort pasa un puntero al elemento que está ordenando */
	return (*(Individuo *)a).fitness - (*(Individuo *)b).fitness;
}

void crear_imagen(const RGB *imagen_objetivo, int num_pixels, int ancho, int alto, int max, int num_generaciones, int tam_poblacion, RGB *imagen_resultado, const char *output_file)
{
	double initial_time_fitness = 0;
	double final_time_fitness = 0;
	double total_time_fitness = 0;

	double fitness_anterior = 0, fitness_actual, diferencia_fitness;
	int rank, world_size;

	Individuo *poblacion = NULL;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	if (rank == 0)
	{

		poblacion = malloc(tam_poblacion * sizeof(Individuo));
		assert(poblacion);

		/* Todos los nodos calculan su parte */
			dummyMethod3();
		for (int i = 0; i < tam_poblacion; i++)
		{
			init_imagen_aleatoria(poblacion[i].imagen, max, num_pixels);
		}
			dummyMethod4();
			dummyMethod3();
		for (int i = 0; i < tam_poblacion; i++)
		{
			fitness(imagen_objetivo, &poblacion[i], num_pixels);
		}
			dummyMethod4();

		qsort(poblacion, tam_poblacion, sizeof(Individuo), comp_fitness);
		//final_time_fitness = MPI_Wtime();
		//total_time_fitness += final_time_fitness - initial_time_fitness;

		// Ordenar individuos según la función de bondad (menor "fitness" --> más aptos)
	}

	MPI_Datatype rgb_type;
	MPI_Datatype individuo_type;
	crear_tipo_datos(num_pixels, &rgb_type, &individuo_type);
	int chunkSize = tam_poblacion / world_size;
	int leftover = tam_poblacion % world_size;

	Individuo *poblacionLocal = malloc(chunkSize * sizeof(Individuo));
	MPI_Scatter(&poblacion[leftover], chunkSize, individuo_type, poblacionLocal, chunkSize, individuo_type, 0, MPI_COMM_WORLD);
	// B. Evolucionar la Población (durante un número de generaciones)
	dummyMethod3();
	for (int g = 0; g < num_generaciones; g++)
	{
		if(rank == 0)
			fitness_anterior = poblacion[0].fitness;

		int cruzarChunkSize = chunkSize/2;
		int cruzarLeftover = leftover/2;
		// Promocionar a los descendientes de los individuos más aptos
		if (rank == 0)
		{
			for (int i = 0; i < cruzarLeftover; i+=2)
			{
				cruzar(&poblacion[i], &poblacion[i+1], &poblacion[cruzarLeftover/2+i], &poblacion[cruzarLeftover/2+i+1], num_pixels);
			}

		}

		for (int i = 0; i < cruzarChunkSize; i+=2)
		{

			cruzar(&poblacionLocal[i], &poblacionLocal[i + 1], &poblacionLocal[cruzarChunkSize/2 + i], &poblacionLocal[cruzarChunkSize/2 + i + 1], num_pixels);
		}


		// Mutar una parte de la individuos de la población (se decide que muten tam_poblacion/4)
		int mutation_start = (tam_poblacion / 4) / world_size;

		if(rank == 0) {
			for(int i = leftover/4; i< leftover; i++){
				mutar(&poblacion[i], max, num_pixels);
			}
		}
		for (int i = mutation_start; i < chunkSize; i++)
		{
			mutar(&poblacionLocal[i], max, num_pixels);
		}


		if (rank == 0)
		{
			initial_time_fitness = MPI_Wtime();
			for (int i = 0; i < leftover; i++)
			{
				fitness(imagen_objetivo, &poblacion[i], num_pixels);
			}
		}

		/* Todos los nodos calculan su parte */
		for (int i = 0; i < chunkSize; i++)
		{
			fitness(imagen_objetivo, &poblacionLocal[i], num_pixels);
		}
		// Cada 10 iteraciones recuperamos subpoblaciones, ordenamos y volvemos a distribuir
		if((g % 10 == 0 && g) || g == num_generaciones - 1){
			
			MPI_Gather(poblacionLocal, chunkSize, individuo_type, &poblacion[leftover], chunkSize, individuo_type, 0, MPI_COMM_WORLD); // Cambiar el tipo de MPI por el derivado

			if (rank == 0)
			{
				qsort(poblacion, tam_poblacion, sizeof(Individuo), comp_fitness);
				final_time_fitness = MPI_Wtime();
				total_time_fitness += final_time_fitness - initial_time_fitness;
				fitness_actual = poblacion[0].fitness;
				diferencia_fitness = -(fitness_actual - fitness_anterior) / fitness_actual * 100;
				if (PRINT)
				{
					printf("Generacion %d - ", g);
					printf("Fitness = %e - ", fitness_actual);
					printf("Diferencia con Fitness Anterior = %.2e%c\n", diferencia_fitness, 37);
				}
			}

			MPI_Scatter(&poblacion[leftover], chunkSize, individuo_type, poblacionLocal, chunkSize, individuo_type, 0, MPI_COMM_WORLD);

		}

			qsort(poblacionLocal, chunkSize, sizeof(Individuo), comp_fitness);
		

	
	}
	dummyMethod4();
	// Devuelve Imagen Resultante
	if (rank == 0)
	{
		//qsort(poblacion, tam_poblacion, sizeof(Individuo), comp_fitness);

		printf("Tiempo invertido en cálculo fitness: %f\n", total_time_fitness);
		memmove(imagen_resultado, poblacion[0].imagen, num_pixels * sizeof(RGB));
		printf("Imagen movida\n");
		// Release memory
	}
	if (rank == 0)
		free(poblacion);
	free(poblacionLocal);
	
}

void cruzar(Individuo *padre1, Individuo *padre2, Individuo *hijo1, Individuo *hijo2, int num_pixels)
{
	// Elegir un "punto" de corte aleatorio a partir del cual se realiza el intercambio de los genes.
	// * Cruzar los genes de cada padre con su hijo
	// * Intercambiar los genes de cada hijo con los del otro padre
	int corte = aleatorio(num_pixels - 1);
	#pragma omp parallel
	{
		#pragma omp for 
			dummyMethod3();
		for (int i = 0; i < corte; i++)
		{
			hijo1->imagen[i] = padre1->imagen[i];
			hijo2->imagen[i] = padre2->imagen[i];
		}
			dummyMethod4();
		#pragma omp for
			dummyMethod3();
		for (int i = corte; i < num_pixels; i++)
		{
			hijo1->imagen[i] = padre2->imagen[i];
			hijo2->imagen[i] = padre1->imagen[i];
		}
			dummyMethod4();
	}
}

void fitness(const RGB *objetivo, Individuo *individuo, int num_pixels)
{
	// Determina la calidad del individuo (similitud con el objetivo)
	// calculando la suma de la distancia existente entre los pixeles
	double fitness = 0;
	dummyMethod1();
	#pragma omp parallel for reduction(+:fitness)
	for (int i = 0; i < num_pixels; i++)
	{

		fitness += abs(objetivo[i].r - individuo->imagen[i].r) + abs(objetivo[i].g - individuo->imagen[i].g) + abs(objetivo[i].b - individuo->imagen[i].b);
	}
	dummyMethod2();

	individuo->fitness = fitness;
}

void mutar(Individuo *actual, int max, int num_pixels)
{
	// Cambia el valor de algunos puntos de la imagen de forma aleatoria.

	// Decidir cuantos pixels mutar. Si el valor es demasiado pequeño,
	// la convergencia es muy pequeña, y si es demasiado alto diverge.
	double ratioMutacion = 0.002;
	int numMutar = (int)num_pixels * ratioMutacion;

	dummyMethod3();
	for (int i = 0; i < numMutar; i++)
	{
		int index = aleatorio(num_pixels - 1);

		actual->imagen[index].r = aleatorio(max);
		actual->imagen[index].g = aleatorio(max);
		actual->imagen[index].b = aleatorio(max);
	}
	dummyMethod4();
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