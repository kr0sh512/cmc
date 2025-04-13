#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
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

void
make_proc(int deepth, int max_deepth)
{
    if (deepth == max_deepth) {
        return;
    }

    printf("Deepth: %d\n", deepth);

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        make_proc(deepth + 1, max_deepth);
        exit(0);
    } else {
        wait(NULL);
    }

    return;
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <deepth>\n", argv[0]);
        return 1;
    }

    long long deepth;
    str_to_ll(argv[1], &deepth);
    make_proc(0, deepth);

    return 0;
}
