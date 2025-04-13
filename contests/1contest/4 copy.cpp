#include <iostream>

int main() {
    int x1_1, y1_1, x1_2, y1_2;
    int x2_1, y2_1, x2_2, y2_2;
    std::cin >> x1_1 >> y1_1 >> x1_2 >> y1_2;
    std::cin >> x2_1 >> y2_1 >> x2_2 >> y2_2;

    double k1, k2;
    k1 = static_cast<double>(y1_2 - y1_1) / (x1_2 - x1_1);
    k2 = static_cast<double>(y2_2 - y2_1) / (x2_2 - x2_1);

    if (k1 == k2) {
        if (y1_1 - k1 * x1_1 == y2_1 - k2 * x2_1) {
            std::cout << 2 << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }

        return 0;
    }

    double b1 = y1_1 - k1 * x1_1;
    double b2 = y2_1 - k2 * x2_1;

    double x_intersect = (b2 - b1) / (k1 - k2);
    double y_intersect = k1 * x_intersect + b1;

    std::cout.precision(6);
    std::cout << std::fixed << x_intersect << " " << y_intersect << std::endl;

    return 0;
}