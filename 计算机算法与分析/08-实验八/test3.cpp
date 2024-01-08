// 图着色问题回溯法
/*
无向图邻接矩阵示例
0 1 1 0 0
0 1 1 0 1
1 1 0 0 1
0 1 0 0 1
0 1 1 1 0
*/
#include <stdio.h>

int color[100];
// int c[100][100];
bool ok(int k, int c[][100]) // 判断顶点k的着色是否发生冲突
{
  int i, j;
  for (i = 1; i < k; i++)
    if (c[k][i] == 1 && color[i] == color[k])
      return false;
  return true;
}

void graphcolor(int n, int m, int c[][100]) {
  int i, k;
  for (i = 1; i <= n; i++)
    color[i] = 0; // 初始化
  k = 1;
  while (k >= 1) {
    color[k] = color[k] + 1;
    while (color[k] <= m)
      if (ok(k, c))
        break;
      else
        color[k] = color[k] + 1; // 搜索下一个颜色

    if (color[k] <= m && k == n) // 求解完毕，输出解
    {
      for (i = 1; i <= n; i++)
        printf("%d ", color[i]);
      printf("\n");
      // return;//return表示之求解其中一种解
    } else if (color[k] <= m && k < n)
      k = k + 1; // 处理下一个顶点
    else {
      color[k] = 0;
      k = k - 1; // 回溯
    }
  }
}
int main() {
  int i, j, n, m;
  int c[100][100]; // 存储n个顶点的无向图的数组
  printf("输入顶点数n和着色数m:\n");
  scanf("%d %d", &n, &m);
  printf("输入无向图的邻接矩阵:\n");
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      scanf("%d", &c[i][j]);
  printf("着色所有可能的解:\n");
  graphcolor(n, m, c);
}
