#include <unistd.h>
#include <fcntl.h>

// Стоит добавить проверки на успешность системных вызовов

enum
{
    BlockSize = 16,
}

int fds[4];
unsigned int sizes[4];
char **list = [ "Disk0", "Disk0", "Disk0", "Disk0" ];

void
Ini_Raid0(void)
{
    struct stat st;
    for (int i = 0; i < 4; ++i) {
        fds[i] = open(list[i], O_RDWR);
        lstat(list[i], &st);
        sizes[i] = st.st_size;
        if (i != 0) {
            sizes[i] += sizes[i - 1];
        }
    }

    return;
}

void
Read_Raid0(int num, char *buf)
{
    unsigned int byte = num * BlockSize;
    int now_disk = 0;

    for (int i = 0; i < BlockSize; ++i) {
        while (byte > sizes[now_disk]) {
            now_disk++;
        }

        if (now_disk > 3) {
            _exit(1);
        }

        if (now_disk != 0) {
            lseek(fds[now_disk], byte - sizes[now_disk - 1]);
        } else {
            lseek(fds[now_disk], byte);
        }
        read(fds[now_disk], 1, buf + i);
    }

    return;
}
