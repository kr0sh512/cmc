#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int
main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);

    if (!fork()) {
        close(fd[1]);
        dup2(fd[0], 0);
        execlp("wc", "wc", NULL);
        _exit(1);
    }

    close(fd[0]);
    int file = open(argv[1], O_RDONLY);

    char test = argv[2][0];
    char buf[8];
    while (read(file, buf, 8) == 8) {
        if (buf[0] != test) {
            continue;
        }
        printf("%s\n", buf);

        write(fd[1], buf, 8);
    }
    close(fd[1]);

    while (wait(NULL) != -1)
        ;

    return 0;
}
