#include <iostream>

class A {
    std::string s;
public:
    A(const std::string& s) : s(s) {}
    ~A() { std::cout << s << std::endl; }
};

void f() {
    std::string s;

    if (!(std::cin >> s)) {
        throw 0;
    }

    A a(s);
    f();
}

int main() {
    try {
        f();
    }
    catch (...) {

    }

    return 0;
}