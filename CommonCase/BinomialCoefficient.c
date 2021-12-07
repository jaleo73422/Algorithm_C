#include <stdio.h>
int sum = 0;

int BinomialCoefficient(int n, int m) {
  if(n == m) {
    return 1;
  } else if (m == 1) {
    return n;
  } else {
    sum = BinomialCoefficient(n - 1, m) + BinomialCoefficient(n - 1, m - 1);
  }

  return sum;
}

int main() {
  printf("%d \n", BinomialCoefficient(7, 3));
  printf("%d \n", BinomialCoefficient(4, 1));
  printf("%d \n", BinomialCoefficient(1, 1));
  printf("%d \n", BinomialCoefficient(5, 5));

  return 0;
}