#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define DICT_WORD_SIZE 25
#define DICT_LENGHT 22740
#define NUM_THREADS 4

typedef char TITLES[DICT_LENGHT][DICT_WORD_SIZE];

//Define un HASH = 40 caractères = 5*DOUBLE de 8 octets
typedef struct {
	double p1;
	double p2;
	double p3;
	double p4;
	double p5;
} HASH;

//Check if two HASH is the same
int same_hash(HASH* one, HASH* two){
	return one->p1==two->p1 &&
	       one->p2==two->p2 &&
	       one->p3==two->p3 &&
	       one->p4==two->p4 &&
	       one->p5==two->p5;
}

// Two fonctions which help manage files
// --------
FILE* openFile(char* url){
	FILE * ds = fopen(url, "r");
	if (ds == NULL){
		exit(EXIT_FAILURE);
	}
	return ds;
}

char * line = NULL;
size_t len = 0;
char * readline(FILE * f){
    ssize_t read;
    if ((read = getline(&line, &len, f)) != -1) {
	line[read-1] = '\0';
      return line;
    }
	return NULL;
}
// --------


// The crack executable take the dict file and the hash in parameter
// ./crack dict.txt shadow.txt
int main(int argc, char *argv[]) {
	char* dict_file = argv[1];
	char* sha_file = argv[2];
	char* result = malloc(sizeof(char)*DICT_LENGHT);
	
	//Store each line in an array
	TITLES* title_tab = malloc(sizeof(TITLES));
	HASH* hash_tab = malloc(sizeof(HASH)*22740);
	HASH* shadow_tab = malloc(sizeof(HASH)*DICT_LENGHT);
	
	FILE * ds = openFile(dict_file);
	char *currline = readline(ds);
	int nbLine = 0;
	while (currline!=NULL)
	{
		char *tmp = strtok(currline, "\t");
		strcpy((*title_tab)[nbLine], tmp);
		tmp = strtok(NULL, "\t");
		memcpy(&hash_tab[nbLine], tmp, sizeof(HASH));
		// printf("%s-%s\n", title_tab+(nbLine*DICT_WORD_SIZE), hash_tab+(nbLine*DICT_HASH_SIZE));
		nbLine++;

		currline = readline(ds);
	}
	fclose(ds);

	ds = openFile(sha_file);
	currline = readline(ds);
	nbLine = 0;
	while (currline!=NULL)
	{
		memcpy(&shadow_tab[nbLine], currline, sizeof(HASH));	
		nbLine++;		

		currline = readline(ds);
	}
	
	
	// ----- OpenMP -----
	omp_set_num_threads(NUM_THREADS);
	dummyMethod1();
	#pragma omp parallel for shared(hash_tab, shadow_tab, result)
	for(int i=0; i<DICT_LENGHT; i++){
		// For each line, check if the hash of the dict is the same
		int tmpnbLine = nbLine;

		for(tmpnbLine = nbLine; tmpnbLine>=0; tmpnbLine--)
		{
			if(same_hash(&shadow_tab[i], &hash_tab[tmpnbLine])){
				result[i]=1;
			}
		}
	}
	dummyMethod2();
	// ------------------

	//Print the final result
	dummyMethod3();
	for(int i=0;i<DICT_LENGHT;i++){
		if(result[i]==1) printf("FINDED - %s\n", (*title_tab)[i]);
	}
	dummyMethod4();
	
	fclose(ds);	
    return 0;
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