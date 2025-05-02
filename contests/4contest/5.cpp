#include <list>
#include <iostream>

int main() {
    std::list<int> l;

    int n;
    std::cin >> n;

    while (n != 0) {
        l.push_back(n);
        std::cin >> n;
    }

    while (std::cin >> n) {
        auto iter = l.begin();

        if (n < 0) {
            n = abs(++n);
            if ((size_t)n >= l.size()) {
                continue;
            }

            while (n--) ++iter;

            l.erase(iter);
        } else {
            int tmp;
            std::cin >> tmp;

            --n;
            while (n-- && iter != l.end()) ++iter;

            l.insert(iter, tmp);

            // l.insert();
        }
    }

    for (auto& i : l) {
        std::cout << i << std::endl;
    }

    return 0;
}
