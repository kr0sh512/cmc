#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void
str_to_ll(char *str, long long *num)
{
    errno = 0;
    char *endptr;
    *num = strtoll(str, &endptr, 10);

    if (*endptr || errno || endptr == str) {
        fprintf(stderr, "Invalid number: %s\n", str);
        exit(1); // TODO: по-хорошему заменить на внешний обработчик ошибок
    }

    return;
}

int
main(int argc, char **argv)
{
    long long year, mth, res = 0;
    str_to_ll(argv[1], &year);
    str_to_ll(argv[2], &mth);

    struct tm t = {0};
    t.tm_isdst = -1;
    t.tm_mday = 1;
    t.tm_mon = mth - 1;
    t.tm_year = year - 1900;

    while (t.tm_mon == mth - 1) {
        if (t.tm_wday > 0 && t.tm_wday < 5) {
            res += 8;
        } else if (t.tm_wday == 5) {
            res += 6;
        }
        t.tm_mday++;
        mktime(&t);
    }

    printf("%d\n", (int) res);

    return 0;
}
