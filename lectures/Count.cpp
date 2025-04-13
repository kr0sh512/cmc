#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>
#include <set>

/*
Количество слов

Напишите программу, которая для заданного ДКА и заданной максимальной длины N выводит общее количество слов не длинее N, допускаемых данным ДКА.

На вход программе подаётся описание ДКА в виде непустых строк следующих следующих видов.

1) Переход из состояния номер 1 в состояние номер 2 по символу "a":

[1] a [2]

2) Обозначение того, что состояние номер 3 является допускающим:

[[3]]

3) Явное объявление состояния под номером 4 (например, на случай если оно не фигурирует ни в каких переходах и не является допускающим):

[4]

После описания ДКА идёт пустая строка, за ней число N.

Номера состояний - это целые неотрицательные числа, в алфавит ДКА входят только строчные символы латинского алфавита.

Число N не может быть больше 100, а ответ помещается в тип size_t.

Начальным состоянием считается то, которое было первым объявлено в описании ДКА (либо в явном виде, либо при описании перехода).
Примеры
Входные данные в файле noMore.in

[0] a [1]
[1] a [0]
[1] b [0]
[[0]]

4

Результат работы в файле noMore.out

7
*/

int main() {
    std::ifstream inputFile("noMore.in");

    std::string line;
    std::regex firstLinePattern(R"(\[(\d+)\])");
    std::regex subsequentLinePattern(R"(\[(\d+)\]\s*([a-z])\s*\[(\d+)\])");
    std::regex finalLinePattern(R"(\[\[(\d+)\]\])");
    std::regex emptyLinePattern(R"(\s*)");
    std::regex numLinePattern(R"(\d+)");

    // Read the first line
    int start_num = -1;
    std::map<int, std::map<char, int>> transitions;
    std::set<int> final_states;

    int n = 0;

    // Read subsequent lines
    while (std::getline(inputFile, line)) {
        std::smatch match;
        if (std::regex_match(line, match, firstLinePattern)) {
            if (start_num == -1) {
                start_num = std::stoi(match[1].str());
            }
        } else if (std::regex_match(line, match, subsequentLinePattern)) {
            if (start_num == -1) {
                start_num = std::stoi(match[1].str());
            }
            int fromState = std::stoi(match[1].str());
            char symbol = match[2].str()[0];
            int toState = std::stoi(match[3].str());
            transitions[fromState][symbol] = toState;
        } else if (std::regex_match(line, match, finalLinePattern)) {
            final_states.insert(std::stoi(match[1].str()));
        } else if (std::regex_match(line, match, emptyLinePattern)) {
            continue;
        } else if (std::regex_match(line, match, numLinePattern)) {
            n = std::stoi(match[0].str());
        } else {
            break;
        }
    }
    inputFile.close();

    size_t ans = 0;
    std::vector<std::map<int, size_t>> dp(n + 1);
    dp[0][start_num] = 1;
    for (int k = 1; k <= n; ++k) {
        for (const auto& [state, count] : dp[k - 1]) {
            for (const auto& [symbol, nextState] : transitions[state]) {
                dp[k][nextState] += count;
            }
        }
    }
    for (int k = 0; k <= n; ++k) {
        for (const auto& [state, count] : dp[k]) {
            if (final_states.count(state)) {
                ans += count;
            }
        }
    }

    std::ofstream outputFile("noMore.out");
    outputFile << ans << std::endl;

    outputFile.close();

    return 0;
}