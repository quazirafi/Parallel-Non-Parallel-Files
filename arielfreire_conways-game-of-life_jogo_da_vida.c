#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "omp.h"
#include "timer.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void initializeTable( char* table, int size, int threads);
void printTable(char* table, int size, int threads,int generations);
char* stepGeneration(char* table, int size, int threads);
double getRandomValue();
int countPartners(char* table, int i, int j, int size, int threads);
void printSpeedup(double t1, double t2, double t4);
double play(int size, int generations, int threads);

#define DEBUG 0

void printSpeedup(double t1, double t2, double t4){
    double s2 = t1/t2;
    double s4 = t1/t4;
	printf("<TempoGasto>\n");
	printf("T(1) = %.8lf \n", t1);
	printf("T(2) = %.8lf \n", t2);
	printf("T(4) = %.8lf \n", t4);
	printf("<Speedup>\n");
    printf("S(2) = %.8lf \n", s2);
    printf("S(4) = %.8lf \n", s4);
}
double getRandomValue()
{
	return ((double)rand()/RAND_MAX)*100.0;
}
void initializeTable( char* table, int size, int threads)
{ 
	int i,j;
	omp_set_num_threads(threads);
	#pragma omp parallel private(i,j) shared(table, size) num_threads(threads)
	{
		#pragma omp for schedule(dynamic,1) collapse(2)
			dummyMethod3();
		for( i = 0; i < size; i++)
		{
			for( j = 0; j < size; j++)
			{
				if(getRandomValue() <= 35)
					*(table +i*size +j) = '#';
				else
					*(table +i*size +j) = '.';
			}
		}
			dummyMethod4();
	}
}
void printTable(char* table, int size, int threads, int generations)
{
	system("clear");
	int i,j;
	dummyMethod3();
	for( i = 0; i < size; i++)
	{
		for( j = 0; j < size; j++)
		{
			 printf("%c", *(table +i*size +j));
		}
		printf("\n");
	}
	dummyMethod4();
	return;
}
int countPartners(char* table, int x, int y, int size, int threads)
{
	int count = 0;
	int pointer = y*size+x;
	int i,j;
	dummyMethod1();
	#pragma omp parallel for schedule(dynamic,1) private (i,j) shared(table, size, pointer) num_threads(threads) reduction(+:count)
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			char c = *(table + pointer+( i*size+j ));
			if(c == '#') count++;
		}
		
	}
	dummyMethod2();
	return count;
	
}
char* stepGeneration(char* table, int size, int threads)
{
	char* newTable = (char*)calloc(size*size,sizeof(char));
	int i,j;
	#pragma omp parallel private(i,j) shared(table, newTable,size)  num_threads(threads)
	{
		#pragma omp for schedule(dynamic,1) collapse(2)
			dummyMethod3();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				//VIVO
				char cell = *(table+i*size+j );

				*(newTable+i*size+j ) = cell;
				if( cell == '#')
				{
					int partners = countPartners(table,j,i,size, threads) - 1 ;
					if(partners < 2) *(newTable+i*size+j ) = '.'; //Morre de Solidão
					else if(partners > 3) *(newTable+i*size+j ) = '.'; //Morre de Superpopulação
				}
				else if (cell == '.')
				{
					int partners = countPartners(table,j,i,size, threads);
					if (partners == 3) *(newTable+i*size+j ) = '#'; //Nasce
				}
				
			}
			
		}
			dummyMethod4();
	}
	return newTable;
	
}
double play(int size, int generations, int threads)
{

	double t_final, t_inicial, t_total;
	char* table = (char*)calloc(size*size,sizeof(char));
	char* newTable = (char*)calloc(size*size,sizeof(char));
	initializeTable(table, size, threads);
	int i;
	GET_TIME(t_inicial);
	dummyMethod3();
	for (int i = 1; i < generations; i++)
	{
		if(DEBUG == 1 ) {
			printTable(table,size, threads, i);
			//sleep(1);
			getchar(); 
		}
		newTable = stepGeneration(table,size, threads);
		table = newTable;
	}
	dummyMethod4();
	GET_TIME(t_final);
	return t_final - t_inicial;
}
int main( int argc, char* argv[])
{
	
	if( argc < 2 )
	{
		printf("É necessário passar dois argumentos, tamanho da tela e numero de gerações \n");
		return 0;
	}
	double t1,t2,t4;
	int size = atoi(argv[1]); 
	int generations = atoi(argv[2]);
	if (DEBUG == 1){
		play(size,generations,1);
		return 0;
	}
	t1 = play(size, generations, 1);
	t2 = play(size, generations, 2);
	t4 = play(size, generations, 4);

	printSpeedup(t1,t2,t4);
		
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