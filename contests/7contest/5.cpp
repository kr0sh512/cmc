class Figure {
public:
    virtual bool equals(const Figure*) const = 0;
    virtual ~Figure() {}
};

class Rectangle : public Figure {
    int a;
    int b;
public:
    Rectangle(int a = 0, int b = 0) : a(a), b(b) {}
    bool equals(const Figure* fig) const {
        const Rectangle* rect = dynamic_cast<const Rectangle*>(fig);
        if (rect) {
            return a == rect->a && b == rect->b;
        }

        return false;
    }
};

class Triangle : public Figure {
    int a;
    int b;
    int c;
public:
    Triangle(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}
    bool equals(const Figure* fig) const {
        const Triangle* tri = dynamic_cast<const Triangle*>(fig);
        if (tri) {
            return a == tri->a && b == tri->b && c == tri->c;
        }

        return false;
    }
};

// #include <cassert>

// int main() {
//     Rectangle r1(10, 5), r2(10, 2), r3(10, 5), r4(5, 10);
//     Triangle t1(1, 2, 3);
//     Figure* f = &r1;

//     assert(!f->equals(&r2));
//     assert(f->equals(&r3));
//     assert(!f->equals(&r4));
//     assert(!f->equals(&t1));
//     assert(!f->equals(nullptr));
// }