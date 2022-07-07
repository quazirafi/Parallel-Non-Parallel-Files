#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 32
#define MAX_STRING 100000

double start_time, end_time, exec_time;
FILE *file_pointer,*result;
int file_length, number_of_section;
char *string;
int *P;

// STRUTTURA UTILIZZATA DAL THREAD PER IL RICONOSCIMENTO DEL PERIODO
typedef struct stage_s {
    int id;
  	int sequence;
  	char *str;
  	char *txt;
  	char *txt2;
  	int *qi;
  	int *pi;

} stage_t;

int strpos(char *, char *);
int gcd(int, int);

int main(int argc, char **argv){
	/* Open filestreams */
	file_pointer = fopen("string.txt","rb");	/*Open read filestream*/
	if (file_pointer==NULL) {fputs ("Read file error",stderr); exit (1);}
	result = fopen("result.txt","w");	/*Open write filestream*/
	if (result==NULL) {fputs ("Write file error",stderr); exit (1);}

	/* Obtain file size */
	fseek(file_pointer, 0, SEEK_END);
	file_length = ftell(file_pointer);
	rewind (file_pointer);
	//STAMPA LA LUNGHEZZA DEL FILE IN INPUT
	//printf("\n########## Length of string: %d\n\n", file_length);

	/* Allocate memory to contain whole file */
	string = (char *) malloc(file_length);
	if (string == NULL) {fputs ("Memory allocation error",stderr); exit (2);}

	/* Copy the file content into string pointer */
	int length = fread(string, sizeof(char),file_length, file_pointer);
	//printf("%d\n", length );
	if (length != file_length) {fputs ("Reading string error",stderr); exit (3);}

	/* The whole file is now loaded in the memory buffer. */
	// STAMPA DEL TESTO
	//printf("\nS [%s]\n\n", string);

	/* 	In this section we describe a single stage n , 0<=n<m that compute 	
		P[n-l(n)+1 .. n-l(n+1)].
	*/
	/* Let's compute the number of stages necessary */
	/* Create the stages pointer */
	stage_t stages[NUM_THREADS];
	int cont=0, sequence = file_length-1;
	while (sequence > 0){
		stages[cont].id = cont;
		stages[cont].sequence = sequence;

		// STAMPA LA LUNGHEZZA DELLA SEQUENZA CHE IL THREAD STA ANDANDO A VERIFICARE
		//printf("id %d sequence %d\n", stages[cont].id, sequence);

		cont++;
		sequence = (int) floor(2.0/3.0*sequence);
	}

	/*	Now we know how many section we have (-1 dovuto all'incremento finale) */
	number_of_section = cont-1;
	//STAMPA IL NUMERO DI SEZIONI SU CUI LAVORARE IN PARALLELO
	//printf("\n########## Number of section is %d\n\n", number_of_section+1);

	int n_threads;

	/* Allocate memory to contain whole result array
		P is the SHARED array containing result
	*/
	P = (int *) malloc((file_length-1) * sizeof (int));
	if (P == NULL) {fputs ("Memory allocation error",stderr); exit (2);}
	//inizialize all to 0
	dummyMethod3();
	for(int i=0; i<file_length-1; i++){
		P[i]=0;
	}
	dummyMethod4();


	/* START TIME */
	start_time = omp_get_wtime();

	//I have to set the number of thread and the parallel section
	
	// ... con paralle
	omp_set_num_threads( atoi(argv[1]) );
	dummyMethod1();
	#pragma omp parallel for
	for (int i=0; i<number_of_section; i++)
	{
		int id, nthrds;
		//I use two auxiliary variable: id to identify the thread and nthrds the total number
		id = omp_get_thread_num();
		//printf("Thread %d ready\n", id);			//********* OK
		nthrds = omp_get_num_threads();
		if (id==0){
			n_threads = nthrds;
		}
		//printf("Thread %d start\n", id);			//********* OK


		/* 	We start to call a string matching algorithm to find all occurences of
			S[0 .. l(n+1)] in S[n-l(n)+1 .. n].
			Let qi, where i = 1 .. r, denote the indices of all these occurences.
			(all indices are in teh string S[0 .. n], thus n-l(n)<qi<n-l(n+1)).
		*/	


		/* 	Creazione della stringa S[0 .. l(n+1)] */
		// stages[id+1].sequence+1 è il numero di caratteri della prima stringa da cercare
		stages[id].str = (char *) malloc(stages[id+1].sequence+1);
		if (stages[id].str == NULL) {fputs ("Memory allocation error",stderr); exit (2);}
		strncpy(stages[id].str,string,stages[id+1].sequence+1);
		//printf("String to find for thread %d:\n%s\n",id, stages[id].str);
		//sleep(1);									//********* OK

		/* 	Creazione della stringa S[n-l(n)+1 .. n] */
		// file_length - ( file_length-1 - stages[id].sequence+1) è il numero di caratteri del testo da controllare
		stages[id].txt = (char *) malloc(file_length - ( file_length-1 - stages[id].sequence + 1));
		if (stages[id].txt == NULL) {fputs ("Memory allocation error",stderr); exit (2);}
		//l'offset iniziale è da dove parte la stringa ovvero n-l(n)+1
		int offset = (file_length-1) - stages[id].sequence + 1;
		//printf("Thread %d:\n%s\n\n",id, string+offset); //********* OK
		//sleep(10);//********* OK
		strncpy(stages[id].txt,string+offset,file_length - ( file_length-1 - stages[id].sequence + 1));
		//printf("String txt of thread %d:\n%s\n\n",id, stages[id].txt); //********* OK
		//sleep(10);//********* OK

		//STAMPA QUELLO CHE IL TREAD CERCA NELLA PARTE DI TESTO CHE STA ANALIZZANDO
		//printf("\n########## Thread %d search\n\n%s\n\nin\n\n%s\n\n",id, stages[id].str, stages[id].txt);

		/*	Creazione del vettore q1 necessario per indicare tutte le occorrenze
			di S[0 .. l(n+1)] in S[n-l(n)+1 .. n] e successiva inizializzazione 
			a 0 di tutti gli elementi dell'array
		*/
		/* 	TODO:						IMPLEMENTAZIONE FUTURA
			Non allocare qi se non ci sono occorrenze nel vettore e togliere il flag occurrences
		*/
		stages[id].qi = (int *) malloc((file_length) * sizeof (int));
		if (stages[id].qi == NULL) {fputs ("Memory allocation error",stderr); exit (2);}
		for(int i=0;i<file_length;i++){
			stages[id].qi[i]=0;
		}

		/* 	Find all occurrences of S[0 .. l(n+1)] in S[n-l(n)+1 .. n] and set qi vector*/
		int pos, cont=0;
		while (pos != -1) {
			pos = strpos (stages[id].txt+cont, stages[id].str);
		  	if (pos != -1) {
		  		//printf("Thread %d ha trovato occorrenza in P[%d]\n",id,pos+cont-1+offset);
		    	stages[id].qi[pos+cont+offset]=1;
		    	//printf("Thread %d ha trovato occorrenza in P[%d]\n",id,pos+cont-1+offset);
		    	cont++;
		  	}
		}

		// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ OK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

		int r=0, last_valid_recurrence;
		//r è il numero di periodi trovati nel primo string matching
		for (int i = 0; i < file_length; i++){
			if (stages[id].qi[i]==1){
				last_valid_recurrence=i;
				r++;
			}
		}

		/*
			TODO: "If there where no occurences String S has no period in the range computed
						and all entries of P[n-l(n)+1 .. n-l(n+1)] are set to false."
		*/

		/*	"If there was only one occurences of S[0 .. l(n+1)] in S[n-l(n)+1 .. n],
						it can be verified to be a period of O(ln) operation."
		*/
		if(r==1){
			//Remember that P[...] start from 1 so its position must be -1
			P[last_valid_recurrence-1]=1;
			//printf("\n!!! A period CERTIFIED is found\nfrom thread %d at the position %d\nsince it is singular in qi !!!\n", id, last_valid_recurrence);
			//STAMPARE L'ULTIMA OCCORRENZA VALIDA NEL THREAD ANALIZZATO
			//printf("Last valid recurrences of thread %d is in pos %d\n",id, last_valid_recurrence);
		}

		/*
			"Otherwise, we continue with another call to a string matching algoritm
						to find all occurences of S[0 .. l(n+1)] in S[0 .. l(n)-1].
						Let pi, i=1..k, denote the indices of all there occurences (p1=0)."
		*/

		/* 	La stringa S[0 .. l(n+1)] la abbiamo già creata : stages[id].str */

		/* 	Creazione della stringa S[0 .. l(n)-1] */
		// (stages[id].sequence - 1) + 1 numero di caratteri nell testo in cui cercare				
		stages[id].txt2 = (char *) malloc((stages[id].sequence - 1) + 1);
		if (stages[id].txt2 == NULL) {fputs ("Memory allocation error",stderr); exit (2);}
		strncpy(stages[id].txt2,string,(stages[id].sequence - 1) + 1);

		// SECONDA TIPOLOGIA DI STRING MATCHING
		//printf("Thread %d search2\n%s\nin\n%s\n\n",id, stages[id].str, stages[id].txt2);

		/*	Creazione del vettore pi necessario per indicare tutte le occorrenze
			di S[0 .. l(n+1)] in S[0 .. l(n)-1] e successiva inizializzazione 
			a 0 di tutti gli elementi dell'array
		*/
		/* 	TODO:						IMPLEMENTAZIONE FUTURA
			Non allocare pi se non ci sono occorrenze nel vettore qi e togliere il flag occurrences
		*/

		stages[id].pi = (int *) malloc((file_length) * sizeof (int));
		if (stages[id].pi == NULL) {fputs ("Memory allocation error",stderr); exit (2);}
		for(int i=0;i<file_length;i++){
			stages[id].pi[i]=0;
		}

		/* 	Find all occurrences of S[0 .. l(n+1)] in S[0 .. l(n)-1] and set pi vector
			Note that cont=1 since p0=0
			*/

		int pos2=0, cont2=1;
		while (pos2 != -1) {
			pos2 = strpos (stages[id].txt2+cont2, stages[id].str);
		  	if (pos2 != -1) {
		  		//printf("\n\n! ! ! ! ! Thread %d ha trovato occorrenza in P[%d]\n\n",id,pos2+cont2);
		    	stages[id].pi[pos2+cont2]=1;
		    	cont2++;
		  	}
		}

		for (int i = 0; i < file_length; i++){
			if (stages[id].pi[i]==1){
				P[i-1]=1;
				//printf("\n!!! A period TO BE CERTIFIED is found\nfrom thread %d at the position %d\nsince using Lemma 3.4 (k>=r) !!!\n", id, i);
			}
		}

		/*	"If recurrences r are greater than 1 I need to verify two lemma:
				Lemma 3.1) 	If a string of lenght m has two periods of length p and q and p+q<=m,
							then it has also a period of length gcd(p,q). This structure enable us 
							to proceed efficently to test which of the qi's is actually a period of s.
		*/

		/*
				Lemma 3.2)	If a string A[1 .. l] has period p and occurs only at positions 
							p1<p2<..<pk of a string B[1 .. ceil(3/2*l)], then the pi's form
							an aritmetic progression with difference p."
		*/

		/*	"Lemma 3.3
					The sequence {pi} and {qi} form an arithmetic progression with difference P,
					where P is the period S[0 .. l(n)+1]"
		*/

		/*	"Lemma 3.4
					If k (n° of pi recurrences) k<r than qi is not a period of S[0 .. n]
					for 1<=i<=r-k "

					...
					se k>=r allora i qi sono periodi
					se k<r le qi tra 1 e r-k non sono periodi, gli altri si
		*/
		
		if(r>=2){
			int k=0;
			//k è il numero di periodi trovati nel secondo string matching
			for (int i = 0; i < file_length; i++){
				if (stages[id].pi[i]==1 || stages[id].qi[i]==1 ){
					P[i-1]=1;
					//printf("\n!!! A period TO BE CERTIFIED is found\nfrom thread %d at the position %d\nsince using Lemma 3.4 !!!\n", id, i);
					k++;
				}
			}
		}
		/*if(k<r){
			int cont_k = 0;
			for (int i = 0; i < file_length; i++){
				if (stages[id].qi[i]==1){
					if(cont_k<r-k){
						//Remember that P[...] start from 1 so its position must be -1
						P[i-1]=0;
						printf("\n!!! A MISMATCHING period is found\nfrom thread %d at the position %d\nsince using Lemma 3.4 (k<r)!!!\n", id, i);
			
					}
					cont_k++;
				}
			}
		}*/	

		stages[id].str = NULL;
		stages[id].txt = NULL;
	}
	dummyMethod2();

	dummyMethod3();
	for(int i=0; i<number_of_section+1; i++){
		/*
		// USARE PER VEDERE I PERIODI E I FALSI PERIODI
		printf("\nqi[");
		for(int j=0; j<file_length; j++){
			printf("%d", stages[i].qi[j]);
		}
		printf("] of thread %d\n\n",i);
		printf("\npi[");
		for(int j=0; j<file_length; j++){
			printf("%d", stages[i].pi[j]);
		}
		printf("] of thread %d\n\n",i);
		*/
		stages[i].qi = NULL;
		stages[i].pi = NULL;
	}
	dummyMethod4();

	/* STOP TIME */
	end_time = omp_get_wtime();
	exec_time = end_time - start_time;

	/*
	printf("\n\nP [ ");
	for(int i=0; i<file_length-1; i++){
		printf("%d", P[i]);
	}
	printf("]\n\n");
	*/
	
	fprintf(result, "P [ ");
	dummyMethod3();
	for(int i=0; i<file_length-1; i++){
		fprintf(result, "%d", P[i]);
	}
	dummyMethod4();
	fprintf(result, "]");

	/* free all pointer */
	free(string);
	string=NULL;
	free(P);
	P=NULL;

	/* Close filestream */
	fclose(file_pointer);	/*Close read filestream*/
	fclose(result); /*Close write filestream*/

	printf("Execution terminated in %g seconds\n", exec_time);
	return 0;
}

int strpos(char *str, char *search){
    //dichiarazioni
    int i,j,n,l;
     
    //inizializzazioni
    l = strlen(search);
    n = strlen(str)-l+1;
     
    //calcoli
							dummyMethod3();
    for(i=0;i<n;i++){
        for(j=0;j<l&&search[j]==str[i+j];j++);
        if(j==l)
                return i;
    }
							dummyMethod4();
    return -1;               
}

//Compute the Greatest Common Divisor
int gcd(int n1, int n2){
	int ris;
	dummyMethod3();
	for (int i=0; i<=n1 && i<=n2; i++){
		//Check if is factor of both integers
		if(n1%i==0 && n2%i==0){
			ris=i;
		}
	}
	dummyMethod4();
	return ris;
}

//00010001000100000000000000000000000000000000100000000000100010001000
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