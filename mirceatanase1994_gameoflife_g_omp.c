#include "stdlib.h"
#include "stdio.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char* argv[]){
	int xvecini[8] = {1,0,-1,-1,-1,0,1,1};
	int yvecini[8] = {1,1,1,0,-1,-1,-1,0};
	int lin,col,i,j,nrIt,k,alive,l;
	char aux;
	FILE* read = fopen(argv[1],"r");
	FILE* write = fopen(argv[3],"w");
	fscanf(read, "%d", &lin);
	fscanf(read, "%d", &col);	
	char **a = malloc ((lin + 2)*sizeof(char *));
	char **temp = malloc ((lin + 2)*sizeof(char *));
	nrIt = atoi(argv[2]);
	//alocare
dummyMethod1();
	#pragma omp parallel for
	for (i=0; i<lin+2; i++){
		a[i]= malloc ((col + 2)*sizeof(char));
		temp[i]= malloc ((col + 2)*sizeof(char));
	}
dummyMethod2();
	
	//citire
	fscanf(read, "%c", &aux);

dummyMethod3();
	for (i=1; i<=lin; i++){
		for (j=1; j<=col; j++){
			fscanf(read, "%c ", &aux);
			a[i][j] = ((aux == 'X')? 1 : 0);
		}
	}
dummyMethod4();
	
	for (i = 0; i<nrIt; i++){
		//(re)bordare matrice	
			dummyMethod1();
		#pragma omp parallel for 		
		for (j = 1; j<=lin; j++){
			a[j][0] = a[j][col];
			a[j][col+1] = a[j][1];
		}
			dummyMethod2();
			dummyMethod1();
		#pragma omp parallel for 
		for (j=1; j<=col; j++){
			a[0][j] = a[lin][j];
			a[lin+1][j] = a[1][j];
		}
			dummyMethod2();
		//colturi
		a[0][0] = a[lin][col];
		a[lin+1][col+1] = a[1][1];
		a[0][col+1] = a[lin][1];
		a[lin+1][0] = a[1][col];

			
		//calculare matrice noua
			dummyMethod1();
		#pragma omp parallel for collapse(2) private(alive, l) 
		for (j = 1; j<=lin; j++){
			for (k=1; k<=col; k++){
				alive = 0;
				for (l = 0; l<8; l++){
					alive +=a[j + yvecini[l]][k+xvecini[l]];
				}
				temp[j][k] = ( ((alive == 2)&&(a[j][k] == 1)) || (alive == 3));
			}
		}
			dummyMethod2();
		//copiere
			dummyMethod1();
		#pragma omp parallel for collapse(2) 	
		for (j = 1; j<=lin; j++){
			for (k = 1; k<=col; k++){
				a[j][k] = temp[j][k];
			}
		}
			dummyMethod2();
	}

	//afisare
	for (i = 1; i<=lin; i++){
		for (j = 1; j<=col; j++){
			fprintf(write, "%s", ((a[i][j]) ? "X ":". "));	
		}
		fprintf(write, "\n");
	}
	fclose(read);
	fclose(write);	
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