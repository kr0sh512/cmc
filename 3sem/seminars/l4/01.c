#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>

void
premission_to_char(char *m, int n, mode_t mode)
{
    for (int i = 0; i < n; ++i) {
        if (!(mode & 1)) {
            m[n - i - 1] = '-';
        }
        mode >>= 1;
    }
}

int
main(int argc, char *argv[])
{
    struct stat st;

    for (int i = 1; i < argc; i++) {
        if (lstat(argv[i], &st) < 0) {
            continue;
        }

        char type;
        if (S_ISREG(st.st_mode)) {
            type = '-';
        } else if (S_ISDIR(st.st_mode)) {
            type = 'd';
        } else if (S_ISLNK(st.st_mode)) {
            type = 'l';
        } else {
            type = '?';
        }

        char m[] = "rwxrwxrwx";
        for (int j = 0; j < 9; j++) {
            if (!((st.st_mode >> j) & 1)) {
                m[8 - j] = '-';
            }
        }

        printf("%c%s %lu %hu %lu %ld %s\n", type, m, st.st_nlink, st.st_uid, st.st_size, st.st_ctime, argv[i]);
    }
    return 0;
}
