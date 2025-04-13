#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{
    int fdin = open("in", O_RDWR);
    if (fdin == -1) {
        return 1;
    }

    double num1, num2;

    // Read the first double
    if (read(fdin, &num1, sizeof(double)) != sizeof(double)) {
        close(fdin);
        return 1;
    }

    // Read the second double
    if (read(fdin, &num2, sizeof(double)) != sizeof(double)) {
        close(fdin);
        return 1;
    }

    // Move the file pointer back to the beginning
    if (lseek(fdin, 0, SEEK_SET) == -1) {
        close(fdin);
        return 1;
    }

    // Write the second double first
    if (write(fdin, &num2, sizeof(double)) != sizeof(double)) {
        close(fdin);
        return 1;
    }

    // Write the first double second
    if (write(fdin, &num1, sizeof(double)) != sizeof(double)) {
        close(fdin);
        return 1;
    }

    close(fdin);

    return 0;
}
