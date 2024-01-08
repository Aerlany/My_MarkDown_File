#include <math.h>
#include <stdio.h>
#define N 50
int a[N][N];

void Table(int k);
void print(int k); // 输出二维数组
void Table(int k)  // 数组下标从1开始
{
  int i, j, s, t;
  int n = 1;
  for (i = 1; i <= k; i++)
    n *= 2; // 求总人数n
  for (i = 1; i <= n; i++)
    a[1][i] = i; // 初始化第一行排

  int m = 1; // 用来控制每一次填表时i行j列的起始填充位置
  for (s = 1; s <= k; s++) {
    n = n / 2;
    for (t = 1; t <= n; t++) // t指明内部对称赋值的循环次数
      for (i = m + 1; i <= 2 * m; i++)
        for (j = m + 1; j <= 2 * m; j++) {
          a[i][j + (t - 1) * m * 2] = a[i - m][j + (t - 1) * m * 2 - m];
          a[i][j + (t - 1) * m * 2 - m] = a[i - m][j + (t - 1) * m * 2];
        }
    m *= 2;
  }
}
void print(int k) {
  int i, j;
  int num = pow(2, k);
  for (i = 1; i <= num; i++) {
    for (j = 1; j <= num; j++) {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}
int main() {
  int k;
  printf("请输入k 的值：");
  scanf("%d", &k);
  printf("\n");
  Table(k);
  print(k);
  return 0;
}
