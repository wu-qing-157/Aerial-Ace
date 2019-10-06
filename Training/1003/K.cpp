#include <cstdio>
#include <map>
#include <cstring>
#include <algorithm>

#define maxn 100010
const int mod1 = 19260817;
const int mod2 = 998244353;
int next[maxn][26];
std::map<std::pair<int, int>, int> mp;
void dfs(int x, int h1, int h2)
{
	mp[std::make_pair(h1, h2)] = x;
	for (int i = 0; i < 26; ++i)
		if (next[x][i])
			dfs(next[x][i], (h1 * 27ll + i + 1) % mod1, (h2 * 33ll + i + 1) % mod2);
}
char s[maxn];
int f[maxn][20];
int pw1[maxn], pw2[maxn], pre1[maxn], pre2[maxn];
inline bool check(int l, int r)
{
	return mp.count(std::make_pair(
	int((pre1[r] - 1ll * pre1[l - 1] * pw1[r - l + 1] % mod1 + mod1) % mod1),
	int((pre2[r] - 1ll * pre2[l - 1] * pw2[r - l + 1] % mod2 + mod2) % mod2)));
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m, q; scanf("%d%d%d", &n, &m, &q);
		mp.clear();
		memset(next[0], 0, sizeof (next[0]));
		pw1[0] = pw2[0] = 1;
		for (int i = 1; i <= m; ++i)
			pw1[i] = 1ll * pw1[i - 1] * 27ll % mod1,
			pw2[i] = 1ll * pw2[i - 1] * 33ll % mod2;
		for (int i = 1; i <= n; ++i)
		{
			int fa; char s[3];
			scanf("%d%s", &fa, s);
			next[fa][s[0] - 'a'] = i;
			memset(next[i], 0, sizeof (next[i]));
		}
		dfs(0, 0, 0);
		scanf("%s", s + 1);
		for (int i = 1; i <= m; ++i)
			pre1[i] = (pre1[i - 1] * 27ll + (s[i] - 'a' + 1)) % mod1,
			pre2[i] = (pre2[i - 1] * 33ll + (s[i] - 'a' + 1)) % mod2;
		for (int i = 1; i <= m; ++i)
		{
			int left = i, right = m;
			while (left < right)
			{
				int mid = left + right >> 1;
				if (check(i, mid)) left = mid + 1;
				else right = mid;
			}
			f[i][0] = left + 1;
		}
		for (int j = 0; j < 20; ++j)
			f[m + 1][j] = m + 2,
			f[m + 2][j] = m + 2;
		for (int i = m; i; --i)
			for (int j = 1; j < 20; ++j)
				f[i][j] = f[f[i][j - 1]][j - 1];
		for (; q; --q)
		{
			int l, r; scanf("%d%d", &l, &r);
			int ans = 0;
			for (int i = 19; ~i; --i)
				if (f[l][i] <= r + 1 && f[l][i] <= m)
					ans |= 1 << i,
					l = f[l][i];
			//printf("l %d r %d\n", l, r);
			auto has = std::make_pair(
	int((pre1[r] - 1ll * pre1[l - 1] * pw1[r - l + 1] % mod1 + mod1) % mod1),
	int((pre2[r] - 1ll * pre2[l - 1] * pw2[r - l + 1] % mod2 + mod2) % mod2));
			printf("%d %d\n", ans + (r == m && mp[has] == 0), mp[has]);
		}
	}
	return 0;
}
/*
2
5 10 5
0 a
0 b
1 a
1 c
2 a
aaacbaacac
1 5
1 6
1 7
3 9
4 10
5 10 5
0 a
0 b
1 a
1 c
2 a
aaacbaacab
1 5
1 6
1 7
3 9
4 10
*/
