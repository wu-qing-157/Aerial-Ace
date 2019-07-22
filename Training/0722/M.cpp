#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 100010
#define lowbit(_x) ((_x) & (-(_x)))
struct Event {
	int pos, val, type;
	inline bool operator < (const Event &that) const {return pos < that.pos || (pos == that.pos && type < that.type);}
} e[maxn * 4];
int hash[maxn], hcnt;
int tr[maxn], ans[maxn];
void add(int x, int v)
{
	for (; x; x -= lowbit(x)) tr[x] += v;
}
int query(int x)
{
	int ret = 0;
	for (; x <= hcnt; x += lowbit(x)) ret += tr[x];
	return ret;
}
int main()
{
	freopen("business.in", "r", stdin);
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m, ecnt = 0; scanf("%d%d", &n, &m);
		memset(tr, 0, (n + 1) << 2); hcnt = 0;
		for (int i = 1; i <= n; ++i)
		{
			int x, q, r; scanf("%d%d%d", &x, &q, &r);
			e[++ecnt] = (Event) {x, q - x, 0};
			e[++ecnt] = (Event) {x + r + 1, q - x, -2};
			hash[++hcnt] = q - x;
		}
		for (int i = 1; i <= m; ++i)
		{
			int y, d; scanf("%d%d", &y, &d);
			e[++ecnt] = (Event) {y, d - y, i};
		}
		std::sort(e + 1, e + ecnt + 1);
		std::sort(hash + 1, hash + hcnt + 1);
		hcnt = std::unique(hash + 1, hash + hcnt + 1) - hash - 1;
		
		for (int i = 1; i <= ecnt; ++i)
		{
			int pos = std::lower_bound(hash + 1, hash + hcnt + 1, e[i].val) - hash;
			if (e[i].type > 0)
			{
				ans[e[i].type] = query(pos);
			}
			else
			{
				add(pos, e[i].type + 1);
			}
		}
		for (int i = 1; i <= m; ++i) printf("%d%c", ans[i], " \n"[i == m]);
	}
	return 0;
}
/*
1
3 3
1 100 300
3 5 300
4 3 10
2 100
5 6
50 100
*/  
