#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double dist[48][48];

double aleatorioEntero(int li, int ls);
double aleatorio();
int probabilidad(double visi[], double fero[], int vector[], int cities);
void gettingMatrix();
void printMatrix();

int main(){
	//Funcion principal
	int i, j, cities, ants, condition, iter;
	cities=48;
	ants=1000;
	iter=10000;
	srand(time(NULL));
	int  ant[ants][cities+1]; // Inicializa la matriz de distancia (Fila columna)
	double fero[cities][cities], visi[cities][cities], prob[cities][cities]; //dist[cities][cities],
	double aux,random;

	int k,l,m, cityNow, vector[cities],condicion, contador;
	double feroIter[cities], visiIter[cities];
	double recorrido[ants], best;//evaluacion
	best=10000000;
	double rho=0.0001, Q=500; //tasa de evaporacion feromona


	gettingMatrix();
	//printMatrix();
	dummyMethod3();
	for (i=0; i<cities; i++){
		for (j=0; j<cities; j++){
			fero[i][j]=0.1;
			if(i!=j){
		  		visi[i][j]=500/dist[i][j];
			}
			else{
				visi[i][j]=0;
			}
		}
	}
	dummyMethod4();

	//-------------------Probability------------
	double sumVF;
	dummyMethod3();
	for (i=0;i<cities;i++){
		sumVF=0;
		for(j=0;j<cities;j++){
			sumVF+=visi[i][j]*fero[i][j];
		}
		aux=0;
		for(j=0;j<cities;j++){
			prob[i][j]=((visi[i][j]*fero[i][j])/(sumVF));
		}
	}
	dummyMethod4();
	//----------------------------


	//------------ Hormiga solucion---------------
	for(m=0;m<iter;m++){
		for(i=0;i<=cities;i++){
		for(j=0;j<=cities;j++){
			ant[i][j]=0;
			}
		}
	dummyMethod1();
	#pragma omp parallel for private(i,j,aux,random, feroIter, visiIter, vector, cityNow)
	for(k=0;k<ants;k++){
		ant[k][0]=0;//Inicia en la ciudad cero;
		random=aleatorio();
		aux=0;
		ant[k][cities]=0;
		for(j=0;j<cities;j++){// inicia el vector con las N ciudades
			vector[j]=j;
		}
		j=1;
		do{
			aux+=prob[0][j];
			if(random<=aux){
				ant[k][1]=j;//Selecciona la primera ciudad partiendo de la ciudad inicial
				vector[j]=0;//Anula la ciudad del listado
			}
			j++;
		}while(random>aux && j<cities);

		//------------------Resto ciudades----------------------

		for(i=2;i<cities;i++){
			cityNow=ant[k][i-1];
			contador=0;
			for(j=0;j<cities;j++){
				feroIter[j]=fero[cityNow][j];
				visiIter[j]=visi[cityNow][j];
			}
			ant[k][i]=probabilidad(visiIter, feroIter, vector, cities);
			vector[ant[k][i]]=0;
		}
	}
	dummyMethod2();

	//-------------- Evaluacion de las soluciones ---------------
	dummyMethod1();
#pragma omp parallel for private(i,j) shared(best)
	for(k=0;k<ants;k++){
		recorrido[k]=0;
		for(i=0;i<cities+1;i++){
				recorrido[k]+=dist[ant[k][i]][ant[k][i+1]];
		}
		if(recorrido[k]<best){
			best=recorrido[k];
			//printf("\n El mejor = %.lf la hormina %i iteracion %i", best,k,m);
		}
	}
	dummyMethod2();
	//----------------- Actualizacion de las feromonas
	dummyMethod1();
	#pragma omp parallel for private(i) shared(fero)
	for(k=0;k<ants;k++){
		for(i=0;i<cities;i++){
			fero[ant[k][i]][ant[k][i+1]]+=Q/recorrido[k];
			fero[ant[k][i+1]][ant[k][i]]+=Q/recorrido[k];
		}
	}
	dummyMethod2();
	dummyMethod1();
	#pragma omp parallel for private(j) shared(fero)
	for(i=0;i<cities;i++){
		for(j=0;j<cities;j++){
			fero[i][j]=fero[i][j]*(1-rho);
			if(fero[i][j]<0.01){
				fero[i][j]=0.01;
			}
		}
	}
	dummyMethod2();
	}//fin de iteraciones
	printf("\nLa menor distancia fue %.lf\n", best);
	//------------------------------------------
	return 0;
}

double aleatorioEntero(int li, int ls){
	double numero;
	srand(time(NULL));
	numero=li+rand() % ((ls+1)-1);
	return numero;
}

double aleatorio(){
	//srand(time(NULL));
	return (double)rand() / (double)RAND_MAX ;
}

int probabilidad(double visi[], double fero[], int vector[], int cities){
	int i, j, city, condicion, contador;
	double sumVF, aux, probRel, number;
	#pragma omp private(i,j,sumVF,aux,probRel, number, condicion, city, contador)
	sumVF=0;
	contador=0;
	for(j=0;j<cities;j++){
		if(vector[j]!=0){
			sumVF+=visi[j]*fero[j];
		}
		if(fero[j]<=0.000001){
			contador++;
		}
	}
	if(sumVF<=0){printf("\n ERROR EN SUMA \n");}
	number=aleatorio();
	aux=0;
	city=-1;
	condicion=0;
	j=0;
	while(j<cities && condicion==0){
		if(vector[j]!=0){
			probRel=(visi[j]*fero[j])/(sumVF);
			aux+=probRel;
			if(aux!=aux|| aux==INFINITY){
				for(i=0;i<cities;i++){
					printf("\n visibilidad %.6lf || fero %.6lf || suma %.6lf ||vector %i || %i", visi[i],fero[i],sumVF,vector[i],contador);
				}

				exit(-1);
			}
			if(number<=aux+0.0001){
				city=j;
				condicion=1;
			}
		}
		//printf("\n %.5lf - %.5lf iter=%i suma %.5lf visi %.5lf fero %.5lf vector %i",aux, number,j, sumVF, visi[j],fero[j],vector[j]);
		j++;
	}
	if(city==-1){
		printf("NO asigno");
		printf("\n %.8lf - %.8lf iter=%i",aux, number,j-1);
		exit(-1);
	}
	return city;
}

void gettingMatrix(){
	int i, j;
	FILE *inputFile;
	inputFile= fopen("matrix.txt", "r");
	char help[300], *token;
	i=0;
	while(!feof(inputFile)){
		fscanf(inputFile, "%s", help);
		token=strtok(help,",");
		j=0;
		while(token != NULL){
			dist[i][j]=atof(token);
			token=strtok(NULL, ",");
			j++;
		}
		i++;
	}
}

void printMatrix(){
	int i, j;
	for(i=0; i<48;i++){
		for(j=0;j<48;j++){
			printf("%.lf ",dist[i][j]);
		}
		printf("\n");
	}
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