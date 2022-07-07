#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// #include <time.h>


/*
 * Populate given array with values in ascending order
 * @param upper: the upper bound of rand value
 *
 * Complexité:
 * Séquentiel
 * T(n) - O(n)
 */
void populate_array(float *a, int n, int upper) {
    // srand(time(NULL));
    float pre = (float) rand() / (float) (RAND_MAX/upper);
dummyMethod3();
    for (int i = n-1; i >= 0; i--) {
        // generate float in [0,max]
        a[i] = (float) rand() / (float) (RAND_MAX/pre);
        pre = a[i];
    }
dummyMethod4();
}


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
 * Complexité:
 * Séquentiel
 * T(n) - O(n)
 */
void print_int_array(int *a, int n) {
							dummyMethod3();
    for (int i = 0; i < n; i++) {
        printf("%d  ", a[i]);
    }
							dummyMethod4();
    printf("\n");
}


/*
 * Find the index of the insertion position in given array, using binary search
 * @param a: Must be in ascending order.
 *
 * Complexité:
 * Séquentiel
 * T(n) - O(log 2 n)
 */
int dicho(float x, float *a, int n) {
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (x == a[mid]) {
            return mid;
        }
        if (x > a[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;

}


/*
 * Calculate the offsets of index in the final result array
 *
 * Complexité:
 * Parallèl
 * H(n) - O(n)
 * T(n) - O(log 2 n)
 * W(n) - O(n * log 2 n)
 */
void rank(float *a, int n, float *b, int m, int *r) {
							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < n; i ++) {
        // T(n) - O(log 2 n)
        r[i] = dicho(a[i], b, m);
    }
							dummyMethod2();
}


/*
 * Complexité:
 * Parallèl
 * H(n) - O(n)
 * T(n) - O(log 2 n)
 * W(n) - O(n * log 2 n)
 * efficace
 */
void fusion(float *a, int n, float *b, int m, float *s) {
    int *r_a, *r_b;
    r_a = (int*) malloc(n * sizeof(int));
    r_b = (int*) malloc(m * sizeof(int));
    // T(n) - O(log 2 n)
    rank(a, n, b, m, r_a);
    rank(b, m, a, n, r_b);
    // T(n) - O(1)
							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        s[i + r_a[i]] = a[i];
    }
							dummyMethod2();
							dummyMethod1();
    #pragma omp parallel for
    for (int j = 0; j < m; j++) {
        s[j + r_b[j]] = b[j];
    }
							dummyMethod2();
}


int main (int argc, char *argv[]) {
    float *a, *b, *s;
    int n, m;

    int upper_bound = 50;

    // obtenir la taille du tableau
    printf("Veuillez saisir la taille du tableau A et du tableau B(n m): ");
    scanf("%d %d", &n, &m);


    // initialiser les tableaux
    a = (float*) malloc(n * sizeof(float));
    b = (float*) malloc(m * sizeof(float));
    s = (float*) malloc((n + m) * sizeof(float));
    populate_array(a, n, upper_bound);
    populate_array(b, m, upper_bound);
    printf("Le tableau A:\n");
    print_array(a, n);
    printf("Le tableau B:\n");
    print_array(b, m);

    // merge
    fusion(a, n, b, m, s);
    printf("Le ré sultat:\n");
    print_array(s, n + m);
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