#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <unistd.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();



#define LIMIT 100000000 /* espacio de busqueda */

int main(int argc, char *argv[]){
    unsigned long long int i,j,limit,limitsqrt;
    int *primes;
    int z = 1,debug=0;
    double wtime;

    /* Parse command line arguments */
    char next_option = ' ';
    limit=LIMIT; // default limit 1 billion
    while((next_option = getopt(argc, argv, "dn:")) != -1) {
        switch(next_option) {
            case 'd':
                debug=1;
                break;
            case 'n':
                limit = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-n N]\n", argv[0]);
                fprintf(stderr, "by Default the largest integer is 1 billion\n");
        }
    }
    printf ( "\n" );
    printf ( "Eraosthenes Sieve \n" );
    printf ( "C Serial version\n" );
    limitsqrt=(int)sqrt((double)limit);

    primes = malloc(sizeof(int)*limit);

    wtime = omp_get_wtime();
    // initialize: primes[i]==1 means that the number i is prime
							dummyMethod1();
	#pragma omp parallel for
    for (i=1;i<limit;i++)
        primes[i]=1;
							dummyMethod2();

    // find all non-primes
	dummyMethod1();
	#pragma omp parallel for
	for (i=4;i<limit;i+=2)
		primes[i]=0;
	dummyMethod2();
	dummyMethod1();
	#pragma omp parallel for schedule(dynamic)
	for (i=3;i<limitsqrt;i+=2)
	if (primes[i])
	    for (j=i*i;j<limit;j +=2*i)
		primes[j]=0;
	dummyMethod2();

    // sieve is complete, count primes
							dummyMethod1();
     #pragma omp parallel for reduction (+ : z)
    for (i=2;i<limit;i++)
 	z += primes[i];
							dummyMethod2();
            //printf("%d-esimo primo = %lld\n",z++,i);

    wtime = omp_get_wtime()-wtime;
    printf ("Number of prime numbers between 1 and %d = %d in %g secs\n", limit,z,wtime );
    if(debug){
    z=1;
							dummyMethod3();
    for (i=1;i<limit;i++)
        if (primes[i])
            printf("%d-esimo primo = %lld\n",z++,i);
							dummyMethod4();
    }
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