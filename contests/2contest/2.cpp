class C
{
    int x;
public:
    C() { x = 0; }
    C(double tmp) { x = 0; }
    C(int tmp) { x = tmp; }
    C(const C o1, const C o2) { x = o1.x + o2.x; }
    C(const C* o) {}
    friend C
        operator+(const C& o1, const C& o2) {
        return C(o1.x + o2.x);
    }
    C
        operator++() {
        return C(++x);
    }
    int operator~() const { return ~x; }
    int
        operator*(const C* obj2) {
        return 0;
    }
};

/*
C
func1(const C& v1, int v2) {
    return C(v2 + v1, ~v1);
}

void
func2(const C* p1, double p2) {
    C v1 = p2;
    C v2[2][2];
    C v3 = func1(func1(func1(&p1[3], p2), ~p1[2]), ++v1 * v2[1]);
}

int
main() {
    return 0;
}
*/