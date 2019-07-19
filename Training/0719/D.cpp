#include <cstdio>
#include <vector>

#define maxn 100010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
typedef long long ll;
std::vector<int> v[maxn], v2[maxn];
int Fa[maxn];
int Find(int x) {return Fa[x] == x ? x : Fa[x] = Find(Fa[x]);}
int main()
{
	freopen("dream.in", "r", stdin);
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n; scanf("%d", &n);
		int maxx = 0;
		for (int i = 1; i <= n; ++i)
		{
			int x; scanf("%d", &x); v[x].push_back(i);
			Fa[i] = i;
			cmax(maxx, x);
		}
		
		for (int i = 1; i <= maxx; ++i)
		{
			for (int j = i; j <= maxx; j += i)
				for (auto it : v[j])
					v2[i].push_back(it);
		}
		ll ans = 0;
		for (int i = maxx; i; --i)
			if (v2[i].size() > 1)
			{
				int fir = v2[i][0];
				for (auto it : v2[i])
					if (Find(it) != Find(fir))
					{
						int f1 = Find(it), f2 = Find(fir);
						Fa[f1] = f2;
						//printf("%d %d\n", f1, f2);
						ans += i;
					}
			}
		printf("Case %d: %lld\n", Cas, ans);
		for (int i = 1; i <= maxx; ++i) v[i].clear(), v2[i].clear();
	}
	return 0;
}
/*
2
2 3 6
5 5 6 7 10 21
*/
