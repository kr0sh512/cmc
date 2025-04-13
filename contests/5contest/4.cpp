#include <map>
#include <iostream>

int main() {
    long long mod = 4294967161;

    std::map<std::pair<long long, long long>, long long> mp;

    long long r, c, v;
    while (std::cin >> r >> c >> v) {
        if (!r && !c && v == mod) break;

        mp[std::make_pair(r, c)] = v;
    }

    while (std::cin >> r >> c >> v) {
        mp[std::make_pair(r, c)] += v;
        mp[std::make_pair(r, c)] %= mod;
    }

    for (auto x : mp) {
        if (x.second) std::cout << x.first.first << " " << x.first.second << " " << x.second << std::endl;
    }

    return 0;
}