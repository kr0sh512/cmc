#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    long long res_pos = 0, res_neg = 0;

    for (int i = 1; i < argc; i++) {
        char *p;
        errno = 0;
        long long val = strtol(argv[i], &p, 10);
        if (*p || errno || (int32_t) val != val || argv[i] == p) {
            return 1;
        }
        // int32_t tmp;
        if (val >= 0) {
            // if (!__builtin_add_overflow(res_pos, val, &tmp)) {
            res_pos += val;
            // }
        } else {
            // if (!__builtin_add_overflow(res_neg, val, &tmp)) {
            res_neg += val;
            // }
        }
    }

    // if (!(res_neg && res_pos)) {
    //     printf("0\n");
    // } else {
    //     printf("%d\n", res_pos);
    //     printf("%d\n", res_neg);
    // }

    printf("%lld\n", res_pos);
    printf("%lld\n", res_neg);

    return 0;
}
