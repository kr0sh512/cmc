#include <map>
#include <iostream>

bool is_num(std::string& s) {
    auto iter = s.begin();
    while (iter != s.end() && std::isdigit(*iter)) ++iter;
    return iter == s.end();
}

enum TokenKind
{
    T_EOF,    // end of input stream
    T_NUMBER, // int64 number
    T_ID,     // identifier
    K_ALG,
    K_ARG,
    K_RES,
    K_NACH,
    K_KON,
    K_TSEL,
    K_VESHCH,
    K_SIM,
    K_LIT,
    K_LOG,
    K_TAB,
    K_NTS,
    K_KTS,
    K_DLIN,
    K_DANO,
    K_NADO,
    K_ESLI,
    K_TO,
    K_INACHE,
    K_VSE,
    K_POKA,
    K_DLYA,
    K_OT,
    K_DO,
    K_ZNACH,
    K_I,
    K_ILI,
    K_NE,
    K_DA,
    K_NET,
    K_PRI,
    K_VYBOR,
    K_VVOD,
    K_VYVOD,
    K_UTV,
    T_SEMICOLON,
    T_COMMA,
    T_ASSIGN,
    T_LBR,
    T_RBR,
    T_LSQBR,
    T_RSQBR,
    T_PLUS,
    T_MINUS,
    T_MUL,
    T_DIV,
    T_EQ,
    T_NE,
    T_GT,
    T_GE,
    T_LT,
    T_LE
};

const std::string tokens[] =
{
    "", // EOF
    "", // NUMBER
    "", // ID
    "алг", "арг", "рез", "нач", "кон", "цел", "вещ", "сим", "лит", "лог",
    "таб", "нц", "кц", "длин", "дано", "надо", "если", "то", "иначе", "все",
    "пока", "для", "от", "до", "знач", "и", "или", "не", "да", "нет",
    "при", "выбор", "ввод", "вывод", "утв",
    ";", ",", ":=", "(", ")", "[", "]", "+", "-", "*",
    "/", "=", "!=", ">", ">=", "<", "<=",
};

int main() {
    // строим словарь соответствий
    std::map<std::string, TokenKind> mp;

    int tmp = 0;
    for (auto& wd : tokens) {
        mp[wd] = TokenKind(tmp++);
    }

    // std::cout << mp["алг"] << " " << mp[";"];

    // std::string s1("123");
    // std::string s2("12a3");
    // std::cout << is_num(s1) << is_num(s2);
    // return -1;

    std::string word;

    while (std::cin >> word) {
        if (mp.find(word) != mp.end()) {
            std::cout << mp[word];
        } else if (is_num(word)) {
            std::cout << 1 << ':' << word;
        } else {
            std::cout << 2 << ':' << word;
        }

        std::cout << std::endl;
    }

    std::cout << 0 << std::endl;

    return 0;
}