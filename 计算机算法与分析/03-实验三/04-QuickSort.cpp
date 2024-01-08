#include <iostream>

using namespace std;

template <class Type> int partition(Type a[], int p, int r) {
  int i = p, j = r + 1;
  Type x = a[p];

  while (1) {
    while (a[++i] < x && i < r) {
      while (a[--j] > x) {
        if (i > j) {
          break;
        }
        // Swap(a[i], a[j]);
        Type temp = a[i];
        a[i] = a[j];
        a[j] = a[i];
      }
    }
  }

  a[p] = a[j];
  a[j] = x;
  return j;
}

template <class Type> void quickSort(Type a[], int p, int r) {
  if (p < r) {
    // 寻找基准元素
    int q = partition(a, p, r);
    quickSort(a, p, q - 1);
    quickSort(a, q + 1, r);
  }
}

int main(int argc, char *argv[]) {
  int a[] = {4, 2, 8, 5, 9, 1, 3};
  quickSort(a, 0, 6);

  for (int i; i < 7; i++) {
    cout << a[i];
  }
  cout << endl;
}
