#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

int
main(int argc, char *argv[])
{
    const char const_str[] = "18446744073709551616";
    int ch, index = 0;
    int64_t res = 0;
    int is_overflow = 0;

    while ((ch = getchar()) != EOF) {
        if (!isspace(ch)) {
            index = 1;
            int64_t tmp = 0;
            if (ch == 'a') {
                if (res > 0) {
                    if (__builtin_mul_overflow(res - 1, 3, &tmp)) {
                        is_overflow = 1;
                    }
                    if (__builtin_sub_overflow(tmp, 1, &res)) {
                        is_overflow = 1;
                    }
                    if (__builtin_add_overflow(res, 3, &tmp)) {
                        is_overflow = 1;
                    }
                    res = tmp;
                } else {
                    if (__builtin_mul_overflow(res, 3, &tmp)) {
                        is_overflow = 1;
                    }
                    if (__builtin_sub_overflow(tmp, 1, &res)) {
                        is_overflow = 1;
                    }
                }

            } else if (ch == '1') {
                if (res > 0) {
                    if (__builtin_mul_overflow(res, 3, &tmp)) {
                        is_overflow = 1;
                    }
                    if (__builtin_add_overflow(tmp, 1, &res)) {
                        is_overflow = 1;
                    }
                } else {
                    if (__builtin_mul_overflow(res + 1, 3, &tmp)) {
                        is_overflow = 1;
                    }
                    if (__builtin_add_overflow(tmp, 1, &res)) {
                        is_overflow = 1;
                    }
                    if (__builtin_sub_overflow(res, 3, &tmp)) {
                        is_overflow = 1;
                    }
                    res = tmp;
                }
            } else if (ch == '0') {
                if (__builtin_mul_overflow(res, 3, &res)) {
                    is_overflow = 1;
                }
            }
        } else {
            if (index) {
                if (is_overflow) {
                    printf("%s\n", const_str);
                } else {
                    printf("%lld\n", res);
                }

                index = 0;
                res = 0;
                is_overflow = 0;
            }
        }
    }

    if (index) {
        if (is_overflow) {
            printf("%s\n", const_str);
        } else {
            printf("%lld\n", res);
        }
    }

    return 0;
}
