#include<cmath>

typedef struct vector {
    double x, y;

    double operator*(const vector &v) const {
        return x*v.x + y*v.y;
    }

    vector operator-(const vector &v) const {
        return vector(x - v.x, y - v.y);
    }

    vector(double a, double b) {x = a; y = b;}
    vector() {x = 0, y = 0;}
};

double mod(const vector &a, const vector &b) {
    return sqrt(pow(a.x - b.x, 2) - pow(a.y-b.y, 2));
}
