#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * palindrome(char *string) {
  int len = strlen(string);
  char *result = malloc(len*2 + 1);
  char *pointer = result;

  int i = 0;
  for (;i<len;i++) {
    *pointer = string[i];
    pointer++;
  }
  i--;
  for (;i>=0;i--) {
    *pointer = string[i];
    pointer++;
  }
  *pointer = 0;
  return result;
}

int main() {
  char *s1 = "red";
  char *s2 = "aeiou";
  char *result = palindrome(s1);
  printf("%s--\n", result);
  return 0;
}
