#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int n,i,k;
    int temp=0;
    scanf("%d",&n);
dummyMethod1();
    #pragma omp parallel for
        for(i=2;i<=n;i++)
         {
            int count = 0;
            //printf("hello");
            for(k=1;k<=i;k++)
            {
                if(i%k == 0)
                {
                    count++;
                }
            }
            if(count == 2)
            {
                printf("%d  ",i);
                temp++;
            }
        }
dummyMethod2();
         printf(" total %d",temp);
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