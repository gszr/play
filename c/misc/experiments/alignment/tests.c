#include <stdio.h>
#include <stdlib.h>

struct  _st {
  char ch;
  char ch2;
  int nn;
  short sh;
} st;

struct _st2 {
  int n;
  short sh;
  char c1;
  char c2;
}st2;

int main() {
  int nm = 10;
  int *nm_p;

  printf("%x\n", &nm);

  scanf("%x", nm_p);

  printf("\n%d", nm_p);
}
