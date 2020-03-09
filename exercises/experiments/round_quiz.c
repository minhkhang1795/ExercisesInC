#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
  double *array;
} Vector;

uint32_t round2(uint32_t input, int n) {
  uint32_t mask = 0;
  mask = ~mask << n;
  return input & mask;
}

union {
  float f;
  unsigned int u;
} p;

int main() {
  // uint32_t input = 31;
  // int n = 2;
  // uint32_t r = round2(input, n);
  // printf("%d\n", r);
  //
  // Vector *v = malloc(sizeof(Vector));
  // v->array = malloc(5*sizeof(double));
  // v->array[0] = 1.2;
  // printf("%f\n", v->array[0]);
  p.f = 17.5;
  unsigned int sign = (p.u >> 31) & 1;
  unsigned int exp = (p.u >> 23) & 0xff;
  unsigned int coef_mask = (1 << 23) - 1;
  unsigned int coef = p.u & coef_mask;
  printf("%d\n", sign);
  printf("%d\n", exp);
  printf("0x%x\n", coef);
  return 0;
}
