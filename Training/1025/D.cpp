#include <cstdio>
#include <cstring>

#define maxn 4010
char s1[maxn], s2[maxn];
int f[maxn][maxn];
int next1[maxn][2], next2[maxn][2], n, m;
int dfs(int a, int b)
{
	if (a > n && b > m) return 0;
	if (f[a][b]) return f[a][b];
	int ans = 0x7fffffff;
	for (int i = 0; i < 2; ++i)
	{
		int ret = dfs(next1[a][i], next2[b][i]) + 1;
		ans > ret ? ans = ret : 0;
	}
	return f[a][b] = ans;
}
void dfs_print(int a, int b)
{
	if (a > n && b > m) return ;
	for (int i = 0; i < 2; ++i)
		if (f[next1[a][i]][next2[b][i]] + 1 == f[a][b])
		{
			printf("%d", i);
			dfs_print(next1[a][i], next2[b][i]);
			return ;
		}
}
int main()
{
	scanf("%s%s", s1 + 1, s2 + 1);
	n = strlen(s1 + 1), m = strlen(s2 + 1);
	next1[n + 1][0] = next1[n + 1][1] = n + 1;
	next1[n][0] = next1[n][1] = n + 1;
	for (int i = n; i; --i)
	{
		memcpy(next1[i - 1], next1[i], sizeof (next1[i]));
		next1[i - 1][s1[i] - '0'] = i;
	}
	
	next2[m + 1][0] = next2[m + 1][1] = m + 1;
	next2[m][0] = next2[m][1] = m + 1;
	for (int i = m; i; --i)
	{
		memcpy(next2[i - 1], next2[i], sizeof (next2[i]));
		next2[i - 1][s2[i] - '0'] = i;
	}
	
	int ans = dfs(0, 0);
	dfs_print(0, 0); puts("");
	return 0;
}
