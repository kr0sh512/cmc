#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

// cmd1 | cmd2

int
main(int argc, char **argv)
{
    char *cmd1 = argv[1];
    char *cmd2 = argv[2];

    int fd[2];
    pipe(fd);

    if (!fork()) {
        dup2(fd[1], 1);
        close(fd[0]);

        execlp(cmd1, cmd1, NULL);
        _exit(1);
    } else if (!fork()) {
        dup2(fd[0], 0);
        close(fd[1]);

        execlp(cmd2, cmd2, NULL);
        _exit(1);
    } else {
        close(fd[0]);
        close(fd[1]);
    }

    while (wait(NULL) != -1)
        ;

    return 0;
}
