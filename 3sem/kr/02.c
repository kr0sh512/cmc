#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int
main(int argc, char **argv)
{
    int file = open(argv[1], O_RDONLY);
    int file_out = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    dup2(file, 0);
    dup2(file_out, 1);

    char buf[101];
    while (fgets(buf, 100, stdin) != NULL) {
        for (int i = 0; i < strlen(buf); i++) {
            if (!strncmp(buf + i, "begin", 5)) {
                printf("{");
                i += 4;
            } else if (!strncmp(buf + i, "end", 3)) {
                printf("}");
                i += 2;
            } else {
                printf("%c", buf[i]);
            }
        }
    }

    rename("tmp", argv[1]);

    return 0;
}
