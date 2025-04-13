#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    double tmp, arip = 0, squar = 0;
    int n = 0;
    while (std::cin >> tmp) {
        ++n;
        arip += (tmp - arip) / n;
        squar += (tmp * tmp - squar) / n;
    }

    std::cout << std::setprecision(10);

    std::cout << arip << std::endl << std::sqrt(squar - arip * arip) << std::endl;

    return 0;
}