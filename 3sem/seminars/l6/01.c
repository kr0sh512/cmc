#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <linux/limits.h>

struct Files
{
    char *pathname;
    __ino_t st_ino;
    __dev_t st_dev;
};

int
main(int argc, char **argv)
{
    struct stat st;
    if (lstat(".", &st) == -1) {
        printf("stat error\n");
        return 1;
    }

    DIR *dir = opendir("..");
    struct dirent *de;
    while ((de = readdir(dir))) {
        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")) {
            continue;
        }

        struct stat sttmp;

        char buf[PATH_MAX];
        snprintf(buf, PATH_MAX, "%s/%s", "..", de->d_name);
        if (lstat(buf, &sttmp) == -1) {
            printf("lstat error\n");
            return 1;
        }
        printf("%s\n", de->d_name);
        if (sttmp.st_dev == st.st_dev && sttmp.st_ino == st.st_ino) {
            printf("%s\n", de->d_name);
        }
    }

    return 0;
}
