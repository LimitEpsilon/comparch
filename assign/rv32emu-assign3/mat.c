#ifdef NATIVE
#include <stdio.h>
#endif // NATIVE

#ifndef MAT_ORDER
// Default MAT_ORDER is 4
#define MAT_ORDER 4
#endif

#ifdef NATIVE
void print_newline() {
  printf("\n");
}
void print_num(unsigned num) {
  printf("%d ", num);
}
#else
void print_newline() {
  volatile char* tx = (volatile char*) 0x40002000;
  *tx = '\n';
}

// Modified from https://www.geeksforgeeks.org/implement-itoa/
void print_num(unsigned num) {
  volatile char* tx = (volatile char*) 0x40002000;
  char str[100];
  int i = 0;
  int length;

  if (num == 0) {
    str[i++] = '0';
  } else {
    while (num != 0) {
      int rem = num % 10;
      str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
      num = num/10;
    }
  }
  length = i-1;

  for (i=length; i>=0; i--) {
    *tx = str[i];
  }
  *tx = ' ';
}
#endif // NATIVE

#ifdef ROW_MAJOR
#define MAT(M,i,j) M[i][j]
#else
#define MAT(M,i,j) M[j][i]
#endif

#ifdef NATIVE
int main(void) {
#else
void _start() {
#endif
  static unsigned A[MAT_ORDER][MAT_ORDER];
  static unsigned B[MAT_ORDER][MAT_ORDER];
  unsigned C[MAT_ORDER][MAT_ORDER];

  unsigned sum = 0;
  unsigned i,j,k;

  // Populate Matrix A and B
  for (i = 0; i < MAT_ORDER; i++)
    for (j = 0; j < MAT_ORDER; j++)
      MAT(A,i,j) = i+j;

  for (i = 0; i < MAT_ORDER; i++)
    for (j = 0; j < MAT_ORDER; j++)
      MAT(B,i,j) = i*j;

  // Matrix multiplication: C = A * B
  for (i = 0; i < MAT_ORDER; i++) {
    for (j = 0; j < MAT_ORDER; j++) {
      for (k = 0; k < MAT_ORDER; k++) {
#ifdef ROW_MAJOR
        sum = sum + A[i][k]*B[k][j];
#else
        sum = sum + A[j][k]*B[k][i];
#endif
      }
      MAT(C,i,j) = sum;
      sum = 0;
    }
  }

  // Print the result
  for (i = 0; i < MAT_ORDER; i++) {
    for (j = 0; j < MAT_ORDER; j++) {
      print_num(C[i][j]);
    }
    print_newline();
  }
#ifdef NATIVE
  return 0;
#endif
}
