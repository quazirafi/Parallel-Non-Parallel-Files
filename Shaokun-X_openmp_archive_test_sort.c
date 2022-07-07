#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


/*
 * Complexité:
 * Séquentiel
 * T(n) - O(n)
 */
void print_array(float *a, int n) {
dummyMethod3();
    for (int i = 0; i < n; i++) {
        printf("%10f ", a[i]);
    }
dummyMethod4();
    printf("\n");
}


/*
 * Si une paire adjacente n'est pas trié e, changez le flag, si le flag est 0, alors le tableau est trié
 *
 * Complexité:
 * Parallèl
 * H(n) - O(n)
 * T(n) - O(1)
 * W(n) - O(n)
 * efficace
 */
char* test_trie(float *a, int n) {
    int not_ascending = 0,
        not_descending = 0,
        is_sorted;
    if (n == 1) {
        return "all same value";
    }
    
    // T(n) - O(1)
							dummyMethod1();
    #pragma omp parallel for shared(not_descending, not_ascending)
    for (int i = 0; i < n-1; i++)  {
        if (a[i] < a[i+1]) {
            not_descending = 1;
        }
        if (a[i] > a[i+1]) {
            not_ascending = 1;
        }
    }
							dummyMethod2();
    if (not_descending == 1 && not_ascending == 1) {
        return "not sorted";
    } else if (not_descending == 1 && not_ascending == 0) {
        return "ascending order";
    } else if (not_descending == 0 && not_ascending == 1) {
        return "descending order";
    } else {
        return "all same value";
    }
}


int main (int argc, char *argv[]) {
    float a[10] = {1,2,3,4,5,6,7,8,9,10};
    float b[10] = {3,7,23,6,9,3,7,0,4,3};
    float c[10] = {10,9,8,7,6,5,4,3,2,2};
    float d[5] = {1,1,1,1,1};
    printf("Array a is:\n");
    print_array(a, 10);
    printf("Test result: %s\n\n", test_trie(a, 10));
    printf("Array a is:\n");
    print_array(b, 10);
    printf("Test result: %s\n\n", test_trie(b, 10));
    printf("Array a is:\n");
    print_array(c, 10);
    printf("Test result: %s\n\n", test_trie(c, 10));
    printf("Array a is:\n");
    print_array(d, 5);
    printf("Test result: %s\n\n", test_trie(d, 5));

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