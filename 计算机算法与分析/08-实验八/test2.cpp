// 圆排列问题 回溯法求解
#include "stdafx.h"
#include <cmath>
#include <iostream>
using namespace std;

float CirclePerm(int n, float *a);

template <class Type> inline void Swap(Type &a, Type &b);

int main() {
  float *a = new float[4];
  a[1] = 1, a[2] = 1, a[3] = 2;
  cout << "圆排列中各圆的半径分别为：" << endl;
  for (int i = 1; i < 4; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
  cout << "最小圆排列长度为：";
  cout << CirclePerm(3, a) << endl;
  return 0;
}

class Circle {
  friend float CirclePerm(int, float *);

private:
  float Center(int t); // 计算当前所选择的圆在当前圆排列中圆心的横坐标
  void Compute(); // 计算当前圆排列的长度
  void Backtrack(int t);

  float min, // 当前最优值
      *x,    // 当前圆排列圆心横坐标
      *r;    // 当前圆排列
  int n;     // 圆排列中圆的个数
};

// 计算当前所选择圆的圆心横坐标
float Circle::Center(int t) {
  float temp = 0;
  for (int j = 1; j < t; j++) {
    // 由x^2 = sqrt((r1+r2)^2-(r1-r2)^2)推导而来
    float valuex = x[j] + 2.0 * sqrt(r[t] * r[j]);
    if (valuex > temp) {
      temp = valuex;
    }
  }
  return temp;
}

// 计算当前圆排列的长度
void Circle::Compute(void) {
  float low = 0, high = 0;
  for (int i = 1; i <= n; i++) {
    if (x[i] - r[i] < low) {
      low = x[i] - r[i];
    }

    if (x[i] + r[i] > high) {
      high = x[i] + r[i];
    }
  }
  if (high - low < min) {
    min = high - low;
  }
}

void Circle::Backtrack(int t) {
  if (t > n) {
    Compute();
  } else {
    for (int j = t; j <= n; j++) {
      Swap(r[t], r[j]);
      float centerx = Center(t);
      if (centerx + r[t] + r[1] < min) // 下界约束
      {
        x[t] = centerx;
        Backtrack(t + 1);
      }
      Swap(r[t], r[j]);
    }
  }
}

float CirclePerm(int n, float *a) {
  Circle X;
  X.n = n;
  X.r = a;
  X.min = 100000;
  float *x = new float[n + 1];
  X.x = x;
  X.Backtrack(1);
  delete[] x;
  return X.min;
}

template <class Type> inline void Swap(Type &a, Type &b) {
  Type temp = a;
  a = b;
  b = temp;
}
