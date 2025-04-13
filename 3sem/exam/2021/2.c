#include <unistd.h>
#include <fcntl.h>

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
        sizes[i] = st.st_size / BlockSize;
        if (i != 0) {
            sizes[i] += sizes[i - 1];
        }
    }

    return;
}

void
Read_Raid0(int num, char *buf)
{
    int now_disk = 0;
    int now_block = 0;
    while (now_block != num) {
                if (sizes[now_disk]
		
		now_disk++;
		now_block++;
		now_disk %= 4;
    }

    return;
}
