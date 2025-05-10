#include <cmath>
#include <string>
#include <sstream>

// class Figure {
// public:
//     virtual double get_square() const = 0;
//     virtual ~Figure() {};
// };

class Rectangle : Figure {
    double a = 0;
    double b = 0;
public:
    Rectangle(double a = 0, double b = 0) : a(a), b(b) {}
    double get_square() const {
        return a * b;
    }
    static Rectangle* make(const std::string& s) {
        std::istringstream ss(s);
        double a, b;
        ss >> a >> b;

        return new Rectangle(a, b);
    }
};

class Square : Figure {
    double a = 0;
public:
    Square(double a = 0) : a(a) {}
    double get_square() const {
        return a * a;
    }
    static Square* make(const std::string& s) {
        std::istringstream ss(s);
        double a;
        ss >> a;

        return new Square(a);
    }
};

class Circle : Figure {
    double r = 0;
public:
    Circle(double r = 0) : r(r) {}
    double get_square() const {
        return M_PI * r * r;
    }
    static Circle* make(const std::string& s) {
        std::istringstream ss(s);
        double r;
        ss >> r;

        return new Circle(r);
    }
};