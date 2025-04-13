#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// CMD < FILE1 >> FILE2 2> FILE3

enum
{
    EXIT_ERROR = 42,
    ACCESS_FILE = 0660
};

int
main(int argc, char **argv)
{
    char *cmd = argv[1];
    char *file1 = argv[2];
    char *file2 = argv[3];
    char *file3 = argv[4];
    pid_t pid = fork();
    if (pid == 0) {

        int fd1 = open(file1, O_RDONLY);
        int fd2 = open(file2, O_WRONLY | O_APPEND | O_CREAT, ACCESS_FILE);
        int fd3 = open(file3, O_WRONLY | O_TRUNC | O_CREAT, ACCESS_FILE);

        if (fd1 == -1 || fd2 == -1 || fd3 == -1) {
            _exit(EXIT_ERROR);
        }

        if (dup2(fd1, 0) == -1 || dup2(fd2, 1) == -1 || dup2(fd3, 2) == -1) {
            _exit(EXIT_ERROR);
        }

        execlp(cmd, cmd, NULL);
        _exit(EXIT_ERROR);
    } else {
        int status;
        wait(&status);
        printf("%d\n", status);
    }

    return 0;
}
