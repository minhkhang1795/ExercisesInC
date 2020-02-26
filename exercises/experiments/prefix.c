#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void prefix(char * s1, char*s2, char*buffer) {
  while(*s1 != '\0' && *s2 !='\0' && *s1 == *s2) {
    *buffer = *s1;
    buffer++;
    s1++;
    s2++;
  }
  *buffer = '\0';
}

int main() {
  char *string = malloc(128);
  char *s1 = " Never gonna give you up";
  char *s2 = " Never gonna let you up";
  prefix(s1, s2, string);
  printf("%s--\n", string);
  return 0;
}
