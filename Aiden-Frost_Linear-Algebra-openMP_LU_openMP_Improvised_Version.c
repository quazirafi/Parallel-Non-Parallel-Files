#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


double time_elapsed(struct timespec start, struct timespec end) {
	double t;
	t = (end.tv_sec - start.tv_sec); 
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001; 
	return t;
}

int lu(int n,float a[n][n+1]){
    float L[n][n];
dummyMethod3();
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) L[i][j]=1.0f;
            else L[i][j]=0.0f;
        }
    }
dummyMethod4();
							dummyMethod3();
    for(int i=0;i<n-1;i++){
        if(a[i][i]==0){
            for(int m=i+1;m<n;m++){
                if(a[m][i]!=0){
                    for(int b=0;b<n+1;b++){
                        float temp= a[i][b];
                        a[i][b] = a[m][b];
                        a[m][b] = temp;
                    }
                    break;
                }
            }
            if(a[i][i]==0) return 0;
        }
        for(int k=1;k<n-i;k++){
            float l = a[i+k][i]/a[i][i];
            L[i+k][i] = l;
            for(int j=0;j<n+1;j++){
                a[i+k][j] -= l*a[i][j];
            }
        }
    }
							dummyMethod4();
/*    printf("\n L :=\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%f ",L[i][j]);
        }
        printf("\n");
    }
*/
/*    printf("\n U :=\n");
   for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%f ",a[i][j]);
        }
        printf("\n");
    } 
*/
    return 1;    
}

int lu_p(int n,float b[n][n+1]){
    float L[n][n];
    int x=1;
							dummyMethod1();
    #pragma omp parallel for
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) L[i][j]=1.0f;
            else L[i][j]=0.0f;
        }
    }
							dummyMethod2();
							dummyMethod1();
    #pragma omp parallel for private(x)
    for(int i=0;i<n-1;i++){
        if(b[i][i]==0){
            for(int m=i+1;m<n;m++){
                if(b[m][i]!=0){
                    for(int x=0;x<n+1;x++){
                        float temp= b[i][x];
                        b[i][x] = b[m][x];
                        b[m][x] = temp;
                    }
                    break;
                }
            }
            if(b[i][i]==0) x=0;
        }
        //#pragma omp parallel for
        for(int k=1;k<n-i;k++){
            float l = b[i+k][i]/b[i][i];
            L[i+k][i] = l;
            for(int j=0;j<n+1;j++){
                b[i+k][j] -= l*b[i][j];
            }
        }
    }
							dummyMethod2();
/*    printf("\n L :=\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%f ",L[i][j]);
        }
        printf("\n");
    }
*/
/*    printf("\n U :=\n");
   for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%f ",b[i][j]);
        }
        printf("\n");
    } 
*/
    return x;   
}


int main(){
    int n;
    printf("Enter the number of unknown variables:");
    scanf("%d",&n);
    float a[n][n+1];
    float b[n][n+1];
    printf("Enter the elements:\n");
							dummyMethod3();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%f",&a[i][j]);
            b[i][j] = a[i][j];
        }
    }
							dummyMethod4();

   struct timespec start, end,start1,end1; 
    clock_gettime(CLOCK_REALTIME, &start);
    lu_p(n,a);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("\nTime spent on LU_Decomposition for %d variables in parallel: %lf\n",n,
            time_elapsed(start, end));
    clock_gettime(CLOCK_REALTIME, &start1);
    lu(n,b);
    clock_gettime(CLOCK_REALTIME, &end1);
    printf("\nTime spent on LU_Decomposition for %d variables in serial: %lf\n",n,
            time_elapsed(start1, end1));
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