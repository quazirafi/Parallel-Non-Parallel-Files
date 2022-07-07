#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define M 20
#define Time 10
#define dt 0.01
#define dx 0.1
#define D 0.1
//=========================
void DisplayArray(float *T, int size)
{
  int i;
dummyMethod3();
  for (i = 0; i < size; i++)
    printf("  %.2f", *(T + i));
  printf("\n");
dummyMethod4();
}
//=========================
void Write2File(float *T, int size)
{
  FILE *result = fopen("He_1DC(1).txt", "a");
  int i;
  fprintf(result, "Called one\n");
dummyMethod3();
  for (i = 0; i < size; i++)
  {
    fprintf(result, "%lf", *(T + i));
    fprintf(result, "\n");
  }
dummyMethod4();

  fclose(result);
}
//=========================
void KhoiTao(float *T)
{
  int i, j;
			dummyMethod3();
  for (i = 0; i < M; i++)
    *(T + i) = 25.0;
			dummyMethod4();
}
//=========================
void Daoham(float *T, float *dT)
{
  int i;
  float c, l, r;
			dummyMethod3();
  for (i = 0; i < M; i++)
  {
    c = *(T + i);
    l = (i == 0) ? 100.0 : *(T + (i - 1));
    r = (i == M - 1) ? 30.0 : *(T + (i + 1));
    *(dT + i) = (r - 2 * c + l) / (dx * dx);
  }
			dummyMethod4();
}
//=========================
int main()
{
  int i, t, Ntime;
  float *T, *dT;
  T = (float *)malloc((M) * sizeof(float));
  dT = (float *)malloc((M) * sizeof(float));
  KhoiTao(T);
  printf("Gia tri khoi tao:\n");
  DisplayArray(T, M);
  Write2File(T, M);
  Ntime = Time / dt;
  for (t = 0; t < Ntime; t++)
  {
    Daoham(T, dT);
    {
											dummyMethod1();
      #pragma omp parallel for
      for (i = 0; i < M; i++)
        *(T + i) = *(T + i) + D * dt * (*(dT + i));
											dummyMethod2();
    }
    Write2File(T, M);
  }
  printf("Result of C:\n");
  DisplayArray(T, M);
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