/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/*
1. This script experiments with array's memory allocation. It runs the foo()
fuction, bar() function and the for loop in the main function. If the program
worked as expected by the genius programmer, it would print out the memory address
of the temporary array initialized in foo(), the address of the temporary array
initialized in bar(), and print out 42 five times because of the loop in the
main() function.

2. It shows the warning about returning address of a local variable (variable
array in foo()). This means that the address of the temporary array variable in
foo() is returned, which might cause an error as this temporary memory cannot
be accessible outside of the foo() function.

3. Output:
foo 0x7ffd428c9bd0
bar 0x7ffd428c9bd0
main (nil)
[1]    30783 segmentation fault  ./a.out

I got a segmentation fault, which breaks when it tries to print out elements
of the array in the main function. I printed out the array before the for loop
in the main() function and it's nil, suggesting that the array has not been initialized.
The problem is that the array variable returned in foo() is a temporary memory
address which only exists locally within the function (local stack frame that holds it).
When the function terminates, all memory addresses in that stack frame will be removed,
and so the int *array in main() basically points to nothing.

Note that the memory addresses printed out by foo() and bar() are the same, suggesting
that after the stack frame holding variables for foo() gets removed, another stack frame
holding variables for bar() gets added at the exact starting memory location as the foo().
That memory location is reused for the bar() stack frame.

4. Nothing really happens on my machine. It still breaks because of the segmentation fault.

5. Commented.
*/
int *foo() {
    int i;
    int array[SIZE];

    // printf("foo %p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    // printf("bar %p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    printf("main %p\n", array); // Check to see what array really is
    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]); // Trying to print 42
    }

    return 0;
}
