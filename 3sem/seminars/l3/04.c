#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{
    int fdin = open(argv[1], O_RDONLY);
    if (fdin == -1) {
        return 1;
    }

    unsigned int res = 0, tmp;
    unsigned char num[4]; // не пишем в int, т.к. неизвестно, какой порядок байтов

    while (read(fdin, num, 4) == 4) {
        // unsigned int tmp = (unsigned int) num << 24 | (unsigned int) num <<
        // 16 |
        //                    (unsigned int) num << 8 | (unsigned int) num;
        for (int i = 0; i < 4; i++) {
            tmp = tmp << 8 | num[i];
        }
        res += tmp;
    }

    printf("%u\n", res);

    close(fdin);

    return 0;
}
