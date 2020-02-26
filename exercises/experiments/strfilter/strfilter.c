#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
strfilter.o: strfilter.c strfilter.h
  gcc -c strfilter.c
*/
char *strfilter(char *s1, char *s2) {
  char *result = malloc(strlen(s1)+1);
  int allChars[128] = {0};

  while (*s2 != 0) {
    allChars[*s2]++;
    s2++;
  }

  char *pointer = result;
  while (*s1 != 0) {
    if (allChars[*s1] > 0) {
      *pointer = *s1;
      pointer++;
    }
    s1++;
  }
  *pointer = 0;
  return result;
}

int main() {
  char *s1 = "equation";
  char *s2 = "aeiou";
  // char *string = malloc(128);
  char * result = strfilter(s1, s2);
  printf("%s--\n", result);
  return 0;
}
