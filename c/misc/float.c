/* from http://www.kernelthread.com/publications/faq/float.c.txt */

#include <stdio.h>
#include <string.h>
#include <math.h>

/* For the ix86, __BYTE_ORDER is __LITTLE_ENDIAN */

#ifndef _IEEE754_SINGLE_BIAS
#define _IEEE754_SINGLE_BIAS 0x7f
#endif

/* bit fields for 32-bit single precision floating
 * point a.k.a. ``IEEE754 Single Precision Format''
 */
typedef struct {
  unsigned int mantissa:23;
  unsigned int exponent:8;
  unsigned int negative:1;
} ieee_float;
 
int
main()
{
  float f;
  unsigned int *u;
  unsigned int mantissa, exponent, negative;

  printf("Float? ");
  scanf("%f", &f);

  /* Assuming sizeof(float) == sizeof(unsigned int)
   * memcpy(&u, &f, sizeof(float)) is an alternative,
   * but that is no lesser a kludge than the following
   */
  u = &f; /* expect compiler warning here */
  printf("uninterpreted hex 0x%x\n", *u);

  negative = ((ieee_float *)&f)->negative;
  exponent = (int)((ieee_float *)&f)->exponent;
  mantissa = ((ieee_float *)&f)->mantissa;

  printf("float    = %.32f\n", f);
  printf("sign     = 0x%x\n", negative);
  printf("mantissa = 0x%x\n", mantissa);
  printf("exponent = 0x%x\n", exponent);
  printf("bias     = 0x%x\n", _IEEE754_SINGLE_BIAS);
  printf("radix    = 0x2\n");

  printf("value    = (-1)^sign * (radix)^(exponent - bias) * (1).mantissa\n");
  printf("           where calculations are in binary (for radix 2)\n");

  exit(0);
}
