/*
 * author: alessandro bitocchi
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef _OPENMP
#	include <omp.h>
#endif
#include "../lib/include/reader.h"



int  KMPSearch(char *P, char *S);
void computeLPSArray(char* pat, int M, int* lps);


int main(int argc, char** argv){

	struct timespec begin, end;
	int thread_count = 2;

	printf("KMP | ");

	if (argv[1] == NULL || argv[2] == NULL){
		perror("ERROR: Input command\n");
		return 1;
	}

	if (argv[3] != NULL)
		thread_count = atoi(argv[3]);

	stringList* strings = read_from_file(argv[1]);
	stringList* packets = read_from_file(argv[2]);

	//printf("WORDS: %d\n", strings->len);
	//printf("NUM_PACK: %d\n", packets->len);

	//for (int i = 0; i < strings->len; i++){
	//	printf("key: %s\n", strings->array[i]);
	//}

	int counter = 0;
	double total_time = 0.0;

	clock_gettime(CLOCK_REALTIME, &begin);
	dummyMethod1();
	#pragma omp parallel for collapse(2) num_threads(thread_count) \
		reduction(+: counter)
	for (int i = 0; i < strings->len; i++){
		for (int j = 0; j < packets->len; j++){
			//int my_counter = 0; /* private */
			counter += KMPSearch(strings->array[i], packets->array[j]);
			//#pragma omp critical
			//counter += my_counter;
		}
	}
	dummyMethod2();

	clock_gettime(CLOCK_REALTIME, &end);


	unsigned int total_match = 0;

	printf("total match: %d | ", counter);

    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;

	printf("Elapsed time: %f seconds\n", elapsed);

	freeStringList(strings);
	freeStringList(packets);
    return 0;
}



void computeLPSArray(char* pat, int M, int* lps){
    int len = 0;

    lps[0] = 0;

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(char* pat, char* txt){
    int M = strlen(pat), N = strlen(txt);
    int lps[M];

    computeLPSArray(pat, M, lps);

    int i = 0, j = 0, counter = 0; // index for txt[], pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            //printf("Found pattern: %s at index %d\n", pat, i - j);
            counter++;
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return counter;
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