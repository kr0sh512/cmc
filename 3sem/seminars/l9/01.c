#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
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
main(int argc, char *argv[])
{
    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            return 1;
        }
        if (pid == 0) {
            char buf[8] = {0};
            read(0, buf, 7);

            // long long t;
            // str_to_ll(buf, &t);

            int t = (int) strtol(buf, NULL, 10);

            printf("%d\n", t * t);
            return 0;
        } else {
            continue;
        }
    }

    while (wait(NULL) != -1)
        ;

    return 0;
}
