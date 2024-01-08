#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 1000 // 背包的最大承重

typedef struct Item {
  int weight; // 物品的重量
  int value;  // 物品的价值
} Item;

int compare(const void *a, const void *b) {
  Item *itemA = (Item *)a;
  Item *itemB = (Item *)b;
  double ratioA = (double)itemA->value / itemA->weight;
  double ratioB = (double)itemB->value / itemB->weight;
  if (ratioA > ratioB) {
    return -1; // 按照单位价值从大到小排序
  } else if (ratioA < ratioB) {
    return 1;
  } else {
    return 0;
  }
}

int knapsack(Item *items, int n, int max_weight) {
  qsort(items, n, sizeof(Item), compare); // 按照单位价值从大到小排序
  int total_value = 0;
  int remaining_weight = max_weight;
  for (int i = 0; i < n; i++) {
    if (remaining_weight >= items[i].weight) {
      total_value += items[i].value;
      remaining_weight -= items[i].weight;
    } else {
      total_value +=
          (double)remaining_weight / items[i].weight * items[i].value;
      break;
    }
  }
  return total_value;
}

int main() {
  int n; // 物品的个数
  scanf("%d", &n);
  Item *items = (Item *)malloc(n * sizeof(Item));
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &items[i].weight, &items[i].value);
  }
  printf("%d\n", knapsack(items, n, MAX_WEIGHT));
  free(items);
  return 0;
}
