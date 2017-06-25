#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char **argv) {
  int *iptr;
  char *cptr;


#if defined(__GNUC__)
# if defined(__i386__)
  __asm__("pushf\norl $0x40000,(%esp)\npopf");
# elif defined(__x86_64__) 
  __asm__("pushf\norl $0x40000,(%rsp)\npopf");
# endif
#endif

  cptr = malloc(sizeof(int) + 1);
 
  iptr = (int *) ++cptr;
 
  *iptr = 42;
  
  printf("%d\n", *iptr);
 
  return 0;
}
