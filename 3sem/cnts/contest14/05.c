#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

volatile int last_prime = 0;
volatile int cnt = 0;

void
f(int n)
{
    if (++cnt == 4) {
        exit(0);
    }

    printf("%d\n", last_prime);
    fflush(stdout);

    return;
}

void
exit_term(int n)
{
    exit(0);

    return;
}

int
is_prime(int n)
{
    if (n < 2) {
        return 0;
    }

    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int
main(int argc, char *argv[])
{
    sigaction(SIGINT, &(struct sigaction){.sa_handler = f, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGTERM, &(struct sigaction){.sa_handler = exit_term, .sa_flags = SA_RESTART}, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    a = (a < 2) ? 2 : a;

    for (int i = a; i < b; ++i) {
        if (is_prime(i)) {
            last_prime = i;
        }
    }

    printf("-1\n");
    fflush(stdout);

    return 0;
}
