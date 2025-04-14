#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    printf("Signed char:    %li to %li\n", SCHAR_MIN, SCHAR_MAX);
    printf("Signed short:   %li to %li\n", SHRT_MIN, SHRT_MAX);
    printf("Signed int:     %li to %li\n", INT_MIN, INT_MAX);
    printf("Signed long:    %li to %li\n", LONG_MIN, LONG_MAX);
    printf("\n");

    printf("Unsigned char:  0 to %lu\n", UCHAR_MAX);
    printf("Unsigned short: 0 to %lu\n", USHRT_MAX);
    printf("Unsigned int:   0 to %lu\n", UINT_MAX);
    printf("Unsigned long:  0 to %lu\n", ULONG_MAX);
    printf("\n");

    printf("Signed float:   %.100f to %lf\n", FLT_MIN, FLT_MAX);
    printf("Signed double:  %.600f to %lf\n", DBL_MIN, DBL_MAX);

    return 0;
}

/*
201: Write a program to determine the ranges of
     `char`, `short`, `int`, and `long` variables, both `signed` and `unsigned`,
     by printing appropriate values from standard headers and by direct computation.
     Harder if you compute them: determine the ranges of the various floating-point types.
*/