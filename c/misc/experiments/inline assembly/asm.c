#include <stdio.h>

int move() {
  int a = 5;
  int b;
  
  asm("movl %1, %%eax; \
       mov %%eax, %0;"
      : "=r" (b)
      : "r" (a)
      : "%eax"
      );
  
  printf("%d %d", a, b);
  
}

int main() {
	int num = 5;
	int mult = num * num;

	//asm("leal (%1,%1,4), %0":"=r"(mult):"r"(num));

	printf("Num: %d\nResult: %d", num, mult);

	return 0;
}
