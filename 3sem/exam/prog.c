// на вход подаётся имя каталога.
// пробежать рекурсивно по всему каталогу и папкам в нём. Если встретился регулярный файл с именем, которое
// заканчивается на .exeсute, открыть, прочесть путь, запустить по нему прогу.

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{
    DIR *d = opendir(argv[1]);
    struct dirent *dd;
    struct stat st;
    while ((dd = readdir(d))) {
        if (strcmp(dd->d_name, ".") == 0 || strcmp(dd->d_name, "..") == 0) {
            continue;
        }

        char str[PATH_MAX];
        snprintf(str, PATH_MAX, "%s/%s", argv[1], dd->d_name);
        lstat(str, &st);
        if (S_ISREG(st.st_mode) && st.st_size < strtol(argv[2], NULL, 10)) {
            if (strlen(str) >= 8 && strcmp(str + strlen(str) - 8, ".execute") == 0) {
                int fd = open(str, O_RDONLY);
                char s[PATH_MAX + 1];
                // memset(s, 0, PATH_MAX);
                s[read(fd, s, PATH_MAX)] = '\0';
                if (!fork()) {
                    execlp(s, s, NULL);
                    _exit(1);
                }
                close(fd);
            }
        }
    }

    return 0;
}
