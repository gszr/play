/*
  (Problem authored by Prof. Bruno O. Silvestre, UFG, Brazil)

  Playing with bit maps:
  
  Given a binary file with the format:
     ----------------------------------
    |     |      |      |              |
    |  N  |  B1  |  B2  |    Blocks    |
    |     |      |      |              |
     ----------------------------------
  Where:
    N  is the number of bytes in each bitmap
    B1 is a bitmap
    B2 is a copy of B1
    Blocks is a storage area, with N blocks of 1024 bytes
  
  - How many blocks are there in the Blocks area?
  - Implement the following functions:
    * void mark_used(FILE *f, int num): mark block 'num' as used in
      the bitmap
    * void mark_free(FILE *f, int num): mark block 'num' as free in
      the bitmap
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef union {
	unsigned char buff[4];
	uint32_t num;
} NUM;

bool testEndianness();
void printErr(const char *str);
void bigToLittleEndian(NUM *num);
void printByteBin(char byte);
void printBitmaps(FILE *fp);
bool checkEqual(FILE *fp);

void markUsed(FILE *fp, int num);
void markFree(FILE *fp, int num);

	int 
main(int argc, char **argv)
{
	FILE *fp;
	NUM num;

	if (argc != 2)
		printErr("Usage: %s <file_name>\n");

	if (!(fp = fopen(argv[1], "rb+")))
		printErr("error opening file\n");

	if (fread(&num.buff, 1, 4, fp) == 0)
		printErr("error reading integer\n");

	if (!testEndianness()) {
		printf("(Little endian arch)\n");
		bigToLittleEndian(&num);
	}


	printf("------------------------------\n");
	printf("\tParte 1\n\n");
	printf("Bitmap size:\t%d bytes\n", num.num);

	fseek(fp, 0L, SEEK_END);
	long fsz = ftell(fp);

	printf("File size:\t%ld bytes\n", fsz);
	printf("Blocks:\t\t%ld\n", (fsz - 4 - 2 * num.num)/1024);

	printf("------------------------------\n");
	printf("\tParte 2\n\n");

	int block = 2;

	printf("Marking block %d as used...\n", block);
	markUsed(fp, block);
	//printBitmaps(fp); // uncomment if you want to print the whole bitmap
	printf("Marking block %d as free...\n", block);
	markFree(fp, block);
	//printBitmaps(fp);

	if (checkEqual(fp))
		printf("\nBitmaps are equal! Take a look at function 'printBitmaps'\nif you want to see them\n");
	else
		printf("Oops... bitmaps are different! Stupid programmer detected\n");

	fclose(fp);
	return EXIT_SUCCESS;
}

bool
/* return true for big endian, false otherwise */
testEndianness()
{
	uint8_t num = 1;
	if (*(char*)&num == 1)
		return false;
	else
		return true;
}

	void
printErr(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

	void
swapChars(unsigned char *ch1, unsigned char *ch2)
{
	unsigned char tmp;
	tmp = *ch1;
	*ch1 = *ch2;
	*ch2 = tmp;
}

	void
bigToLittleEndian(NUM *num)
{
	swapChars(&num->buff[0], &num->buff[3]);
	swapChars(&num->buff[1], &num->buff[2]);
}

	void 
markUsed(FILE *fp, int num)
{
	char byte;

	// b = byte to be changed
	// d = bit to be changed in that byte
	int b = --num / 8, d = num % 8;

	printf("\tByte: %d\n", b + 1);
	printf("\t Bit: %d\n", d + 1);

	// going to the correct position in the first bitmap
	fseek(fp, 4 + b, SEEK_SET);
	// reading the byte we'll change
	fread(&byte, 1, 1, fp);
	printf("\tBefore marking used:\n\t");
	printByteBin(byte);
	printf("\n");
	// setting the bit inside the byte we've just read
	byte |= (1 << (8 - d - 1));
	printf("\tAfter marking used:\n\t");
	printByteBin(byte);
	printf("\n");
	// backing up 1 byte to write in the due position
	fseek(fp, -1, SEEK_CUR);
	fwrite(&byte, 1, 1, fp);
	// moving to the second bitmap to write
	fseek(fp, 1004 + b, SEEK_SET);
	fwrite(&byte, 1, 1, fp);
}

	void 
markFree(FILE *fp, int num)
{
	char byte;
	int b = --num / 8, d = num % 8;

	printf("\tByte: %d\n", b + 1);
	printf("\t Bit: %d\n", d + 1);

	fseek(fp, 4 + b, SEEK_SET);
	fread(&byte, 1, 1, fp);
	printf("\tBefore marking free:\n\t");
	printByteBin(byte);
	printf("\n");
	byte &= ~(1 << (8 - d - 1));
	printf("\tAfter marking free:\n\t");
	printByteBin(byte);
	printf("\n");
	fseek(fp, ftell(fp) - 1, SEEK_SET);
	fwrite(&byte, 1, 1, fp);   
	fseek(fp, 1004 + b, SEEK_SET);
	fwrite(&byte, 1, 1, fp);
}

	void
printByteBin(char b)
{
	int i;
	for (i = 7; i >= 0; i--)
		printf("%d", (b & (1 << i)) != 0);
}

	void
printBitmaps(FILE *fp)
{
	int i;
	char c;
	fseek(fp, 4, SEEK_SET);
	printf("\n1st Bitmap\n");
	for (i = 0; i < 1000; i++) {
		fread(&c, 1, 1, fp);
		printByteBin(c);
	}

	printf("\n2nd Bitmap\n");
	for (i = 0; i < 1000; i++) {
		fread(&c, 1, 1, fp);
		printByteBin(c);
	}
	printf("\n");
}

	bool
checkEqual(FILE *fp)
{
	int i;
	char b1[1000], b2[1000];
	fseek(fp, 4, SEEK_SET);
	fread(b1, 1000, 1, fp);
	fread(b2, 1000, 1, fp);
	for (i = 0; i < 1000; i++)
		if (b1[i] != b2[i])
			return false;
	return true;
}
