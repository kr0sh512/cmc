#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <string.h>
#include <linux/limits.h>

int
main(int argc, char *argv[])
{
    DIR *dir = opendir(argv[1]);
    unsigned long long sum = 0;
    struct dirent *de;
    while (de = readdir(dir)) {
        char *name = calloc(PATH_MAX, sizeof(char));
        snprintf(name, PATH_MAX, "%s/%s", argv[1], de->d_name);

        struct stat st;
        if (lstat(name, &st) < 0) {
            continue;
        }
        if (S_ISREG(st.st_mode)) {
            sum += st.st_size;
        }
    }

    closedir(dir);

    printf("%d\n", sum);

    return 0;
}
