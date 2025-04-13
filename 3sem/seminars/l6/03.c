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
    long long year, day, dw, res = 0;
    str_to_ll(argv[1], &year);
    str_to_ll(argv[2], &day);
    str_to_ll(argv[3], &dw);

    struct tm t = {0};
    t.tm_isdst = -1;
    t.tm_mday = 1;
    t.tm_year = year - 1900;

    while (t.tm_year == year - 1900) {
        mktime(&t);
        if (t.tm_mday == day && dw == t.tm_wday) {
            res++;
        }
        t.tm_mday++;
    }

    printf("%d\n", (int) res);

    return 0;
}
