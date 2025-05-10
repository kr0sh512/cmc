#include <iostream>
#include <string>
#include <cctype>

int main() {
    int c;
    c = getchar();

    bool is_num = false;

    while (c != EOF) {
        if (c == '0' && !is_num) {
            int old = c;
            c = getchar();

            if (isdigit(c)) {
                continue;
            }

            if (c == EOF) {
                putchar(old);
                break;
            }

            putchar(old);
        } else if (isdigit(c)) {
            is_num = true;
        } else {
            is_num = false;
        }

        putchar(c);
        c = getchar();
    }

    return 0;
}