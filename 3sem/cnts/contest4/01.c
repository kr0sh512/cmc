#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

enum
{
    PEN_CHAR_BIT = 12
};

int
safe_write(int fd, void *buf, size_t count)
{
    errno = 0;
    size_t bytes_written = 0;
    while (bytes_written < count) {
        ssize_t res = write(fd, buf + bytes_written, count - bytes_written);

        if (res < 0) {
            if (errno == EINTR) {
                errno = 0;
                continue;
            }

            fprintf(stderr, "Error writing to file descriptor %d\n", fd);
            close(fd);
            exit(1); // TODO: по-хорошему заменить на внешний обработчик ошибок
        }

        bytes_written += res;
    }

    return bytes_written;
}

int
main(int argc, char **argv)
{
    int fdout = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fdout == -1) {
        return 1;
    }

    unsigned char res[4];
    unsigned tmp;
    while (scanf("%u", &tmp) == 1) {
        res[0] = (tmp & (0x0F << (CHAR_BIT + PEN_CHAR_BIT))) >> (CHAR_BIT + PEN_CHAR_BIT);
        res[1] = (tmp & (0xFF << PEN_CHAR_BIT)) >> PEN_CHAR_BIT;
        res[2] = (tmp & (0x0F << CHAR_BIT)) >> CHAR_BIT;
        res[3] = tmp & 0xFF;
        safe_write(fdout, res, sizeof(res));
    }

    close(fdout);

    return 0;
}
