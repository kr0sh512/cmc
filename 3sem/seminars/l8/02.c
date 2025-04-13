#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/mman.h>

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
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <deepth> <file>\n", argv[0]);
        return 1;
    }

    long long deepth;
    str_to_ll(argv[1], &deepth);

    for (int i = 1; i <= deepth; i++) {
        if (fork() == 0) {
            int fd = open(argv[2], O_CREAT | O_WRONLY, 0666);

            lseek(fd, (deepth - i) * sizeof(int), SEEK_SET);
            write(fd, &i, sizeof(int));

            close(fd);

            return 0;
        }
    }

    return 0;
}
