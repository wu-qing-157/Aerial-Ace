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
db cost[20][20], len[20], minx[20], maxx[20], H;
vector<P> v[20], left[20], right[20], p1, p2;
const db oo = 1e11;
db f[1 << 15][20];
int main()
{
	int n; scanf("%d", &n);
	H = 0;
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
			cmax(H, y);
		}
		len[i] = maxx[i] - minx[i];
		// printf("len[%d] = %lf\n", i, len[i] );
		bool dir = 0;
		for (int j = 1; j < k; ++j)
		{
			if (dir) left[i].push_back(v[i][j]);
			else right[i].push_back(v[i][j]);
			if (v[i][j].y == H && !dir) dir = 1;
		}
		left[i].push_back(v[i][0]);
/*
		puts("left");
		for (auto poi : left[i]) printf("%lf %lf\n", poi.x, poi.y );
		puts("right");
		for (auto poi : right[i]) printf("%lf %lf\n", poi.x, poi.y );
*/
		std::reverse(left[i].begin(), left[i].end());
	}

// puts("---------------");
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			if (i == j) continue;
			db dist = oo; p1.clear(); p2.clear();
			for (auto poi : right[i]) p1.push_back(P(poi.x - minx[i], poi.y));
			for (auto poi : left[j]) p2.push_back(P(len[i] + len[j] + poi.x - maxx[j], poi.y));

/*
			printf("work %d %d\n", i, j);
			puts("p1");
			for (auto poi : p1) printf("%lf %lf\n", poi.x, poi.y );
			puts("p2");
			for (auto poi : p2) printf("%lf %lf\n", poi.x, poi.y );
*/
			for (int ii = 0, jj = 0; ii < p1.size() || jj < p2.size(); )
			{
				if (p1[ii].y < p2[jj].y)
				{
					P dir_vec = (p2[jj] - p2[jj - 1]) * (p1[ii].y - p2[jj - 1].y) / (p2[jj].y - p2[jj - 1].y);
					dir_vec = p2[jj - 1] + dir_vec;
					cmin(dist, dir_vec.x - p1[ii].x);
					++ii;
				}
				else if (p1[ii].y > p2[jj].y)
				{
					P dir_vec = (p1[ii] - p1[ii - 1]) * (p2[jj].y - p1[ii - 1].y) / (p1[ii].y - p1[ii - 1].y);
					dir_vec = p1[ii - 1] + dir_vec;
					cmin(dist, p2[jj].x - dir_vec.x);
					++jj;
				}
				else
				{
					cmin(dist, p2[jj].x - p1[ii].x);
					++ii; ++jj;
				}
			}
			cost[i][j] = len[j] - dist;
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
