#include <map>
#include <vector>
#include <iostream>

int main() {
    std::map<std::string, std::vector<int>> mp;

    std::string name;
    int grade;
    while (std::cin >> name >> grade) {
        mp[name].push_back(grade);
    }

    for (auto& x : mp) {
        std::cout << x.first << " ";

        double tmp = 0;
        int n = 0;
        for (auto& i : x.second) {
            tmp += i;
            ++n;
        }

        std::cout << tmp / n << std::endl;
    }

    return 0;
}