#include <vector>
#include <cstdint>

void process(std::vector<int64_t>& mas, int64_t limit) {
    auto itert = mas.end();
    int dst = 0;

    for (auto it = mas.begin() + mas.size() - 1; it != mas.begin() - 1; --it) {
        dst = it - mas.begin();

        if (*it >= limit) {
            mas.insert(itert, *it);
            itert = mas.end();
        }

        it = mas.begin() + dst;
    }

    return;
}

// #include <iostream>

// int main() {
//     std::vector<int64_t> mas = { 1, 4, 3, 2 };
//     int64_t limit = 3;

//     process(mas, limit);

//     for (const auto& val : mas) {
//         std::cout << val << " ";
//     }

//     return 0;
// }