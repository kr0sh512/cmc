#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int
check(void)
{
    int succes = 0;
    int status;

    while (wait(&status) != -1) {
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            succes++;
        }
    }

    return succes;
}

void
run(char *cmd)
{
    pid_t pid = fork();
    if (pid == -1) {
        exit(1);
    } else if (pid == 0) {
        execlp(cmd, cmd, NULL);
        _exit(1);
    }

    return;
} // 1 - при успехе

int
main(int argc, char **argv)
{
    int succes = 0;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == 's') {
            succes += check();
            run(argv[i] + 1);
            succes += check();
        } else if (argv[i][0] == 'p') {
            run(argv[i] + 1);
        } else {
            fprintf(stderr, "Error in arguments\n");
            exit(1);
        }
    }

    succes += check();

    printf("%d\n", succes);

    return 0;
}
