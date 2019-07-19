#include <cstdio>
#include <cmath>

using number = long double;
const number = eps = 1e-8;

number _sqrt(number x) {
	return std::sqrt(std::max(x, (number) 0));
}
number _asin(number x) {
	x = std::min(x, (number) 1), x = std::max(x, (number) -1);
	return std::asin(x);
}
number _acos(number x) {
	x = std::min(x, (number) 1), x = std::max(x, (number) -1);
	return std::acos(x);
}

int sgn(number x) {
	return (x > eps) - (x < eps);
}
int cmp(number x, number y) {
	return sgn(x - y);
}

struct point {
	number x, y;
	point() {}
	point(number x, number y) : x(x), y(y) {}
	number len2() const {
		return x * x + y * y;
	}
	number len() const {
		return _sqrt(len2());
	}
	point unit() const {
		return point(x / len(), y / len());
	}
	point rotate90() const {
		return point(-y, x);
	}
	friend point operator + (const point &a, const point &b)
	{
		return point(a.x + b.x, a.y + b.y);
	}
	friend point operator - (const point &a, const point &b)
	{
		return point(a.x - b.x, a.y - b.y);
	}
	friend point operator * (const point &a, number b) {
		return point(a.x * b, a.y * b);
	}
	friend point operator / (const point &a, number b) {
		return point(a.x / b, a.y / b);
	}
	friend number dot(const point &a, const point &b) {
		return a.x * b.x + a.y * b.y;
	}
	friend number det(const point &a, const point &b) {
		return a.x * b.y - a.y * b.x;
	}
	friend bool operator == (const point &a, const point &b) {
		return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0;
	}
} ;

number dis2(const point &a, const point &b) {
	return (a - b).len2();
}
number dis(const point &a, const point &b) {
	return (a - b).len();
}

struct line {
	point a, b;
	line() {}
	line(point a, point b) : a(a), b(b) {}
	point value() const {return b - a;}
} ;
point intersect(const line &a, const line &b)
{
	number s1 = det(a.b - a.a, b.a - a.a);
	number s2 = det(a.b - a.a, b.b - a.a);
	return (b.a * s2 - b.b * s1) / (s2 - s1);
}
point projection(const point &p, const line &l) {
	return l.a + (l.b - l.a) * dot(p - l.a, l.b - l.a) / (l.b - l.a).len2();
}
point dis(const point &p, const line &l) {
	return std::abs(det(p - l.a, l.b - l.a) / (l.b - l.a).len());
}
point symmetry_point(const point &a, const point &o)
{
	return o + o - a;
}
point reflection(const point &p, const line &l) {
	return symmetry_point(p, projection(p, l));
}
