#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <stdint.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    const char const_str[] = "18446744073709551616";

    char tmp_str[PATH_MAX];

    while (scanf("%s", tmp_str) == 1) {
        int64_t res = 0;
        uint64_t base = 1;

        int is_overflow = 0;

        for (int i = strlen(tmp_str) - 1; i >= 0; i--) {
            char ch = tmp_str[i];

            if (ch == 'a') {
                if (__builtin_sub_overflow(res, base, &res)) {
                    is_overflow = 1;

                    break;
                }
            } else if (ch == '1') {
                if (__builtin_add_overflow(res, base, &res)) {
                    is_overflow = 1;

                    break;
                }
            } else if (ch != '0') {
                fprintf(stderr, "Invalid input\n");

                return 1;
            }

            if (__builtin_mul_overflow(base, 3, &base) && i != 0) {
                is_overflow = 1;

                break;
            }
        }

        if (is_overflow) {
            printf("%s\n", const_str);
        } else {
            printf("%lld\n", res);
        }
    }

    return 0;
}
