#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

int
main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if (!pid) {
        close(fd[0]);
        dup2(fd[1], 1);
        execlp("gpg", "gpg", "-d", "--batch", "--passphrase", argv[2], "--pinentry-mode", "loopback", "--quiet",
               "--no-tty", "--no-keyring", argv[1], NULL);
        _exit(1);
    } else if (pid == -1) {
        exit(1);
    }
    close(fd[1]);
    wait(NULL);

    dup2(fd[0], 0);

    int tmp;
    int64_t sum = 0;
    while (scanf("%d", &tmp) != EOF) {
        sum += tmp;
    }

    printf("%ld\n", sum);

    return 0;
}
