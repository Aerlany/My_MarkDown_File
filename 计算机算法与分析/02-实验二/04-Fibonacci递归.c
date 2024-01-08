#include <stdio.h>

int Fibonacci(int n) {
  if (n == 0 || n == 1) {
    return 1;
  }
  return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
  int n;
  printf("Input a number for n:");
  scanf("%d", &n);

  int result = Fibonacci(n);
  printf("Fibonacci数列第%d项：%d\n", n, result);
}
