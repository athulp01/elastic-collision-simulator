#include<cmath>

struct vector2D {
    double x, y;

    double operator*(const vector2D &v) const {
        return x*v.x + y*v.y;
    }

    vector2D operator-(const vector2D &v) const {
        return vector2D(x - v.x, y - v.y);
    }

    vector2D(double a, double b) {x = a; y = b;}
    vector2D() {x = 0, y = 0;}
};

double mod(const vector2D &a, const vector2D &b) {
    return sqrt(pow(a.x - b.x, 2) - pow(a.y-b.y, 2));
}
