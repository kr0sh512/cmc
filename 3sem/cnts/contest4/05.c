#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#include <endian.h>

int
main(int argc, char *argv[])
{
    if (argc != 4) {
        return 1;
    }

    int fdin = open(argv[1], O_RDONLY);
    int fdout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fdin == -1 || fdout == -1) {
        return 1;
    }

    char *p;
    errno = 0;
    long long mod = strtoll(argv[3], &p, 10);
    if (errno || *p || p == argv[3] || !mod || (int32_t) mod != mod) {
        return 1;
    }

    unsigned long long res = 0;
    unsigned long long num = 1;
    unsigned char buf;
    int r = read(fdin, &buf, sizeof(buf));
    if (r && r != sizeof(buf)) {
        return 1;
    }
    while (r > 0) {
        for (int i = 0; i < CHAR_BIT; i++) {
            num %= mod;
            res += (num * num) % mod;
            res %= mod;

            if (buf & (1 << i)) {
                int32_t res32 = res;

                if (write(fdout, &res32, sizeof(res32)) == -1) {
                    return 1;
                }
            }
            num++;
        }
        r = read(fdin, &buf, sizeof(buf));
        if (r && r != sizeof(buf)) {
            return 1;
        }
    }

    if (r == -1) {
        return 1;
    }

    close(fdin);
    close(fdout);

    return 0;
}
