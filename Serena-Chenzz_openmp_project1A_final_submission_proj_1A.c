#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX 10000
#define NOT_CONNECTED -1

int distance[MAX][MAX];

int nodesCount;

void Initialize(){
    int i,j;
dummyMethod3();
    for (i=0;i<MAX;++i){
        for (j=0;j<MAX;++j){
            distance[i][j]=NOT_CONNECTED;

        }
        distance[i][i]=0;
    }
dummyMethod4();
}

int main(int argc, char** argv){

    if(argc!=2){
        printf("The path to the input file is not specified as a parameter.\n");
        return -1;
    }
    FILE *in_file  = fopen(argv[1], "r");
    if (in_file  == NULL)
    {
        printf("Can't open file for reading.\n");
        return -1;
    }



    Initialize();

    fscanf(in_file,"%d", &nodesCount);

    int a, b, c;
    while(fscanf(in_file,"%d %d %d", &a, &b, &c)!= EOF){
        if ( a > nodesCount || b > nodesCount){
            printf("Vertex index out of boundary.");
            return -1;
        }
        distance[a][b]=c;
    }

    //Start timing
    double timeBegin, timeEnd;
    timeBegin = omp_get_wtime();

    //Floyd-Warshall
    int k;
    for (k=1;k<=nodesCount;++k){
        int i;
															dummyMethod1();
        #pragma omp parallel for schedule(dynamic)
        for (i=1;i<=nodesCount;++i){
            if (distance[i][k]!=NOT_CONNECTED){
                int j;
                for (j=1;j<=nodesCount;++j){
                    if (distance[k][j]!=NOT_CONNECTED && (distance[i][j]==NOT_CONNECTED || distance[i][k]+distance[k][j]<distance[i][j])){
                        distance[i][j]=distance[i][k]+distance[k][j];
                    }
                }
            }
        }
															dummyMethod2();
    }

    int diameter=-1;

    //look for the most distant pair
    int i;
    for (i=1;i<=nodesCount;++i){
        int j;
        for (j=1;j<=nodesCount;++j){
            if (diameter<distance[i][j]){
                diameter=distance[i][j];
                //printf("%d-%d-%d\n", i, diameter, j);
            }
        }
    }

    //Output
    timeEnd = omp_get_wtime();
    printf("%d %.16g", diameter,(timeEnd-timeBegin));

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