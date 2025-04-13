#include <stdio.h>
#include <stdint.h>

int
main()
{
    uint64_t num;
    int free_blocks = 0;

    while (scanf("%lx", &num) != EOF) {
        for (int i = 0; i < 64; i += 2) {
            if (((num >> i) & 0x3) == 0x0) {
                free_blocks++;
            }
        }
    }

    printf("%d\n", free_blocks);
    return 0;
}
