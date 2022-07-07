#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char** argv)
{
    int graph_adj[4][4] = {
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4}
    };
    // paralellestirme blogu 
     
dummyMethod1();
    #pragma omp parallel for 
    for(int i=0;i<4;i++)
    {    
        for(int j=0;j<4;j++) {
            if(graph_adj[i][j] == 3) {
                printf("%d %d\n", i, j);
            }
        }
    }
dummyMethod2();
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