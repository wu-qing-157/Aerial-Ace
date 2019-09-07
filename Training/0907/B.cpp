#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 2000010
int ty[maxn], v[maxn], hash[maxn], hcnt;
int Fa[maxn];
int Find(int x) {return Fa[x] == x ? x : Fa[x] = Find(Fa[x]);}
int main()
{
	int n, q; scanf("%d%d", &n, &q);
	for (int i = 1; i <= q; ++i) scanf("%d%d", ty + i, v + i), ty[i] == 1 ? hash[++hcnt] = v[i], hash[++hcnt] = v[i] + 1 : 0;
	std::sort(hash + 1, hash + hcnt + 1);
	hcnt = std::unique(hash + 1, hash + hcnt + 1) - hash - 1;
	for (int i = 1; i <= q; ++i) ty[i] == 1 ? v[i] = std::lower_bound(hash + 1, hash + hcnt + 1, v[i]) - hash : 0;

	for (int i = 1; i <= hcnt; ++i) Fa[i] = i;
	for (int i = 1; i <= q; ++i)
	{
		if (ty[i] == 1)
		{
			if (hash[v[i]] + 1 == hash[v[i] + 1])
			{
				if (Find(v[i]) != Find(v[i] + 1))
					Fa[Find(v[i])] = Find(v[i] + 1);
			}
		}
		else
		{
			int pos = std::lower_bound(hash + 1, hash + hcnt + 1, v[i]) - hash;
			if (hash[pos] != v[i]) printf("%d\n", v[i]);
			else
			{
				printf("%d\n", hash[Find(pos)]);
			}
		}
	}
	return 0;
}
