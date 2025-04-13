/**
 * @file templates.c
 * @brief This file contains various template functions and includes necessary headers for file operations, memory
 * management, mathematical computations, and system calls.
 *
 * The following libraries are included:
 * - stdio.h: Provides functionalities for file operations such as fopen, fclose, fprintf, fscanf, printf, and scanf.
 * - stdlib.h: Provides functionalities for memory management, conversions, and other utility functions such as exit,
 * malloc, free, atoi, strtol, strtoul, atof, strtod, abs, labs, llabs, div, ldiv, and lldiv.
 * - fcntl.h: Provides file control options such as O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_EXCL, O_TRUNC, O_APPEND,
 * O_NONBLOCK, O_SYNC, O_DSYNC, O_RSYNC, O_FSYNC, O_ASYNC, O_CLOEXEC, O_DIRECTORY, O_NOFOLLOW, O_NOCTTY, O_TMPFILE,
 * O_DIRECT, O_LARGEFILE, O_NOATIME, O_PATH, and O_NDELAY.
 * - unistd.h: Provides access to the POSIX operating system API.
 * - sys/file.h: Provides file control options.
 * - sys/types.h: Defines data types used in system calls such as mode_t, off_t, pid_t, uid_t, gid_t, dev_t, ino_t,
 * nlink_t, blksize_t, blkcnt_t, fsblkcnt_t, and fsfilcnt_t.
 * - sys/stat.h: Defines the structure of the data returned by the functions fstat(), lstat(), and stat().
 * - limits.h: Defines the sizes of basic types.
 * - errno.h: Defines macros for reporting and retrieving error conditions through error codes.
 * - stdint.h: Provides a set of typedefs that specify exact-width integer types.
 * - math.h: Provides mathematical functions.
 * - dirent.h: Defines the format of directory entries.
 * - string.h: Provides string handling functions.
 *
 * The following functions are implemented:
 * - void safe_read(int fd, void *buf, size_t count): Reads data from a file descriptor safely, handling interruptions
 * and errors.
 * - void safe_write(int fd, void *buf, size_t count): Writes data to a file descriptor safely, handling interruptions
 * and errors.
 * - void str_to_ll(char *str, long long *num): Converts a string to a long long integer, handling errors.
 * - void endian_swap(void *src, void *dst, size_t size): Swaps the endianness of a block of memory.
 *
 * The main function:
 * - int main(int argc, char *argv[]): Template main function that checks the number of arguments, opens input and
 * output files, and closes them.
 */

#include <stdio.h>     // Standard I/O functions
#include <stdlib.h>    // Standard library functions: memory allocation, process control, conversions, etc.
#include <fcntl.h>     // File control options
#include <unistd.h>    // POSIX API: read, write, close, etc.
#include <sys/file.h>  // File control options
#include <sys/types.h> // Data types used in system calls
#include <sys/stat.h>  // Data returned by the functions fstat(), lstat(), and stat()
#include <limits.h>    // Sizes of basic types
#include <errno.h>     // Error reporting macros
#include <stdint.h>    // Exact-width integer types
#include <math.h>      // Mathematical functions
#include <dirent.h>    // Directory entry format
#include <string.h>    // String handling functions
#include <sys/stat.h>  // Data returned by the functions fstat(), lstat(), and stat()

// Function declarations
int safe_read(int fd, void *buf, size_t count);      // Reads data from a file descriptor safely
int safe_write(int fd, void *buf, size_t count);     // Writes data to a file descriptor safely
void str_to_ll(char *str, long long *num);           // Converts a string to a long long integer
void endian_swap(void *src, void *dst, size_t size); // Swaps the endianness of a block of memory

int
safe_read(int fd, void *buf, size_t count)
{
    errno = 0;
    size_t bytes_read = 0;
    while (bytes_read < count) {
        ssize_t res = read(fd, buf + bytes_read, count - bytes_read);

        if (res < 0) {
            if (errno == EINTR) {
                errno = 0;
                continue;
            }

            fprintf(stderr, "Error reading from file descriptor %d\n", fd);
            close(fd);
            exit(1); // TODO: по-хорошему заменить на внешний обработчик ошибок
        }

        if (res == 0) {
            break;
        }

        bytes_read += res;
    }

    return bytes_read;
}

int
safe_write(int fd, void *buf, size_t count)
{
    errno = 0;
    size_t bytes_written = 0;
    while (bytes_written < count) {
        ssize_t res = write(fd, buf + bytes_written, count - bytes_written);

        if (res < 0) {
            if (errno == EINTR) {
                errno = 0;
                continue;
            }

            fprintf(stderr, "Error writing to file descriptor %d\n", fd);
            close(fd);
            exit(1); // TODO: по-хорошему заменить на внешний обработчик ошибок
        }

        bytes_written += res;
    }

    return bytes_written;
}

void
str_to_ll(char *str, long long *num)
{
    errno = 0;
    char *endptr;
    *num = strtoll(str, &endptr, 10);

    if (*endptr || errno || endptr == str) {
        fprintf(stderr, "Invalid number: %s\n", str);
        exit(1); // TODO: по-хорошему заменить на внешний обработчик ошибок
    }

    return;
}

void
endian_swap(void *src, void *dst, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        ((char *) dst)[i] = ((char *) src)[size - i - 1];
    }

    return;
}

// template main function
enum
{
    ARGS_NUM = 4,
};

int
main(int argc, char *argv[])
{
    if (argc != ARGS_NUM) {
        fprintf(stderr, "Wrong number of arguments\n");
        return 1;
    }

    int fdin = open(argv[1], O_RDONLY);
    if (fdin == -1) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);

        return 1;
    }

    int fdout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fdout == -1) {
        fprintf(stderr, "Error opening file %s\n", argv[2]);
        close(fdin);

        return 1;
    }

    close(fdin);
    close(fdout);

    return 0;
}
