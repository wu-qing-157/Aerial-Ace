#include <cstdio>
#include <cmath>
#include <vector>
#include <deque>
#include <algorithm>

typedef double db;
const db eps = 1e-10;
using namespace std;
#define cmin(_a, _b) (_a > (_b) ? _a = (_b), 1 : 0)
#define cmax(_a, _b) (_a < (_b) ? _a = (_b), 1 : 0)
db _sqrt(db x) {
	return sqrt(max(x, (db) 0));
}
int sgn(db x) {
	return (x > eps) - (x < -eps);
}
int cmp(db x, db y) {
	return sgn(x - y);
}
struct P {
	db x, y;
	P () {}
	P (db x, db y) : x(x), y(y) {}
	db len2() const {return x * x + y * y;}
	db len() const {return _sqrt(len2());}
	P norm() const {return P(x / len(), y / len());}
	P turn90() const {return P(-y, x);}
	friend P operator + (const P &a, const P &b) {
		return P(a.x + b.x, a.y + b.y);
	}
	friend P operator - (const P &a, const P &b) {
		return P (a.x - b.x, a.y - b.y);
	}
	friend P operator * (const P &a, db b) {
		return P (a.x * b, a.y * b);
	}
	friend P operator / (const P &a, db b) {
		return P (a.x / b, a.y / b);
	}
	friend db operator * (const P &a, const P &b) {
		return a.x * b.y - a.y * b.x;
	}
	friend db operator ^ (const P &a, const P &b) {
		return a.x * b.x + a.y * b.y;
	}
	friend bool operator == (const P &a, const P &b) {
		return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0;
	}
	int quad() const {return sgn(y) == 1 || (sgn(y) == 0 && sgn(x) >= 0);}
} ;
struct L {
	P a, b;
	L () {}
	L (P a, P b):a(a), b(b) {}
	bool onLeft(const P &p) const {return sgn((b - a) * (p - a)) > 0;}
	P v() {return b - a;}
	L push() const {
		P delta = (b - a).turn90().norm() * eps;
		return L(a - delta, b - delta);
	}
} ;
db det(P a, P b, P c) {
	return (b - a) * (c - a);
}
bool parallel(L l1, L l2) {
	return sgn(l1.v() * l2.v()) == 0;
}
P intersect(L l1, L l2) {
	db s1 = det(l1.a, l1.b, l2.a);
	db s2 = det(l1.a, l1.b, l2.b);
	return (l2.a * s2 - l2.b * s1) / (s2 - s1);
}
bool sameDir(const L &l0, const L &l1) {
	return parallel(l0, l1) && sgn((l0.b - l0.a) ^ (l1.b - l1.a)) == 1;
}
bool operator < (const P &a, const P &b) {
	if (a.quad() != b.quad())
		return a.quad() < b.quad();
	else
		return sgn((a*b)) > 0;
}
bool operator < (const L &l0, const L &l1) {
	if (sameDir(l0, l1))
		return l1.onLeft(l0.a);
	else return (l0.b - l0.a) < (l1.b - l1.a);
}
bool check(const L &u, const L &v, const L &w) {
	return w.onLeft(intersect(u, v));
}
bool intersection(vector<L> &l) {
	sort(l.begin(), l.end());
	deque<L> q;
	for (int i = 0; i < (int) l.size(); ++i) {
		if (i && sameDir(l[i], l[i - 1])) continue;
		while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], l[i]))
			q.pop_back();
		while (q.size() > 1 && !check(q[1], q[0], l[i]))
			q.pop_front();
		q.push_back(l[i]);
	}
	while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0]))
		q.pop_back();
	while (q.size() > 2 && !check(q[1], q[0], q[q.size() - 1]))
		q.pop_front();
	vector<P> ret;
	for (int i = 0; i < (int) q.size(); ++i)
		ret.push_back(intersect(q[i], q[(i + 1) % q.size()]));
	return ret.size() > 2;
}
db cost[20][20], len[20], minx[20], maxx[20];
vector<P> v[20];
const db oo = 1e11;

inline bool check(db x, int i1, int i2)
{
	vector<L> l; vector<P> p1 = v[i1], p2 = v[i2];
	P delta1 = P(-minx[i1], 0), delta2 = P(x - maxx[i2], 0);
	if (maxx[i1] - minx[i1] < minx[i2] + x - maxx[i2]) return 0;
	for (int i = 0, _ = p1.size(); i < _; ++i)
		l.push_back(L(p1[i] + delta1, p1[(i + 1) % _] + delta1));
	for (int i = 0, _ = p2.size(); i < _; ++i)
		l.push_back(L(p2[i] + delta2, p2[(i + 1) % _] + delta2));
	return intersection(l);
}
db f[1 << 15][20];
int main()
{
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		int k; scanf("%d", &k);
		minx[i] = oo, maxx[i] = -oo;
		for (int j = 1; j <= k; ++j)
		{
			db x, y;
			scanf("%lf%lf", &x, &y);
			v[i].push_back(P(x, y));
			cmin(minx[i], x);
			cmax(maxx[i], x);
		}
		len[i] = maxx[i] - minx[i];
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			if (i == j) continue;
			db left = 0, right = 4e8;
			while (right - left > 1e-4)
			{
				db mid = (left + right) * 0.5;
				if (check(mid, i, j)) left = mid;
				else right = mid;
			}
			cost[i][j] = left - len[i];
		}
	/*for (int i = 1; i <= n; ++i, puts(""))
		for (int j = 1; j <= n; ++j)
			printf("%.6lf ", cost[i][j]);*/
	for (int S = 1, _ = 1 << n; S < _; ++S)
		for (int i = 1; i <= n; ++i)
			f[S][i] = oo;
	for (int i = 1; i <= n; ++i)
		f[1 << (i - 1)][i] = len[i];
	for (int S = 1, _ = 1 << n; S < _; ++S)
	{
		for (int i = 1; i <= n; ++i)
			if (S & (1 << (i - 1)))
			{
				for (int j = 1; j <= n; ++j)
					if (!(S & (1 << (j - 1))))
						cmin(f[S | (1 << (j - 1))][j], f[S][i] + cost[i][j]);
			}
	}
	db ans = oo;
	for (int i = 1; i <= n; ++i)
		cmin(ans, f[(1 << n) - 1][i]);
	printf("%.3lf\n", ans);
	return 0;
}
/*
3
4
0 0
1 0
0 5
-1 5
4
0 0
1 0
2 5
1 5
4
0 0
3 0
2 5
1 5

3
4
0 0
204 0
412 1031
-253 1031
6
0 0
110 0
290 436
100 1031
0 1031
-400 750
5
0 0
120 0
100 1031
0 1031
-281 93
*/
