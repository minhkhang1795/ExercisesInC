/*  Test code for the functions in rand.c

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

#include "rand.h"

/*
time_rand.c analysis. Here is the result I got when running the file

201.073000 ms 	 dummy
584.402000 ms 	 dummy2
667.855000 ms 	 random_float
658.533000 ms 	 my_random_float
1673.135000 ms 	 my_random_float2
674.102000 ms 	 random_float
1210.704000 ms 	 my_random_double
622.232000 ms 	 random_double


The fastest one for float are both random_float() and my_random_float() as the
bottleneck is the random() function and both of them use it.

The fastest one for double is random_double(). my_randome_double() is twice
as slow as random_double() is because I call random() two times in  the my_randome_double().
*/


/* Get the total of user time and system time used by this process.
*/
double get_seconds() {
    double user, sys;
    struct rusage r;

    getrusage(RUSAGE_SELF, &r);

    user = r.ru_utime.tv_sec * 1000.0 + r.ru_utime.tv_usec / 1000.0;
    sys = r.ru_stime.tv_sec * 1000.0 + r.ru_stime.tv_usec / 1000.0;

    // printf("%lf\n", user);

    return user+sys;
}

/* Compute the total time used by a function.

iters: number of times to call the function
func: function to call
*/
double time_func(int iters, float(*func)())
{
    int i;
    float f;
    double t0, t1;

    srandom(time(NULL));

    t0 = get_seconds();
    for (i=0; i<iters; i++) {
        f = func();
    }
    t1 = get_seconds();
    return t1 - t0;
}

/* Compute the total time used by a function.

iters: number of times to call the function
func: function (of type double) to call
*/
double time_func_double(int iters, double(*func)())
{
    int i;
    double f, t0, t1;

    srandom(time(NULL));

    t0 = get_seconds();
    for (i=0; i<iters; i++) {
        f = func();
    }
    t1 = get_seconds();
    return t1 - t0;
}


int main(int argc, char *argv[])
{
    double time;
    int iters = 100000000;
    int seed = 17;

    time = time_func(iters, dummy);
    printf("%f ms \t dummy\n", time);

    time = time_func(iters, dummy2);
    printf("%f ms \t dummy2\n", time);

    time = time_func(iters, random_float);
    printf("%f ms \t random_float\n", time);

    time = time_func(iters, my_random_float);
    printf("%f ms \t my_random_float\n", time);

    time = time_func(iters, my_random_float2);
    printf("%f ms \t my_random_float2\n", time);

    time = time_func(iters, random_float);
    printf("%f ms \t random_float\n", time);

    time = time_func_double(iters, my_random_double);
    printf("%f ms \t my_random_double\n", time);

    time = time_func_double(iters, random_double);
    printf("%f ms \t random_double\n", time);
}
