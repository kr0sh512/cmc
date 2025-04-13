#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
#include <math.h>
#include <dirent.h>
#include <string.h>

size_t
len(const char *buf)
{
    size_t i = 0;
    while (buf[i] != '\0') {
        ++i;
    }
    return i;
}

size_t
shift_left(char *str, size_t st, size_t shift_amount, size_t length)
{
    size_t i = st;
    if (i + shift_amount > length) {
        return length;
    }

    while (i + shift_amount < length) {
        str[i] = str[i + shift_amount];
        ++i;
    }

    return length - shift_amount;
}

void
normalize_path(char *path)
{
    size_t length = len(path);

    size_t i = 1;
    while (path[i]) {
        if (path[i - 1] == '/' && path[i] == '.') {
            if (path[i + 1] == '.' && (path[i + 2] == '/' || !path[i + 2])) {
                if (i < 1) {
                    if (path[i + 2] == '/') {
                        length = shift_left(path, i, 3, length);
                        --i;
                    } else if (!path[i + 2]) {
                        length = shift_left(path, i, 2, length);
                        --i;
                    }
                } else {
                    size_t j = i - 2;

                    while (j > 0 && path[j] != '/') {
                        --j;
                    }

                    ++j;

                    if (path[i + 2] == '/') {
                        length = shift_left(path, j, i + 3 - j, length);
                        i = j - 1;
                    } else if (!path[i + 2]) {
                        length = shift_left(path, j, i + 2 - j, length);
                        i = j - 1;
                    }
                }
            } else if (path[i + 1] == '/' || !path[i + 1]) {
                if (path[i + 1] == '/') {
                    length = shift_left(path, i, 2, length);
                    --i;
                } else if (!path[i + 1]) {
                    length = shift_left(path, i, 1, length);
                    --i;
                }
            }
        }

        ++i;
    }

    if (len(path) != 1 && path[len(path) - 1] == '/') {
        path[len(path) - 1] = '\0';
    }

    return;
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char path[PATH_MAX];
    strncpy(path, argv[1], PATH_MAX - 1);
    path[PATH_MAX - 1] = '\0';

    normalize_path(path);

    printf("Normalized path: %s\n", path);

    return EXIT_SUCCESS;
}
