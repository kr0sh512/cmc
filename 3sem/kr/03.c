#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int
main(int argc, char **argv)
{
    int mas[5] = {0, 0, 0, 0, 0};

    int num = 5, tmp;

    while (scanf("%d", &tmp) == 1) {
        for (int i = 0; i < 4; i++) {
            mas[i] = mas[i + 1];
        }
        mas[4] = tmp;
        num--;
    }

    // if (num < 0) {
    //     num = 0;
    // }
    num = num < 0 ? 0 : num;

    for (int i = num; i < 5; i++) {
        printf("%d ", mas[i]);
    }
    printf("\n");

    return 0;
}
