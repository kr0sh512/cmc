#include <stdio.h>     // Standard I/O functions
#include <stdlib.h>    // Standard library functions: memory allocation, process control, conversions, etc.
#include <unistd.h>    // POSIX API: read, write, close, etc.
#include <sys/types.h> // Data types used in system calls
#include <sys/stat.h>  // Data returned by the functions fstat(), lstat(), and stat()
#include <limits.h>    // Sizes of basic types
#include <dirent.h>    // Directory entry format
#include <string.h>    // String handling functions

enum
{
    ARGS_NUM = 2,
};

int
main(int argc, char *argv[])
{
    if (argc != ARGS_NUM) {
        fprintf(stderr, "Wrong number of arguments\n");
        return 1;
    }

    int n = 0;

    DIR *ddir = opendir(argv[1]);
    struct dirent *de;
    while ((de = readdir(ddir))) {
        char *name = calloc(PATH_MAX, sizeof(char));
        if (!name) {
            return 1;
        }

        int ret = snprintf(name, PATH_MAX, "%s/%s", argv[1], de->d_name);
        if (ret < 0 || ret >= PATH_MAX) {
            free(name);
            return 1;
        }

        struct stat st;
        if (stat(name, &st) < 0) {
            continue;
        }
        char ext[] = ".exe";
        if (S_ISREG(st.st_mode) && !access(name, X_OK) && strlen(name) >= 4 &&
            !strcmp(name + strlen(name) - (sizeof(ext) - 1), ext)) {
            ++n;
        }
    }

    printf("%d\n", n);

    closedir(ddir);

    return 0;
}
