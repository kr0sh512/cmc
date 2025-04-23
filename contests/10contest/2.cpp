#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <stack>

void optimize(std::map<char, std::vector<std::string>>& map) {
    std::set<char> exist;
    std::stack<char> stack;


    stack.push('S');
    exist.insert('S');

    while (!stack.empty()) {
        char now = stack.top();
        stack.pop();

        for (const auto& str : map[now]) {
            for (const auto& c : str) {
                if (!('A' <= c && c <= 'Z')) {
                    continue;
                }
                if (exist.find(c) == exist.end()) {
                    exist.insert(c);
                    stack.push(c);
                }
            }
        }
    }

    auto it = map.begin();
    while (it != map.end()) {
        if (exist.find(it->first) == exist.end()) {
            it = map.erase(it);
        } else {
            ++it;
        }

    }

    return;
}

int main() {
    // std::vector<std::pair<char, std::string>> mas;
    std::map<char, std::vector<std::string>> map;
    char left;
    std::string right;

    while (std::cin >> left >> right) {
        // mas.push_back(std::make_pair(left, right));
        map[left].push_back(right);
    }

    optimize(map);

    // for (const auto& rule : mas) {
    //     if (map.find(rule.first) != map.end()) {
    //         std::cout << rule.first << " " << rule.second << std::endl;
    //     }
    // }

    for (const auto& rules : map) {
        for (const auto& rule : rules.second) {
            std::cout << rules.first << " " << rule << std::endl;
        }
    }

    return 0;
}