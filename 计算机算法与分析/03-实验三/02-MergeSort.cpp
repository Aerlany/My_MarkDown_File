#include <cstdio>
#include <iostream>
using namespace std;

/*
 *合并排序
 *先将数组a相邻元素两两配对
 *用合并算法进行排序构成n/2组长度为2的排好序的子数组段
 * 再将其排序成长度为4的数组段
 *
合并排序（Merge Sort）是一种经典的排序算法，采用分治策略（Divide and
Conquer）进行排序。它的基本思想是将待排序的序列划分为若干个子序列，每个子序列都是有序的，然后将这些有序的子序列合并成一个有序的序列。

合并排序的具体实现可以分为以下三个步骤：

分割：将待排序的序列递归地分成两个子序列，直到子序列的长度为1或0为止。

归并：将已经排好序的子序列进行归并，即将两个有序的子序列合并成一个有序的序列。这里使用了两个指针，分别指向待归并的两个子序列，每次比较两个指针所指向的元素的大小，将较小的元素放入一个新的序列中，并将对应的指针向后移动。

合并：将两个有序的子序列合并成一个有序的序列。

 */

template <class Type> void Merge(Type c[], Type d[], int l, int m, int r) {
  int i = l, j = m + 1, k = 1;
  while ((i <= m) && (j <= r)) {
    if (c[i] <= c[j]) {
      d[k++] = c[i++];
    } else {
      d[k++] = c[j++];
    }
    if (i > m) {
      for (int q = j; q <= r; q++) {
        d[k++] = c[q];
      }
    } else {
      for (int q = i; q <= m; q++) {
        d[k++] = c[q];
      }
    }
  }
}

template <class Type> void MergePass(Type x[], Type y[], int s, int n) {
  int i = 0;
  while (i <= n - 2 * s) {
    Merge(x, y, i, i + s - 1, i + 2 * s - 1);
    i = i + 2 * s;
  }
  if (i + s < n) {
    Merge(x, y, i, i + s - 1, n - 1);
  } else {
    for (int j = i; j <= n - 1; j++) {
      y[j] = x[j];
    }
  }
}

template <class Type> void MergeSort(Type a[], int n) {
  // Type *b = new Type[n];
  Type b[n];
  int s = 1;
  while (s < n) {
    MergePass(a, b, s, n); // 合并到数组b
    s += s;
    MergePass(b, a, s, n); // 合并到数组a
    s += s;
  }
}

int main(int argc, char *argv[]) {
  int array[] = {2, 34, 35, 66, 1, 32, 23, 10};

  for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
    printf("%d\t", array[i]);
  }
  cout << endl;

  MergeSort(array, 8);

  for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
    printf("%d\t", array[i]);
  }
  cout << endl;
}
