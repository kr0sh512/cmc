#include <iostream>
using namespace std;

class Row
{
public:
    int* const cells = new int[3];

    int*
        begin() const {
        return cells;
    }

    int*
        end() const {
        return cells + 3;
    }

    int& operator[](int ind) const {
        return cells[ind];
    }
};

class Matrix
{
public:
    const Row r[3];

    const Row*
        begin() const {
        return r;
    }

    const Row*
        end() const {
        return r + 3;
    }

    int&
        operator[](int ind1, int ind2) {
        return r[ind1][ind2];
    }
};

// int
// main() {
//     Matrix m;
//     m[1, 1] = 5;

//     for (const auto& row : m) {
//         for (auto cell : row) {
//             cout << cell << " ";
//         }
//         cout << "\n";
//     }
// }
