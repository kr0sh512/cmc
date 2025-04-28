#include <vector>
#include <iostream>
#include <algorithm>

template <typename I, typename F>
I separate(I beg, I end, F pred) {
    auto tmp = beg;
    while (tmp != end) {
        std::cout << *tmp << std::endl;
        ++tmp;
    }


    auto r = remove_if(beg, end, pred);

    tmp = beg;
    while (tmp != end) {
        std::cout << *tmp << std::endl;
        ++tmp;
    }

    std::cout << "meow" << std::endl;

    return r;
}

int main() {
    std::vector v{ 1, -2, 3, -4, 5, -6 };
    auto r = separate(v.begin(), v.end(), [](auto x) { return x >= 0; });

    // std::cout << std::distance(v.begin(), r) << std::endl << std::endl;

    for (auto& item : v) {
        std::cout << item << std::endl;
    }

    return 0;
}