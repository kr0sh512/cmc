#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void
ex(void)
{
    // разослать SIGKILL
    // а некому.

    exit(1);
}

void
swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;

    return;
}

int
main(int argc, char **argv)
{
    int fd1[2];
    int fd2[2];
    if (close(2) == -1 || pipe(fd1) == -1 || pipe(fd2)) {
        ex();
    }

    for (int i = 1; i < argc; ++i) {
        pid_t pid = fork();
        if (pid == 0) {

            if (i != 1 && i != argc - 1) {
                if (dup2(fd2[1], 1) == -1 || dup2(fd1[0], 0) == -1) {
                    ex();
                }
            } else if (i == 1) {
                if (dup2(fd2[1], 1) == -1) {
                    ex();
                }
            } else {
                if (dup2(fd1[0], 0) == -1) {
                    ex();
                }
            }

            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);

            execlp(argv[i], argv[i], NULL);
            _exit(1);
        } else if (pid == -1) {
            ex();
        }

        swap(&fd1[0], &fd2[0]);
        swap(&fd1[1], &fd2[1]);
        wait(NULL);
    }

    return 0;
}
