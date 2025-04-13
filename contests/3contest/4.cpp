#include <cmc_complex.h>
#include <cmc_complex_stack.h>
#include <cmc_complex_eval.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

using namespace numbers;


int main(int argc, char** argv) {
    complex C(argv[1]);
    double R = std::stod(argv[2]);
    int N = std::stoi(argv[3]);
    std::vector<std::string> record;
    for (int i = 4; i < argc; i++) {
        record.push_back(argv[i]);
    }

    complex I, z, next = C + R;
    double h = 2 * M_PI;
    double s = h / N;
    for (double i = 0; i < h; i += s) {
        z = next;
        next = C + R * complex(std::cos(i), std::sin(i));
        I += eval(record, (z + next) / 2) * (next - z);
    }

    std::cout << I.to_string() << std::endl;

    return 0;
}
