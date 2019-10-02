#include <cstdio>
#include <cmath>
#include <algorithm>

typedef long double db;

const int N = 1010;
const db pi = acosl(-1.0);
const db eps = 1e-9;

int sgn(db x) {
	return (x > eps) - (x < -eps);
}

int sgn(db x, db y) {
	return sgn(x - y);
}

int n;

struct P {
	db x, y;
	P operator - (const P &a) const {return (P) {x - a.x, y - a.y};}
	bool operator < (const P& a) const{
		if (sgn(x, a.x) != 0) return x < a.x;
		return y < a.y;
	}
	db len() {return sqrtl(x * x + y * y);}
} p[N];

struct C {
	P o; db r;
	db oint(db t1, db t2) {
		return r * (r * (t2 - t1) + o.x * (sinl(t2) - sinl(t1)) - o.y * (cosl(t2) - cosl(t1)));
	}
} a[N];

struct D {
	db x; int c;
	bool operator < (const D &a) const {
		return x < a.x;
	}
} pos[N * 2];

db acos_(db x) {
	if (x < -1 + eps) return acosl(-1);
	if (x > 1 - eps) return acosl(1);
	return acosl(x);
}

db work(int c) {
	int tot = 0, cnt = 0;
	for (int i = 1; i <= n; ++i)
	if (i != c)
	{
		P d = a[i].o - a[c].o; db dis = d.len();
		if (a[c].r <= a[i].r - dis + eps) return 0;
		if (a[i].r <= a[c].r - dis + eps || a[i].r + a[c].r <= dis + eps) continue;
		db g = atan2l(d.y, d.x), g0 = acos_((dis * dis + a[c].r * a[c].r - a[i].r * a[i].r) / (2 * dis * a[c].r)), l = g - g0, r = g + g0;
		if (l < -pi) l += pi * 2;
		if (r >= pi) r -= 2 * pi;
		if (l > r) ++cnt;
		pos[++tot] = (D) {l, 1};
		pos[++tot] = (D) {r, -1};
	}
	pos[0].x = -pi, pos[++tot].x = pi;
	std::sort(pos + 1, pos + 1 + tot);
	db ans = 0;
	for (int i = 1; i <= tot; cnt += pos[i++].c)
		if (cnt == 0) ans += a[c].oint(pos[i - 1].x, pos[i].x);
	return ans;
}
db f(db z)
{
	db ret = 0;
	for (int i = 1; i <= n; ++i) a[i] = (C) {p[i], 1 - z};
	for (int i = 1; i <= n; ++i) ret += work(i);
	return ret / 2;
}
db simpson(db a, db b)
{
	db c = (a + b) / 2;
	return (f(a) + f(b) + 4 * f(c)) * (b - a) / 6;
}
db integral(db a, db b, db eps)
{
	db c = (a + b) / 2;
	db mid = simpson(a, b), l = simpson(a, c), r = simpson(c, b);
	if (std::abs(l + r - mid) <= 15 * eps)
		return l + r + (l + r - mid) / 15;
	else
		return integral(a, c, eps / 2) + integral(c, b, eps / 2);
}
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%Lf%Lf", &p[i].x, &p[i].y);
		std::sort(p + 1, p + n + 1);
		printf("Case %d: %.15lf\n", Cas, (double) integral(0, 1, 8e-8));
	}
}
