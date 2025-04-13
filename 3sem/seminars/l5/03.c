// подкаталог пустой
// совпадают айдишники
// есть права у остальных на запись
// rmdir

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
        if ((de->d_name[0] == '.' && strlen(de->d_name) == 1) ||
            (strlen(de->d_name) == 2) && !strcmp(de->d_name, "..")) {
            continue;
        }
        char *name = calloc(PATH_MAX, sizeof(char));
        snprintf(name, PATH_MAX, "%s/%s", argv[1], de->d_name);

        struct stat st;
        if (lstat(name, &st) < 0) {
            continue;
        }
        if (!(S_ISDIR(st.st_mode))) {
            continue;
        }

        if (st.st_uid != getuid()) {
            continue;
        }

        if (!(st.st_mode & 2)) {
            continue;
        }

        int num_files = 0;
        DIR *dirt = opendir(name);
        while (readdir(dirt)) {
            num_files++;
            if (num_files > 2) {
                break;
            }
        }

        if (num_files > 2) {
            continue;
        }

        closedir(dirt);
        rmdir(name);
    }

    closedir(dir);
    return 0;
}
