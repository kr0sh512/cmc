#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void
str_to_ll(char *str, long long *num)
{
    errno = 0;
    char *endptr;
    *num = strtoll(str, &endptr, 10);

    if (*endptr || errno || endptr == str) {
        fprintf(stderr, "Invalid number: %s\n", str);
        exit(1); // TODO: по-хорошему заменить на внешний обработчик ошибок
    }

    return;
}

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
    if (argc < 3) {
        return 1;
    }

    long long n;
    str_to_ll(argv[2], &n);

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        return 1;
    }

    int is_first = 1;
    double prev;

    for (int i = 0; i < n; ++i) {
        double tmp;
        int r = read(fd, &tmp, sizeof(tmp));
        if (r == -1 || (r && r != sizeof(tmp))) {
            return 1;
        }
        if (r < 1) {
            break;
        }

        if (!is_first) {
            tmp -= prev;
        } else {
            is_first = 0;
        }

        if (lseek(fd, -sizeof(tmp), SEEK_CUR) == -1) {
            return 1;
        }
        safe_write(fd, &tmp, sizeof(tmp));
        prev = tmp;
    }

    close(fd);

    return 0;
}
