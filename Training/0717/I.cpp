#include <cstdio>
#include <unordered_set>

#define maxn 1000010
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
int a[maxn], rig[maxn];
std::unordered_set<int> set;
int main()
{
	int n, q;
	while (1)
	{
		scanf("%d%d", &n, &q);
		if (!n && !q) return 0;
		if (n >= maxn) while (1);
		set.clear();
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for (int i = 1, j = 0; i <= n; ++i)
		{
			while (j < n && !set.count(a[j + 1])) set.insert(a[++j]);
			rig[i] = j;
			set.erase(a[i]);
		}
		for (; q; --q)
		{
			int ql, qr; scanf("%d%d", &ql, &qr);
			if (rig[ql] >= qr) puts("OK");
			else printf("%d\n", a[rig[ql] + 1]);
		}
		puts("");
	}
	return 0;
}
