// -> написать шаблонную функцию, которая ищет макс значение в константном или неконстантном контейнере
#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <class Container>
typename Container::value_type Max(const Container& c) {
    typename Container::value_type max = *c.cbegin();

    for (auto it = c.cbegin(); it != c.cend(); ++it) {
        if (*it > max) {
            max = *it;
        }
    }

    return max;
}

template <typename T>
void dbl(T& c) {
    auto it = c.begin();

    while (it != c.end()) {
        it = c.insert(++it, *it);
        ++it;
    }

    return;
}

template <typename T>
void rever(T b, T e) {
    if (b == e) return;

    --e;

    while (b != e) {
        swap(*b++, *e);

        if (b == e) break;

        --e;
    }

    return;
}

struct Pred {
    bool operator()(int x) {
        return x % 3;
    }
};

template<typename T, typename P> // T - указатель P - предикат
void f(T b, T e, P pred, typename T::value_type val = {}) {
    while (b != e) {
        if (pred(*b)) {
            *b = val;
        }
        ++b;
    }

    return;
}

int main() {
    list<int> l = { 1, 2, 3, 4, 5 };
    cout << Max<list<int>>(l) << endl;

    f(l.begin(), l.end(), Pred());
    for (const auto& elem : l) {
        cout << elem << " ";
    }
    cout << endl;

    // dbl(l);
    // rever(l.begin(), l.end());
    // for (const auto& elem : l) {
    //     cout << elem << " ";
    // }
    // cout << endl;

    vector<long> v = { 1, 3, 3, 4, 5 };
    cout << Max<vector<long>>(v) << endl;

    // dbl(v);
    rever(v.begin(), v.end());
    for (const auto& elem : v) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}