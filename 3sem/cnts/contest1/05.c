#include <stdio.h>
#include <stdlib.h>

void
swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;

    return;
}

int
next_permutation(int *arr, int n)
{
    int i = n - 2;

    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    if (i < 0) {
        return 0;
    }

    int j = n - 1;

    while (arr[j] <= arr[i]) {
        j--;
    }

    swap(&arr[i], &arr[j]);

    int pt1 = i + 1, pt2 = n - 1;

    while (pt1 < pt2) {
        swap(&arr[pt1++], &arr[pt2--]);
    }

    return 1;
}

int
main()
{
    int n;

    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    if (n <= 0 || n >= 10) {
        return 1;
    }

    int *arr = (int *) malloc(n * sizeof(*arr));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    do {
        for (int i = 0; i < n; i++) {
            printf("%d", arr[i]);
        }

        printf("\n");
    } while (next_permutation(arr, n));

    free(arr);

    return 0;
}
