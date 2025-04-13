#include <stdio.h>
#include <stdlib.h>

enum
{
    NUM_OF_DIGITS = '9' - '0' + 1,
    NUM_OF_LETTERS = 'z' - 'a' + 1,
    BIT_MASK_1 = 0b111011,
    BIT_MASK_2 = 0b001000,
    MAX_NUM = 64,
};

int
main(void)
{
    int c;

    while ((c = getchar()) != EOF) {
        int code = 0;

        if (c <= '9' && c >= '0') {
            code = c - '0' + 1;
        } else if (c <= 'z' && c >= 'a') {
            code = c - 'a' + NUM_OF_DIGITS + 1;
        } else if (c <= 'Z' && c >= 'A') {
            code = c - 'A' + NUM_OF_DIGITS + NUM_OF_LETTERS + 1;
        }

        if (code == 0) {
            continue;
        }

        code = code & BIT_MASK_1;
        code ^= BIT_MASK_2;

        int res = 0;
        if (code <= NUM_OF_DIGITS && code >= 1) {
            res = code - 1 + '0';
        } else if (code <= NUM_OF_DIGITS + NUM_OF_LETTERS && code >= NUM_OF_DIGITS + 1) {
            res = code + 'a' - NUM_OF_DIGITS - 1;
        } else if (code <= NUM_OF_DIGITS + NUM_OF_LETTERS * 2 && code >= NUM_OF_DIGITS + NUM_OF_LETTERS + 1) {
            res = code + 'A' - NUM_OF_DIGITS - NUM_OF_LETTERS - 1;
        } else if (code == 0) {
            res = '@';
        } else if (code == MAX_NUM - 1) {
            res = '#';
        }

        putchar(res);
    }

    return 0;
}
