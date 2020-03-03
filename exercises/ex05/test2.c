#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "rand.h"

int main (int argc, char *argv[])
{
    int i;
    double x;

    srandom (time (NULL));

    for (i=0; i<10000000; i++) {
        // x = log(my_random_float());
        x = my_random_float();
        printf ("%lf\n", x);
    }

    return 0;
}
