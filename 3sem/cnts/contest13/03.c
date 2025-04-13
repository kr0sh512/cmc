#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

enum
{
    ACCESS_FILE = 0660
};

int
main(int argc, char **argv)
{
    char *cmd1 = argv[1];
    char *cmd2 = argv[2];
    char *cmd3 = argv[3];
    char *file1 = argv[4];
    char *file2 = argv[5];

    int fd1 = open(file1, O_RDONLY);
    int fd2 = open(file2, O_WRONLY | O_APPEND | O_CREAT, ACCESS_FILE);
    if (fd1 == -1 || fd2 == -1) {
        exit(1);
    }

    int fd[2];
    if (pipe(fd) == -1) {
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        close(fd[0]);
        if (dup2(fd[1], 1) == -1) {
            _exit(1);
        }

        pid = fork();
        if (pid == 0) {

            if (dup2(fd1, 0) == -1) {
                _exit(1);
            }

            execlp(cmd1, cmd1, NULL);
            _exit(1);
        } else if (pid == -1) {
            exit(1);
        }

        int status;
        wait(&status);

        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            pid = fork();
            if (pid == 0) {
                execlp(cmd2, cmd2, NULL);
                _exit(1);
            } else if (pid == -1) {
                exit(1);
            }

            wait(NULL);
        }

        _exit(0);
    } else if (pid == -1) {
        exit(1);
    }

    close(fd[1]);
    pid = fork();
    if (pid == 0) {

        if (dup2(fd2, 1) == -1 || dup2(fd[0], 0)) {
            _exit(1);
        }

        execlp(cmd3, cmd3, NULL);
        _exit(1);
    } else if (pid == -1) {
        exit(1);
    }

    close(fd[0]);

    while (wait(NULL) != -1)
        ;
    return 0;
}
