#include <iostream>
#include <string>

class Result {
    long long val;
public:
    Result(long long val) : val(val) {}
    long long value() const { return val; }
};

// Функция определена по условию. Выкидывает результат в виде exception
void f(long long a, long long b, int k) {
    if (k == 0) {
        throw Result(a + b);
    }

    if (b == 1) {
        throw Result(a);
    }

    try {
        f(a, b - 1, k);
    }
    catch (const Result& result) {
        f(a, result.value(), k - 1);
    }
}

int main() {
    long long a, b;
    int k;
    while (std::cin >> a >> b >> k) {
        try {
            f(a, b, k);
        }
        catch (const Result& result) {
            std::cout << result.value() << std::endl;
        }
    }

    return 0;
}