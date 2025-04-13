#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

enum
{
    PRCN = 10000,
};

int
main(int argc, char *argv[])
{
    long double a = 0;

    for (int i = 1; i < argc; i++) {
        char *p;
        errno = 0;
        long double val = strtod(argv[i], &p);
        if (*p || errno || argv[i] == p) {
            return 1;
        }

        if (i == 1) {
            a = val * PRCN;
        } else {
            a = round(a * (100.L + val) / 100.L);
        }
    }

    if (argc == 1) {
        return 1;
    }

    printf("%.4Lf\n", a / PRCN);

    return 0;
}
