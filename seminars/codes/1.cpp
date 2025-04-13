#include <string.h>
#include <cstring>
#include <utility>
#include <iostream>

class string
{
    int len; // количество памяти
    char* str;

public:
    string(const char* s = "") {
        len = strlen(s) + 1;
        str = new char[len];
        strcpy(str, s);
    }

    char&
        operator[](int n) {
        return str[n];
    }

    string
        operator+(string s) {
        string tmp;
        tmp.len = s.len + len - 1;
        tmp.str = new char[tmp.len];

        strcpy(tmp.str, str);
        strcpy(tmp.str + len - 1, s.str);

        return tmp;
    }

    // string
    //     operator=(string s) {
    //     if (s.str == str) {
    //         return s;
    //     }

    //     delete[] str;
    //     len = s.len;
    //     str = new char[len];
    //     strcpy(str, s.str);

    //     return *this;
    // }

    // ~string() { delete[] str; } почему-то с ним не работает (?)

    void
        print() {
        std::cout << str << " " << len << std::endl;
    }
};


int
main() {
    string s1("abcd"), s2("qw"), s3;
    s2[1] = 'A';
    s2.print();
    s3 = s1 + s2;

    s3.print();
}
