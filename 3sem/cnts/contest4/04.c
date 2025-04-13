#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void
inorder_traversal(struct Node *mas, int32_t idx, int32_t *keys, int32_t *pos)
{
    if (idx == 0) {
        return;
    }
    if (idx == -1) {
        idx = 0;
    }

    inorder_traversal(mas, mas[idx].left_idx, keys, pos);
    keys[(*pos)++] = mas[idx].key;
    inorder_traversal(mas, mas[idx].right_idx, keys, pos);

    return;
}

int
main(int argc, char **argv)
{
    if (argc < 2) {
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

    int n = lseek(fd, 0, SEEK_END) / sizeof(struct Node);
    lseek(fd, 0, SEEK_SET);

    struct Node *mas = calloc(n, sizeof(struct Node));

    for (int i = 0; i < n; ++i) {
        struct Node tmp;

        unsigned char buf[sizeof(tmp)];
        int r = read(fd, buf, sizeof(tmp));
        if (r == -1) {
            free(mas);
            close(fd);
            return 1;
        }
        if (r < 12) {
            break;
        }
        int n_byte = sizeof(int32_t);
        tmp.key = 0;
        tmp.left_idx = 0;
        tmp.right_idx = 0;
        if (is_le) {
            for (int j = 0; j < n_byte; ++j) {
                tmp.key |= (u_int32_t) buf[j] << (CHAR_BIT * j);
                tmp.left_idx |= (u_int32_t) buf[j + n_byte * 1] << (CHAR_BIT * j);
                tmp.right_idx |= (u_int32_t) buf[j + n_byte * 2] << (CHAR_BIT * j);
            }
        } else {
            for (int j = 0; j < n_byte; ++j) {
                tmp.key |= (u_int32_t) buf[j] << (CHAR_BIT * (sizeof(u_int32_t) - (j + 1)));
                tmp.left_idx |= (u_int32_t) buf[j + n_byte * 1] << (CHAR_BIT * (sizeof(u_int32_t) - (j + 1)));
                tmp.right_idx |= (u_int32_t) buf[j + n_byte * 2] << (CHAR_BIT * (sizeof(u_int32_t) - (j + 1)));
            }
        }

        mas[i] = tmp;
    }

    int32_t *keys = calloc(n, sizeof(int32_t));
    int32_t pos = 0;
    inorder_traversal(mas, -1, keys, &pos);

    for (int32_t i = 0; i < pos; ++i) {
        printf("%d\n", keys[i]);
    }

    free(keys);
    free(mas);
    close(fd);

    return 0;
}
