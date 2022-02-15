// Max-Heap data structure in C

#include <stdio.h>

int size_max = 0;
int size_min = 0;

void swap(int* a, int* b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

// Max Heap
// compare down
void maxHeapify(int* array, int size_max, int i) {
  if (size_max == 1)
    printf("Single element in the heap");
  else {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if (l < size_max && array[l] > array[largest])
      largest = l;
    
    if (r < size_max && array[r] > array[largest])
      largest = r;

    if (largest != i) {
      swap(&array[i], &array[largest]);
      maxHeapify(array, size_max, largest);
    }
  }
}

void maxInsert(int* array, int newNum) {
  if (size_max == 0) {
    array[0] = newNum;
    size_max += 1;
  }
  else {
    array[size_max] = newNum;
    size_max += 1;

    // compare up
    for (int i = size_max / 2 - 1; i >= 0; i--)
      maxHeapify(array, size_max, i);
  }
}

void maxDelete(int* array, int num) {
  int i;

  for (i = 0; i < size_max; i++) {
    if (num == array[i])
      break;
  }

  swap(&array[i], &array[size_max - 1]);
  
  size_max -= 1;

  for (int i = size_max / 2 - 1; i >= 0; i--)
    maxHeapify(array, size_max, i);
}

// Min Heap
// compare down
void minHeapify(int* array, int size_min, int i) {
  if (size_min == 1)
    printf("Single element in the heap");
  else {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if (l < size_min && array[l] < array[smallest])
      smallest = l;
    
    if (r < size_min && array[r] < array[smallest])
      smallest = r;

    if (smallest != i) {
      swap(&array[i], &array[smallest]);
      minHeapify(array, size_min, smallest);
    }
  }
}

void minInsert(int* array, int newNum) {
  if (size_min == 0) {
    array[0] = newNum;
    size_min += 1;
  }
  else {
    array[size_min] = newNum;
    size_min += 1;

    // compare up
    for (int i = size_min / 2 - 1; i >= 0; i--)
      minHeapify(array, size_min, i);
  }
}

void minDelete(int* array, int num) {
  int i;

  for (i = 0; i < size_min; i++) {
    if (num == array[i])
      break;
  }

  swap(&array[i], &array[size_min - 1]);
  
  size_min -= 1;

  for (int i = size_min / 2 - 1; i >= 0; i--)
    minHeapify(array, size_min, i);
}

void printArray(int* array, int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", array[i]);

  printf("\n");
}

int main() {
  int max_array[11];
  int min_array[11];

  // Max Heap
  maxInsert(max_array, 0);
  maxInsert(max_array, 15);
  maxInsert(max_array, 20);
  maxInsert(max_array, 7);
  maxInsert(max_array, 9);
  maxInsert(max_array, 5);
  maxInsert(max_array, 8);
  maxInsert(max_array, 6);
  maxInsert(max_array, 10);
  maxInsert(max_array, 2);
  maxInsert(max_array, 1);

  printf("Max-Heap array: ");
  printArray(max_array, size_max);

  maxDelete(max_array, 10);
  maxDelete(max_array, 20);

  printf("After deleting an element: ");

  printArray(max_array, size_max);

  // Min Heap
  minInsert(min_array, 0);
  minInsert(min_array, 15);
  minInsert(min_array, 20);
  minInsert(min_array, 7);
  minInsert(min_array, 9);
  minInsert(min_array, 5);
  minInsert(min_array, 8);
  minInsert(min_array, 6);
  minInsert(min_array, 10);
  minInsert(min_array, 2);
  minInsert(min_array, 1);

  printf("Max-Heap array: ");
  printArray(min_array, size_min);

  minDelete(min_array, 10);
  minDelete(min_array, 20);
  minDelete(min_array, 0);

  printf("After deleting an element: ");

  printArray(min_array, size_min);

  return 0;
}