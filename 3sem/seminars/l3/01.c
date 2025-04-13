#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{

    char *fin = argv[1];
    char *fout = argv[2];

    // printf("fdin: %d\n", fin);

    int fdin = open(fin, O_RDONLY);
    if (fdin == -1) {
        return 1;
    }

    int fdout = open(fout, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    for (;;) {
        char c[1024];
        int r = read(fdin, c, 1024);
        if (r == -1) {
            return 1;
        }
        if (r == 0) {
            break;
        }
        write(fdout, c, r);
    }

    close(fdin);
    close(fdout);

    return 0;
}
