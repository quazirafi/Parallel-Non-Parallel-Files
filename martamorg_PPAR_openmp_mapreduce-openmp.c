#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int NB_WORDS = 10;
int STRING_MAX_SIZE = 20;

/* A function to generate random strings */
void gen_random(char *s, int len) {
    static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
dummyMethod3();
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
dummyMethod4();
    s[len] = 0;
}

/* A function to print arrays of strings */
void printArrayStrings(char **array){

dummyMethod3();
    for(int i = 0; i < NB_WORDS; i++){
        printf("%s\n", array[i]);
    }
dummyMethod4();
}

/* A function to print the counts */
void printArrayInt(int *count){

							dummyMethod3();
    for(int i = 0; i < 26; i++){
        printf("%d ", count[i]);
    }
							dummyMethod4();
}

/* A function that maps a String to a count of characters */
void map1 (char* c, int *count){

    static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";

							dummyMethod3();
    for(int i= 0; i < 26; i++){
        count[i] = 0;
    }
							dummyMethod4();
    // to be completed
							dummyMethod3();
    for (int i=0; i < sizeof(c); i++){
        for (int j=0; j < 26; j++){

            if (c[i] == alphanum[j]){
                count[j]++;
            }
        }
    }
							dummyMethod4();

}

void map1par (char **array, int *count){

    static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";

							dummyMethod3();
    for(int i= 0; i < 26; i++){
        count[i] = 0;
    }
							dummyMethod4();

    // to be completed

							dummyMethod1();
    #pragma omp parallel for
    for(int k=0; k < NB_WORDS; k++){
        char* c = array[k];

        for (int i=0; i < sizeof(c); i++){
            for (int j=0; j < 26; j++){

                if (c[i] == alphanum[j]){
                    count[j]++;
                }
            }
        }
    }
							dummyMethod2();

    //call red1 with array with NB_WORDS diff counts (?)
    

}

int red1 (int *wordsCounts, int *count){
    /*
    for(int i=0; i < NB_WORDS; i++){
        count += wordsCounts;
    }
    return count;
    */

    return 0;
}

int red2 (int *count){

    int sum = 0;

							dummyMethod1();
    #pragma omp parallel for shared(count) reduction(+: sum)
    for (int i = 0; i < 26; i++)
    {
        sum += count[i];
    }
							dummyMethod2();
    return(sum);

}

int main()
{
    omp_set_num_threads(4);

    // init
    char *array[NB_WORDS];
    srand(time(NULL));
							dummyMethod3();
    for(int i = 0; i < NB_WORDS; i++){
        int strSize = 1 + rand() % STRING_MAX_SIZE;
        array[i] = (char *)malloc(strSize * sizeof(char));
        gen_random(array[i], strSize);
    }
							dummyMethod4();



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