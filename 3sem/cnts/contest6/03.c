#include <stdlib.h>

struct s1
{
    char f1;
    long long f2;
    char f3;
};

struct s2
{
    char f1;
    char f3;
    long long f2;
};

size_t
compactify(void *ptr, size_t size)
{
    if (size == 0) {
        return 0;
    }

    size_t count = size / sizeof(struct s1);
    struct s1 *src = (struct s1 *) ptr;
    struct s2 *dst = (struct s2 *) ptr;

    for (size_t i = 0; i < count; ++i) {
        struct s1 tmp = src[i];
        dst[i].f1 = tmp.f1;
        dst[i].f3 = tmp.f3;
        dst[i].f2 = tmp.f2;
    }

    return count * sizeof(struct s2);
}
