#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

volatile int cnt = 0;

void
f(int n)
{
    if (cnt == 5) {
        exit(0);
    }

    printf("%d\n", cnt++);
    fflush(stdout);

    return;
}

int
main(int argc, char *argv[])
{
    sigaction(SIGHUP, &(struct sigaction){.sa_handler = f, .sa_flags = SA_RESTART}, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    for (;;) {
        pause();
    }

    return 0;
}
