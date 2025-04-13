#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <string.h>

enum
{
    KIBIBYTE = 1024
};

int
main(int argc, char *argv[])
{
    long long int sum = 0;

    for (int i = 1; i < argc; ++i) {
        struct stat st;

        if (!(lstat(argv[i], &st) < 0 || st.st_nlink != 1 || !S_ISREG(st.st_mode) || st.st_size % KIBIBYTE != 0)) {
            sum += st.st_size;
        }
    }

    printf("%lld\n", sum);

    return 0;
}
