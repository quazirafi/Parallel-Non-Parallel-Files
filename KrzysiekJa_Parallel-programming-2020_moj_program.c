#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <math.h>
#include "pomiar_czasu.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//#define WYMIAR 7936
//#define ROZMIAR 62980096
//#define WYMIAR 1024
//#define ROZMIAR 1048576
#define WYMIAR 10000
#define ROZMIAR 100000000

//#define WYMIAR 19200
//#define ROZMIAR 368640000

void mat_vec(double* a, double* x, double* y, int n, int nt);

main ()
{
  static double x[WYMIAR],y[WYMIAR],z[WYMIAR];
  double *a;
  double t1;
  int n,nt,i,j;
  const int ione=1;
  const double done=1.0;
  const double dzero=0.0;

  a = (double *) malloc(ROZMIAR*sizeof(double));

dummyMethod3();
  for(i=0;i<ROZMIAR;i++) a[i]=0.00000001*i;
  for(i=0;i<WYMIAR;i++) x[i]=0.0001*(WYMIAR-i);
dummyMethod4();
dummyMethod3();

  n=WYMIAR;
dummyMethod4();

  nt=4;
  //printf("Podaj liczbe watkow: "); scanf("%d",&nt);

  printf("\nPoczatek procedury macierz-wektor\n\n");

  
  inicjuj_czas();
  t1 = omp_get_wtime();
  mat_vec(a,x,y,n,nt);
  t1 = omp_get_wtime() - t1;
  drukuj_czas();
  

  printf("\nKoniec procedury macierz-wektor\n");
  printf("\tczas wykonania: %lf, Gflop/s: %lf, GB/s> %lf\n",  
	 t1, 2.0e-9*ROZMIAR/t1, (1.0+1.0/n)*8.0e-9*ROZMIAR/t1);

  printf("\nPoczatek procedur sprawdzajacych\n");
  // test
//  printf("TEST\n");


  inicjuj_czas();
  t1 = omp_get_wtime();
			dummyMethod1();
#pragma omp parallel for num_threads(nt) firstprivate(n) private(j) 
  for(i=0;i<n;i++){
    double t=0.0;
    int ni = n*i;
    for(j=0;j<n;j++){
      t+=a[ni+j]*x[j];
    }
    z[i]=t;
  }
			dummyMethod2();
  t1 = omp_get_wtime() - t1;
  drukuj_czas();

  printf("\nKoniec procedury macierz-wektor\n");
  printf("\tczas wykonania: %lf, Gflop/s: %lf, GB/s> %lf\n",  
	 t1, 2.0e-9*ROZMIAR/t1, (1.0+1.0/n)*8.0e-9*ROZMIAR/t1);

			dummyMethod3();
  for(i=0;i<WYMIAR;i++){
    if(fabs(y[i]-z[i])>1.e-9*z[i]) printf("Blad!\n");
  }
			dummyMethod4();


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