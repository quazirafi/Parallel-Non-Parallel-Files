/******
 * Fix 2:
 * This fix uses a private variable that lives
 * in each thread's individual stack
 **********/
#include "stdio.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// #define NUMPAD 4
// #define NUMTHREADS 4

struct s{
    float value;
    //int pad[NUM];
} Array[4];
int main( int argc, char *argv[ ] )
{
    omp_set_num_threads(NUMTHREADS);
    int someBigNumber = 1000000000;
    
    //Start time
    double time0 = omp_get_wtime( );
dummyMethod1();
    #pragma omp parallel for
    
    for( int i = 0; i < 4; i++ ){
        float privateVar = Array[i].value; //now a copy of this lives in each thread's stack
        for( int j = 0; j < someBigNumber; j++ ){
            privateVar = privateVar + 2.;
        }
        Array[i].value = privateVar;
    }
dummyMethod2();
    
    //Timing
    double time1 = omp_get_wtime( );
    double timeElapsed = time1- time0;
    
    //Performance
    
    //Speculative for now
    double megaAddsPerSecond = (double)someBigNumber*(double)4/timeElapsed/1000000.;
    
    //Write to a txt file
    FILE *fp;
    //headers
    fp = fopen("fix2.txt", "a");
    
    fprintf (fp, "%d\t", NUMPAD);
    fprintf (fp, "%d\t", NUMTHREADS);
    fprintf (fp, "%f\t",megaAddsPerSecond);
    fprintf (fp, "%f\t",1000000.*timeElapsed);
    fprintf (fp, "Fix 2");
    fprintf (fp, "\n");
    
    
    printf("Threads: %d\n", NUMTHREADS);
    printf("Padding: %d\n", NUMPAD);
    printf("Elapsed Time=%10.2lf microseconds\n",1000000.*timeElapsed);
    printf("Average Performance = %8.2lf MegaAdds/Sec\n", megaAddsPerSecond);
    printf ("Fix 1\n");
    printf("***** \n");
    
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