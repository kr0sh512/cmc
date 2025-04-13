#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

volatile int counter = 0;
volatile int signals = 0;

int fd2;

void handler(int sig) {
    ++signals;
    if (signals < 3) {
        printf("%d\n", counter / 2);
    } else {
        lseek(fd2, 0, SEEK_SET);
        char buf;
        while (read(fd2, &buf, 1) > 0) {
            write(1, &buf, 1);
        }
        exit(0);
    }

}

int main(int argc, char** argv) {
    signal(SIGINT, handler);

    int fd1 = open(argv[1], O_RDONLY, 0666);
    fd2 = open(argv[2], O_CREAT | O_WRONLY);

    char buf;
    while (read(fd1, &buf, 1) > 0) {
        if (counter % 2 == 0) {
            write(fd2, &buf, 1);
        }
        ++counter;
    }

    return 0;
}