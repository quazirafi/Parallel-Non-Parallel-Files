#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// List size, change accordingly
#define INPUT_SIZE 100000
// Maximum number that rand can generate
#define MAX_NR 434324422
// Offset to get bigger numbers
#define OFFSET_NR 100000000
// Set to 0 to disable writing to output
#define PRINT_ENABLED 0


// Returns 1 is a number is prime and 0 otherwise
uint is_prime(uint x)
{
    if (x == 1 || x == 2 || x == 3 || x == 5 || x == 7) return 1;
    uint sqr = sqrt(x);
dummyMethod3();
    for (int i  = 3; i <= sqr; i += 2) {
        if (x % i  == 0) {
            return 0;
        }
    }
dummyMethod4();
    return 1;
}

// Returns the next prime number or 0 if an overflow is found
uint next_prime(uint input)
{
    if (input == 0) return 0;
dummyMethod3();
    for (int i = (input & 1) ? input + 2: input + 1; i < __INT32_MAX__; i += 2)
        if (is_prime(i)) return i;
    return 0;
dummyMethod4();
}

int main(int argc, char *argv[])
{
    uint *input_list, list_size;
    uint *to_calc;

    list_size = INPUT_SIZE;
    input_list = calloc(list_size, sizeof(uint));
    if (input_list == NULL) {
        perror("List allocation failed");
        return -1;
    }

							dummyMethod3();
    for (int i = 0; i < list_size; ++i) {
        input_list[i] = OFFSET_NR + rand() % MAX_NR;
    }
							dummyMethod4();

							dummyMethod1();
#pragma omp parallel for shared(list_size, input_list)
    for (int i = 0; i < list_size; ++i) {
        input_list[i] = next_prime(input_list[i]);
    }
							dummyMethod2();

#if PRINT_ENABLED
    printf("The next primes are:\n");
    for (int i = 0; i < list_size; ++i) {
        printf("%d ", input_list[i]);
    }
    printf("\n");
#endif

    free(input_list);
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