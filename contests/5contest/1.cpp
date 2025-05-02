#include <iostream>
#include <vector>
#include <algorithm>

int cnt_bit(unsigned int a) {
    int res1 = 0;
    while (a != 0) {
        res1 += a & 1;
        a = a >> 1;
    }

    return res1;
}

bool comp(unsigned int a, unsigned int b) {
    return cnt_bit(a) < cnt_bit(b);
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