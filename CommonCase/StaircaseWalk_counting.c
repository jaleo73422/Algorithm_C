#include <stdio.h>

// one array
int main() {
  int row = 8;
  int column = 8;
  int step[row];

  for (int n1 = 0; n1 < row; n1 ++) {
    step[n1] = 1;
  }

  for (int n2 = 1; n2 < column; n2++) {
    for (int n3 = 1; n3 < row; n3++) {
      step[n3] = step[n3] + step[n3 - 1];
    }

  }

  printf("%d \n", step[row - 1]);

  return 0;
}