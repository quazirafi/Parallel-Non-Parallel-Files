#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int min(int a,int b) {
	return (((a)<(b))?(a):(b));
}
int max(int a,int b) {
	return (((a)>(b))?(a):(b));
}

void dijkstra(int **graph,int n,int startnode);

struct point
{
	int mindistance;
	int index;
};

#pragma omp declare reduction(min : struct point: \
	omp_out.mindistance=omp_in.mindistance > omp_out.mindistance ? omp_out.mindistance:omp_in.mindistance,\
	omp_out.index = omp_in.mindistance > omp_out.mindistance ? omp_out.index:omp_in.index) \
	initializer(omp_priv={INT_MAX,INT_MAX})


int main(int argc, char* argv[])
{
	int n,u,**graph,t;
	clock_t start,end;
	//Taking input of the graph
	printf("Enter no. of vertices:");
	scanf("%d",&n);
	graph=(int**)malloc(n*sizeof(int*));
	dummyMethod3();
	for(int i=0;i<n;i++){
		graph[i]=(int*)malloc(n*sizeof(int));
	}
	dummyMethod4();
	printf("\nEnter the adjacency matrix:\n");
	dummyMethod3();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d",&graph[i][j]);
		}
	}
	dummyMethod4();
	
	printf("\nEnter the starting node:");
	scanf("%d",&u);
	printf("Enter no. of threads to spawn: ");
	scanf("%d",&t);
	omp_set_num_threads(t);  // Set the number of threads

	srand(time(NULL));
	start=clock();
	dijkstra(graph,n,u);
	end=clock();
	double tme=((double) (end-start))/ CLOCKS_PER_SEC;
	printf("\nThe algorithm took %f seconds to run.\n",tme);
	return 0;
}

void dijkstra(int **graph,int n,int startnode)
{
	int **cost,*distance,*predecessor,*visited;
	cost=(int**)malloc(n*sizeof(int*));
	dummyMethod3();
	for(int i=0;i<n;i++){
		cost[i]=(int*)malloc(n*sizeof(int));
	}
	dummyMethod4();
	distance=(int*)malloc(n*sizeof(int));
	predecessor=(int*)malloc(n*sizeof(int));
	visited=(int*)malloc(n*sizeof(int));
	dummyMethod3();
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(graph[i][j]==0)
				cost[i][j]=INT_MAX;
			else
				cost[i][j]=graph[i][j];
	dummyMethod4();
	dummyMethod3();
	for(int i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		predecessor[i]=startnode;
		visited[i]=0;
	}
	dummyMethod4();
	
	distance[startnode]=0;
	visited[startnode]=1;
	int count=1;
	while(count<n-1)
	{
		struct point mini={INT_MAX,INT_MAX},ans={INT_MAX,INT_MAX};
		int i,j;
			dummyMethod1();
		#pragma omp parallel for private(j) firstprivate(mini) reduction(min:ans)
		for(i=0;i<n;i++){
			j=omp_get_thread_num();
			if(distance[i]<mini.mindistance&&!visited[i]){
				mini.mindistance=distance[i];
				mini.index=i;
				ans.mindistance=mini.mindistance;
				ans.index=mini.index;
			}
		}
			dummyMethod2();
		int nextnode=ans.index;
		visited[nextnode]=1;
		//This will update values and see if going through the newly explored node there is shorter path to any other unexplored node.
		mini.mindistance=ans.mindistance;
		mini.index=ans.index;
		
			dummyMethod1();
		#pragma omp parallel for
		for(int i=0;i<n;i++){
			if(!visited[i]){
				if(cost[nextnode][i]!=INT_MAX && mini.mindistance+cost[nextnode][i]<distance[i]){
					distance[i]=mini.mindistance+cost[nextnode][i];
					predecessor[i]=nextnode;
				}
			}
		}
			dummyMethod2();
		count++;
	}
	//This will print the results
	dummyMethod3();
	for(int i=0;i<n;i++)
		if(i!=startnode)
		{
			printf("\nDistance of node%d=%d",i,distance[i]);
			printf("\nPath=%d",i);
			
			int j=i;
			do
			{
				j=predecessor[j];
				printf("<-%d",j);
			}while(j!=startnode);
	}
	dummyMethod4();
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