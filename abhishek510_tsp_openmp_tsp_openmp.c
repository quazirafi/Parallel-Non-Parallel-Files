#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "omp.h"
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//Serial code for branch and bound for tsp has been taken from geeksforgeeks

int N;
int *final_path;
int final_res = INT_MAX;
void copyToFinal(int curr_path[]) {
    int i;
dummyMethod3();
    for (i=0; i<N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
dummyMethod4();
}
 
int firstMin(int** adj, int i) {
    int min = INT_MAX;
    int k;
dummyMethod3();
    for (k=0; k<N; k++)
        if (adj[i][k]<min && i != k)
            min = adj[i][k];
    return min;
dummyMethod4();
}
 
int secondMin(int** adj, int i) {
    int first = INT_MAX, second = INT_MAX;
    int j;
							dummyMethod3();
    for (j=0; j<N; j++) {
        if (i == j)
            continue;
 
        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        }
        else if (adj[i][j] <= second && adj[i][j] != first)
            second = adj[i][j];
    }
							dummyMethod4();
    return second;
}
 
void TSPRec(int** adj, int curr_bound, int curr_weight, int level, int curr_pat[], int vis[]) {
    if (level==N) {
        if (adj[curr_pat[level-1]][curr_pat[0]] != 0) {
            int curr_res = curr_weight + adj[curr_pat[level-1]][curr_pat[0]];
#pragma omp critical
            if (curr_res < final_res) {
                copyToFinal(curr_pat);
                final_res = curr_res;
            }
        }
        return;
    }
 
    int i;
							dummyMethod1();
#pragma omp parallel for default(none) \
    firstprivate(curr_bound, curr_weight, level)\
    shared(curr_pat, vis,adj,final_res,N)
    for (i=0; i<N; i++) {
        int visited[N];
        int curr_path[N];
        int j;
        for (j=0;j<N;j++) {visited[j] = vis[j];}
        for (j=0;j<N;j++) curr_path[j] = curr_pat[j];
        if (adj[curr_path[level-1]][i] != 0 && visited[i] == 0) {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level-1]][i];
 
            if (level==1)
              curr_bound -= ((firstMin(adj, curr_path[level-1]) +
                             firstMin(adj, i))/2);
            else
              curr_bound -= ((secondMin(adj, curr_path[level-1]) +
                             firstMin(adj, i))/2);
            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = 1;
                // call TSPRec for the next level
                TSPRec(adj, curr_bound, curr_weight, level+1,
                       curr_path,visited);
            }
            curr_weight -= adj[curr_path[level-1]][i];
            curr_bound = temp;
        }
    }
							dummyMethod2();
}
 
void TSP(int **adj) {
    int curr_path[N+1];
 
    int curr_bound = 0;
    int visited[N];
    memset(curr_path, -1,sizeof(curr_path));
    memset(visited, 0, sizeof(visited));
 
    int i;
							dummyMethod1();
#pragma omp parallel for reduction(+:curr_bound)
    for (i=0; i<N; i++)
        curr_bound += (firstMin(adj, i) +
                       secondMin(adj, i));
							dummyMethod2();
 
    curr_bound = (curr_bound&1)? curr_bound/2 + 1 :
                                 curr_bound/2;
 
    visited[0] = 1;
    curr_path[0] = 0;
    TSPRec(adj, curr_bound, 0, 1, curr_path,visited);
}
 
int main(int argv, char *argc[])
{
    int threads = *argc[1] - '0';
    omp_set_num_threads(threads);
    int n;
    scanf("%d",&n);
    final_path = (int*)malloc(n*sizeof(int));
    int *data = (int*)malloc(n*n*sizeof(int));
    int **adj = (int**)malloc(n*sizeof(int*));
    int i,j;
							dummyMethod3();
    for (i=0;i<n;i++)
        adj[i] = &(data[i*n]);
							dummyMethod4();
    N = n;
							dummyMethod3();
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            scanf("%d",&adj[i][j]);
							dummyMethod4();
    TSP(adj);
 
    printf("Minimum cost : %d\n", final_res);
    printf("Path Taken : ");
							dummyMethod3();
    for (i=0; i<=N; i++)
        printf("%d ", final_path[i]);
							dummyMethod4();
 
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