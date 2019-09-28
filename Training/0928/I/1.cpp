#include <cstdio>
#include <cmath>

struct point {
    double x, y;
    point(double x, double y) : x(x), y(y) {}
    friend point operator+(const point &a, const point &b) {
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend double det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend double dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
};

struct line {
    double 
};

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf
