#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strsplit(char *string, char sep, char *first, char *second) {
  char seps[2];
  seps[0] = sep;
  char *i = strstr(string, seps);
  strncpy(first, string, abs(i - string));
  strcpy(second, ++i);
}

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
  // char *string = "Hello World! Software";
  // char *first = malloc(128);
  char *second = malloc(128);
  // strsplit(string, ' ', first, second);
  // printf("string: %s\n", string);
  // printf("first: %s\n", first);
  // printf("second: %s\n", second);
  char *s1 = " Never gonna give you up";
  char *s2 = " Never gonna let you up";
  prefix(s1, s2, second);
  printf("%s--\n", second);
  return 0;
}
