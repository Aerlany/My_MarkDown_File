#include <stdio.h>
int main(int argc, char *argv[]) {
  int n;
  printf("Input a number for n:");
  scanf("%d", &n);

  int result = 1;
  for (int i = 1; i <= n; i++) {
    result *= i;
  }

  printf("%d的阶乘是%d\n", n, result);
}
