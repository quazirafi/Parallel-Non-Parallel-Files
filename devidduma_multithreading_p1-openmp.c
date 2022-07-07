#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int size, p;

int main() {
	// enter digit size of sum
	printf("Enter size of sum: ");
	scanf("%d", &size);

	// enter size of p
	printf("Enter p number of threads: ");
	scanf("%d", &p);

    // total sum
    double total_sum = 0;

dummyMethod1();
    #pragma omp parallel for num_threads(4) schedule(dynamic)
	for(int n = 0; n < size; n++) {
        // An
        double An = 0;

        #pragma omp parallel for num_threads(p/4) schedule(guided)
        for(int k = 0; k < n; k++) {
            double term = cos((double)(pow((double)(k), 3.0) - 1.0) / (double)(n));
            term = term < 0 ? term*(-1.0) : term;

            An += term;
        }

        total_sum += An;
    }

    printf("Total sum: %f", total_sum);
}
dummyMethod2();
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