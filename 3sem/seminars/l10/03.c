#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int
main(int argc, char **argv)
{
    int n = strtoll(argv[1], NULL, 10);

    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    int tmp = 1;
    write(fd2[1], &tmp, sizeof(tmp));

    if (!fork()) {
        int i = 0;
        close(fd1[0]);
        close(fd2[1]);

        while (i < n) {
            read(fd2[0], &i, sizeof(i));
            if (i > n) {
                break;
            }
            printf("Channel %d: %d\n", 1, i);
            i++;
            write(fd1[1], &i, sizeof(i));
        }

        return 0;
    } else if (!fork()) {
        int i = 0;
        close(fd2[0]);
        close(fd1[1]);

        while (i < n) {
            read(fd1[0], &i, sizeof(i));
            if (i > n) {
                break;
            }
            printf("Channel %d: %d\n", 2, i);
            i++;
            write(fd2[1], &i, sizeof(i));
        }

        return 0;
    } else {
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);
    }

    while (wait(NULL) != -1)
        ;

    return 0;
}
