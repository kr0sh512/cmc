#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <sys/types.h>

enum
{
    YEAR_OFFSET = 1900
};

int
main(void)
{

    int fd[2];
    pipe(fd);
    time_t delta;
    struct tm *dt;

    pid_t pid = fork();
    if (pid == 0) {
        pid = fork();

        if (pid == 0) {
            pid = fork();

            if (pid == 0) {
                close(fd[0]);

                delta = time(NULL);
                if (write(fd[1], &delta, sizeof(delta)) == -1 || write(fd[1], &delta, sizeof(delta)) == -1 ||
                    write(fd[1], &delta, sizeof(delta)) == -1) {
                    _exit(1);
                }
            } else if (pid == -1) {
                _exit(1);
            }
            close(fd[1]);
            wait(NULL);
            if (read(fd[0], &delta, sizeof(delta)) == -1) {
                _exit(1);
            }
            dt = localtime(&delta);
            printf("D:%02d\n", dt->tm_mday);
            fflush(stdout);
            _exit(0);
        } else if (pid == -1) {
            _exit(1);
        }

        close(fd[1]);
        wait(NULL);
        if (read(fd[0], &delta, sizeof(delta)) == -1) {
            _exit(1);
        }
        dt = localtime(&delta);
        printf("M:%02d\n", dt->tm_mon + 1);
        fflush(stdout);
        _exit(0);
    } else if (pid == -1) {
        _exit(1);
    }
    close(fd[1]);
    wait(NULL);
    if (read(fd[0], &delta, sizeof(delta)) == -1) {
        _exit(1);
    }
    dt = localtime(&delta);
    printf("Y:%04d\n", dt->tm_year + YEAR_OFFSET);
    fflush(stdout);

    return 0;
}
