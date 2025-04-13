#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

volatile unsigned char cell;
int fd[2];

void
usr_hndl(int sig)
{
    write(fd[1], &cell, 1);
    kill(getppid(), SIGUSR1);

    return;
}

void
usr_hndl1(int sig)
{
    read(fd[0], &cell, 1);

    return;
}

int
main(int argc, char **argv)
{
    pipe(fd);

    pid_t *mas = malloc((argc - 1) * sizeof(pid_t));
    int n = argc - 1;

    int64_t size = 0;
    for (int i = 1; i < argc; ++i) {
        struct stat st;
        lstat(argv[i], &st);
        size = st.st_size;

        pid_t pid = fork();
        if (!pid) {
            int file = open(argv[i], O_RDONLY);
            close(fd[0]);

            signal(SIGUSR1, usr_hndl);
            for (;;) {
                pause();
            }
            _exit(1);
        }
        mas[i - 1] = pid;
    }
    close(fd[1]);

    signal(SIGUSR1, usr_hndl1);
    unsigned int adr;
    while (scanf("%u", &adr) != -1) {
        kill(mas[adr % n], SIGUSR1);
    }

    return 0;
}
