#include <cmath>
#include <string>

namespace numbers {
    class complex {
        double c_re, c_im;
    public:
        complex(double r = 0, double i = 0) : c_re(r), c_im(i) {}
        explicit complex(const std::string& s) {
            sscanf(s.c_str(), "(%lf,%lf)", &c_re, &c_im);
        }
        double re() const {
            return c_re;
        }
        double im() const {
            return c_im;
        }
        double abs2() const {
            return c_re * c_re + c_im * c_im;
        }
        double abs() const {
            return sqrt(abs2());
        }
        std::string to_string() const {
            char buf[100];
            sprintf(buf, "(%.10g,%.10g)", c_re, c_im);

            return std::string(buf);
        }
        complex& operator+=(const complex& other) {
            c_re += other.c_re;
            c_im += other.c_im;

            return *this;
        }
        complex& operator-=(const complex& other) {
            c_re -= other.c_re;
            c_im -= other.c_im;

            return *this;
        }
        complex& operator*=(const complex& other) {
            double r = c_re * other.c_re - c_im * other.c_im;
            double i = c_re * other.c_im + c_im * other.c_re;
            c_re = r;
            c_im = i;

            return *this;
        }
        complex& operator/=(const complex& other) {
            double r = (c_re * other.c_re + c_im * other.c_im) / other.abs2();
            double i = (c_im * other.c_re - c_re * other.c_im) / other.abs2();
            c_re = r;
            c_im = i;

            return *this;
        }
        friend complex operator+(const complex& C, const complex& other) {
            return complex(C.c_re + other.c_re, C.c_im + other.c_im);
        }
        friend complex operator-(const complex& C, const complex& other) {
            return complex(C.c_re - other.c_re, C.c_im - other.c_im);
        }
        friend complex operator*(const complex& C, const complex& other) {
            return complex(C.c_re * other.c_re - C.c_im * other.c_im, C.c_re * other.c_im + C.c_im * other.c_re);
        }
        friend complex operator/(const complex& C, const complex& other) {
            double r = (C.c_re * other.c_re + C.c_im * other.c_im) / other.abs2();
            double i = (C.c_im * other.c_re - C.c_re * other.c_im) / other.abs2();

            return complex(r, i);
        }
    };

    complex operator-(const complex& C) {
        return complex(-C.re(), -C.im());
    }
    complex operator~(const complex& C) {
        return complex(C.re(), -C.im());
    }
}