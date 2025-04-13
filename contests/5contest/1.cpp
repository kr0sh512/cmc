#include <iostream>
#include <vector>
#include <algorithm>

bool comp(unsigned int a, unsigned int b) {
    int res1 = 0;
    while (a != 0) {
        res1 += a & 1;
        a = a >> 1;
    }

    int res2 = 0;
    while (b != 0) {
        res2 += b & 1;
        b = b >> 1;
    }

    return res1 < res2;
}


int main() {
    std::vector<unsigned int> v;
    unsigned int tmp;
    while (std::cin >> tmp) {
        v.push_back(tmp);
    }

    std::stable_sort(v.begin(), v.end(), comp);

    for (auto x : v) {
        std::cout << x << std::endl;
    }

    return 0;
}