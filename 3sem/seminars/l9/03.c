#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <errno.h>

// инвертированная сегментная таблица сегментов
// 32-х разрядная система

typedef struct
{
    pid_t pid;
    unsigned int VirtNum;
} page_record;

unsigned int
f(page_record *pagetable, unsigned int VAdr, int size_segtable)
{
    pid_t pid = getpid();

    unsigned int pagenum = VAdr >> (12); // 12 - размер страницы

    for (int i = 0; i < size_segtable; i++) {
        if (pagetable[i].VirtNum == pagenum && pagetable[i].pid == pid) {
            return i << (32 - 12) + (VAdr << 20 >> 20);
        }
    }

    return -1;
}

int
main(int argc, char *argv[])
{
    return 0;
}
