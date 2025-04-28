#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

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

    std::vector<std::pair<TokenKind, std::string>> v;
    for (auto& h : mp) {
        v.push_back(std::make_pair(h.second, h.first));
    }

    std::sort(v.begin(), v.end());

    int n = 0;
    for (auto& h : v) {
        std::cout << h.first << " <=> " << h.second << "\t";
        if (!(n++ % 4)) {
            std::cout << std::endl;
        }
    }

    return 0;
}