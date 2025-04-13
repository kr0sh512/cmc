#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

// cmd < file1 >> file2

int
main(int argc, char **argv)
{
    char *file1 = argv[2];
    char *file2 = argv[3];
    char *cmd = argv[1];

    if (!fork()) {
        int fin = open(file1, O_RDONLY);
        int fout = open(file2, O_WRONLY | O_APPEND | O_CREAT, 0666);

        dup2(fin, 0);
        dup2(fout, 1);

        execlp(cmd, cmd, NULL);
        _exit(1);
    } else {
        wait(NULL);
    }

    return 0;
}
