#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <deepth>\n", argv[0]);
        return 1;
    }

    long long deepth;
    str_to_ll(argv[1], &deepth);

    // long long i = 1;

    // while (deepth > 0) {
    //     printf("Deepth: %lld\n", i++);

    //     if (deepth == 1) {
    //         break;
    //     }

    //     if (!fork()) {
    //         deepth--;
    //     } else {
    //         wait(NULL);

    //         break;
    //     }
    // }

    for (int i = 1; i <= deepth; i++) {
        if (i == deepth || fork() > 0) {
            wait(NULL);
            printf("Deepth: %d\n", i);

            break;
        }
    }

    return 0;
}
