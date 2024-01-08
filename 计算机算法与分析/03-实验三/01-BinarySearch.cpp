#include <iostream>
#include <stdio.h>
using namespace std;

template <class Type> int BinarySearch(Type arrary[], const Type x, int n) {
  int left = 0;
  int right = n - 1;

  while (left <= right) {
    int middle = (left + right) / 2;
    if (x == arrary[middle]) {
      return middle;
    } else if (x > arrary[middle]) {
      left = middle + 1;
    } else {
      right = middle - 1;
    }
  }

  return -1;
}

int main(int argc, char *argv[]) {
  int arrary[] = {1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 21, 23, 33, 45, 67};

  printf("%d找到了在数组索引%d\n", 8,
         BinarySearch(arrary, 8, sizeof(arrary) / sizeof(arrary[0])));

  return 0;
}
