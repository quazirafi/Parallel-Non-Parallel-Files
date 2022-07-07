#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<limits.h>
#include<sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define chunk 2
struct Edge
{
    int src, dest, weight;
};
struct Graph
{
	int V, E;
	struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = 
	(struct Graph*) malloc( sizeof(struct Graph) );
	graph->V = V;
	graph->E = E;
	graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
	return graph;
}

void printArr(int dist[], int n)
{
	printf("Vertex   Distance from Source\n");
dummyMethod3();
	for (int i = 0; i < n; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
}
dummyMethod4();

void bellman(struct Graph* graph, int src)
{
	int V = graph->V;
	int E = graph->E;
	int dist[V];
			dummyMethod1();
	#pragma omp parallel for schedule(dynamic,chunk)  
		for (int i = 0; i < V; i++)
			dist[i]   = INT_MAX;
			dummyMethod2();
	dist[src] = 0;
			dummyMethod1();
	#pragma omp parallel for schedule(dynamic,chunk) collapse(2) 
		for (int i = 1; i <= V-1; i++)
		{
			for (int j = 0; j < E; j++)
			{
				int u = graph->edge[j].src;
				int v = graph->edge[j].dest;
				int weight = graph->edge[j].weight;
				if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
					dist[v] = dist[u] + weight;
			}
		}
			dummyMethod2();
			dummyMethod1();
	#pragma omp parallel for schedule(dynamic,chunk)  	
		for (int i = 0; i < E; i++)
		{
			int u = graph->edge[i].src;
			int v = graph->edge[i].dest;
			int weight = graph->edge[i].weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				printf("Graph has negative weight cycle");
		}
			dummyMethod2();
	printArr(dist, V);
 	return;
}

int main()
{
	int V,i,E;
	struct timeval TimeValue_Start;
	struct timezone TimeZone_Start;
	struct timeval TimeValue_Final;
	struct timezone TimeZone_Final;
	long time_start,time_end;
	double time_overhead;	
	printf("Enter the number of vertices : ");
	scanf("%d",&V);
	printf("Enter the number of edges : ");
	scanf("%d",&E);	
	struct Graph* graph = createGraph(V, E); 
	printf("Enter the source,destination and weights for edges : \n");
	dummyMethod3();
	for(i=0;i<E;i++){
		scanf("%d %d %d",&graph->edge[i].src,&graph->edge[i].dest,&graph->edge[i].weight);

	}
	dummyMethod4();
	gettimeofday(&TimeValue_Start,&TimeZone_Start);
	#pragma omp parallel default(shared)
		#pragma omp single
			bellman(graph,0);	
	gettimeofday(&TimeValue_Final,&TimeZone_Final);
	time_start=TimeValue_Start.tv_sec*1000000+TimeValue_Start.tv_usec;
	time_end=TimeValue_Final.tv_sec*1000000+TimeValue_Final.tv_usec;
	time_overhead=(time_end-time_start)/1000000.0;
	printf("\nTime in Seconds(t)  :%lf\n",time_overhead);		
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