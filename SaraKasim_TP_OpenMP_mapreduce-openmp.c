#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <stdlib.h>

#include <sys/time.h>

#include <math.h>

#include <string.h>

#include "omp.h"

#include <time.h>

int NB_WORDS = 10;
int STRING_MAX_SIZE = 20;

/* A function to generate random strings */
void gen_random(char * s, int len) {
  static
  const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
dummyMethod3();
  for (int i = 0; i < len; ++i) {
    s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
  }
dummyMethod4();
  s[len] = 0;
}

/* A function to print arrays of strings */
void printArrayStrings(char ** array) {

dummyMethod3();
  for (int i = 0; i < NB_WORDS; i++) {
    printf("%s\n", array[i]);
  }
dummyMethod4();
}

/* A function to print the counts */
void printArrayInt(int * count) {

			dummyMethod3();
  for (int i = 0; i < 26; i++) {
    printf("%d ", count[i]);
  }
			dummyMethod4();
}

/* A function that maps a String to a count of characters */
void map1(char * c, int * count) {

			dummyMethod3();
  for (int i = 0; i < 26; i++) {
    count[i] = 0;
  }
			dummyMethod4();

			dummyMethod3();
  for (int i = 0; i < strlen(c); i++) {
    count[(int) c[i] - 97]++;
  }
			dummyMethod4();
}

int main() {

  // init
  char * array[NB_WORDS];
  srand(time(NULL));
			dummyMethod3();
  for (int i = 0; i < NB_WORDS; i++) {
    int strSize = 1 + rand() % STRING_MAX_SIZE;
    array[i] = (char * ) malloc(strSize * sizeof(char));
    gen_random(array[i], strSize);
  }
			dummyMethod4();

  printArrayStrings(array);

  // map (on a single word)
  int * count = (int * ) malloc(26 * sizeof(int));
  map1(array[0], count);
  //printArrayInt(count);

  // map (parallel)

  int ** countMult = (int ** ) malloc(NB_WORDS * sizeof(int * ));
			dummyMethod3();
  for (int i = 0; i < NB_WORDS; i++) {
    countMult[i] = (int * ) malloc(26 * sizeof(int));
  }
			dummyMethod4();

  int resReduce1[26] = {
    0
  };
  int resReduce2 = 0;

  #pragma omp parallel for shared(countMult, resReduce1, resReduce2)
  for (int i = 0; i < NB_WORDS; i++) {
    #pragma omp parallel for
    for (int j = 0; j < strlen(array[i]); j++) {
      #pragma omp critical 
      {
        map1(array[i], countMult[i]);

      }
    }
    #pragma omp parallel for
    for (int x = 0; x < 26; x++) {
      resReduce1[x] = resReduce1[x] + countMult[i][x];
    }
  }

  #pragma omp parallel 
 {
    #pragma omp for

    for (int i = 0; i < 26; i++) {
      resReduce2 += resReduce1[i];

    }
  }

  for (int i = 0; i < NB_WORDS; i++) {
    printf("\n");
    printArrayInt(countMult[i]);
  }

  printf("\nTotal number of occurences of each letter ");
  for (int i = 0; i < 26; i++) {

    printf("%d ", resReduce1[i]);
  }

  printf("\nTotal number of characters in the text %d \n", resReduce2);

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