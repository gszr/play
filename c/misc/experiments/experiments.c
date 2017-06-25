#include <stdio.h>
#include <time.h>

#define BCD_TO_BIN(val)	(((val)&15)+((val)>>4)*10)

int main() {
    printf("%d = %s", 2, BCD_TO_BIN(2));
}
