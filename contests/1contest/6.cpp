#include <iostream>
#include <iomanip>

/*
На плоскости даны две прямые. Каждая прямая задается парой точек, через которые она проходит. Требуется установить, пересекаются ли эти прямые, и найти координаты точки пересечения.
Input format

Вводятся сначала координаты двух различных точек, через которые проходит первая прямая, а затем - координаты еще двух различных (но, быть может, совпадающих с первыми двумя) точек, через которые проходит вторая прямая. Координаты каждой точки - целые числа, по модулю не превышающие 1000.
Output format

Если прямые не пересекаются, выведите одно число 0. Если прямые совпадают, выведите 2. Если прямые пересекаются ровно в одной точке, то выведите сначала число 1, а затем два вещественных числа - координаты точки пересечения с точностью не менее 5 знаков после десятичной точки.
Notes

Пишите переиспользуемый код - у вас должны появится классы точки, прямой, функция получение точки пересечения.
*/

class Point {
public:
    long double x, y;

    Point(long double x = 0, long double y = 0) : x(x), y(y) {}
};

class Line {
public:
    long double a, b, c;

    Line(const Point& p1, const Point& p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = p1.x * p2.y - p2.x * p1.y;
    }

    bool isParallel(const Line& other) const {
        return std::abs(a * other.b - b * other.a) < 1e-9;
    }

    bool isCoincide(const Line& other) const {
        return isParallel(other) && std::abs(c - other.c) < 1e-9;
    }

    Point intersection(const Line& other) const {
        long double det = b * other.a - a * other.b;

        long double x = (a * other.c - c * other.a) / det;
        long double y = (c * other.b - b * other.c) / det;

        return Point(x, y);
    }

};

int main() {
    Point* p = new Point[4];
    for (int i = 0; i < 4; ++i) {
        std::cin >> p[i].x >> p[i].y;
    }

    Line line1(p[0], p[1]);
    Line line2(p[2], p[3]);

    delete[] p;

    if (line1.isCoincide(line2)) {
        std::cout << 2;
    } else if (line1.isParallel(line2)) {
        std::cout << 0;
    } else {
        Point intersection = line1.intersection(line2);
        std::cout << std::fixed << std::setprecision(5);
        std::cout << 1 << " " << intersection.x << " " << intersection.y;
    }

    std::cout << std::endl;

    return 0;
}
