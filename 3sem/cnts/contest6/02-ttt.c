#include <stdio.h>        // Standard I/O functions
#include <stdlib.h>       // Standard library functions: memory allocation, process control, conversions, etc.
#include <fcntl.h>        // File control options
#include <unistd.h>       // POSIX API: read, write, close, etc.
#include <sys/file.h>     // File control options
#include <sys/types.h>    // Data types used in system calls
#include <sys/stat.h>     // Data returned by the functions fstat(), lstat(), and stat()
#include <linux/limits.h> // Sizes of basic types
#include <limits.h>       // Sizes of basic types
#include <errno.h>        // Error reporting macros
#include <stdint.h>       // Exact-width integer types
#include <math.h>         // Mathematical functions
#include <dirent.h>       // Directory entry format
#include <string.h>       // String handling functions
#include <sys/stat.h>     // Data returned by the functions fstat(), lstat(), and stat()

// переписать на strcmp.

void
normalize_path(char *buf)
{
    unsigned long long pt_real = 0, pt_res = 0;

    unsigned long long len = 0; // проверить правильное вычисление длины
    while (buf[len++] != '\0')
        ;
    len--;

    while (pt_real < len) {
        printf("pt: %lld -- %d %d %d\n", pt_real, pt_real - 2 == len, buf[pt_real] == '.',
               buf[pt_real + 1] == '.'); // может вызвать выход за массив
        if ((len - pt_real >= 3 && buf[pt_real] == '.' && buf[pt_real + 1] == '.' && buf[pt_real + 2] == '/') ||
            (pt_real - 2 == len && buf[pt_real] == '.' && buf[pt_real + 1] == '.')) {
            printf("meow\n");
            if (pt_real > 0 && buf[pt_real - 1] == '/') {
                pt_real += 3;

                if (pt_res == 1) {
                    continue;
                }

                if (pt_res == 0) { // impossible ?
                    pt_res = 1;
                    continue;
                }
                pt_res -= 2;
                while (pt_res > 0 && buf[pt_res] != '/') {
                    pt_res--;
                }

                pt_res++;
                continue;
            }
        } else if ((len - pt_real >= 2 && buf[pt_real] == '.' && buf[pt_real + 1] == '/') ||
                   (len == pt_real - 1 && buf[pt_real] == '.')) {
            if (pt_real > 0 && buf[pt_real - 1] == '/') {
                // printf("paw\n");
                pt_real += 2;

                continue;
            }
        }

        buf[pt_res] = buf[pt_real];
        pt_real++;
        pt_res++;
    }

    // if (pt_real > 1 && buf[pt_real - 1] == '.') {
    //     if (pt_real > 2 && buf[pt_real - 2] == '.' && buf[pt_real - 3] == '/') {
    //         if (pt_res > 1) {
    //             pt_res -= 2;
    //             while (pt_res > 0 && buf[pt_res - 1] != '/') {
    //                 pt_res--;
    //             }
    //         }
    //     } else if (pt_real > 1 && buf[pt_real - 2] == '/') {
    //         if (pt_res > 0) {
    //             pt_res--;
    //         }
    //     }
    // }

    buf[pt_res] = '\0';

    if (pt_res > 1 && buf[pt_res - 1] == '/') {
        buf[pt_res - 1] = '\0';
    }

    return;
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char path[PATH_MAX];
    strncpy(path, argv[1], PATH_MAX - 1);
    path[PATH_MAX - 1] = '\0';

    normalize_path(path);

    printf("Normalized path: %s\n", path);

    return EXIT_SUCCESS;
}
