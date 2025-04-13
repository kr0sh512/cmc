#include <iostream>

class C
{
    unsigned long long x = 0;
    bool last = false;

public:
    C() {
        if (std::cin >> x) {
            return;
        }

        last = true;
    }

    ~C() {
        if (last) {
            return;
        }

        std::cout << x << " ";
    }
};

void
f() {
    C c;

    if (std::cin.eof()) {
        return;
    }

    f();

    return;
}

int
main() {
    f();
    std::cout << std::endl;

    return 0;
}
