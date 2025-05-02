#include <vector>
#include <algorithm>

void process(const std::vector<int>& v1, std::vector<int>& v2) {
    std::vector<int> copy_v1(v1);
    std::sort(copy_v1.begin(), copy_v1.end());
    auto last = std::unique(copy_v1.begin(), copy_v1.end());
    copy_v1.erase(last, copy_v1.end());

    auto iter = --v2.end();
    int num = (int)v2.size() - 1;

    while (iter != --v2.begin()) {
        if (std::binary_search(copy_v1.begin(), copy_v1.end(), num)) {
            iter = v2.erase(iter);
        }

        num--;
        iter--;
    }

    return;
}


// #include <iostream>
// int main() {
//     std::vector<int> v1 = { 0, 2, 4, 10, -6, 2, 2, 4 };
//     std::vector<int> v2 = { 0, 2, 4, 10, -6, 2, 2, 4 };

//     process(v1, v2);

//     for (auto& i : v2) {
//         std::cout << i << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }