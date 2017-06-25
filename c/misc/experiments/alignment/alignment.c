#include <stdio.h>
#include <stdlib.h>

void *aligned_memory_alloc( size_t size, size_t alignment ) {
  void *pa, *ptr;

  /*pa=malloc(((size+alignment-1)&~(alignment-1))+sizeof(void *)+alignment-1);*/

  pa=malloc((size+alignment-1)+sizeof(void *));
  if(!pa)

    return NULL;
  
  ptr=(void*)( ((size_t)pa+sizeof(void *)+alignment-1)&~(alignment-1) );

  *((void **)ptr-1)=pa;
  
  printf("\n\n%x\n\n", ptr);
  printf("\n\n%x\n\n", ((void**)ptr-1));

  printf("CAlignedAlloc::new(%d,%d)=%x\n", (size_t)size, alignment, (size_t)ptr);

  return ptr;
}

void aligned_free( void *ptr ) {

  printf("CAlignedAlloc::free(%x)\n", (size_t)ptr);

  if(ptr)
    free(*((void **)ptr-1));

}



int main() {
  void *pt = aligned_memory_alloc(16, 8);

  aligned_free(pt);

}
