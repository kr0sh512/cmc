#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// пинг понг для n процессов

int
main(int argc, char **argv)
{
    int n = (int) strtoll(argv[1], NULL, 10);
    int max_n = (int) strtoll(argv[2], NULL, 10);

    for (int i = 0; i < n; ++i) {
    }

    while (wait(NULL) != -1)
        ;

    return 0;
}
