#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <string.h>
#include <linux/limits.h>

struct File
{
    char *pathname;
    __ino_t st_ino;
    __dev_t st_dev;
};

int
cmp_structs(struct File elem1, struct stat elem2)
{
    return elem1.st_dev == elem2.st_dev && elem1.st_ino == elem2.st_ino;
}

int
cmp_mas(const void *a, const void *b)
{
    struct File elem1 = *(struct File *) a;
    struct File elem2 = *(struct File *) b;

    return strcmp(elem1.pathname, elem2.pathname);
}

int
main(int argc, char **argv)
{
    struct File *mas = calloc(10, sizeof(struct File));
    if (mas == NULL) {
        fprintf(stderr, "Error! Can't calloc mas\n");

        return 1;
    }
    int n = 0, capacity = 10;

    for (int i = 1; i < argc; ++i) {

        struct stat st;
        if (stat(argv[i], &st) < 0) {
            continue;
        }

        int flag = 0;
        for (int j = 0; j < n; ++j) {
            if (cmp_structs(mas[j], st)) { // 1 if equal
                flag = 1;

                if (strcmp(mas[j].pathname, argv[i]) < 0) {
                    mas[j].pathname = argv[i];
                }

                break;
            }
        }

        if (!flag) {
            if (n == capacity) {
                capacity *= 2;

                while (!realloc(mas, capacity * sizeof(mas[0])) && capacity > n) {
                    capacity--;
                }

                if (capacity == n) {
                    fprintf(stderr, "Error! Can't realloc mas\n");

                    return 1;
                }
            }

            mas[n++] = (struct File){argv[i], st.st_ino, st.st_dev};
        }
    }

    qsort(mas, n, sizeof(mas[0]), cmp_mas);

    for (int i = 0; i < n; ++i) {
        printf("%s\n", mas[i].pathname);
    }

    free(mas);

    return 0;
}
