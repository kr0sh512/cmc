#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <stdio.h>

char *
relativize_path(const char *path1, const char *path2)
{
    char *spath1 = calloc(strlen(path1) + 2, sizeof(char));
    strcpy(spath1, path1);
    spath1[strlen(path1)] = '\0';
    if (spath1[strlen(path1) - 1] != '/') {
        strcat(spath1, "/");
    }

    char *res;
    if ((res = calloc(PATH_MAX, sizeof(char))) == NULL) {
        exit(1);
    }

    int i = 0;
    int ptr = 0;
    while (spath1[i] == path2[i] && spath1[i]) {
        if (spath1[i] == '/') {
            ptr = i;
        }
        i++;
    }

    int deep1 = 0;
    while (spath1[i]) {
        if (spath1[i] == '/') {
            deep1++;
        }

        i++;
    }

    if (!deep1 && path2[strlen(path2) - 1] == '/') {
        snprintf(res, PATH_MAX, ".");
        return res;
    }

    int deep2 = 0;
    i = ptr + 1;
    while (path2[i]) {
        if (path2[i] == '/') {
            deep2++;
        }

        i++;
    }

    for (int j = 0; j < deep1; j++) {
        res[j * 3] = '.';
        res[j * 3 + 1] = '.';
        res[j * 3 + 2] = '/';
    }

    if (deep2 == 0 && deep1) {
        if (res[strlen(res) - 1] == '/') {
            res[strlen(res) - 1] = '\0';
        }
        return res;
    }

    snprintf(res + deep1 * 3, PATH_MAX - deep1 * 3, "%s", path2 + ptr + 1);

    if (res[strlen(res) - 1] == '/') {
        res[strlen(res) - 1] = '\0';
    }

    return res;
}

int
main()
{
    const char *path1 = "/home/krosh/cmc/contest5";
    const char *path2 = "/home/krosh/cmc/contest5/subdir/file.txt";

    char *relative_path = relativize_path(path1, path2);
    printf("Relative path: %s\n", relative_path);

    const char *path3 = "/a/b/c/d";
    const char *path4 = "/a/e/f";

    printf("Relative path: %s\n", relativize_path(path3, path4));

    const char *path5 = "/a/f/g/h/j";
    const char *path6 = "/a/f/g/h";
    printf("Relative path: %s\n", relativize_path(path5, path6));

    const char *path7 = "/a";
    const char *path8 = "/a";
    printf("Relative path: %s\n", relativize_path(path7, path8));

    return 0;
}
