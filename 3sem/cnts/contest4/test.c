#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void
create_binary_file(const char *filename, struct Node *nodes, int n)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; ++i) {
        struct Node node = nodes[i];
        node.key = htonl(node.key);
        node.left_idx = htonl(node.left_idx);
        node.right_idx = htonl(node.right_idx);
        write(fd, &node, sizeof(struct Node));
    }
    close(fd);
}

char *
execute_program(const char *filename)
{
    char command[256];
    snprintf(command, sizeof(command), "./04 %s", filename);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    char *output = malloc(1024);
    fread(output, 1, 1024, fp);
    pclose(fp);
    return output;
}

void
test_case(struct Node *nodes, int n, const char *expected_output)
{
    const char *filename = "test.bin";
    create_binary_file(filename, nodes, n);
    char *output = execute_program(filename);
    assert(strcmp(output, expected_output) == 0);
    free(output);
}

int
main()
{
    struct Node nodes1[] = {{10, 1, 2}, {5, 0, 0}, {15, 0, 0}};
    test_case(nodes1, 3, "15 10 5 \n");

    struct Node nodes2[] = {{20, 1, 2}, {10, 0, 0}, {30, 0, 0}};
    test_case(nodes2, 3, "30 20 10 \n");

    printf("All tests passed.\n");
    return 0;
}
