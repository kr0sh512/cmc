#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdint.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void
read_struct(int fd, struct Node *node, int is_le)
{
    unsigned char buf[sizeof(*node)];
    int n = 0;
    while (n != sizeof(*node)) {
        ssize_t off = read(fd, buf + n, sizeof(*node) - n);
        if (off == -1) {
            close(fd);
            exit(1);
        }
        n += off;
    }
    // int r = read(fd, buf, sizeof(*node));
    // if (r == -1) {
    //     close(fd);
    //     exit(1);
    // }

    int n_byte = sizeof(int32_t);
    node->key = 0;
    node->left_idx = 0;
    node->right_idx = 0;

    for (int j = 0; j < n_byte; ++j) {
        int off = (is_le) ? (CHAR_BIT * (sizeof(uint32_t) - (j + 1))) : (CHAR_BIT * j);

        node->key |= (uint32_t) buf[j] << off;
        node->left_idx |= (uint32_t) buf[j + n_byte * 1] << off;
        node->right_idx |= (uint32_t) buf[j + n_byte * 2] << off;
    }
}

void
inorder_traversal(int fd, int32_t idx, int is_le)
{
    if (idx == 0) {
        return;
    }
    if (idx == -1) {
        idx = 0;
    }

    struct Node tmp;
    if (lseek(fd, idx * sizeof(struct Node), SEEK_SET) == -1) {
        close(fd);
        exit(1);
    }
    read_struct(fd, &tmp, is_le);

    inorder_traversal(fd, tmp.right_idx, is_le);
    printf("%d\n", tmp.key);
    inorder_traversal(fd, tmp.left_idx, is_le);

    return;
}

int
main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }

    int test = 1;
    int is_le = 0;
    if (*(char *) &test == 1) {
        is_le = 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        return 1;
    }

    inorder_traversal(fd, -1, is_le);
    putchar('\n');
    close(fd);

    return 0;
}
