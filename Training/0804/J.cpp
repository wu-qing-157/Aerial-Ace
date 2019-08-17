#include <cstdio>
#include <cstring>

#define maxn 110
const int mod = 998244353;
int f[maxn][maxn][maxn];
int pos[maxn], a[maxn], b[maxn], pas[maxn];
bool vis[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n);
		memset(pos, 0, (n + 1) << 2);
		memset(pas, 0, (n + 1) << 2);
		memset(vis, 0, n + 1);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), pas[a[i]] = i, vis[a[i]] = 1;
		for (int i = 1; i <= n; ++i) scanf("%d", b + i), pos[b[i]] = i, vis[b[i]] = 1;
		memset(f, 0, sizeof (f));
		int num = 0;
		for (int i = 1; i <= n; ++i) num += !vis[i];
		for (int i = 0; i <= n + 1; ++i)
			for (int j = 0; j <= n + 1; ++j)
				f[0][i][j] = 1;
		for (int len = 1; len <= n; ++len)
			for (int l1 = 1, r1 = len; r1 <= n; ++l1, ++r1)
				for (int l2 = 1, r2 = len; r2 <= n; ++l2, ++r2)
				{
					if (a[l1] && pos[a[l1]])
					{
						if (l2 <= pos[a[l1]] && pos[a[l1]] <= r2)
						{
							int nl = pos[a[l1]] - l2, nr = r2 - pos[a[l1]];
							f[len][l1][l2] = 1ll * f[nl][l1 + 1][l2] * f[nr][l1 + 1 + nl][pos[a[l1]] + 1] % mod;
						}
						else f[len][l1][l2] = 0;
					}
					else
					{
						for (int k = l2; k <= r2; ++k)
						if (!b[k] || (!a[l1] && !pas[b[k]]))
						{
							int nl = k - l2, nr = r2 - k;
							f[len][l1][l2] = (f[len][l1][l2] + 1ll * f[nl][l1 + 1][l2] * f[nr][l1 + 1 + nl][k + 1]) % mod;
						}
					}
					//printf("f[%d][%d][%d] = %d\n", len, l1, l2, f[len][l1][l2] );
				}
		int ans = f[n][1][1];
		for (; num; --num) ans = 1ll * ans * num % mod;
		printf("%d\n", ans );
	}
	return 0;
}