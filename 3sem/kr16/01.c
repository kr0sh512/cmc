#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

int
main(int argc, char **argv)
{
    long long unsigned int tmp, res = 0;

    while (scanf("%llu", &tmp) != EOF) {
        for (int i = 0; i < sizeof(tmp) * 8; i += 2) {
            if (!((tmp >> i) & 0x3)) {
                res++;
            }
        }
    }

    printf("%llu\n", res);

    return 0;
}
