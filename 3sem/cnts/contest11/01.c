#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdio.h>

int
proc(void)
{
    int pid = fork();
    if (!pid) {
        write(1, "1\n", 2);
    }
    return pid;
}

int
main(int argc, char **argv)
{
    proc(), proc(), proc();

    return 0;
}
