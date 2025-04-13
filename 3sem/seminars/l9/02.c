#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <errno.h>

// 8-ми сегментная таблица сегментов
// 32-х разрядная система

typedef struct
{
    int size;
    int base;
} segment;

unsigned int
f(segment *segtable, unsigned int VAdr)
{
    int bit = 3;
    unsigned int segnum = VAdr >> (32 - bit);
    unsigned int segoff = VAdr & ((1 << (32 - bit)) - 1);

    int addr = segtable[segnum].base + segoff;
    int size = segtable[segnum].size;

    if (segoff >= size) {
        return 25;
        // exit(1);
    }

    return addr;
}

int
main(int argc, char *argv[])
{
    segment segtable[8] = {};

    return 0;
}
