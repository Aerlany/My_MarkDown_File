#include <stdio.h>
#include <string.h>

void lcs(char *x, char *y) {
  int m = strlen(x);
  int n = strlen(y);
  int c[m + 1][n + 1];
  int i, j;
  for (i = 0; i <= m; i++) {
    for (j = 0; j <= n; j++) {
      if (i == 0 || j == 0) {
        c[i][j] = 0;
      } else if (x[i - 1] == y[j - 1]) {
        c[i][j] = c[i - 1][j - 1] + 1;
      } else {
        c[i][j] = (c[i - 1][j] > c[i][j - 1]) ? c[i - 1][j] : c[i][j - 1];
      }
    }
  }
  int index = c[m][n];
  char result[index + 1];
  result[index] = '\0';
  i = m;
  j = n;
  while (i > 0 && j > 0) {
    if (x[i - 1] == y[j - 1]) {
      result[index - 1] = x[i - 1];
      i--;
      j--;
      index--;
    } else if (c[i - 1][j] > c[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }
  printf("The longest common subsequence is: %s\n", result);
}

int main() {
  char x[100], y[100];
  printf("Enter the first sequence: ");
  scanf("%s", x);
  printf("Enter the second sequence: ");
  scanf("%s", y);
  lcs(x, y);
  return 0;
}
