/*
*********************************************
*  314 Principles of Programming Languages  *
*  Fall 2014                              *
*********************************************
*/

#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <time.h>
#include "word_list.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[])
{
	HashFunction hf[] = { RSHash, JSHash, ELFHash, BKDRHash, SDBMHash,
		DJBHash, DEKHash, BPHash, FNVHash, APHash,
		hash_div_701, hash_div_899, hash_mult_700, hash_mult_900
	};
	word_list *wl;
	char *word;
	char *bv;
	double start, end, diff;
	size_t wl_size;
	size_t bv_size;
	size_t num_hf;
	size_t i, j;
	unsigned int hash;
	int misspelled;
	// Set Number of threads to 4
	omp_set_num_threads(4); 
	//
	if (argc != 2) {
		printf("Please give word to spell check\n");
		exit(EXIT_FAILURE);
	}
	word = argv[1];

	/* load the word list */
	wl = create_word_list("word_list.txt");
	if (!wl) {
		fprintf(stderr, "Could not read word list\n");
		exit(EXIT_FAILURE);
	}
	wl_size = get_num_words(wl);
	
	start = omp_get_wtime();
	/* create the bit vector */
	bv_size = 100000000;
	num_hf = sizeof(hf) / sizeof(HashFunction);
	bv = calloc(bv_size, sizeof(char));
	if (!bv) {
		destroy_word_list(wl);
		exit(EXIT_FAILURE);
	}
	
	dummyMethod1();
	#pragma omp parallel for private(j, hash) schedule(guided)
	for (i = 0; i < wl_size; i++) {
		for (j = 0; j < num_hf; j++) {
			hash = hf[j] (get_word(wl, i));
			hash %= bv_size;
			bv[hash] = 1;
		}
	}
	dummyMethod2();

	/* do the spell checking */
	misspelled = 0;
	dummyMethod3();
	for (j = 0; j < num_hf; j++) {
		hash = hf[j] (word);
		hash %= bv_size;
		if (bv[hash] == 0)
			misspelled = 1;
	}
	dummyMethod4();
	end = omp_get_wtime();
	diff = end - start;
	printf("Spell check time: %f\n", diff);

	/* tell the user the result */
	if (misspelled)
		printf("Word %s is misspelled\n", word);
	else
		printf("Word %s is spelled correctly\n", word);

	free(bv);
	destroy_word_list(wl);
	return EXIT_SUCCESS;
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