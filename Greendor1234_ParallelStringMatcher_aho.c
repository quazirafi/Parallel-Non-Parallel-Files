/*
 * author: alessandro bitocchi
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef _OPENMP
#	include <omp.h>
#endif

#include "../lib/include/ahocorasick.h"
#include "../lib/include/reader.h"


void callback_match_total(void *arg, struct aho_match_t* m){
    long long int* match_total = (long long int*)arg;
    (*match_total)++;
}


int main(int argc, char** argv){
    struct ahocorasick aho;
    long long int match_total = 0;
    unsigned int total_match = 0;

    struct timespec begin, end;
    int thread_count = 2;

    aho_init(&aho);

    printf("AHO | ");

	if (argv[1] == NULL || argv[2] == NULL){
		perror("ERROR: Input command\n");
		return 1;
	}

	if (argv[3] != NULL)
		thread_count = atoi(argv[3]);


	stringList* strings = read_from_file(argv[1]);
	stringList* packets = read_from_file(argv[2]);

	//int id[strings->len] = {0};

	//#pragma omp parallel for num_threads(thread_count)
	dummyMethod3();
	for (int i = 0; i < strings->len; i++)
		aho_add_match_text(&aho, strings->array[i],
				strlen(strings->array[i]));
	dummyMethod4();

    aho_create_trie(&aho);
    aho_register_match_callback(&aho, callback_match_total, &match_total);

    clock_gettime(CLOCK_REALTIME, &begin);
							dummyMethod1();
	#pragma omp parallel for num_threads(thread_count) \
		reduction(+: total_match)
    for (int i = 0; i < packets->len; i++)
    	total_match += aho_findtext(&aho, packets->array[i], strlen(packets->array[i]));
							dummyMethod2();
    clock_gettime(CLOCK_REALTIME, &end);


    //printf("total match:%u\n", aho_findtext(&aho, "PROVAstringaSCRIVENDOqUDPualcUDosaPDUPDkicaom",
    //			strlen("PROVAstringaSCRIVENDOqUDPualcUDosaPDUPDkicaom")));

    aho_destroy(&aho);


    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;

    printf("total match: %d | ", total_match);
	printf("Elapsed time: %f seconds\n", elapsed);

	freeStringList(strings);
	freeStringList(packets);

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