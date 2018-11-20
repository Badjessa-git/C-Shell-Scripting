#include <stdio.h>

int main() {
  char c = 'C';  /* do not change */
  float f = 3;   /* do not change */
  int g;         /* do not change */
  float i = 4.3;
  
  c =  c + (char)1;
  f = 3.7;
  g = (int) (i + f + 0.4);

  printf("c = %d\n", (int)c);
  printf("c = %c\n", c);
  printf("f = %d\n", (int)f);
  printf("f = %1.2f\n", f);
  printf("g = %d\n", g);
  printf("i = %d\n", (int)i);
  printf("i = %E\n", (double) ((int)i)); 
  return 0;
  /* place your printf statements here; cannot use constants */
  /* Q: Any warning(s) related to promotion?
     A:There were some warning about promotion,  Assignment of double to int: g = i + f + 0.4
  */

}
