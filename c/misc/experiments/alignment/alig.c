#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static void memset_16aligned(void *space, char byte, size_t nbytes)
{
  assert((nbytes & 0x0F) == 0);
  assert(((uintptr_t)space & 0x0F) == 0);
}

int main(void)
{
  void *mem = malloc(1024+15);
  void *ptr = (void *)(((uintptr_t)mem+15) & ~ 0x0F);
  printf("0x%08" PRIXPTR ", 0x%08" PRIXPTR "\n", mem, ptr);
  memset_16aligned(ptr, 0, 1024);
  free(mem);
  return(0);
}
