/*
gcc gcc kmomp2.c -lm -O2 -fopenmp
time ./a.out

real    1m32,205s
user    5m59,687s
sys     0m1,454s
*/

//#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
//#pragma GCC option("arch=native","tune=native","no-zero-upper")
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// ***************************************************
#define N 100000
#define Nv 1000
#define Nc 100
#define THRESHOLD 0.000001

// ***************************************************
float Vec[N][Nv] ;
float Center[Nc][Nv] ;
int Class[N] ;

//****************************************************
void initCenter( void )
{       
	int i=0,d,f,p[Nc],j,k;
	srand(1234);
	while(i<Nc) {
		d=rand()%N;
        f=1;
															dummyMethod3();
        for(j=0;j<i;j++){
            if (p[j]==d){ 
                f=0;
                break;
            }
        }
															dummyMethod4();
        if (f==1){
            p[i]=d;
																							dummyMethod3();
            for(k=0;k<Nv;k++){
                Center[i][k]=Vec[d][k]; 
            }
																							dummyMethod4();
            i++;
        }
	}
}

// ***************************************************
// returns the total minimum distance
// *************************************************
float estimateClass( void )
{
    
    float mdist=0;

							dummyMethod1();
    #pragma omp parallel for reduction(+:mdist) schedule(static)// addition of schedule 
    for(int i=0;i<N;i++){
        int th=-1;

        float min=350000;
        #pragma omp parallel for reduction(min:min) schedule(static)// addition of schedule 
        for (int j=0;j<Nc;j++){
            float dist=0;
            //#pragma omp parallel for reduction(+:dist) schedule(static) -> needs more time 
            for (int k=0;k<Nv;k++){
                dist=dist+(Vec[i][k]-Center[j][k])*(Vec[i][k]-Center[j][k]);
            }
            dist=sqrt(dist);
            if (min>dist){
                min=dist;
                th=j;
            }
        }
        Class[i]=th;
        mdist=mdist+min;
    }
							dummyMethod2();

    return mdist;
}


// ***************************************************
void estimateCenter( void )
{   
    float b[Nc][Nv];
							dummyMethod3();
    for (int i=0;i<Nc;i++)
        for (int j=0;j<Nv;j++)
            b[i][j]=0;
							dummyMethod4();

    int i=0,y=0;
    do{
        int a=Class[i];
															dummyMethod3();
        for (int j=0;j<i;j++){
            if (a==Class[j]){
                flag=0;
                break;
            }
        }
															dummyMethod4();
        if (flag==1){
            int s=0;
																							dummyMethod3();
            for(int k=i;k<N;k++){
                if (a==Class[k]){
                    s++;
                    for (int m=0;m<Nv;m++){
                        b[y][m]=b[y][m]+Vec[k][m];
                    }
                }
            }
																							dummyMethod4();
																							dummyMethod3();
            for (int m=0;m<Nv;m++)
                b[y][m]=b[y][m]/s;
																							dummyMethod4();
            y++;
        }
        i++;
    }while (i<N);
    
							dummyMethod3();
    for (int i=0;i<Nc;i++)
        for (int j=0;j<Nv;j++){
            Center[i][j]=b[i][j];
//            printf(" %f --",Center[i][j]);
        }
							dummyMethod4();
//        printf("\n");
}


// ***************************************************
void SetVec( void )
{
    int i, j ;
    srand(1234);
							dummyMethod3();
    for( i = 0 ; i< N ; i++ )
        for( j = 0 ; j < Nv ; j++ )
            Vec[i][j] = (1.0*rand())/RAND_MAX ;
							dummyMethod4();
}

// ***************************************************
void printVec( void )
{
int i ;

dummyMethod3();
for( i = 0 ; i< Nc ; i++ )
    //for( j = 0 ; j < N ; j++ ){
        printf( "%d\n",i );}
dummyMethod4();

//}

// ***************************************************
int main()
{
float totDist ;
float prevDist ;

SetVec() ;

initCenter() ;

totDist = 1.0e30 ;
do {
prevDist = totDist ;
totDist = estimateClass() ;
estimateCenter() ;
} while((prevDist-totDist)/totDist> THRESHOLD ) ;
/*
for (int i=0;i<Nc;i++){
    for (int j=0;j<Nv;j++)
        printf(" %f --",Center[i][j]);
    printf("\n");}
*/
printf("%f \n",totDist);

return 0 ;
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