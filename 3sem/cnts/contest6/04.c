#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <errno.h>

enum
{
    ARGS_NUM = 3,
    MAX_DIRS = 1000,
};

void
str_to_ll(char *str, long long *num)
{
    errno = 0;
    char *endptr;
    *num = strtoll(str, &endptr, 10);

    if (*endptr || errno || endptr == str) {
        fprintf(stderr, "Invalid number: %s\n", str);
        exit(1); // TODO: по-хорошему заменить на внешний обработчик ошибок
    }

    return;
}

void
list_files(char *path_from, const int start, size_t max_size, int depth)
{
    if (depth > 4) {
        return;
    }

    DIR *dir = opendir(path_from);
    if (dir == NULL) {
        return;
    }

    char **dirs = (char **) calloc(MAX_DIRS, sizeof(char *));
    if (dirs == NULL) {
        exit(1);
    }

    int cnt = 0;

    struct dirent *dd;
    while ((dd = readdir(dir))) {
        if (!(strcmp(dd->d_name, ".") && strcmp(dd->d_name, ".."))) {
            continue;
        }

        char name[PATH_MAX];
        int ret = snprintf(name, sizeof(name), "%s/%s", path_from, dd->d_name);
        if (ret < 0 || ret >= PATH_MAX) {
            exit(1);
        }

        struct stat st;
        if (lstat(name, &st) < 0) {
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            dirs[cnt] = (char *) calloc(PATH_MAX, sizeof(char));
            memcpy(dirs[cnt], name, strlen(name));
            cnt++;
        } else if (st.st_size <= max_size && !access(name, R_OK) && S_ISREG(st.st_mode)) {
            ret = snprintf(name, sizeof(name), "%s/%s", path_from + start + 1, dd->d_name);

            if (ret < 0 || ret >= PATH_MAX) {
                exit(1);
            }

            printf("%s\n", name + (name[0] == '/'));
        }
    }

    for (int i = 0; i < cnt; i++) {
        list_files(dirs[i], start, max_size, depth + 1);

        free(dirs[i]);
    }

    closedir(dir);
    free(dirs);

    return;
}

int
main(int argc, char *argv[])
{
    if (argc != ARGS_NUM) {
        return 1;
    }

    int len_arg = strlen(argv[1]);
    char *dir_path = calloc(PATH_MAX, sizeof(char));
    memcpy(dir_path, argv[1], len_arg - (argv[1][len_arg - 1] == '/'));

    int len_path = strlen(dir_path);
    if (!len_path) {
        dir_path[0] = '/';
        dir_path[1] = '\0';
    }

    long long max_size;
    str_to_ll(argv[2], &max_size);

    list_files(dir_path, len_path, max_size, 1);

    free(dir_path);

    return EXIT_SUCCESS;
}
