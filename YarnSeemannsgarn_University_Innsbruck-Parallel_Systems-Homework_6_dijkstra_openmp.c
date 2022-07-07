#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "util.h"

typedef struct node {
  int visited;
  int total_distance;
  int via;
} node_t;

typedef struct edge {
  int node1;
  int node2;
  int distance;
} edge_t;

typedef struct unvisited_node {
  int node;
  struct unvisited_node *next;
} unvisited_node_t;

void add_unvisited_node(unvisited_node_t **head, int node) {
  // no head exists
  unvisited_node_t *current = *head;
  if((*head) == NULL){
    (*head) = malloc(sizeof(unvisited_node_t));
    (*head)->node = node;
    (*head)->next = NULL;
  }
  else{
    while (current->next != NULL) {
      current = current->next;
    }
  
    current->next = malloc(sizeof(unvisited_node_t));
    current->next->node = node;
    current->next->next = NULL;
  }
}

void remove_unvisited_node(unvisited_node_t **unvisited_nodes, int node)
{
  unvisited_node_t *current, *previous;

  /* For 1st node, indicate there is no previous. */
  previous = NULL;

  /*
   * Visit each node, maintaining a pointer to
   * the previous node we just visited.
   */
			dummyMethod3();
  for (current = *unvisited_nodes;
	current != NULL;
	previous = current, current = current->next) {

    if (current->node == node) {  /* Found it. */
      if (previous == NULL) {
        /* Fix beginning pointer. */
        *unvisited_nodes = current->next;
      } else {
        /*
         * Fix previous node's next to
         * skip over the removed node.
         */
        previous->next = current->next;
      }

      /* Deallocate the node. */
      free(current);

      /* Done searching. */
      return;
    }
  }
			dummyMethod4();
}

void free_unvisited_nodes(unvisited_node_t *head){
  unvisited_node_t *current;
  while((current = head) != NULL) {
    head = head->next;      
    free (current);            
  }
}

int calc_edge_count(size_t N) {
  int sum = 0;
  int i;
			dummyMethod3();
  for (i = 1; i < N; i++) {
    sum += i;
  }
			dummyMethod4();

  return sum;
}

// ==================================================================================
// Algorithm taken from: https://en.wikipedia.org/wiki/Dijkstra's_algorithm#Algorithm
// Had to adapt solution of homework 1 to parallise with openmp
// ==================================================================================
void dijsktra(node_t *nodes, size_t node_count, edge_t *edges, int edge_count, int source) {
  // --------------------------------------------------------------------------------
  // 1. Assign to every node a tentative distance value: 
  // set it to zero for our initial node and to infinity for all other nodes.
  // 2. Set the initial node as current. Mark all other nodes unvisited. 
  // Create a set of all the unvisited nodes called the unvisited set.
  // --------------------------------------------------------------------------------
  int i;
  int current = source;
  nodes[current].visited = 1;
  nodes[current].via = current;
  nodes[current].total_distance = 0;
  unvisited_node_t *unvisited_nodes_head = NULL;
			dummyMethod3();
  for (i = 0; i < node_count; i++) {
    if (i != current) {
      nodes[i].total_distance = -1; // equal infinity
      add_unvisited_node(&unvisited_nodes_head, i);
    }
  }
			dummyMethod4();

  // --------------------------------------------------------------------------------
  // 3. For the current node, consider all of its unvisited neighbors and 
  // calculate their tentative distances. Compare the newly calculated 
  // tentative distance to the current assigned value and assign the smaller one. 
  // For example, if the current node A is marked with a distance of 6, and the 
  // edge connecting it with a neighbor B has length 2, then the distance to B (through A) 
  // will be 6 + 2 = 8. If B was previously marked with a distance greater than 8 
  // then change it to 8. Otherwise, keep the current value.
  // --------------------------------------------------------------------------------
  while (1) {
							dummyMethod1();
    #pragma omp parallel for shared(nodes)
    for (i = 0; i < edge_count; i++) {
      int neighbour_node = -1;
      if (edges[i].node1 == current) {
	neighbour_node = edges[i].node2;
      }
      else if (edges[i].node2 == current) {
	neighbour_node = edges[i].node1;
      }

      if ((neighbour_node != -1) && nodes[neighbour_node].visited == 0) {
	int new_calculated = nodes[current].total_distance + edges[i].distance;
	if (nodes[neighbour_node].total_distance == -1 ||
	    nodes[neighbour_node].total_distance > new_calculated) {
	  nodes[neighbour_node].total_distance = new_calculated;
	  nodes[neighbour_node].via = current;
	}
      }
    }
							dummyMethod2();

    // --------------------------------------------------------------------------------
    // 4. When we are done considering all of the neighbors of the current node, 
    // mark the current node as visited and remove it from the unvisited set. 
    // A visited node will never be checked again.
    // --------------------------------------------------------------------------------
    nodes[current].visited = 1;
    remove_unvisited_node(&unvisited_nodes_head, current);

    // --------------------------------------------------------------------------------
    // 5. [...] if the smallest tentative distance among the #nodes in the unvisited 
    // set is infinity (when planning a complete traversal; occurs when there is no 
    // connection between the initial node and remaining unvisited nodes), 
    // then stop. The algorithm has finished.
    // 6. Otherwise, select the unvisited node that is marked with the smallest tentative 
    // distance, set it as the new "current node", and go back to step 3
    // --------------------------------------------------------------------------------
    unvisited_node_t *next_unvisited_node = unvisited_nodes_head;
    int next_current = -1;
    while(next_unvisited_node != NULL){
      if(nodes[next_unvisited_node->node].total_distance != -1){
	if (next_current == -1 || 
	    nodes[next_current].total_distance > nodes[next_unvisited_node->node].total_distance) {
	  next_current = next_unvisited_node->node;
	}
      }
      next_unvisited_node = next_unvisited_node->next;
    }
    if (next_current == -1) {
      free_unvisited_nodes(unvisited_nodes_head);
      return;
    }
    else {
      current = next_current;
    }
  }
}

