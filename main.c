#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTACKSIZE 10

typedef struct {
  int v;
  int w;
} Edge;

Edge EDGE(int v, int w) {
  Edge e = {v, w};
  return e;
}

typedef struct {
  int V;
  int E;
  int **adj;
} Graph ;

int **MATRIXint(int n, int m, int val) {
  int i, j;
  int **M = malloc(n * sizeof(int *));
  for (i = 0; i < n; i++) {
    M[i] = malloc(m * sizeof(int));
    for (j = 0; j < m; j++)
      M[i][j] = val;
  }
  return M;
}


Graph *GRAPHinit(int V) {
  Graph *G = malloc(sizeof(Graph));
  G->V = V;
  G->E = 0;
  G->adj = MATRIXint(V, V, 0);
  return G;
}

void GRAPHinsertE(Graph *G, Edge e) {
  int v = e.v;
  int w = e.w;
  if (G->adj[v][w] == 0)
    G->E++;
  G->adj[v][w] = 1;
  G->adj[w][v] = 1;
}

void GRAPHremoveE(Graph *G, Edge e) {
  int v = e.v;
  int w = e.w;
  if (G->adj[v][w] == 1)
    G->E--;
  G->adj[v][w] = 0;
  G->adj[w][v] = 0;
}

int GRAPHedges(Edge a[], Graph *G) {
  int v, w, E = 0;
  for (v = 0; v < G->V; v++)
    for (w = v + 1; w < G->V; w++)
      if (G->adj[v][w] == 1)
        a[E++] = EDGE(v, w);
  return E;
}

// Placeholder for GRAPHdestroy and GRAPHcopy implementations
void GRAPHdestroy(Graph *G) {
  // Implementation needed
  if (G != NULL)
  {
    if(G->adj != NULL)
    {
      for (int i = 0; i< G->V; i++)
      {
	free(G->adj[i]);
      }
      free(G->adj);
    }

  free(G);
  }
}

Graph *GRAPHcopy(Graph *G) {
  // Implementation needed
  return NULL;
}

void GraphShowAdjMatrix(Graph *G) {
  int v, w;
  printf("  ");
  for(int i = 0; i <= G->V - 1; i++)
    printf(" %d ", i);
  printf("\n");
  for(int i = 0; i <= G->V - 1; i++)
    printf("----",i);
  printf("\n%d|", 0);
  for(int v = 0; v <= G->V - 1; v++){
    for(int w = 0; w <= G->V - 1; w++){
      printf(" %d ", G->adj[v][w]);
    }
    printf("\n%d|", v+1);
  }
}

void DFS_recursive(Graph *G, int i, int *visited)
{
  visited[i] = 1;
  for(int w=0; w < G->V; w++)
  {
    if(!visited[w] && G->adj[i][w] == 1)
      DFS_recursive(G, w, visited);
  }
}

typedef struct
{
  int top;
  int elements[MAXSTACKSIZE];
} stack;

stack *initstack(int size)
{
  stack *newstack = (stack *)malloc(sizeof(stack));
  if(newstack == NULL)
    return NULL;
  
  newstack->top = -1;
  return newstack;
}

int push(stack *stackvar, int i)
{
  if(stackvar->top < MAXSTACKSIZE - 1)
  {
    stackvar->top = stackvar->top + 1;
    stackvar->elements[stackvar->top] = i;
    printf("pushed element: %d\n", stackvar->elements[stackvar->top]);
    return 0;
  }
  else
  {
    printf("Stack overflow\n");
    return -1;
  }
}


int pop(stack *stackvar)
{
  if(stackvar->top >= 0)
  {
    int poppedelement = stackvar->elements[stackvar->top];
    printf("popped element: %d\n", stackvar->elements[stackvar->top]); 
    stackvar->elements[stackvar->top] = 0;
    stackvar->top = stackvar->top - 1;
    return poppedelement;
  }
  else
  {
    printf("Stack underflow\n");
    return -1;
  }
}


void DFS_stack(Graph *G, int v, int *visited)
{
  stack *newstack = initstack(G->V);
  push(newstack, v);
  while(newstack->top >= 0)
  {
    int v = pop(newstack);
    if(!visited[v])
    {
      visited[v] = 1;
      for(int w = 0; w < G->V; w++)
	{
	  if(G->adj[v][w] == 1 && !visited[w])
	  {
	    push(newstack, w);
	  }
	}
    }
  }
  free(newstack);
}

int main(void)
{
  Graph *G = GRAPHinit(3);
  printf("G->V: %d\n", G->V);
  Edge edge01 = EDGE(0,1);
  GRAPHinsertE(G, edge01);
  Edge edge12 = EDGE(1,2);
  GRAPHinsertE(G, edge12);
  printf("G->E: %d\n", G->E);
  GraphShowAdjMatrix(G);

  int visited[G->V];
  for(int i=0; i < G->V; i++)
    visited[i] = 0;
  DFS_recursive(G, 0, visited);
  for(int i=0; i < G->V; i++)
    printf("\n vertex %d: %d\n",i, visited[i]);

  for(int i=0; i < G->V; i++)
    visited[i] = 0;
  
  DFS_stack(G, 0, visited);
  GRAPHdestroy(G);
}


