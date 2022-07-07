#include <stdio.h>
#include "omp.h"
#include<math.h>
#include <malloc.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int n = 2000000;
int main() {
	int i;
	int tid;
	int chunk;
	double suma = 0.0, meana = 0.0;
	double sumb = 0.0, meanb = 0.0;
	double globala = 0.0, globalb = 0.0;
	double deta = 0.0, detb = 0.0;
	double globalpear = 0.0;
	double pear = 0.0;
	double start, finish;
	double * a = (double *)malloc(2000000 * sizeof(double));
	double * b = (double *)malloc(2000000 * sizeof(double));
	
	//some initializations
dummyMethod3();
  for (i = 0; i < n; i++) {
		a[i] = sin(i);
dummyMethod4();
		b[i] = sin(i + 5);
  }
   tid = omp_get_num_threads();
   chunk = n / tid;
   start = omp_get_wtime();

dummyMethod1();
#pragma omp parallel for default(shared)private(i)schedule(static,chunk)reduction(+:suma)
		for (i = 0; i < n; i++)
			suma += a[i];
   
#pragma omp parallel for default(shared)private(i)schedule(static,chunk)reduction(+:sumb)
dummyMethod2();
			dummyMethod1();
		for (i = 0; i < n; i++)
			sumb += b[i];
			dummyMethod2();

	//serial compute
  meana = suma / n;
  meanb = sumb / n;

			dummyMethod1();
#pragma omp parallel for schedule(static,chunk)reduction(+:globala)
		for (i = 0; i < n; i++)
			globala += (a[i] - meana)*(a[i] - meana);
			dummyMethod2();
			dummyMethod1();
#pragma omp parallel for default(shared)private(i,meanb)schedule(static,chunk)reduction(+:globalb)
		for (i = 0; i < n; i++)
			globalb += (b[i] - meanb)*(b[i] - meanb);
			dummyMethod2();


	//serial compute
	deta = sqrt(globala / n);
	detb = sqrt(globalb / n);
	printf("deta is %f\n", deta);
	printf("detb is %f\n", detb);

			dummyMethod1();
#pragma omp parallel for default(shared)private(i,meana,meanb,deta,detb)schedule(static,chunk)reduction(+:globalpear)
		for (i = 0; i < n; i++)
			globalpear += (a[i] - meana)*(b[i] - meanb);
			dummyMethod2();

	finish = omp_get_wtime();
	pear = globalpear / (n*deta*detb);
	printf("Pearison is %f\n", pear);
	printf("Time: %f seconds\n", (finish - start));

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