#include <stdio.h>
int main(int argc, char *argv[]) {
  int n;
  printf("Input a number for n:");
  scanf("%d", &n);

  int buffer[1024];

  for (int i = 0; i < n; i++) {
    if (i == 0) {
      buffer[i] = 1;
    } else if (i == 1) {
      buffer[i] = 1;
    } else {
      buffer[i] = buffer[i - 1] + buffer[i - 2];
    }
  }

  printf("Fibonacci数列：\n");
  for (int j = 0; j < n; j++) {
    printf("第%d项：%d\n", j, buffer[j]);
  }
}
