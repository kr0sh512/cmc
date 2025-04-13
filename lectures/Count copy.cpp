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
    std::regex state_declaration_pattern(R"(\[(\d+)\])");
    std::regex transition_pattern(R"(\[(\d+)\]\s*([a-z])\s*\[(\d+)\])");
    std::regex accepting_state_pattern(R"(\[\[(\d+)\]\])");

    std::map<int, std::map<char, int>> state_transitions;
    std::set<int> accepting_states;
    int start_state = -1;

    std::ifstream Input("noMore.in");
    std::string line;

    while (std::getline(Input, line)) {
        std::smatch match_result;

        if (start_state == -1 && std::regex_match(line, match_result, state_declaration_pattern)) {
            start_state = std::stoi(match_result[1].str());
        } else if (std::regex_match(line, match_result, transition_pattern)) {
            start_state = start_state == -1 ? std::stoi(match_result[1].str()) : start_state;
            state_transitions[std::stoi(match_result[1].str())][match_result[2].str()[0]] = std::stoi(match_result[3].str());
        } else if (std::regex_match(line, match_result, accepting_state_pattern)) {
            accepting_states.insert(std::stoi(match_result[1].str()));
        } else if (line.empty()) {
            break;
        }
    }

    int max_length;
    Input >> max_length;
    Input.close();

    size_t total_count = 0;
    std::vector<std::map<int, size_t>> dp_table(max_length + 1);
    dp_table[0][start_state] = 1;

    for (int length = 1; length <= max_length; ++length) {
        for (const auto& [current_state, count] : dp_table[length - 1]) {
            for (const auto& [transition_char, next_state] : state_transitions[current_state]) {
                dp_table[length][next_state] += count;
            }
        }
    }

    for (int length = 0; length <= max_length; ++length) {
        for (const auto& [state, count] : dp_table[length]) {
            if (accepting_states.count(state)) {
                total_count += count;
            }
        }
    }

    std::ofstream Output("noMore.out");
    Output << total_count << std::endl;
    Output.close();

    return 0;
}
