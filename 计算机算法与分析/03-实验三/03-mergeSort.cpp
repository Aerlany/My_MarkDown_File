#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &nums, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  vector<int> left_nums(n1);
  vector<int> right_nums(n2);

  // 新数组赋值（对半分）
  for (int i = 0; i < n1; i++) {
    left_nums[i] = nums[left + i];
  }
  for (int i = 0; i < n2; i++) {
    right_nums[i] = nums[mid + 1 + i];
  }

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (left_nums[i] <= right_nums[j]) {
      nums[k] = left_nums[i];
      i++;
    } else {
      nums[k] = right_nums[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    nums[k] = left_nums[i];
    i++;
    k++;
  }

  while (j < n2) {
    nums[k] = right_nums[j];
    j++;
    k++;
  }
}

void mergeSort(vector<int> &nums, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);
  }
}

int main() {
  vector<int> nums = {5, 1, 4, 2, 8, 6, 7, 3};
  int n = nums.size();

  mergeSort(nums, 0, n - 1);

  for (int i = 0; i < n; i++) {
    cout << nums[i] << " ";
  }
  cout << endl;

  return 0;
}
