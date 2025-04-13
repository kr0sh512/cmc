#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>

int
acs(const char *name, int mode)
{
    struct stat st;

    if (lstat(name, &st) < 0) {
        return -1;
    }
    uid_t uid = getuid();
    if (uid == 0) {
        return 0;
    }

    uid_t st_mode = st.st_mode;
    if (st.st_mode == uid) {
        st_mode >>= 6;
    } else if (st.st_gid == getgid()) {
        st_mode >>= 3;
    }
    st_mode &= 7;

    // for (int i = 0; i < 3; ++i) {
    //     if (st_mode ^ mode & 1) {
    //         return -1;
    //     }
    //     st_mode >>= 1;
    //     mode >>= 1;
    // }

    if (st_mode & mode == mode) {
        return 0;
    }

    return -1;
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
