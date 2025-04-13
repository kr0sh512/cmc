#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

volatile sig_atomic_t sigusr1_received = 0;

void
sigusr1_handler(int signum)
{
    sigusr1_received = 1;
}

int
main(int argc, char **argv)
{
    int n = (int) strtol(argv[1], NULL, 10);

    int fd[2];
    pipe(fd);

    signal(SIGUSR1, sigusr1_handler);

    if (!fork()) {
        close(fd[0]);
        FILE *out = fdopen(fd[1], "w");

        int i = 1;
        while (i <= n) {
            printf("1 %d\n", i);
            fflush(stdout);
            fprintf(out, "%d\n", i);
            fflush(out);
            kill(getppid(), SIGUSR1);
            pause();
            if (i >= n) {
                break;
            }
            i++;
        }

        fclose(out);
        return 0;
    } else if (!fork()) {
        close(fd[1]);
        FILE *in = fdopen(fd[0], "r");

        int i;
        while (1) {
            if (i >= n) {
                break;
            }
            i++;
            printf("2 %d\n", i);
            fflush(stdout);
            kill(getppid(), SIGUSR1);
            pause();
        }

        fclose(in);
        return 0;
    }

    close(fd[0]);
    close(fd[1]);

    while (wait(NULL) != -1)
        ;

    printf("Done\n");

    return 0;
}
