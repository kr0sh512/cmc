#include <string>
using namespace std;

class BinaryNumber
{
    string str;
public:
    BinaryNumber(const string& s = "0") {
        str = s;
    }
    operator string () const {
        return str;
    }
    const BinaryNumber& operator++() {
        std::string::iterator i = str.end() - 1;
        while (*i == '1' && i != str.begin()) {
            *i = '0';
            --i;
        }
        if (i == str.begin()) {
            str.insert(str.begin(), '1');
        } else {
            *i = '1';
        }

        return *this;
    }
};
