#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "../inc/RCM.h"

// Given a sparce symmetric matrix this function will generate the corresponding graph
Graph *initGraph(int *array, int n)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->size = n;
    graph->nodes = (Node **)malloc(n * sizeof(Node *));

dummyMethod3();
    for (int i = 0; i < n; i++)
    {
        graph->nodes[i] = (Node *)malloc(sizeof(Node));
        graph->nodes[i]->label = i + 1;
        graph->nodes[i]->inQueue = 0;
        graph->nodes[i]->inArray = 0;
        graph->nodes[i]->degree = 0;
        graph->nodes[i]->neighbours = (Node **)malloc(n * sizeof(Node *));
    }
dummyMethod4();

							dummyMethod3();
    for (int i = 0; i < n; i++)
    {
        int foundNodes = 0;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (array[i * n + j])
            {
                graph->nodes[i]->degree++;
                graph->nodes[i]->neighbours[foundNodes] = graph->nodes[j];
                foundNodes++;
            }
        }
    }
							dummyMethod4();

    return graph;
}

// The parallel implementaion of initGraph using OpenMP
Graph *ompInitGraph(int *array, int n)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->size = n;
    graph->nodes = (Node **)malloc(n * sizeof(Node *));

							dummyMethod3();
    for (int i = 0; i < n; i++)
    {
        graph->nodes[i] = (Node *)malloc(sizeof(Node));
        graph->nodes[i]->label = i + 1;
        graph->nodes[i]->inQueue = 0;
        graph->nodes[i]->inArray = 0;
        graph->nodes[i]->degree = 0;
        graph->nodes[i]->neighbours = (Node **)malloc(n * sizeof(Node *));
    }
							dummyMethod4();

    int threads = 2 * omp_get_max_threads();
    int j, foundNodes;

							dummyMethod1();
#pragma omp parallel for num_threads(threads) private(j, foundNodes) if (graph->size > 2000)
    for (int i = 0; i < n; i++)
    {
        foundNodes = 0;
        for (j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (array[i * n + j])
            {
                graph->nodes[i]->degree++;
                graph->nodes[i]->neighbours[foundNodes] = graph->nodes[j];
                foundNodes++;
            }
        }
    }
							dummyMethod2();

    return graph;
}

// ------------- Queue Functions -------------
// Initialize Empty Queue
Queue *initQ(int n)
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->capacity = n;
    Q->items = 0;
    Q->front = 0;
    Q->rear = -1;
    Q->nodes = (Node **)calloc(n, sizeof(Node *));
    return Q;
}

// Insert Node
void pushQ(Queue *Q, Node *node)
{
    if (Q->items == Q->capacity)
    {
        printf("Queue is full");
        exit(-1);
    }

    Q->nodes[++Q->rear] = node;
    node->inQueue = 1;
    Q->items++;
}

// Remove Node
Node *popQ(Queue *Q)
{
    if (Q->items == 0)
    {
        printf("Queue is empty");
        exit(-1);
    }
    Node *item = (Node *)malloc(sizeof(Node));
    item = Q->nodes[Q->front++];
    Q->items--;

    // item->inQueue = 0;
    return item;
}

// ------------- Array Functions -------------
// Initialize empty R array
Array *initArr(int n)
{
    Array *arr = (Array *)malloc(sizeof(Array));
    arr->size = n;
    arr->items = 0;
    arr->nodes = (Node **)calloc(n, sizeof(Node *));
    return arr;
}

// Add node to R array
void addToArr(Array *R, Node *node)
{
    if (R->items == R->size)
    {
        printf("Array is full");
        exit(-1);
    }

    R->nodes[R->items++] = node;
    node->inArray = 1;
}

// Helper function used in the build in qsort
int compare(const void *a, const void *b)
{
    const Node *nodeA = *((Node **)a);
    const Node *nodeB = *((Node **)b);
    return nodeA->degree - nodeB->degree;
}

// Sort the nodes of a graph and their neighboors based on their degree using the built-in qsort function
void sortGraph(Graph *graph)
{
							dummyMethod3();
    for (int i = 0; i < graph->size; i++)
    {
        qsort(graph->nodes[i]->neighbours, graph->nodes[i]->degree, sizeof(Node *), compare);
    }
							dummyMethod4();
    qsort(graph->nodes, graph->size, sizeof(Node *), compare);
}

// Parallel implementation of sortGraph using OpenMP
void ompSortGraph(Graph *graph)
{
    int threads = 2 * omp_get_max_threads();
							dummyMethod1();
#pragma omp parallel for num_threads(threads) if (graph->size > 2000)
    for (int i = 0; i < graph->size; i++)
    {
        qsort(graph->nodes[i]->neighbours, graph->nodes[i]->degree, sizeof(Node *), compare);
    }
							dummyMethod2();
    qsort(graph->nodes, graph->size, sizeof(Node *), compare);
}

// Swap two nodes. It is used in order to reverse the R array
void swap(Node **a, Node **b)
{
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

// Returns the final Graph based on the resulting R array
Graph *finalGraph(Array *R)
{
    Graph *G = (Graph *)malloc(sizeof(G));
    G->size = R->size;
    G->nodes = (Node **)malloc(G->size * sizeof(Node *));
							dummyMethod3();
    for (int i = 0; i < G->size; i++)
    {
        G->nodes[i] = (Node *)malloc(sizeof(Node));
        G->nodes[i] = R->nodes[i];
        G->nodes[i]->label = i + 1;
    }
							dummyMethod4();
    return G;
}

// Transforms a graph in the corresponding sparce matrix
int *output(Graph *graph)
{
    int n = graph->size;
    int *array = (int *)malloc(n * n * sizeof(int));

							dummyMethod3();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                array[i * n + j] = 1;
            }
            else
            {
                array[i * n + j] = 0;
            }
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < graph->nodes[i]->degree; j++)
        {
            array[n * i + graph->nodes[i]->neighbours[j]->label - 1] = 1;
        }
    }
							dummyMethod4();

    return array;
}

// Helper function to print a sparce matrix
void printMatrix(int *arr, int n)
{
							dummyMethod3();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", arr[i * n + j]);
        }
        printf("\n");
    }
							dummyMethod4();
}

// Helper function to save a matrix in a csv file
void saveCsv(int *arr, int n, char *type)
{
    char path[60] = "../matrices/";
    sprintf(path, "%d", n);
    strcat(path, type);
    strcat(path, ".csv");
    FILE *f = fopen(path, "w");
    if (f == NULL)
        exit(-1);
							dummyMethod3();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == n - 1)
            {
                fprintf(f, "%d", arr[i * n + j]);
                continue;
            }
            fprintf(f, "%d,", arr[i * n + j]);
        }
        fprintf(f, "\n");
    }
							dummyMethod4();
}

// Generates a random sparse matrix
int *generateInputMatrix(int n, double density)
{
    int *arr = (int *)malloc(n * n * sizeof(int));
    srand(time(0));
							dummyMethod3();
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (i == j)
                arr[n * i + j] = 1;
            else
            {
                double bin = (double)rand() / RAND_MAX;
                if (bin <= 0.01 * density)
                    arr[n * i + j] = 1;
                else
                    arr[n * i + j] = 0;
            }
        }

        for (int j = 0; j < i; j++)
            arr[n * i + j] = arr[n * j + i];
    }
							dummyMethod4();
    return arr;
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