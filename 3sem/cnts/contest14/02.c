#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

volatile int mode = 0; // 0 - +    1 - *

void
mul(int n)
{
    mode = 1;

    return;
}

void
sum(int n)
{
    mode = 0;

    return;
}

int
main(int argc, char *argv[])
{
    sigaction(SIGINT, &(struct sigaction){.sa_handler = sum, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGQUIT, &(struct sigaction){.sa_handler = mul, .sa_flags = SA_RESTART}, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int res = 0, tmp;

    while (scanf("%d", &tmp) == 1) {
        if (mode == 0) {
            __builtin_add_overflow(res, tmp, &res);
        } else {
            __builtin_mul_overflow(res, tmp, &res);
        }
        printf("%d\n", res);
        fflush(stdout);
    }

    // for (;;) {
    //     pause();
    // }

    return 0;
}
