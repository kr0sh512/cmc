#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

enum
{
    MAX_LEN = 8
};

void
process_line(int line_number)
{
    char buffer[MAX_LEN + 1] = {0};
    read(0, buffer, sizeof(buffer) - 1);
    long long number = strtoll(buffer, NULL, 10);
    long long square = number * number;
    printf("%d %lld\n", line_number, square);

    return;
}

int
main()
{
    pid_t pid;

    for (int i = 0; i < 3; i++) {
        if ((pid = fork()) == 0) {
            process_line(i + 1);
            exit(0);
        }
    }

    while (wait(NULL) != -1)
        ;

    return 0;
}
