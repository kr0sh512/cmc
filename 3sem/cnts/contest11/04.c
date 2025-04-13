#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main()
{
    pid_t pid;

    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        printf("%d", i);
        fflush(stdout);

        if (i == n) {
            printf("\n");
            return 0;
        } else {
            printf(" ");
            fflush(stdout);
        }
        pid = fork();

        if (!pid) {
            continue;
        } else {
            wait(NULL);
            return 0;
        }
    }

    return 0;
}
