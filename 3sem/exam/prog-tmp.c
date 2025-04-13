// на вход подаётся имя каталога.
// пробежать рекурсивно по всему каталогу и папкам в нём. Если встретился регулярный файл с именем, которое
// заканчивается на .exeсute, открыть, прочесть путь, запустить по нему прогу.

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int
main(int argc, char *argv[])
{
    DIR *d = opendir(argv[1]);
    struct dirent *dd;
    while ((dd = readdir(d))) {
        char str[PATH_MAX];
        snprintf(str, PATH_MAX, "%s/%s", argv[1], dd->d_name);

        write(1, str, strlen(str));
        write(1, "\n", 1);
    }

    return 0;
}
