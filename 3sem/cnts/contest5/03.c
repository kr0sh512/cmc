#include <stdlib.h>

enum
{
    RWX_PERMISSIONS = 0777,
};

int
parse_rwx_permissions(const char *str)
{
    if (str == NULL) {
        return -1;
    }

    const char expected[] = "rwxrwxrwx";

    unsigned res = 0;
    int i = 0;
    while (str[i]) {
        res <<= 1;

        if (str[i] == expected[i] && expected[i]) {
            res |= 1;
        } else if (str[i] != '-' || !expected[i]) {
            return -1;
        }

        ++i;
    }

    if (res > RWX_PERMISSIONS || res < 0 || expected[i]) {
        return -1;
    }

    return res;
}
