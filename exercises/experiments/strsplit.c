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

int main() {
  char *string = "Hello World! Software";
  char *first = malloc(128);
  char *second = malloc(128);
  strsplit(string, ' ', first, second);
  printf("string: %s\n", string);
  printf("first: %s\n", first);
  printf("second: %s\n", second);
  return 0;
}
