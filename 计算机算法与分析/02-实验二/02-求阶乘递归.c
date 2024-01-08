#include <stdio.h>

int factorial(int n) {
  if (n <= 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}

int main(int argc, char *argv[]) {
  int n;
  printf("Input a number for n:");
  scanf("%d", &n);

  int result = factorial(n);

  printf("%d的阶乘是%d\n", n, result);
}
