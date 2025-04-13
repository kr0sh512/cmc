#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int fdin = open(argv[1], O_RDONLY);
    int fdout = open(argv[2], O_RDWR | O_CREAT, 0666);

    off_t len = lseek(fdin, 0, SEEK_END);
    char *fin = mmap(NULL, len, PROT_READ, MAP_SHARED, fdin, 0);

    ftruncate(fdout, len);
    char *fout = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0);

    memcpy(fout, fin, len);

    close(fdin);
    close(fdout);
    munmap(fin, len);
    munmap(fout, len);

    return 0;
}
