#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//#include <unistd.h>
#include "omp.h"
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>

double time_elapsed(struct timespec start, struct timespec end) {
	double t;
	t = (end.tv_sec - start.tv_sec); 
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001; 
	return t;
}

int **makemat(int n,int **a,int c){
    int flag;
    int **b;
    b=malloc(sizeof(int*) *(n-1));
dummyMethod3();
    for(int i=0;i<n-1;i++)
        b[i]=malloc(sizeof(int*) * n-1);

    for(int i=0;i<n-1;i++){
dummyMethod4();
							dummyMethod3();
        flag=0;
        for(int j=0;j<n-1;j++){
            if(j==(c-1)){
                b[i][j]=a[i+1][j+1];
                flag=1;
            }
            else
            {
                if(flag)
                    b[i][j]=a[i+1][j+1];
                else
                {
                    b[i][j]=a[i+1][j];
                }
            }
        }
    }
							dummyMethod4();
    return b;
}
int determinant(int n,int **a){
    int d=0;
    if(n==1)
        return a[0][0];
    
							dummyMethod3();
    for(int i=1;i<=n;i++){
        int **b=makemat(n,a,i);

        if(i%2==0)
            d-=a[0][i-1] * determinant(n-1,b);
        else if(i%2==1)
            d+=a[0][i-1] * determinant(n-1,b);
    }
							dummyMethod4();
    return d;
}

int largest_eigen(int **a,int error,int n){
    float temp, lambda_new, lambda_old;
    float x[n],x_new[n];
    int i,j, step=1;
    //printf("Enter Initial Guess Vector:\n");
			dummyMethod3();
	 for(i=0;i<n;i++)
	 {
		  /*
          printf("x[%d]=",i);
		  scanf("%f", &x[i]);
          */
         if(i==0) x[i]=1;
         else x[i]=0;
	 }
			dummyMethod4();
	 /* Initializing Lambda_Old */
	 lambda_old = 1;
	 /* Multiplication */
	 up:
			dummyMethod3();
	 for(i=0;i<n;i++)
	 {
		  temp = 0.0;
		  for(j=0;j<n;j++)
		  {
		   	temp = temp + a[i][j]*x[j];
		  }
		  x_new[i] = temp;
	 }
			dummyMethod4();
	 /* Replacing */
			dummyMethod3();
	 for(i=0;i<n;i++)
	 {
	  	x[i] = x_new[i];
	 }
			dummyMethod4();
	 /* Finding Largest */
	 lambda_new = fabs(x[0]);
			dummyMethod3();
	 for(i=1;i<n;i++)
	 {
		  if(fabs(x[i])>lambda_new)
		  {
		   	lambda_new = fabs(x[i]);
		  }
	 }
			dummyMethod4();
	 /* Normalization */
			dummyMethod3();
	 for(i=0;i<n;i++)
	 {
	  	x[i] = x[i]/lambda_new;
	 }
			dummyMethod4();
	 /* Display
	 printf("\n\nSTEP-%d:\n", step);
	 printf("Eigen Value = %f\n", lambda_new);
	 printf("Eigen Vector:\n");
    */
	 /* Checking Accuracy */
	 if(fabs(lambda_new-lambda_old)>error)
	 {
		  lambda_old=lambda_new;
		  step++;
		  goto up;
	 }
							dummyMethod3();
    for(i=0;i<n;i++)
	 {
	  	printf("%f\t", x[i]);
	 }
							dummyMethod4();
	return lambda_new;
}
int largest(float *e,int n){
    float x=e[0];
							dummyMethod3();
    for(int i=0;i<n;i++){
        if(e[i]>x)
            x=e[i];
    }
							dummyMethod4();
    return x;
}

void eigen_values(int **a,int n,int limit){
    int *c[n];
							dummyMethod3();
    for(int i=0;i<n;i++){
        c[i]= (int*)malloc(n*sizeof(int));
    }
							dummyMethod4();
							dummyMethod3();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            c[i][j]=a[i][j];
        }
    }
							dummyMethod4();
    //printf("%d is an eigen value\n",limit);
							dummyMethod1();
    #pragma omp parallel for
    for(int i= -limit;i!=limit;i++){
        for(int j=0;j<n;j++){
            int temp=a[j][j];
            c[j][j]=temp - i;
        }

        int d=determinant(n,c);
        //printf("%d is the current iteration, %d is the determinant\n",i,d);
        if(d==0){
            float *e=(float*)malloc(n*sizeof(float));
            for(int i=0;i<n;i++){
                int **f=makemat(n,c,i+1);
                if((i+1)%2==1)
                    e[i]=(float)determinant(n-1,f);
                else
                    e[i]= -(float)determinant(n-1,f);
                
            }
            float largest_no=largest(e,n);
            for(int i=0;i<n;i++){
                e[i]=e[i]/largest_no;
            }
            printf("\nEigen vector:\n");
            for(int i=0;i<n;i++){
                printf("%f ",e[i]);
            }
            printf("\n%d is the corresponding eigen value\n",i);
            printf("\n");
        }
    }
							dummyMethod2();
}


int main(){
    int n,error=0.001;
    printf("Enter the dimensions of the matrix: ");
    scanf("%d",&n);
    printf("\nEnter the elements:\n");
    int **a;
    a=malloc(sizeof(int*)*n);
							dummyMethod3();
    for(int i=0;i<n;i++)
        a[i]=malloc(sizeof(int*) * n);
							dummyMethod4();
							dummyMethod3();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
							dummyMethod4();
    int D = determinant(n,a);
    printf("The determinant is %d\n",D);
    int l_eigen=largest_eigen(a,error,n);
    printf("\n%d is the corresponding eigen value\n",l_eigen);
    struct timespec start, end; 
    clock_gettime(CLOCK_REALTIME, &start);
    eigen_values(a,n,l_eigen);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("\nTime spent on eigen value calculation for %dx%d matrix: %lf\n",n,n,
            time_elapsed(start, end));
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