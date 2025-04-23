// Разбор журналов

// Реализуйте класс CFGrammar, который используется для представления контекстно-свободной грамматики и вычисления множеств First и Follow для её нетерминалов. Терминалами грамматики считаются строчные символы латинского алфавита, а нетерминалами - заглавные символы латинского алфавита.

// 1) У класса должен быть реализован метод add_rule(char, const std::string&) для добавления нового правила в грамматику. Первый аргумент представляет нетерминал, из которого выводится правило, и может иметь значения от "А" до "Z". Второй аргумент представляет само правило, выводимое из данного нетерминала и может быть строкой (возможно, пустой), состоящей из допустимых терминалов и нетерминалов.

// 2) У класса должен быть реализован метод get_first(), который возвращает ассоциативный массив (map или unordered_map), ключами которого являются нетерминалы грамматики, а значениями - множество символов, входящих в First от этого нетерминала. Допустимыми элементами множества являются терминалы и специальный символ '_' для обозначения пустой цепочки (эпсилон).

// 3) У класса должен быть реализован метод get_follow(), который возвращает ассоциативный массив (map или unordered_map), ключами которого являются нетерминалы грамматики, а значениями - множество символов, входящих в Follow от этого нетерминала. Допустимыми элементами множества являются терминалы и специальный символ '$' для обозначения конца строки.

// 4) У класса должен быть реализован метод is_ll1(), который возвращает true, если грамматика удовлетворяет критерию LL(1) и false в противном случае.

// После подстановки решения студента, следующий код должен работать и выдавать ожидаемый результат (см. пример ввода и вывода):

#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool is_terminal(char c) { return c >= 'a' && c <= 'z'; }
bool is_non_terminal(char c) { return c >= 'A' && c <= 'Z'; }

std::string set_to_canonical_string(const auto& set_of_chars, char special_symbol) {
    std::string result;
    bool has_special_symbol = false;
    for (char c : set_of_chars) {
        if (is_terminal(c))
            result += c;
        else
            has_special_symbol = true;
    }
    std::sort(result.begin(), result.end());
    if (has_special_symbol)
        result += special_symbol;
    return result;
}

// Here goes your submission

class CFGrammar {
private:
    std::unordered_map<char, std::vector<std::string>> rules;
    std::unordered_map<char, std::set<char>> first;
    std::unordered_map<char, std::set<char>> follow;

    void compute_first() {
        bool changed;
        do {
            changed = false;
            for (const auto& [non_terminal, productions] : rules) {
                for (const auto& production : productions) {
                    bool nullable = true;
                    for (char symbol : production) {
                        if (is_terminal(symbol)) {
                            if (first[non_terminal].insert(symbol).second) {
                                changed = true;
                            }
                            nullable = false;
                            break;
                        } else if (is_non_terminal(symbol)) {
                            for (char c : first[symbol]) {
                                if (c != '_' && first[non_terminal].insert(c).second) {
                                    changed = true;
                                }
                            }
                            if (first[symbol].count('_') == 0) {
                                nullable = false;
                                break;
                            }
                        }
                    }
                    if (nullable && first[non_terminal].insert('_').second) {
                        changed = true;
                    }
                }
            }
        } while (changed);
    }

    void compute_follow() {
        follow.begin()->second.insert('$');
        bool changed;
        do {
            changed = false;
            for (const auto& [non_terminal, productions] : rules) {
                for (const auto& production : productions) {
                    std::set<char> trailer = follow[non_terminal];
                    for (auto it = production.rbegin(); it != production.rend(); ++it) {
                        char symbol = *it;
                        if (is_non_terminal(symbol)) {
                            for (char c : trailer) {
                                if (follow[symbol].insert(c).second) {
                                    changed = true;
                                }
                            }
                            if (first[symbol].count('_') == 1) {
                                trailer.insert(first[symbol].begin(), first[symbol].end());
                                trailer.erase('_');
                            } else {
                                trailer = first[symbol];
                            }
                        } else if (is_terminal(symbol)) {
                            trailer = { symbol };
                        } else {
                            trailer.clear();
                        }
                    }
                }
            }
        } while (changed);
    }

public:
    void add_rule(char non_terminal, const std::string& production) {
        rules[non_terminal].push_back(production);
    }

    std::unordered_map<char, std::set<char>> get_first() {
        if (first.empty()) {
            compute_first();
        }
        return first;
    }

    std::unordered_map<char, std::set<char>> get_follow() {
        if (follow.empty()) {
            compute_first();
            compute_follow();
        }
        return follow;
    }

    bool is_ll1() {
        for (const auto& [non_terminal, productions] : rules) {
            std::set<char> seen;
            for (const auto& production : productions) {
                std::set<char> first_set;
                bool nullable = true;
                for (char symbol : production) {
                    if (is_terminal(symbol)) {
                        first_set.insert(symbol);
                        nullable = false;
                        break;
                    } else if (is_non_terminal(symbol)) {
                        first_set.insert(first[symbol].begin(), first[symbol].end());
                        if (first[symbol].count('_') == 0) {
                            nullable = false;
                            break;
                        }
                    }
                }
                if (nullable) {
                    first_set.insert(follow[non_terminal].begin(), follow[non_terminal].end());
                }
                for (char c : first_set) {
                    if (seen.count(c)) {
                        return false;
                    }
                    seen.insert(c);
                }
            }
        }
        return true;
    }
};

int main() {
    std::string line;
    std::regex rule_regex("^([A-Z])\\s*->\\s*([a-zA-Z]*)$");

    CFGrammar grammar;
    while (std::getline(std::cin, line)) {
        std::smatch m;
        if (std::regex_match(line, m, rule_regex)) {
            grammar.add_rule(m[1].first[0], m[2]);
        } else {
            break;
        }
    }

    std::vector<std::pair<char, std::string>> sorted_first;
    for (auto& entry : grammar.get_first())
        sorted_first.emplace_back(entry.first, set_to_canonical_string(entry.second, '_'));
    std::sort(sorted_first.begin(), sorted_first.end());

    std::cout << "First:" << std::endl;
    for (auto& entry : sorted_first)
        std::cout << entry.first << ": " << entry.second << std::endl;

    std::vector<std::pair<char, std::string>> sorted_follow;
    for (auto& entry : grammar.get_follow())
        sorted_follow.emplace_back(entry.first, set_to_canonical_string(entry.second, '$'));
    std::sort(sorted_follow.begin(), sorted_follow.end());

    std::cout << "Follow:" << std::endl;
    for (auto& entry : sorted_follow)
        std::cout << entry.first << ": " << entry.second << std::endl;

    std::cout << "is LL(1): " << (grammar.is_ll1() ? "Yes" : "No") << std::endl;
    return 0;
}
/*
Примеры
Входные данные

S -> ABC
A -> aA
A ->
B -> b
B -> C
C -> c

Результат работы

First:
A: a_
B: bc
C: c
S: abc
Follow:
A: bc
B: c
C: c$
S: $
is LL(1): Yes
*/