#include <cstdio>

#define maxn 100010
int Fa[maxn];
int Find(int x) {return Fa[x] == x ? x : Fa[x] = Find(Fa[x]);}
int main()
{
	int n, m; scanf("%d%d", &n, &m);
	int ans = m;
	for (int i = 1; i <= n; ++i) Fa[i] = i;
	for (int i = 1; i <= m; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		a = Find(a); b = Find(b);
		if (a != b)
		{
			Fa[a] = b;
			--ans;
		}
	}
	printf("%d\n", ans);
	return 0;
}
/*
5 3
3 5
5 1
1 3
*/
