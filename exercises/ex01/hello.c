#include <stdio.h>

int main() {
    /*
      1. Adding `int x = 5` will add these 2 lines to the assembly
      output (hello-1a.s):
        subq	$16, %rsp
        movl	$5, -4(%rbp)

      2. Turning on the -O2 flag (hello-2a.s): the assembly output is longer
      than the old one. Two lines above that are linked to `int x = 5` seem to
      disappear. This is probably because variable x is not used in this program
      so the compiler removes it from the assembly code to save space.

      3. Without optimization (hello-1b.s), the assembly code still produces 2
      lines in answer 1 above. However, the compiler uses printf instead of puts
      to print the x value. The "Hello World" string declared on the top is now
      replaced by "%i" which is the string input in printf.

        With optimization (hello-2b.s), the assembly code doesn't use printf but
      uses a weird __printf_chk fuction. According to Linux Foundation Referenced
      Specifications, this function is to check for stack overflow before
      computing the result. The output of the optimized assembly code is also
      longer than the unoptimized one.

      4. Without optimization (hello-1c.s), comparing to hello-1b.s, the
      assembly code adds and modifies a few lines of code for the new changes:
        movl	$5, -8(%rbp)
        movl	-8(%rbp), %eax
        addl	$1, %eax
        movl	%eax, -4(%rbp)
      The block of code above includes a function addl, which basically executes
      the operation of adding 1 to x. The code below that looks essentially
      similar to the one in hello-1b.s

        With optimization (hello-2c.s), comparing to the unoptimized version
      hello-1c.s, the optimized output call the __printf_chk function first
      before calling addq (instead of addl) function. It also introduces two
      lines of `xorl	%eax, %eax`, which according to stack overflow means
      a way to zero a register on x86.
      https://stackoverflow.com/a/23575803/6308776

      In general, optimization helps reduce space and speed up the execution of
      the code.
    */
    int x = 5;
    int y = x + 1;
    printf("%i", y);
    return 0;
}
