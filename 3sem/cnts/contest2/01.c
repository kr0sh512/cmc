// #include <stdio.h>

typedef int STYPE;
typedef unsigned int UTYPE;

STYPE
bit_reverse(STYPE value)
{
    UTYPE result = 0;
    UTYPE uvalue = (UTYPE) value;
    for (int i = 0; i < sizeof(STYPE) * 8; i++) {
        result <<= 1;
        result |= uvalue & 1;
        uvalue >>= 1;
    }
    return (STYPE) result;
}

// int main(void) {

//     STYPE value = 0b10101010;
//     STYPE result = bit_reverse(value);
//     printf("%d\n", result);
//     printf("%ld\n", sizeof(STYPE));

//     return 0;
// }
