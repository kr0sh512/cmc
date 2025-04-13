#include <vector>
#include <set>
#include <algorithm>
#include <cstdint>

void process(const std::vector<int>& mas1, std::vector<int>& mas2) {
    std::set<int> set1(mas1.begin(), mas1.end());

    if (set1.empty() || mas2.empty()) {
        return;
    }

    for (auto it = mas2.end() - 1; it != mas2.begin() - 1; --it) {
        int dst = it - mas2.begin();

        if (std::find(set1.begin(), set1.end(), dst) != set1.end()) {
            mas2.erase(it);
        }
    }

    return;
}