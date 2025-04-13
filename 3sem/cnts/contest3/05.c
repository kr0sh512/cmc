#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

enum
{
    CHAR_IN_INT = 12
};

struct Elem
{
    struct Elem *next;
    char *str;
};

struct Elem *
dup_elem(struct Elem *head)
{
    if (head == NULL) {
        return NULL;
    }

    head->next = dup_elem(head->next);

    errno = 0;
    char *p;
    long n = strtol(head->str, &p, 10);
    if (errno || (int) n != n || n == INT_MAX || *p || p == head->str) {
        return head;
    }

    struct Elem *new = calloc(1, sizeof(*new));
    if (new == NULL) {
        exit(1);
    }

    char *str = calloc(CHAR_IN_INT, sizeof(*str));
    snprintf(str, CHAR_IN_INT, "%d", (int) n + 1);

    new->str = str;
    new->next = head;

    return new;
}
