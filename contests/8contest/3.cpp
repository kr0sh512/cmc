/*
Реализуйте класс S следующим образом:

    Класс хранит целое число (типа int).
    Число считывается со стандартного потока ввода в конструкторе.
    Число выводится на стандартный поток вывода в деструкторе.
    Следующая программа:

    using namespace std;
    void func(S v)
    {
        if (v) {
            func(move(v));
        }
    }

    int main()
    {
        func(S());
    }

    считывает последовательность целых чисел и выводит на стандартный поток вывода их сумму.
    Если входная последовательность пустая, программа не выводит ничего.

Проверка на переполнение не требуется.

Глобальные переменные, static, mutable запрещены.

Сдаваемый на проверку класс должен подключать необходимые заголовочные файлы.
Examples
Input

1 2 3

Output

6
*/

#include <iostream>

class S {
    int v;
    int sum;
    bool last;
    bool first;
public:
    S(S&& s) {
        int val;
        first = false;

        if (std::cin >> val) {
            v = val;
            last = false;
            sum = s.sum + v;
        } else {
            last = true;
            sum = s.sum;
        }

    }
    ~S() {
        if (last && !first) {
            std::cout << sum << std::endl;
        }
    }
    S() : v(0), sum(0), last(true), first(true) {
        int val;

        if (std::cin >> val) {
            v = val;
            last = false;
            sum = v;
        }
    }

    operator bool() const {
        return !last;
    }
};

// using namespace std;
// void func(S v) {
//     if (v) {
//         func(move(v));
//     }
// }

// int main() {
//     func(S());
// }