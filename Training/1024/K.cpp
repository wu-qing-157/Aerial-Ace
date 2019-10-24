#include <cstdio>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
#define maxn 110
const int mod = 1e9 + 7;
int p[maxn], r[maxn];
double ppp[maxn];
vector<int> v, fd[233];
int con[233];
map<vector<int>, int> id;
int cnter;
void dfs(int x, int lim)
{
	if (x == 4)
	{
		id[v] = ++cnter;
		fd[cnter] = v;
		con[cnter] = lim;
		return ;
	}
	for (int i = 0; i <= lim; ++i)
	{
		v.push_back(i);
		dfs(x + 1, lim);
		v.pop_back();
	}
	v.push_back(lim + 1);
	dfs(x + 1, lim + 1);
	v.pop_back();
}
vector<int> fa;
void simplify()
{
	vector<int> v2; v2.clear();
	int ct = 0;
	int idd[6] = {0};
	for (int it : fa)
		if (!it) v2.push_back(0);
		else if (!idd[it]) v2.push_back(idd[it] = ++ct);
		else v2.push_back(idd[it]);
	fa = v2;
}
int pr[maxn], prcnt, mp[maxn];
inline bool cmp(int a, int b) {return mp[a] < mp[b] || (mp[a] == mp[b] && a < b);}
bool vis[maxn];
int f[maxn][maxn];
int main()
{
	int T; scanf("%d", &T);
	dfs(0, 0); mp[1] = 1;
	for (int i = 2; i <= 100; ++i)
	{
		if (!vis[i]) mp[pr[++prcnt] = i] = i;
		for (int j = 1; j <= prcnt && i * pr[j] <= 100; ++j)
		{
			vis[i * pr[j]] = 1;
			mp[i * pr[j]] = mp[i];
			if (i % pr[j] == 0) break;
		}
	}
	for (; T; --T)
	{
		int n; scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%lf", ppp + i), p[i] = (int) floor(ppp[i] * 100 + 1e-6);
		for (int i = 1; i <= n; ++i) r[i] = i;
		std::sort(r + 1, r + n + 1, cmp);
		int ans = p[1];
		int lst = 0;
		f[0][1] = 1;
		for (int i = 1, j; i <= n; lst = i, i = j)
		{
			int now = r[i];
			if (mp[now] < 10)
			{
				j = i + 1;
				for (int S = 1; S <= cnter; ++S)
				{
					fa = fd[S];
					f[i][S] = (f[i][S] + 1ll * f[i - 1][S] * (mod + 1 - p[now])) % mod;
					int ct = con[S];
					for (int ii = 0; ii < 4; ++ii)
						if (now % pr[ii + 1] == 0 && fa[ii] == 0)
							fa[ii] = ++ct;
					for (int ii = 0; ii < 4; ++ii)
						for (int jj = ii + 1; jj < 4; ++jj)
							if (now % pr[ii + 1] == 0 && now % pr[jj + 1] == 0)
							{
								int minn = min(fa[ii], fa[jj]);
								for (int kk = 0; kk < 4; ++kk)
									if (fa[kk] == fa[ii] || fa[kk] == fa[jj])
										fa[kk] = minn;
							}
					simplify();
					for (int it : fa) printf("%d ", it); puts("");
					f[i][id[fa]] = (f[i][id[fa]] + 1ll * f[i - 1][S] * p[now]) % mod;
				}
				for (int S = 1; S <= cnter; ++S) printf("f[%d][%d] = %d\n", i, S, f[i][S]);
			}
			else
			{
				while (j <= n && mp[r[i]] == mp[r[j]]) ++j;
				int pp = p[i];
				for (int ii = i + 1; ii < j; ++ii)
					pp = 1ll * pp * (mod + 1 - p[ii]) % mod;
				(ans += pp) %= mod;
				for (int S = 1; S <= cnter; ++S)
				{
					for (int SS = 0, _ = j - i; SS < (1 << _); ++SS)
					{
						pp = 1;
						fa = fd[S];
						for (int ii = 0; ii < _; ++ii)
							if (SS & (1 << ii))
							{
								pp = 1ll * pp * p[r[ii + i]] % mod;
						for (int i2 = 0; i2 < 4; ++i2)
						for (int jj = 0; jj < 4; ++jj)
							if (now % pr[i2 + 1] == 0 && now % pr[jj + 1] == 0)
							{
								int minn = min(fa[i2], fa[jj]);
								for (int kk = 0; kk < 4; ++kk)
									if (fa[kk] == fa[i2] || fa[kk] == fa[jj])
										fa[kk] = minn;
							}
							
							}
							else pp = 1ll * pp * (mod + 1 - p[r[ii + i]]) % mod;
						
						simplify();
						f[i][id[fa]] = (f[i][id[fa]] + 1ll * pp * f[lst][S]) % mod;
					}
				}
			}
		}
		for (int S = 1; S <= cnter; ++S)
			ans = (ans + 1ll * con[S] * f[lst][S]) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
