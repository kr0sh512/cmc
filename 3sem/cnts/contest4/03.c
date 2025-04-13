#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>

enum
{
    ARGS_NUM = 2,
};

int
safe_read(int fd, void *buf, size_t count)
{
    errno = 0;
    size_t bytes_read = 0;
    while (bytes_read < count) {
        ssize_t res = read(fd, buf + bytes_read, count - bytes_read);

        if (res < 0) {
            if (errno == EINTR) {
                errno = 0;
                continue;
            }

            fprintf(stderr, "Error reading from file descriptor %d\n", fd);
            close(fd);
            exit(1); // TODO: по-хорошему заменить на внешний обработчик ошибок
        }

        if (res == 0) {
            break;
        }

        bytes_read += res;
    }

    return bytes_read;
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
main(int argc, char *argv[])
{
    if (argc != ARGS_NUM) {
        fprintf(stderr, "Wrong number of arguments\n");
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);

        return 1;
    }

    long long num, min_num = LLONG_MAX;
    off_t pt_min = -1;

    while (safe_read(fd, &num, sizeof(num)) == sizeof(num)) {
        if (num < min_num || pt_min == -1) {
            min_num = num;

            if ((pt_min = lseek(fd, 0, SEEK_CUR) - sizeof(num)) == -1) {
                fprintf(stderr, "Error in navigate file %s\n", argv[1]);

                return 1;
            }
        }
    }

    if (min_num != LLONG_MIN && pt_min != -1) {
        min_num = -min_num;
        if (lseek(fd, pt_min, SEEK_SET) == -1) {
            fprintf(stderr, "Error in navigate file %s\n", argv[1]);

            return 1;
        }

        if (safe_write(fd, &min_num, sizeof(min_num)) != sizeof(num)) {
            printf("Error while writing");

            return 1;
        }
    }

    close(fd);

    return 0;
}
