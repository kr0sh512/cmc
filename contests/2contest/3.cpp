#include <iostream>
#include <string>
#include <iomanip>

// Напишите программу, которая выполняет RLE-кодирование стандартного потока ввода.

// При RLE (run length encoding) кодировании последовательность одинаковых идущих подряд символов заменяется на специальный маркер с длиной последовательности.

// Последовательности одинаковых символов длиной не более 4 остаются без изменений (кроме символа '#'). Последовательности одинаковых символов длиной более 4 заменяются на последовательность символов '#', CHAR, N, '#', где CHAR — это символ, N — число повторений, записываемое в текстовом виде в шестнадцатеричной системе счисления с цифрами 0-9 и a-f.

// Последовательность символов '#' любой длины кодируется всегда как описано выше.

// Использовать ввод-вывод языка Си++.

int main() {
    std::string s;

    while (std::cin) {
        std::string line;
        std::getline(std::cin, line);
        s += line + "\n";
    }

    std::string result;

    size_t iter1 = 0;
    size_t iter2 = 0;

    while (iter1 < s.size()) {
        iter2 = iter1;
        while (iter2 < s.size() && s[iter1] == s[iter2]) {
            iter2++;
        }
        int count = iter2 - iter1;

        if (count > 4) {
            result += "#";
            result += s[iter1];

            std::stringstream ss;
            ss << std::hex << count;
            std::string hexCount = ss.str();

            result += hexCount;
            result += "#";
        } else if (s[iter1] == '#') {
            result += "#";
            result += s[iter1];
            result += std::to_string(count);
            result += "#";
        } else {
            for (int i = 0; i < count; ++i) {
                result += s[iter1];
            }
        }

        iter1 = iter2;
    }

    std::cout << result << std::endl;

    return 0;
}
