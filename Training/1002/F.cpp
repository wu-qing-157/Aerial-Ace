#include <cstdio>
#include <cmath>
#include <algorithm>

typedef double db;

const int N = 1010;
const db pi = acos(-1.0);
const db eps = 1e-10;

int n;

struct P {
	db x, y;
	P operator - (const P &a) const {return (P) {x - a.x, y - a.y};}
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
		if (a[i].r * 2 <= dis + eps) continue;
		db g = atan2l(d.y, d.x), g0 = acos_(dis / (2 * a[c].r)), l = g - g0, r = g + g0;
		if (l < -pi - eps) l += pi * 2, ++cnt;
		if (r > pi + eps) r -= 2 * pi, ++cnt;
		pos[++tot] = (D) {l, 1};
		pos[++tot] = (D) {r, -1};
	}
	pos[0].x = -pi, pos[++tot].x = pi;
	std::sort(pos + 1, pos + tot);
	db ans = 0;
	for (int i = 1; i <= tot; cnt += pos[i++].c)
		if (cnt == 0)
			ans += a[c].oint(pos[i - 1].x, pos[i].x);
	return ans;
}
int cnt = 0;
db f(db z)
{
	cnt++;
	if (1 - z < eps) return 0;
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
		for (int i = 1; i <= n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
		printf("%d\n", cnt);
		printf("Case %d: %.15f\n", Cas, (double) integral(0, 1, 1e-7));
	}
}

