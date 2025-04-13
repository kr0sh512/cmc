#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int
main()
{
    pid_t pid;
    pid = fork();
    if (!pid) {
        pid = fork();
        if (!pid) {
            printf("3 ");

            return 0;
        } else if (pid == -1) {
            return 1;
        } else {
            wait(NULL);
            printf("2 ");
        }
        return 0;
    } else if (pid == -1) {
        return 1;
    } else {
        wait(NULL);
        printf("1");
    }

    printf("\n");

    return 0;
}
