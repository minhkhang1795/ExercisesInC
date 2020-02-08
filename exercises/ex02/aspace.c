/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

/**

3.
stack:
+ main
+ var2
+ pointer p pointing to a empty space in heap
+ pointer s pointing to "Hello, World" in constants
heap: malloc(128)
globals: var1
constants: "Hello, World"
code: all the code in main and other functions defined

4. Heap did grow up when I added 'void *t = malloc(128)';
[Output]
t points to 0xc7e0a0
s points to 0x400744

t is the new pointer variable allocated with malloc(128). As t > p when I ran it
the heap on my system did grow up.

5. I added the print() function to print the output below

[Output]
Address of var1 in main is 0x7ffda88accfc
Address of local is 0x7ffda88accd4

As address of var1 in main < address of the local variable in the print() function,
the stack grows down.

6. I added the function randomExperiment() for this question and chose 2 as my random number.
[Output]
a points to 0x1caf540
b points to 0x1caf560

The difference is 20 in hex value or 32 in decimal value.
*/

int var1;

/**
 * Function to print out the address of a given variable
 * @param pointer: pointer to the variable
 */
void print(int *main) {
    int local;
    if (main < &local)
        printf("Stack grows up\n");
    else
        printf("Stack grows down\n");

    printf("Address of var1 in main is %p\n", main);
    printf("Address of local is %p\n", &local);
}

/**
 * Function to allocate memories for two variables and print out their addresses
 * @param var: random integer input
 */
void randomExperiment(int var) {
    void *a = malloc(var);
    void *b = malloc(var);
    printf("a points to %p\n", a);
    printf("b points to %p\n", b);
}

int main() {
    int var2 = 5;
    void *p = malloc(128);
    void *t = malloc(128);
    if (t > p)
      printf("Heap grows up.\n");
    else
      printf("Heap grows down.\n");

    char *s = "Hello, World";

    printf("Address of main is %p\n", main);
    printf("Address of var1 is %p\n", &var1);
    printf("Address of var2 is %p\n", &var2);
    printf("p points to %p\n", p);
    printf("t points to %p\n", t);
    printf("s points to %p\n", s);

    print(&var2);
    randomExperiment(2);
    return 0;
}
