#include <time.h>
#include <stdio.h>

void
f(int *y, int *m, int *d, int offset)
{ // offset in seconds
    struct tm t = {0};
    // struct tm* tptr = calloc(1, sizeof(struct tm));
    t.tm_isdst = -1;
    t.tm_year = *y - 1900;
    t.tm_mon = *m - 1;
    t.tm_mday = *d;
    time_t time = mktime(&t);
    time += offset;
    localtime_r(&time, &t);
    *y = t.tm_year + 1900;
    *m = t.tm_mon + 1;
    *d = t.tm_mday;

    return;
}

int
main(void)
{
    int y = 2021;
    int m = 1;
    int d = 1;
    f(&y, &m, &d, 65 * 60 * 60 * 24);
    printf("%d-%d-%d\n", y, m, d);

    return 0;
}
