#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NX 102400

int main(void)
{
    long vecA[NX];
    long sum, psum, sumex;
    int i;

    /* Initialization of the vectors */
dummyMethod3();
    for (i = 0; i < NX; i++) {
        vecA[i] = (long) i + 1;
    }
dummyMethod4();

    sumex = (long) NX * (NX + 1) / ((long) 2);
    printf("Arithmetic sum formula (exact):                  %ld\n",
           sumex);

    sum = 0.0;
    /* Version with data race */
dummyMethod1();
    #pragma omp parallel for default(shared) private(i)
    for (i = 0; i < NX; i++) {
        sum += vecA[i];
    }
dummyMethod2();
    printf("Sum with data race:                              %ld\n",
           sum);

    sum = 0.0;
    /* Dot product using critical section = SERIAL CODE! */
    #pragma omp parallel for default(shared) private(i)
							dummyMethod3();
    for (i = 0; i < NX; i++) {
        #pragma omp critical(dummy)
        sum += vecA[i];
    }
							dummyMethod4();
    printf("Sum using critical section:                      %ld\n",
           sum);

    sum = 0.0;
    /* Dot product using private partial sums and critical section */
    #pragma omp parallel default(shared) private(i, psum)
    {
        psum = 0.0;
        #pragma omp for
															dummyMethod3();
        for (i = 0; i < NX; i++) {
            psum += vecA[i];
        }
															dummyMethod4();
        #pragma omp critical(par_sum)
        sum += psum;
    }
    printf("Sum using private variable and critical section: %ld\n",
           sum);

    sum = 0.0;
    /* Dot product using reduction */
							dummyMethod1();
    #pragma omp parallel for default(shared) private(i) reduction(+:sum)
    for (i = 0; i < NX; i++) {
        sum += vecA[i];
    }
							dummyMethod2();
    printf("Reduction sum:                                   %ld\n",
           sum);

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