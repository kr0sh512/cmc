#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int
main(int argc, char **argv)
{
    int n = (int) strtoll(argv[1], NULL, 10);

    int fd[2];
    pipe(fd);

    int tmp = 1;
    write(fd2[1], &tmp, sizeof(tmp));

    if (!fork()) {
        int i = 0;
        close(fd[0]);

        while (i < n) {
            if (read(fd2[0], &i, sizeof(i)) == -1) {
                return 0;
            }
            if (i >= n) {
                write(fd1[1], &i, sizeof(i));
                break;
            }
            printf("%d %d\n", 1, i);
            fflush(stdout);
            i++;
            write(fd1[1], &i, sizeof(i));
        }

        return 0;
    } else if (!fork()) {
        int i = 0;
        close(fd2[0]);
        close(fd1[1]);

        while (i < n) {
            if (read(fd1[0], &i, sizeof(i)) == -1) {
                return 0;
            }
            if (i >= n) {
                write(fd1[1], &i, sizeof(i));
                break;
            }
            printf("%d %d\n", 2, i);
            fflush(stdout);
            i++;
            write(fd2[1], &i, sizeof(i));
        }

        return 0;
    }

    close(fd[0]);
    close(fd[1]);

    while (wait(NULL) != -1)
        ;

    printf("Done\n");

    return 0;
}
