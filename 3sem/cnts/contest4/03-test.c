#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

ssize_t
my_write(int fd, void *buf, size_t count)
{
    size_t count_1 = 0;
    ssize_t count_2;
    while (count_1 != count) {
        count_2 = write(fd, buf, count - count_1);
        if (count_2 == -1) {
            return -1;
        } else if (count_2 == 0) {
            return (ssize_t) count_1;
        } else {
            count_1 += (size_t) count_2;
        }
    }
    return (ssize_t) count_1;
}

ssize_t
my_read(int fd, void *buf, size_t count)
{
    size_t count_1 = 0;
    ssize_t count_2;
    while (count_1 != count) {
        count_2 = read(fd, buf, count - count_1);
        if (count_2 == -1) {
            return -1;
        } else if (count_2 == 0) {
            return (ssize_t) count_1;
        } else {
            count_1 += (size_t) count_2;
        }
    }
    return (ssize_t) count_1;
}

int
main(int argc, char **argv)
{
    if (argc < 2) {
        return 1;
    }

    int fd;
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        return 1;
    }

    long long num, min, shift = 0;

    if (my_read(fd, &min, sizeof(min)) < sizeof(min)) {
        if (errno) {
            close(fd);
            return 1;
        }
        close(fd);
        return 0;
    }

    for (int i = (int) sizeof(num); my_read(fd, &num, sizeof(min)) == sizeof(min); i += (int) sizeof(num)) {
        if (num < min) {
            min = num;
            shift = i;
        }
    }

    lseek(fd, shift, 0);
    if (errno) {
        close(fd);
        return 1;
    }

    if (min != LLONG_MIN) {
        min = -min;
    }

    if (my_write(fd, &min, sizeof(min)) != sizeof(min)) {
        close(fd);
        return 1;
    }

    close(fd);
    if (errno) {
        return 1;
    }
}
