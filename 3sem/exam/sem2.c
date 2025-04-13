// суть - предсказываем поведение кэша.

#include <stdio.h>
#include <string.h>

enum
{
    CACHE_LEN = 1024,
    BLOCK_SIZE = 512,
};

int
main(void)
{
    unsigned addrs[CACHE_LEN];
    memset(addrs, -1, CACHE_LEN);

    unsigned addr, cnt = 0;
    while (scanf("%u", &addr) == 1) {
        int i = (addr / BLOCK_SIZE) % CACHE_LEN;
        cnt += (addrs[i] != -1) && (addrs[i] != addr);
        addrs[i] = addr;
    }
}
