#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <fstream>

int main() {
    std::map<int, std::map<char, int>> trans;
    std::set<int> accept_states;
    int init_state = -1;

    std::ifstream Input("noMore.in");
    std::string str;
    while (std::getline(Input, str)) {
        if (str.empty()) break;
        if (str.find("[[") != std::string::npos) {
            int state;
            sscanf(str.c_str(), "[[%d]]", &state);
            accept_states.insert(state);
            if (init_state == -1) {
                init_state = state;
            }
        } else if (std::count(str.begin(), str.end(), '[') == 2) {
            int left_state, right_state;
            char symbol;
            sscanf(str.c_str(), "[%d] %c [%d]", &left_state, &symbol, &right_state);
            if (init_state == -1) {
                init_state = left_state;
            }
            trans[left_state][symbol] = right_state;
        } else {
            int state;
            sscanf(str.c_str(), "[%d]", &state);
            if (init_state == -1) {
                init_state = state;
            }
        }
    }

    int N;
    Input >> N;

    std::vector<std::map<int, size_t>> dp(N + 1);
    dp[0][init_state] = 1;

    for (int k = 1; k <= N; ++k) {
        for (auto& [state, count] : dp[k - 1]) {
            for (auto& [symbol, right_state] : trans[state]) {
                dp[k][right_state] += count;
            }
        }
    }

    size_t ans = 0;
    for (int k = 0; k <= N; ++k) {
        for (auto& [state, count] : dp[k]) {
            if (accept_states.count(state)) {
                ans += count;
            }
        }
    }

    std::ofstream Output("noMore.out");
    Output << ans << std::endl;

    Output.close();
    Input.close();

    return 0;
}
