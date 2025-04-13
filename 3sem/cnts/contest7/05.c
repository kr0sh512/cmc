#include <stdio.h>
#include <time.h>

enum
{
    SYNODIC_PERIOD_DAYS = 29,
    SYNODIC_PERIOD_HOURS = 12,
    SYNODIC_PERIOD_MINUTES = 44,
    FULL_MOON_YEAR = 2021,
    FULL_MOON_MONTH = 5,
    FULL_MOON_DAY = 26,
    FULL_MOON_HOUR = 11,
    FULL_MOON_MINUTE = 14,
};

void
add_synodic_period(struct tm *tm)
{
    tm->tm_mday += SYNODIC_PERIOD_DAYS;
    tm->tm_hour += SYNODIC_PERIOD_HOURS;
    tm->tm_min += SYNODIC_PERIOD_MINUTES;
    timegm(tm);
}

void
sub_synodic_period(struct tm *tm)
{
    tm->tm_mday -= SYNODIC_PERIOD_DAYS;
    tm->tm_hour -= SYNODIC_PERIOD_HOURS;
    tm->tm_min -= SYNODIC_PERIOD_MINUTES;
    timegm(tm);
}

struct tm
find_full_moon_after(struct tm start)
{
    struct tm full_moon = {0};
    full_moon.tm_isdst = -1;
    full_moon.tm_year = FULL_MOON_YEAR - 1900;
    full_moon.tm_mon = FULL_MOON_MONTH - 1;
    full_moon.tm_mday = FULL_MOON_DAY;
    full_moon.tm_hour = FULL_MOON_HOUR;
    full_moon.tm_min = FULL_MOON_MINUTE;
    timegm(&full_moon);

    while (timegm(&full_moon) < timegm(&start)) {
        add_synodic_period(&full_moon);
    }

    while (timegm(&full_moon) > timegm(&start)) {
        sub_synodic_period(&full_moon);
    }

    add_synodic_period(&full_moon);

    return full_moon;
}

struct tm
find_fourth_monday_after(struct tm start)
{
    struct tm date = start;
    date.tm_mday++;

    int num_of_mondays = 0;
    while (num_of_mondays < 4) {
        timegm(&date);

        if (date.tm_wday == 1) {
            num_of_mondays++;
        }

        date.tm_mday++;
    }

    date.tm_mday--;

    timegm(&date);

    return date;
}

int
main()
{
    int year;
    if (scanf("%d", &year) != 1) {
        return 1;
    }

    struct tm start = {0};
    start.tm_isdst = -1;
    start.tm_year = year - 1900;
    start.tm_mday = 257;

    timegm(&start);

    struct tm full_moon = find_full_moon_after(start);
    struct tm event_date = find_fourth_monday_after(full_moon);

    printf("%04d-%02d-%02d\n", event_date.tm_year + 1900, event_date.tm_mon + 1, event_date.tm_mday);

    return 0;
}
