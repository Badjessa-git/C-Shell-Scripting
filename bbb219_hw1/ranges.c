/// Badjessa B. Bahoumda
/// Find the ranges of char, short, int, long, both signed and unsigned
/// using symoblic constants

#include <stdio.h>
#include <limits.h>

int main() {
  printf("Maximum value of signed Char is %d\n", (int) CHAR_MAX);
  printf("Minimum value of signed Char is %d\n", (int) CHAR_MIN);
  printf("Maximum value of Unsigned Char is %u\n",(unsigned int)  UCHAR_MAX);
  printf("Maximum value of signed Short is %d\n", SHRT_MAX);
  printf("Minimum value of signed Short is %d\n", SHRT_MIN);
  printf("Maximum value of Unsigned Short is %u\n", USHRT_MAX);
  printf("Maximum value of signed Int is %d\n", INT_MAX);
  printf("Minimum value of signed Int is %d\n", INT_MIN);
  printf("Maximum value of Unsigned Int is %u\n", UINT_MAX);
  printf("Maximum value of signed long is %ld\n", LONG_MAX);
  printf("Minimum value of signed long is %ld\n", LONG_MIN);
  printf("Maximum value of Unsigned Long %lu\n\n", ULONG_MAX);

  printf("Now finding the same values with bit manipulation...\n\n");

  //Find the same ranges using bit manipulation
  printf("Minimum value of signed Char %d\n",(int) (-(char)((unsigned char) ~0 >> 1) - 1));
  printf("Maximum value of signed Char %d\n",(int) ((char) ((unsigned char) ~0 >> 1)));
  printf("Maximum value of Unsigned Char %u\n",(unsigned int) ((unsigned char)~0));
  printf("Minimum value of signed Short %d\n",-(short)((unsigned short)~0 >>1) -1);
  printf("Maximum value of signed Short %d\n",(short)((unsigned short)~0 >> 1));
  printf("Maximum value of Unsigned Char %u\n",(unsigned short)~0);
  printf("Minimum value of signed Int %d\n",-(int)((unsigned int)~0 >> 1) -1);
  printf("Maximum value of signed Int %d\n",(int)((unsigned int)~0 >> 1));
  printf("Maximum value of Unsigned Int %u\n",(unsigned int)~0);
  printf("Minimum value of signed Long %ld\n",-(long)((unsigned long)~0 >>1) -1);
  printf("Maximum value of signed Long %ld\n",(long)((unsigned long)~0 >> 1));
  printf("Maximum value of Unsigned Long %lu\n",(unsigned long)~0);

  return 0;
}
