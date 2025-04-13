#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

enum
{
    MAX_MODE = 0777,
};

int
main(int argc, char *argv[])
{
    const char s[] = "rwxrwxrwx";

    for (int i = 1; i < argc; ++i) {
        char *p;
        errno = 0;
        int n = strtol(argv[i], &p, 8);

        if (errno || *p || p == argv[i] || n > MAX_MODE || n < 0) {
            return 1;
        }

        for (int j = 0; j < sizeof(s) - 1; ++j) {
            putchar((n & (1 << (sizeof(s) - 2 - j))) ? s[j] : '-');
        }

        printf("\n");
    }

    return 0;
}
