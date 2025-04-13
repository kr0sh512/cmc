#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    struct stat st;

    if (lstat(argv[1], &st) < 0) {
        exit(1);
    }

    if (S_ISDIR(st.st_mode)) {
        char *file = calloc(strlen(argv[1]) + 30, sizeof(char));

        snprintf(file, strlen(argv[1]) + 30, "%s/%s.uid", argv[1], argv[0]);

        sprintf(file, "%s/%s.uid", argv[1], argv[0]);

        int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
        uid_t uid = getuid();
        write(fd, &uid, sizeof(uid_t));

        close(fd);
    } else if (S_ISREG(st.st_mode)) {
        int fd = open(argv[1], O_WRONLY | O_TRUNC);
        write(fd, st.st_uid, sizeof(uid_t));

        close(fd);
    } else {
        exit(1);
    }
}
