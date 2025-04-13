#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <linux/limits.h>

void
check_and_sum_files(const char *dir1, const char *dir2, off_t *total_size)
{
    DIR *d1 = opendir(dir1);
    if (!d1) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(d1)) != NULL) {
        char path1[PATH_MAX];
        int r = snprintf(path1, sizeof(path1), "%s/%s", dir1, entry->d_name);
        if (r < 0 || r >= sizeof(path1)) {
            _exit(1);
        }

        struct stat st1;
        if (lstat(path1, &st1) == -1 || !S_ISREG(st1.st_mode)) {
            continue;
        }

        if (access(path1, W_OK) == 0) {
            char path2[PATH_MAX];
            r = snprintf(path2, sizeof(path2), "%s/%s", dir2, entry->d_name);
            if (r < 0 || r >= sizeof(path2)) {
                _exit(1);
            }

            struct stat st2;
            if (stat(path2, &st2) == -1) {
                continue;
            }

            if (S_ISREG(st2.st_mode) && st1.st_dev == st2.st_dev && st1.st_ino == st2.st_ino) {
                *total_size += st1.st_size;
            }
        }
    }

    closedir(d1);
}

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <directory1> <directory2>\n", argv[0]);
        return 1;
    }

    off_t total_size = 0;
    check_and_sum_files(argv[1], argv[2], &total_size);

    printf("%ld\n", total_size);

    return 0;
}
