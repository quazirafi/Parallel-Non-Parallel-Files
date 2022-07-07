#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (int argc, char *argv[])
{
  int tamanho_vetores;
  unsigned long int prod = 0.0;

  if(argc<2){
    printf("uso %s <tamanho vetores>\n", argv[0]);
    exit(1);
  }
  
  /* tamanho dos vetores */
  tamanho_vetores = atoi(argv[1]);
  
  
  /* alocacao do vetor A */
  unsigned long int *a = (unsigned long int *) malloc(sizeof(unsigned long int) * tamanho_vetores);
  /* alocacao do vetor B */
  unsigned long int *b = (unsigned long int *) malloc(sizeof(unsigned long int) * tamanho_vetores);
  
  /* Initialização. */
   /* inicializacao dos vetores */
dummyMethod1();
    #pragma omp parallel for
    for (int i=0; i<tamanho_vetores; i++)
      a[i] = i;

    #pragma omp parallel for
dummyMethod2();
dummyMethod1();
    for (int i=0; i<tamanho_vetores; i++)
      b[i] = i;

    /* produto escalar dos vetores */
dummyMethod2();
							dummyMethod1();
    #pragma omp parallel for reduction(+:prod)
    for (int i=0; i<tamanho_vetores; i++)
      prod += a[i] * b[i];
							dummyMethod2();

  free(a);
  free(b);
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