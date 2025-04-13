#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int
main()
{

    pid_t pid;
    int n;

    pid = fork();
    if (!pid) {
        for (;;) {
            if (scanf("%d", &n) != 1) {
                return 0;
            }

            pid = fork();
            if (!pid) {
                continue;
            }
            int status;
            wait(&status);
            if (pid == -1 || !WIFEXITED(status) || WEXITSTATUS(status)) {
                return -1;
            }

            printf("%d\n", n);
            return 0;
        }
    } else {
        int status;
        wait(&status);
        if (pid == -1 || !WIFEXITED(status) || WEXITSTATUS(status)) {
            printf("-1\n");
        }
    }

    return 0;
}
