/*
 На стандартный поток ввода программе подаётся выражение в польской записи. Выражение может содержать имена переменных и бинарные операции +, -, *, /. Имя переменной — это строчная латинская буква. Элементы ввода могут разделяться произвольным количеством пробельных символов.

Напечатайте введённое выражение в инфиксной записи. Для сохранения приоритетов бинарные операции заключите в скобки. Выражение напечатайте в одной строке текста без пробельных символов.
Examples
Input

abc++

Output

(a+(b+c))
*/

#include <iostream>
#include <string>
#include <stack>

bool is_operation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int main() {
    char c;
    std::stack<std::string> stack;

    while (std::cin >> c) {
        if (is_operation(c)) {
            std::string r = stack.top();
            stack.pop();

            std::string l = stack.top();
            stack.pop();

            stack.push("(" + l + c + r + ")");
        } else {
            stack.push(std::string(1, c));
        }
    }

    std::cout << stack.top() << std::endl;

    stack.pop();

    return 0;
}
