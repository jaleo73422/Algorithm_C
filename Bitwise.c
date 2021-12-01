#include <stdio.h>
#include <limits.h>

// Number of 1 Bits
int count_1_bit(unsigned int n) { 
  unsigned int count = 0; 
  while(n) 
  { 
    count += n & 1; 
    n >>= 1; 
  } 
  return count; 
}

// Bit Reversal
unsigned int bit_reverse_1(unsigned int num)
{
  unsigned int  NO_OF_BITS = sizeof(num) * 8;
  unsigned int reverse_num = 0, i, temp;

  for (i = 0; i < NO_OF_BITS; i++)
  { 
    // Decide whether the digit is 1
    temp = (num & (1 << i));

    // If yes, reverrse it
    // non-zero(False) is equal to 1(True)
    if(temp) {
      reverse_num |= (1 << ((NO_OF_BITS - 1) - i));
    }
  }
  
  return reverse_num;
}

unsigned int bit_reverse_2(unsigned int num)
{
  unsigned int  NO_OF_BITS = sizeof(num) * 8;
  unsigned int reverse_num = 0;
  int i;

  for (i = 0; i < NO_OF_BITS; i++)
  {
    if((num & (1 << i)))
      reverse_num |= 1 << ((NO_OF_BITS - 1) - i);  
  }
  
  return reverse_num;
}

// Least Significant 1 Bit
int least_significant_1_bit(int x)
{
  return x & -x;
}

// Power of 2 Test
bool is_power_of_2(int x)
{
  return !(x & (x-1));
}

// XOR Swap
void swap(int& x, int& y)
{
  x = x ^ y;
  y = x ^ y;
  x = x ^ y;
}

// Missing Number Problem

// Nim

// Josephus Problem

// Letter Case Conversion
int tolower(int c)
{
  return (c >= 'A' && c <= 'Z') ? c ^ 32 : c;
}
 
int toupper(int c)
{
  return (c >= 'a' && c <= 'z') ? c ^ 32 : c;
}

// 8 Queen Problem

int main() {
  unsigned int n1 = 1;
  int n2 = 28;
  int n3 = 32;
  int n4 = 10;
  int n5 = 20;

  // Number of 1 Bits
  printf("==Number of 1 Bits== \n");
  printf("%d. \n", count_1_bit(1));
  printf("%d. \n", count_1_bit(-1));

  // Bit Reversal
  printf("==Bit Reversal== \n");
  printf("%u \n", bit_reverse_1(n1));
  printf("%u \n", bit_reverse_2(n1));
  printf("maximum in c: %d \n", INT_MAX);

  // Least Significant 1 Bit
  printf("==Least Significant 1 Bit== \n");
  printf("%d \n", least_significant_1_bit(n2));

  // Power of 2 Test
  printf("==Power of 2 Test== \n");
  printf("%d \n", is_power_of_2(n2));
  printf("%d \n", is_power_of_2(n3));

  // XOR Swap
  printf("==XOR Swap== \n");
  swap(n4, n5);
  printf("%d %d\n", n4, n5);

  // Missing Number Problem

  // Nim

  // Josephus Problem

  // Letter Case Conversion
  printf("==Letter Case Conversion== \n");
  printf("%c \n", tolower('A'));
  printf("%c \n", toupper('a'));

  // 8 Queen Problem

  return 0;
}