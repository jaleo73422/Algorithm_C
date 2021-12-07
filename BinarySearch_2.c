#include <stdio.h>

// Recursive BS
int BinarySearch(int* nums, const int target, const int left, const int right) {
  if (left <= right) {
    int middle = (left + right) / 2;

    if (target < nums[middle]) {
      return BinarySearch(nums, target, left, middle - 1);
    } else if (target > nums[middle]) {
      return BinarySearch(nums, target, middle + 1, right);
    } else {
      return middle;
    }
  }
  
  return -1;
}

int main() {
  int num1[6] = {3, 5, 9, 11, 16, 21};
  int num2[] = {3, 5, 9, 11, 16, 21, 27};
  int x1 = 3;
  int x2 = 5;
  int x3 = 11;
  int x4 = 16;
  int x5 = 21;
  int x6 = 27;

  printf("%d \n", BinarySearch(num1, x1, 0, sizeof(num1) / sizeof(num1[0]) - 1));
  printf("%d \n", BinarySearch(num1, x2, 0, sizeof(num1) / sizeof(num1[0]) - 1));
  printf("%d \n", BinarySearch(num1, x3, 0, sizeof(num1) / sizeof(num1[0]) - 1));
  printf("%d \n", BinarySearch(num1, x4, 0, sizeof(num1) / sizeof(num1[0]) - 1));
  printf("%d \n", BinarySearch(num1, x5, 0, sizeof(num1) / sizeof(num1[0]) - 1));

  printf("%d \n", BinarySearch(num2, x1, 0, sizeof(num2) / sizeof(num2[0]) - 1));
  printf("%d \n", BinarySearch(num2, x2, 0, sizeof(num2) / sizeof(num2[0]) - 1));
  printf("%d \n", BinarySearch(num2, x5, 0, sizeof(num2) / sizeof(num2[0]) - 1));
  printf("%d \n", BinarySearch(num2, x6, 0, sizeof(num2) / sizeof(num2[0]) - 1));

  return 0;
}