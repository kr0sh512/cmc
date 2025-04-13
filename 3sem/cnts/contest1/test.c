#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>

int
cmp(const void *a, const void *b)
{
    if (*(int *) a % 2 == 0) {
        if (*(int *) b % 2 == 1) {
            return -1;
        }
        if (*(int *) a > *(int *) b) {
            return 1;
        }
        if (*(int *) a < *(int *) b) {
            return -1;
        }
        return 0;
    }
    if (*(int *) b % 2 == 0) {
        return 1;
    }
    if (*(int *) a > *(int *) b) {
        return -1;
    }
    if (*(int *) a < *(int *) b) {
        return 1;
    }
    return 0;
}

void
sort_even_odd(size_t count, int *data)
{
    qsort(data, count, sizeof(int), cmp);
}

int
main()
{
    int a[] = {4, 2, 5, 3, 1, 0, -4, -2, -68, 23, 3};
    sort_even_odd(sizeof(a) / sizeof(a[0]), a);

    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%d ", a[i]);
    }

    printf("\n");

    return 0;
}
