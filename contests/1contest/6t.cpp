#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout, std::cin, std::endl;

class Point
{
public:
    double x;
    double y;
    Point(const double a = 0, const double b = 0) : x{ a }, y{ b } {}
};
class Line
{
public:
    // m * x + n * y + k = 0;
    double n;
    double m;
    double k;
    Line(const Point& a, const Point& b) {
        m = a.y - b.y;
        n = b.x - a.x;
        k = a.x * b.y - b.x * a.y;
    }
};

Point* crossPoint(const Line& l_1, const Line& l_2) {
    double det = l_1.m * l_2.n - l_2.m * l_1.n;
    if (abs(det) < 1e-9) {
        return nullptr;
    }

    double x = (l_1.n * l_2.k - l_2.n * l_1.k) / det;
    double y = (l_2.m * l_1.k - l_1.m * l_2.k) / det;

    return new Point(x, y);
}

int main() {
    double x1, x2, y1, y2;
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    Line l_1(Point(x1, y1), Point(x2, y2));

    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    Line l_2(Point(x1, y1), Point(x2, y2));

    Point* pnt = crossPoint(l_1, l_2);
    if (pnt != nullptr) {
        std::cout << std::fixed << std::setprecision(5);
        std::cout << 1 << " " << pnt->x << " " << pnt->y << std::endl;
        delete pnt;
        return 0;
    }

    double det1 = l_1.n * l_2.k - l_2.n * l_1.k;
    double det2 = l_1.m * l_2.k - l_2.m * l_1.k;

    if (abs(det1) < 1e-9 && abs(det2) < 1e-9) {
        std::cout << 2 << std::endl;
        return 0;
    }
    std::cout << 0 << std::endl;
}
