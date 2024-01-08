#include <stdio.h>

void move(char A, char B) { printf("%c ------> %c\n", A, B); }

void Hannoi(int n, char a, char b, char c) {
  if (n == 1) {
    move(a, b);
  } else {
    Hannoi(n - 1, a, c, b);
    move(a, b);
    Hannoi(n - 1, c, b, a);
  }
}

int main(int argc, char *argv[]) {
  Hannoi(3, 'A', 'B', 'C');
  return 0;
}
