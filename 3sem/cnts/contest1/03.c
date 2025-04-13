#include <stdio.h>
#include <stdlib.h>

enum
{
    MAX_N = 2000
};

int
is_prime(int num)
{
    if (num <= 1) {
        return 0;
    }
    if (num <= 3) {
        return 1;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return 0;
    }
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

int
main(void)
{
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    if (n >= MAX_N || !is_prime(n)) {
        return 1;
    }

    // двумерный под хранение результата. Не может быть одномерным, т.к. заполняются столбцы по порядку
    int **mas = (int **) malloc(n * sizeof(mas));
    if (mas == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        mas[i] = (int *) malloc(n * sizeof(*mas));

        if (mas[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(mas[j]);
            }

            free(mas);
            return 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int a = 0; a < n; a++) {
            mas[i][(a * i) % n] = a;
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 1; i < n; i++) {
            printf("%d ", mas[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(mas[i]);
    }
    free(mas);

    return 0;
}
