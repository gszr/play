/* Simple code to show alignment problems in structs, how GCC put padding and how to avoid this.
 * Build with -Wpadded option, amd GCC will print warnings about alignment problems..
 *
 * By: Bruno C. Buss (bruno dot buss at gmail dot com)
 * Date: 30/11/2008
 */

#include <stdio.h>

/* mystruct is a struct with alignment problems... GCC will do padding before res and after bcode to align struct size

It should be something like this:
|----------------------------------------------------|
|   END  |  BYTE0   |  BYTE1   |  BYTE2   |  BYTE3   |
|----------------------------------------------------|
| 0x0000 |   tam    |   tam    |   tam    |   tam    |
|----------------------------------------------------|
| 0x0004 | bchar[0] | bchar[1] |   res    |   res    |
|----------------------------------------------------|
| 0x0008 |   res    |   res    |   res    |   res    |
|----------------------------------------------------|
| 0x000C |   res    |   res    | bcode[0] | bcode[1] |
|----------------------------------------------------|
| 0x0010 |  ........................................ |
|----------------------------------------------------|

But end like this:
|----------------------------------------------------|
|   END  |  BYTE0   |  BYTE1   |  BYTE2   |  BYTE3   |
|----------------------------------------------------|
| 0x0000 |   tam    |   tam    |   tam    |   tam    |
|----------------------------------------------------|
| 0x0004 | bchar[0] | bchar[1] |   PAD    |   PAD    |
|----------------------------------------------------|
| 0x0008 |   res    |   res    |   res    |   res    |
|----------------------------------------------------|
| 0x000C |   res    |   res    |   res    |   res    |
|----------------------------------------------------|
| 0x0010 | bcode[0] | bcode[1] |   PAD    |   PAD    |
|----------------------------------------------------|
| 0x0014 |  .......................................  |
|----------------------------------------------------|

So, you want an 16 bytes struct, but it will have 20...*/
typedef struct _mystruct{
	int tam;
	char bchar[2];
	double res;
	char bcode[2];
} mystruct;


/* So, lets put the char arrays together so they don't break
 * the alignment
 *
 * OBS: We also could moved bcode[] to before res, but if later we
 * want to change bchar size or bcode size, we may need to move things again...
 */
typedef struct _mystruct_fixed{
	int tam;
	double res;
	char bchar[2];	
	char bcode[2];
} mystruct_fixed;

/* Simple char struct don't get padding, cause they don't
 * need to be aligned with any other data types
 */
typedef struct _mycharstruct{
	char bchar[3];
} mycharstruct;

/* In this case, GCC will align b[] to a multiple of 2 (size of short).
 * But if b size is any multiple of 2 (2, 4, 6, 8, ...),
 * GCC will not put any padding
 */
typedef struct _myshortcharstruct{
	short a;
	char b[1];
} myshortcharstruct;

/* In this case, GCC will align c[] to a multiple of 4 (size of int).
 * But if b size is any multiple of 4 (4, 8, 12, 16, ...),
 * GCC will not put any padding
 */
typedef struct _myintcharstruct{
	int a;
	char c[2];
} myintcharstruct;

/* In this case, GCC will align c[] to a multiple of 4, not 8 (size of double),
 * because the double data type are already aligned in multiples of 4.
 * But if b size is any multiple of 4 (4, 8, 12, 16, ...),
 * GCC will not put any padding
 */
typedef struct _mydoublecharstruct{
	double a;
	char c[4];
} mydoublecharstruct;

int main(void)
{
	mystruct a;
	mystruct_fixed b;
		
	printf("Sizes:\n");

	printf("-int                 = %d\n", sizeof(int));
	printf("-char                = %d\n", sizeof(char));
	printf("-double              = %d\n", sizeof(double));
	printf("-mystruct            = %d\n", sizeof(mystruct));
	printf("-mystruct_fixed      = %d\n", sizeof(mystruct_fixed));	
	printf("-mycharstruct        = %d\n", sizeof(mycharstruct));	
	printf("-myshortcharstruct   = %d\n", sizeof(myshortcharstruct));
	printf("-myintcharstruct     = %d\n", sizeof(myintcharstruct));
	printf("-mydoublecharstruct  = %d\n", sizeof(mydoublecharstruct));	


	printf("Memory Positions of mystruct a:\n");

	printf("-mystruct a          = %p\n", &a);
	printf("-int tam             = %p\n", &a.tam);
	printf("-char bchar[0]       = %p\n", &a.bchar[0]);
	printf("-char bchar[1]       = %p\n", &a.bchar[1]);
	printf("-double res          = %p\n", &a.res);
	printf("-char bcode[0]       = %p\n", &a.bcode[0]);
	printf("-char bcode[1]       = %p\n", &a.bcode[1]);
	
	printf("Memory Positions of mystruct_fixed b:\n");

	printf("-mystruct_fixed b    = %p\n", &b);
	printf("-int tam             = %p\n", &b.tam);
	printf("-double res          = %p\n", &b.res);	
	printf("-char bchar[0]       = %p\n", &b.bchar[0]);
	printf("-char bchar[1]       = %p\n", &b.bchar[1]);
	printf("-char bcode[0]       = %p\n", &b.bcode[0]);
	printf("-char bcode[1]       = %p\n", &b.bcode[1]);	
	
	return 0;
}
