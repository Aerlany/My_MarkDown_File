#include <math.h>
#include <stdio.h>

int main() {
  double y;                      /*纵坐标y*/
  int x, m;                      /*横坐标x*/
  for (y = 1; y >= -1; y -= 0.1) /*纵轴y从1~-1，步长为0.1*/
  {
    m = acos(y) *
        10; /*利用math.h中的反余弦函数，求对应横坐标的值，此时m为int型变量*/
    for (x = 1; x < m; x++) /*开始逐行打点*/
      printf(" ");          /*在曲线定点右侧，打印空格*/
    printf("*");            /*第一个曲线定点打印“*”*/
    for (; x < 62 - m; x++) /*开始打印对称曲线定点，由于对称性x的终值为62-m*/
      printf(" "); /*在两定点之间打印空格*/
    printf("*\n"); /*第二个曲线定点打印“*”，并换行*/
  }
  return 0;
}
