#include <stdio.h>

int BinarySearch(int* nums, const int target, const int numsSize) {
  int left = 0;
  int right = numsSize - 1;

  while (left <= right) {
    int middle = (left + right) / 2;

    if (target < nums[middle]) {
      right = middle - 1;
    } else if (target > nums[middle]) {
      left = middle + 1;
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

  printf("%d \n", BinarySearch(num1, x1, sizeof(num1) / sizeof(num1[0])));
  printf("%d \n", BinarySearch(num1, x2, sizeof(num1) / sizeof(num1[0])));
  printf("%d \n", BinarySearch(num1, x3, sizeof(num1) / sizeof(num1[0])));
  printf("%d \n", BinarySearch(num1, x4, sizeof(num1) / sizeof(num1[0])));
  printf("%d \n", BinarySearch(num1, x5, sizeof(num1) / sizeof(num1[0])));

  printf("%d \n", BinarySearch(num2, x1, sizeof(num2) / sizeof(num2[0])));
  printf("%d \n", BinarySearch(num2, x2, sizeof(num2) / sizeof(num2[0])));
  printf("%d \n", BinarySearch(num2, x5, sizeof(num2) / sizeof(num2[0])));
  printf("%d \n", BinarySearch(num2, x6, sizeof(num2) / sizeof(num2[0])));

  return 0;
}