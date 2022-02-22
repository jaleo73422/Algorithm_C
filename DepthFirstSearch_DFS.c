#include <stdio.h>
#include <stdlib.h>

struct node {
  int vertex;
  struct node* next;
};

struct node* createNode(int v);

struct Graph {
  int numVertices;
  int* visited;

  // We need int** to store a two dimensional array.
  // Similary, we need struct node** to store an array of Linked lists.
  struct node** adjLists;
};

// DFS algo
void DFS(struct Graph* graph, int vertex) {
  struct node* adjList = graph->adjLists[vertex];
  struct node* temp = adjList;

  graph->visited[vertex] = 1;
  
  printf("Visited %d \n", vertex);

  while (temp != NULL) {
    int connectedVertex = temp->vertex;

    if(graph->visited[connectedVertex] == 0) {
      DFS(graph, connectedVertex);
    }
    
    temp = temp->next;
  }
}

// create a node
struct node* createNode(int v) {
  struct node* newNode = (struct node*) malloc(sizeof(struct node));
  
  newNode->vertex = v;
  newNode->next = NULL;

  return newNode;
}

// create graph
struct Graph* createGraph(int vertices) {
  struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
  
  graph->numVertices = vertices;

  graph->adjLists = (struct node**) malloc(vertices * sizeof(struct node*));
  graph->visited = (int*) malloc(vertices * sizeof(int));

  for(int i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }

  return graph;
}

// add edge
void addEdge(struct Graph* graph, int src, int dest) {
  // add edge from src to dest
  struct node* newNode = createNode(dest);
  
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  // add edge from dest to src
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

// print the graph
void printGraph(struct Graph* graph) {
  for(int v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjLists[v];
    
    printf("Adjacency list of vertex %d: ", v);
    
    while(temp) {
      printf("%d -> ", temp->vertex);
      
      temp = temp->next;
    }

    printf("\n");
  }
}

int main() {
  struct Graph* graph = createGraph(4);
  
  addEdge(graph, 0, 1);
  addEdge(graph, 0, 2);
  addEdge(graph, 1, 2);
  addEdge(graph, 2, 3);

  printGraph(graph);

  DFS(graph, 2);

  return 0;
}