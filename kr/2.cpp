#include <vector>
// #include <iostream>
#include <algorithm>

template <typename I, typename F>
I separate(I beg, I end, F pred) {
    std::vector<int> mas_to;
    std::copy_if(beg, end, std::back_inserter(mas_to), pred);

    auto r = remove_if(beg, end, pred);
    std::copy(mas_to.begin(), mas_to.end(), r);

    return r;
}

// int main() {
//     std::vector v{ 1, -2, 3, -4, 5, -6 };
//     auto r = separate(v.begin(), v.end(), [](auto x) { return x >= 0; });

//     // std::cout << std::distance(v.begin(), r) << std::endl << std::endl;

//     std::cout << "meow" << std::endl;

//     for (auto& item : v) {
//         std::cout << item << std::endl;
//     }

//     return 0;
// }