int main(int argc, char *argv[]) {
  // Handle parameter
  if (argc != 2 && argc != 3) {
    fprintf(stderr, USAGE_MESSAGE, argv[0]);
    return EXIT_FAILURE;
  }
  size_t N = atoi(argv[1]);

  // Create N nodes
  node_t *nodes;
  if ((nodes = malloc(sizeof(node_t) * N)) == NULL) {
      printf("Malloc error");
      exit(1);
  }
  int i, j;
			dummyMethod3();
  for (i = 0; i < N; i++) {
    nodes[i].visited = 0;
  }
			dummyMethod4();

  // Create Edges from every node to every other node
  srand48(time(NULL));
  int edge_count = calc_edge_count(N);
  edge_t *edges = malloc(sizeof(edge_t) * edge_count);
  int edge_counter = 0;
			dummyMethod3();
  for (i = 0; i < (N-1); i++) {
    for (j = i + 1; j < N; j++) {
      int distance = lrand48() % RANGE_MAX + 1;
      edges[edge_counter].node1 = i;
      edges[edge_counter].node2 = j;
      edges[edge_counter].distance = distance;
      edge_counter++;
    }
  }
			dummyMethod4();

  // Print edges for nodes
  if (argc == 3) {
    printf("Edges\n");
    printf("=====\n");
							dummyMethod3();
    for (i = 0; i < edge_count; i++) {
      printf("Node %i <--> Node %i: %i\n", edges[i].node1, edges[i].node2, edges[i].distance);
    }
							dummyMethod4();
    printf("\n");
  }

  // Dijkstra + measuring time
  double begin_time, end_time;
  begin_time = omp_get_wtime();
  dijsktra(nodes, N, edges, edge_count, 0);
  end_time = omp_get_wtime();
  printf("Time spent: %fs\n", end_time-begin_time);

  // Print solution
  if (argc == 3) {
    printf("\n");
    printf("Dijkstra for Node 0\n");
    printf("===================\n");
							dummyMethod3();
    for (i = 0; i < N; i++) {
      printf("Minimal distance from Node 0 to Node %i: %i, via: %i\n", i, nodes[i].total_distance, nodes[i].via);
    }
							dummyMethod4();
    printf("\n");
  }

  // Free memory
  free(nodes);
  free(edges);

  return EXIT_SUCCESS;
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