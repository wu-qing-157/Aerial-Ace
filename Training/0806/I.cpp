#include <cstdio>
#include <vector>
#include <cstring>

#define maxn 300010
std::vector<int> e[maxn];
inline void link(int a, int b)
{
	e[a].push_back(b);
}
char str[maxn];
int next[maxn][26], fail[maxn], len[maxn], cnt[maxn], last, tot, n;
inline int new_node(int l)
{
	len[++tot] = l;
	return tot;
}
inline void init()
{
	tot = -1; n = 0; last = 0;
	new_node(0);
	new_node(-1);
	str[0] = -1;
	fail[0] = 1;
}
inline int get_fail(int x)
{
	while (str[n - len[x] - 1] != str[n]) x = fail[x];
	return x;
}
inline void extend(int c)
{
	++n;
	int cur = get_fail(last);
	if (!next[cur][c])
	{
		int now = new_node(len[cur] + 2);
		fail[now] = next[get_fail(fail[cur])][c];
		next[cur][c] = now;
	}
	last = next[cur][c];
	++cnt[last];
}
void count()
{
	for (int i = tot; i; --i)
	{
		cnt[fail[i]] += cnt[i];
		link(fail[i], i);
	}
}
int ans[maxn];
bool vis[maxn];
void dfs(int x)
{
	if (x)
	{
		vis[len[x]] = 1;
		if (vis[(len[x] + 1) / 2])
			ans[len[x]] += cnt[x];
	}
	for (int it : e[x])
		dfs(it);
	if (x) vis[len[x]] = 0;
}
int main()
{
	while (scanf("%s", str + 1) != EOF)
	{
		init();
		for (int i = 1; str[i]; ++i)
			extend(str[i] - 'a');
		count();
		dfs(0);
		for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], " \n"[i == n]);
		for (int i = 0; i <= tot; ++i) e[i].clear();
		memset(ans, 0, (n + 1) << 2);
		memset(cnt, 0, (tot + 1) << 2);
		memset(fail, 0, (tot + 1) << 2);
		for (int i = 0; i <= tot; ++i)
			memset(next[i], 0, sizeof (next[i]));
	}
	return 0;
}
