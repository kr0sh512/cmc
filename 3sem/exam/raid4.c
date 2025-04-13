#include <unistd.h>
#include <fcntl.h>

enum
{
    BlockSize = 16,
}

int fds[5];
void
Write_Raid4(int num, char *buf)
{
    unsigned char tmp1[BlockSize];
    unsigned char tmp2[BlockSize];
    int num_disk = num % 4;

    lseek(fd[num_disk], num * BlockSize);
    lseek(fd[4], num * BlockSize);
    read(fd[num_disk], tmp1, BlockSize);
    read(fd[4], tmp2, BlockSize);

    for (int i = 0; i < BlockSize; ++i) {
        tmp2[i] ^= tmp1[i];
        tmp2[i] ^= buf[i];
    }

    lseek(fd[num_disk], num * BlockSize);
    lseek(fd[4], num * BlockSize);
    write(fd[num_disk], buf, BlockSize);
    write(fd[4], tmp2, BlockSize);

    return;
}
