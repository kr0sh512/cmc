#include <stdio.h>

enum
{
    MY_INT_MAX = ~0u >> (!0),
    MY_INT_MIN = ~(~0u >> (!0))
};

int
satsum(int v1, int v2)
{
    int sum;
    if (!__builtin_add_overflow(v1, v2, &sum)) {
        return sum;
    } else if (v1 > 0) {
        return MY_INT_MAX;
    } else {
        return MY_INT_MIN;
    }

    return 0;
}
