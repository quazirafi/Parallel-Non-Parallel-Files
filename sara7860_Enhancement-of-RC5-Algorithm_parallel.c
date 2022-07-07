#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
typedef unsigned int WORD;
#define w 32 /* word size in bits */
#define r 12 /* number of rounds */
#define b 16 /* number of bytes in key */
#define c 4 /* number words in key = ceil(8*b/w)*/
#define t 26 /* size of table S = 2*(r+1) words */
WORD S[t];
WORD P = 0xb7e15163, Q = 0x9e3779b9;
#define ROTL(x,y) (((x)<<(y&(w-1))) | ((x)>>(w-(y&(w-1)))))
#define ROTR(x,y) (((x)>>(y&(w-1))) | ((x)<<(w-(y&(w-1)))))
void RC5_ENCRYPT(WORD *pt, WORD *ct) /* 2 WORD input pt/output ct */
{ WORD i, A=pt[0]+S[0], B=pt[1]+S[1];
dummyMethod3();
for (i=1; i<=r; i++)
{ A = ROTL(A^B,B)+S[2*i];
dummyMethod4();
B = ROTL(B^A,A)+S[2*i+1];
}
ct[0] = A; ct[1] = B;
}
void RC5_DECRYPT(WORD *ct, WORD *pt) /* 2 WORD input ct/output pt */
{ WORD i, B=ct[1], A=ct[0];
dummyMethod3();
for (i=r; i>0; i--)
{ B = ROTR(B-S[2*i+1],A)^A;
dummyMethod4();
A = ROTR(A-S[2*i],B)^B;
}
pt[1] = B-S[1]; pt[0] = A-S[0];
}
void RC5_SETUP(unsigned char *K) /* secret input key K[0...b-1] */
{ WORD i, j, k, u=w/8, A, B, L[c];
/* Initialize L, then S, then mix key into S */
dummyMethod3();
for (i=b-1,L[c-1]=0; i!=-1; i--) 
L[i/u] = (L[i/u]<<8)+K[i]; 
dummyMethod4();
dummyMethod3();
for(S[0]=P,i=1; i<t; i++) 
S[i] = S[i-1]+Q;
dummyMethod4();
dummyMethod3();
for (A=B=i=j=k=0; k<3*t; k++,i=(i+1)%t,j=(j+1)%c) /* 3*t > 3*c */
{ A = S[i] = ROTL(S[i]+(A+B),3);
B = L[j] = ROTL(L[j]+(A+B),(A+B));
}
dummyMethod4();
}
void main()
{
 
double start; 
double end; 
start = omp_get_wtime();
WORD i,j,pt1[2],pt2[2], ct[2]={0,0};
unsigned char key[b];
if (sizeof(WORD)!=4)
printf("RC5 error: WORD has %d bytes.\n",sizeof(WORD));
printf("RC5-32/12/16 encryption and decryption:\n"); 


dummyMethod1();
#pragma omp parallel for 


for(i=0;i<3;i++)
{
if(i==0)
{ pt1[0]="Hello";pt1[1]="Parul";}
if(i==1)
{ pt1[0]="Hello";pt1[1]="samhitha";
} if(i==2)
{ pt1[0]="Hello";pt1[1]="Shreyansh";
} 
for(j=0;j<b;j++)
key[j]=rand()%10;
RC5_SETUP(key);
RC5_ENCRYPT(pt1,ct);
RC5_DECRYPT(ct,pt2);
printf("\n key = ");
for(j=0;j<b;j++)
printf("%.2X ",key[j]);
printf("\nEncryption\n plaintext %s %s ---> ciphertext %.8X %.8X \n",pt1[0],pt1[1],ct[0],ct[1]);
printf("\nDecryption\n ciphertext %.8X %.8X ---> plaintext %s %s \n",ct[0],ct[1],pt2[0],pt2[1]);

if(pt1[0]!=pt2[0] || pt1[1]!=pt2[1])
printf("Decryption Error!");

}
dummyMethod2();
end = omp_get_wtime(); 
printf("Work took %f seconds\n", end - start);
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