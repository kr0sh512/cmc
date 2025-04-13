#include <iostream>

class A {
private:
    int x;
    bool to_print;
public:
    A() {
        x = 0;
        to_print = false;
    }

    A(const A& a) {
        std::cin >> x;
        int t;
        std::cin >> t;
        x += t;
        to_print = true;
    }

    ~A() {
        if (to_print) {
            std::cout << x << std::endl;
        }
    }

};