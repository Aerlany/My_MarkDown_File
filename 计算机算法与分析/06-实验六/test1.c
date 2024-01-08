#include <stdio.h>
#include <stdlib.h>

// 活动结构体
typedef struct activity {
  int start_time;
  int end_time;
} Activity;

// 活动按结束时间从早到晚排序
int cmp(const void *a, const void *b) {
  Activity *activity1 = (Activity *)a;
  Activity *activity2 = (Activity *)b;
  return activity1->end_time - activity2->end_time;
}

// 活动安排函数
void activity_schedule(Activity activities[], int n) {
  // 按结束时间排序
  qsort(activities, n, sizeof(Activity), cmp);

  // 记录安排的活动数量
  int count = 1;

  // 记录上一个安排的活动的结束时间
  int last_end_time = activities[0].end_time;

  // 从第二个活动开始依次进行安排
  for (int i = 1; i < n; i++) {
    // 如果当前活动的开始时间晚于上一个活动的结束时间，说明可以安排
    if (activities[i].start_time >= last_end_time) {
      count++;
      last_end_time = activities[i].end_time;
    }
  }

  // 输出安排的活动数量
  printf("The maximum number of activities that can be scheduled is %d.\n",
         count);
}

int main() {
  // 活动列表
  Activity activities[] = {{1, 3}, {2, 5},  {3, 7}, {4, 8},
                           {5, 9}, {6, 10}, {8, 11}};
  int n = sizeof(activities) / sizeof(Activity);

  activity_schedule(activities, n);

  return 0;
}
