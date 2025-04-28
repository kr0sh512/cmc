// #include <iostream>
#include <vector>

template <typename T>
size_t incremental_seq(const T& cnt) {
    int max_len = 0;

    auto iter = cnt.begin();

    int last = *iter;
    int now = 1;
    while (iter != cnt.end()) {
        if (last + 1 == *iter) {
            ++now;
        } else {
            max_len = std::max(max_len, now);
            now = 1;
        }

        last = *iter;

        ++iter;
    }

    return max_len;
}


// int main() {
//     std::vector v{ 4,1,2,3,4,3,4,5 };
//     std::cout << incremental_seq(v) << std::endl;

//     return 0;
// }