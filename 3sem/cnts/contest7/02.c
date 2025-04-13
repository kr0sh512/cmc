#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum
{
    THURSDAY = 4,
    YEAR_OFFSET = 1900,
    LAST_DIGIT_REM = 3,
    GOOD_THURSDAY1 = 2,
    GOOD_THURSDAY2 = 4
};

int
main(int argc, char *argv[])
{
    int year;
    if (scanf("%d", &year) != 1) {
        fprintf(stderr, "Invalid input\n");

        return 1;
    }

    struct tm t = {0};
    t.tm_isdst = -1;
    t.tm_mday = 1;
    t.tm_year = year - YEAR_OFFSET;

    int num_of_thursdays = 0, last_month = 0;

    while (t.tm_year == year - YEAR_OFFSET) {
        mktime(&t);

        if (t.tm_mon != last_month) {
            last_month = t.tm_mon;
            num_of_thursdays = 0;
        }

        if (t.tm_wday == THURSDAY) {
            num_of_thursdays++;

            if (t.tm_mday % LAST_DIGIT_REM != 0 &&
                (num_of_thursdays == GOOD_THURSDAY1 || num_of_thursdays == GOOD_THURSDAY2)) {
                printf("%d %d\n", t.tm_mon + 1, t.tm_mday);
            }

            t.tm_mday += 7;
        } else {
            t.tm_mday++;
        }
    }

    return 0;
}
