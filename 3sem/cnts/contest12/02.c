#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int
run(const char *cmd)
{
    pid_t pid = fork();
    if (pid == -1) {
        exit(1);
    } else if (pid == 0) {
        execlp(cmd, cmd, NULL);
        _exit(1);
    }
    int status;
    waitpid(pid, &status, 0);

    return WIFEXITED(status) && !WEXITSTATUS(status);
} // 1 - при успехе

int
main(int argc, char **argv)
{
    if (argc != 4) {
        return 1;
    }

    char *cmd1 = argv[1];
    char *cmd2 = argv[2];
    char *cmd3 = argv[3];

    return !((run(cmd1) || run(cmd2)) && run(cmd3));
}
