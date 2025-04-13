#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

volatile int count = 0;

void
func(int sign)
{
    if (count < 5) {
        printf("%d\n", count);
        fflush(stdout);
        count++;
    } else {
        exit(0);
    }
}

int
main(int argc, char *argv[])
{
    printf("%d\n", getpid());
    fflush(stdout);

    if (signal(SIGHUP, func) == SIG_ERR) {
        exit(1);
    }
    for (;;) {
        pause();
    }

    return 0;
}
