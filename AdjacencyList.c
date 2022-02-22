#include <stdio.h>
#include <stdlib.h>

struct node {
  int vertex;
  struct node* next;
};

// struct node* createNode(int);

struct Graph {
  int numVertices;
  struct node** adjLists;
};

// create a node
struct node* createNode(int v) {
  struct node* newNode = (struct node*) malloc(sizeof(struct node));
  
  newNode->vertex = v;
  newNode->next = NULL;

  return newNode;
}

// create a graph
struct Graph* createAGraph(int vertices) {
  struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
  
  graph->numVertices = vertices;
  graph->adjLists = (struct node**) malloc(vertices * sizeof(struct node*));

  for (int i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL;

  return graph;
}

// add edge
void addEdge(struct Graph* graph, int s, int d) {
  // add edge from s to d
  struct node* newNode = createNode(d);
  
  newNode->next = graph->adjLists[s];
  graph->adjLists[s] = newNode;

  // add edge from d to s
  newNode = createNode(s);
  newNode->next = graph->adjLists[d];
  graph->adjLists[d] = newNode;
}

// print the graph
void printGraph(struct Graph* graph) {
  for (int v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjLists[v];
    
    printf("\n Vertex %d : ", v);
    
    while (temp) {
      printf("%d -> ", temp->vertex);
      
      temp = temp->next;
    }
    
    printf("\n");
  }
}

int main() {
  struct Graph* graph = createAGraph(4);
  
  /*
  1 -> NULL
  0 -> NULL
  NULL
  NULL
   */
  addEdge(graph, 0, 1);
  /*
  2 -> 1 -> NULL
  0 -> NULL
  0 -> NULL
  NULL
   */
  addEdge(graph, 0, 2);
  /*
  3 -> 2 -> 1 -> NULL
  0 -> NULL
  0 -> NULL
  0 -> NULL
   */
  addEdge(graph, 0, 3);
  /*
  3 -> 2 -> 1 -> NULL
  2 -> 0 -> NULL
  1 -> 0 -> NULL
  0 -> NULL
   */
  addEdge(graph, 1, 2);

  printGraph(graph);

  return 0;
}