#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define V 5 // 图的顶点数

int graph[V][V] = { // 用邻接矩阵存储图
    {0, 2, 0, 6, 0},
    {2, 0, 3, 8, 5},
    {0, 3, 0, 0, 7},
    {6, 8, 0, 0, 9},
    {0, 5, 7, 9, 0}};

int findMinKey(int key[], int visited[]) {
  int min = INT_MAX, min_index;
  for (int v = 0; v < V; v++) {
    if (visited[v] == 0 && key[v] < min) {
      min = key[v];
      min_index = v;
    }
  }
  return min_index;
}

void printMST(int parent[], int n) {
  printf("边\t权值\n");
  for (int i = 1; i < V; i++) {
    printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
  }
}

void primMST() {
  int parent[V];
  int key[V];
  int visited[V];

  for (int i = 0; i < V; i++) {
    key[i] = INT_MAX;
    visited[i] = 0;
  }

  key[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < V - 1; count++) {
    int u = findMinKey(key, visited);
    visited[u] = 1;
    for (int v = 0; v < V; v++) {
      if (graph[u][v] && visited[v] == 0 && graph[u][v] < key[v]) {
        parent[v] = u;
        key[v] = graph[u][v];
      }
    }
  }

  printMST(parent, V);
}

int main() {
  primMST();
  return 0;
}
