#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char **argv) {
  float *f;
  char *cptr;

  struct foo {
    short f1;
    int t2;
    char t3;
  } __attribute__((packed));

#if defined(__GNUC__)
# if defined(__i386__)
  /* Enable Alignment Checking on x86 */
  __asm__("pushf\norl $0x40000,(%esp)\npopf");
# elif defined(__x86_64__) 
  /* Enable Alignment Checking on x86_64 */
  __asm__("pushf\norl $0x40000,(%rsp)\npopf");
# endif
#endif

  /* malloc() always provides aligned memory */
  cptr = malloc(sizeof(float) + 1);
 
  /* Increment the pointer by one, making it misaligned */
  //f = (float*)++cptr;
 
  /* Dereference it as an int pointer, causing an unaligned access */
  *f = 2.222;
  
  printf("%d", sizeof(struct foo));
  struct foo st;
  //st.t2 = 10;

  return 0;
}
