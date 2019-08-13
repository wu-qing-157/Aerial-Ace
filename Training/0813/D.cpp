#include <cstdio>
#include <algorithm>

#define maxn 100010
struct Frac {
	int a, b;
	inline bool operator < (const Frac &that) const {return 1ll * a * that.b < 1ll * b * that.a;}
	inline bool operator <= (const Frac &that) const {return 1ll * a * that.b <= 1ll * b * that.a;}
	inline bool operator == (const Frac &that) const {return 1ll * a * that.b == 1ll * b * that.a;}
	void simple()
	{
		int gcc = std::__gcd(a, b);
		a /= gcc; b /= gcc;
		if (b < 0) a = -a, b = -b;
	}
} ;
struct Opt {
	Frac x; int id;
	inline bool operator < (const Opt &that) const {return x < that.x;}
} p[maxn];
Frac va[maxn];
int a[maxn], b[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int ans = 0, suma = 0, sumb = 0;
		int n, C; scanf("%d%d", &n, &C);
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d%d", a + i, b + i);
			p[i] = (Opt) {(Frac) {-b[i], a[i]}, i};
			p[i].x.simple();
			suma -= a[i];
			sumb -= b[i];
		}
		std::sort(p + 1, p + n + 1);
		Frac lst = (Frac) {-1, 0};
		bool flag = 0;
		for (int i = 1; i <= n && !flag; ++i)
		{
			if (suma == 0 && sumb == C)
			{
				flag = 1; break;
			}
			//printf("pos %d/%d\n", p[i].x.a, p[i].x.b);
			if (suma != 0)
			{
				//printf("sb %d sa %d\n", sumb, suma);
				Frac x = (Frac) {C - sumb, suma};
				x.simple();
				if (lst <= x && x <= p[i].x) va[++ans] = x;
			}
			lst = p[i].x;
			suma += 2 * a[p[i].id];
			sumb += 2 * b[p[i].id];
		}
		if (flag) {puts("-1"); continue;}
		Frac x = (Frac) {C - sumb, suma};
		x.simple();
		if (lst <= x) va[++ans] = x;
		std::sort(va + 1, va + ans + 1);
		ans = std::unique(va + 1, va + ans + 1) - va - 1;
		printf("%d", ans);
		for (int i = 1; i <= ans; ++i)
			printf(" %d/%d", va[i].a, va[i].b);
		puts("");
	}
	return 0;
}
