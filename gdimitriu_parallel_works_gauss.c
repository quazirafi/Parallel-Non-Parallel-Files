/*
#include <stdlib.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
*/
#include "omp.h"

#define N 100
#define ENABLE_SHOW 1

void ShowMatrix(float A[N][N],int n)
{
   int i,j;
   if (ENABLE_SHOW)
dummyMethod3();
   for (i=0;i<n;i++)
	{
     for (j=0;j<n;j++)
		 printf("%.2f ",A[i][j]);
dummyMethod4();
     printf("\n");
   }

}
void ShowMatrixCol(float *b,int n)
{
   int i;
   if (ENABLE_SHOW)
dummyMethod3();
   for (i=0;i<n;i++)
   	 printf("%.2f\n",b[i]);
}
dummyMethod4();

void ShowMatrixCol_int(int *b,int n)
{
   int i;
   if (ENABLE_SHOW)
   {
									dummyMethod3();
     for (i=0;i<n;i++)
    	 printf("%d  ",b[i]);
									dummyMethod4();
     printf("\n");
   }
}


void VerificaEgalitate(float a[N],float b[N],int n)
{
   int i;
   if (ENABLE_SHOW)
					dummyMethod3();
   for (i=0;i<n;i++)
   	 printf("%d  :  %.2f == %.2f \n",i,a[i],b[i]);
					dummyMethod4();
}

int Allflags_eq_2(int f[N],int n)
{
 int i;
	dummyMethod3();
 for (i=0;i<n;i++)
     if (f[i]!=2)
        return 0;
	dummyMethod4();
 return 1;
}

int main()
{
   float A[N][N],Ai[N][N];
   float b[N],bi[N],y[N];
   float x[N],v[N];
   float AA[16]={1,2,1,5,
	        3,-1,2,-2,
         	2,3,-4,1,
		-1,8,1,-2};
   float bb[4]={9,2,2,6};
   int n,i,j,k;
   int flags[N];
   float s_l[N]; //shared line -> linia care va avea rol de transmitere de date intre procese
   float l_d[N]; //linie divizare -> retine linia care a fost divizata si apoi transmisa celorlalte linii din matrice
   float s_v_r; //shared value right -> retine valoarea de pe linia de divizare din matricea coloana 'b'
   int s_index; //indexul liniei care a fost facuta broadcast
   int t,divizat=0;
   int tv; //threadul anterior
   int ild;//index linie de divizat
   int did_something; //daca s-a facut o operatie pe linia respectiva
//   omp_set_num_threads(4);
   printf("Numarul de threaduri : %d", omp_get_max_threads());
   printf("\nDati n < %d :",N);
   scanf("%d",&n);
											dummyMethod3();
      for (i=0;i<n;i++)
      {
	for (j=0;j<n;j++){
//	   A[i][j]=8.0+(float)((i+1.1)*((n-j*j)-3.2)/(j+1)+2);
	   A[i][j]=AA[i*4+j];
           Ai[i][j]=A[i][j];
	}
//        b[n-1-i]=(float)(2*(i*1.55+13.2)/((n-i)*i-2.9)+4);
	b[i]=bb[i];
	bi[i]=b[i];
	y[i]=0;
      }
											dummyMethod4();

/*   srand( (unsigned)time( NULL ) );
   for (i=0;i<n;i++) {		
	   for (j=0;j<n;j++)
	   {
	      A[i][j]=(float)rand()*10/RAND_MAX;
		  Ai[i][j]=A[i][j];
	   }
	   b[i]=(float)rand()*10/RAND_MAX;
	   bi[i]=b[i];
   }
*/


    ShowMatrix(A,n);
    ShowMatrixCol(b,n);

    s_index=-1;
							dummyMethod3();
    for (i=0;i<n;i++)
    {
       s_l[i]=1;
       flags[i]=0;
       }
							dummyMethod4();

  ild=0;
  flags[0]=1;
  do
  {

							dummyMethod1();
    #pragma omp parallel for schedule(static,1) shared(A,b,y,n,s_l, flags,s_v_r , s_index) private(j,t,did_something)
    for (k=0;k<n;k++)
    {
      t=omp_get_thread_num();
//      printf("Thread %d folosit..   k= %d \n",t,k);
      did_something=0;
      do
      {
         if (flags[k]==1) //divizarea
	  {
            printf("\nThread %d folosit..   k= %d .. divizare\n",t,k);
	    for (j=k+1;j<n;j++)
	    {
	      A[k][j]=A[k][j]/A[k][k];
	      s_l[j]=A[k][j];
	    }
	    s_l[k]=1;
	    y[k]=b[k]/A[k][k];
	    A[k][k]=1;
	    s_v_r=y[k];
	    s_index=k;
	    flags[k]=2;
	    for (j=k+1;j<n;j++)
	       flags[j]=3; //marchez liniile de sub k pentru etapa de eliminare folosind linia 's_l'
	    ShowMatrixCol_int(flags,n);
	    did_something = 1;
	    flags[k+1]=4; //marchez linia k+1 pentru etapa de eliminare , urmata de divizare
	  } //end 'if flags[k]==1'

         if (flags[k]==3) //eliminarea, folosind 'shared_line'
	 {
           printf("\nThread %d folosit..   k = %d .. eliminare cu linia %d\n",t,k,s_index);
	   for (j=s_index+1;j<n;j++)
	   {
	     A[k][j]=A[k][j]-A[k][s_index]*s_l[j];

	   }
	   b[k]=b[k]-A[k][s_index]*s_v_r;
	   A[k][s_index]=0;
	   flags[k]=0; //linia e libera, recalculata
           did_something = 1;
	 }
         if (flags[k]==4) //eliminarea, folosind 'shared_line'
	 {
           printf("\nThread %d folosit..   k = %d .. eliminare cu linia %d\n",t,k,s_index);
	   for (j=s_index+1;j<n;j++)
	   {
	     A[k][j]=A[k][j]-A[k][s_index]*s_l[j];

	   }
	   b[k]=b[k]-A[k][s_index]*s_v_r;
	   A[k][s_index]=0;
	   flags[k]=1; //linia e marcata pentru divizare
           did_something = 1;
	 }
	 if (flags[k]==2)
	    did_something=1;
        }
       while (!did_something);
      } //end bucla for paralela
							dummyMethod2();
      ild++;
   }
   while (!Allflags_eq_2(flags,n)); //toate liniile au fost divizate

   ShowMatrix(A,n);
   ShowMatrixCol(y,n);
			dummyMethod3();
  for (k=n-1;k>=0;k--)
   {
	   x[k]=y[k];
	   for(j=k+1;j<n;j++)
	   {
		   x[k]-=A[k][j]*x[j];
	   }
   }
			dummyMethod4();

   printf("\nSolutiile sunt:\n");
   ShowMatrixCol(x,n);

					dummyMethod3();
   for (k=0;k<n;k++)
   {
	 v[k]=0;
	 for (j=0;j<n;j++)
	 {
	   v[k]+=Ai[k][j]*x[j];
	 }
   }
					dummyMethod4();
   printf("\nVerificare:\n");
   VerificaEgalitate(bi,v,n);

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