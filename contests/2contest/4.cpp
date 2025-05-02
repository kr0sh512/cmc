#include <string>

class BinaryNumber
{
    std::string str;
public:
    BinaryNumber(const std::string& s = "0") {
        str = s;
    }

    operator std::string() const {
        return str;
    }

    const BinaryNumber& operator++() {
        auto i = --str.end();

        while (*i == '1' && i != str.begin()) {
            *i = '0';
            --i;
        }

        if (i == str.begin()) {
            *i = '0';
            str.insert(str.begin(), '1');
        } else {
            *i = '1';
        }

        return *this;
    }
};
