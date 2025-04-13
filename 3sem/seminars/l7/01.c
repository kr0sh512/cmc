#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR | O_CREAT, 0666);

    struct stat st;
    lseek(fd, 0, SEEK_END);
    stat(argv[1], &st);
    char *addr = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < st.st_size / 2; i++) {
        char tmp = addr[i];
        addr[i] = addr[st.st_size - i - 1];
        addr[st.st_size - i - 1] = tmp;
    }

    close(fd);
    munmap(addr, st.st_size);

    return 0;
}
