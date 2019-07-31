#include <cstdio>
#include <algorithm>

#define maxn 510
const int mod = 1e9 + 7;
// 2, 3, 5, 7, 11, 13, 17, 19
bool vis[maxn];
int pr[maxn], prcnt, mp[maxn];
inline bool cmp(int a, int b)
{
	return mp[a] < mp[b];
}
int f[maxn][257];
int r[maxn], pnum[maxn], fst[maxn][257];
int main()
{
	int T; scanf("%d", &T);
	mp[1] = 1;
	for (int i = 2; i < maxn; ++i)
	{
		if (!vis[i]) mp[pr[++prcnt] = i] = i, pnum[i] = prcnt - 1;
		for (int j = 1; j <= prcnt && i * pr[j] < maxn; ++j)
		{
			vis[i * pr[j]] = 1;
			mp[i * pr[j]] = mp[i];
			if (i % pr[j] == 0) break;
		}
	}
	mp[0] = -1;
	for (; T; --T)
	{
		int n, k; scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) r[i] = i;
		std::sort(r + 1, r + n + 1, cmp);
		for (int j = 0; j <= k; ++j)
			for (int S = 0; S < 256; ++S) f[j][S] = 0;
		for (int j = 0; j <= k; ++j) for (int S = 0; S < 256; ++S) fst[j][S] = 0;
		f[0][0] = 1;
		int lst = 0;
		for (int i = 1; i <= n; ++i)
		{
			int nw = r[i], tmp = r[i];
			int Sta = 0;
			bool flag = 0;
			for (; tmp != 1; tmp /= mp[tmp])
			{
				if ((Sta & (1 << pnum[mp[tmp]])) != 0) flag = 1;
				if (mp[tmp] < 20) Sta |= 1 << pnum[mp[tmp]];
			}
			if (mp[nw] != mp[r[lst]])
			{
				for (int jj = 0; jj <= k; ++jj)
					for (int S = 0; S < 256; ++S)
						(fst[jj][S] += f[jj][S]) %= mod;
				for (int j = 0; j <= k; ++j)
					for (int S = 0; S < 256; ++S) f[j][S] = 0;
				lst = i;
			}
			/*printf("%d %d\n", nw, Sta);
			for (int j = 0; j <= k; ++j)
				for (int S = 0; S < 3; ++S) printf("f[%d][%d] = %d\n", j, S, fst[j][S]);*/

			if (flag) continue;
			for (int j = 1; j <= k; ++j)
				for (int S = 0; S < 256; ++S)
					if ((S & Sta) == 0)
						(f[j][S | Sta] += fst[j - 1][S]) %= mod;
		}
		int ans = 0;
		for (int j = 0; j <= k; ++j)
			for (int S = 0; S < 256; ++S)
				(fst[j][S] += f[j][S]) %= mod;
		for (int i = 1; i <= k; ++i)
			for (int S = 0; S < 256; ++S)
				(ans += fst[i][S]) %= mod;
		printf("%d\n", ans);
	}
	return 0;
}
/*
2
4 2
6 4
*/
