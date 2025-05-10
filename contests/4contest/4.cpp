#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Acc {
    double sum = 0;
    size_t count = 0;

    void operator()(double value) {
        sum += value;
        count++;
    }
};

int main() {
    std::vector<double> data;

    double value;
    while (std::cin >> value) data.push_back(value);

    size_t n = data.size();
    size_t first_cut = n / 10;

    auto it_begin = data.begin() + first_cut;
    auto it_end = data.end() - first_cut;

    std::sort(it_begin, it_end);

    size_t min_cut = (it_end - it_begin) / 10;

    it_begin += min_cut;
    it_end -= min_cut;

    Acc acc = std::for_each(it_begin, it_end, Acc());

    std::cout << std::fixed << std::setprecision(10);
    std::cout << acc.sum / acc.count << std::endl;

    return 0;
}