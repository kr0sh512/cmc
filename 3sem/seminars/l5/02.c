#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{
    DIR *dir = opendir(argv[1]);
    struct dirent *de;
    while (de = readdir(dir)) {
        char *name = calloc(PATH_MAX, sizeof(char));
        snprintf(name, PATH_MAX, "%s/%s", argv[1], de->d_name);

        struct stat st;
        if (lstat(name, &st) < 0) {
            continue;
        }
        if (!(S_ISREG(st.st_mode))) {
            continue;
        }

        if (access(name, 3)) {
            continue;
        }
        int len = strlen(name);

        if (name[len - 1] == '~' || (len >= 4 && strcmp(name + strlen(name) - 4, ".bak") == 0)) {
            unlink(name);
        }
    }

    closedir(dir);
    return 0;
}
