#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define maxn 1000010
char _S[1 << 25], *_T = _S;
inline int F()
{
	int cnt = 0; char ch;
	while (ch = *_T++, ch < '0' || ch > '9') ;
	cnt = ch - '0';
	while (ch = *_T++, ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
	return cnt;
}
typedef long long ll;
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int p[maxn], dep[maxn], fa[maxn], son[maxn], mp[maxn], top[maxn];
void dfs1(int x)
{
	dep[x] = dep[fa[x]] + 1;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa[x])
		{
			fa[iter -> to] = x;
			dfs1(iter -> to);
			mp[iter -> to] > mp[son[x]] ? son[x] = iter -> to : 0;
		}
	mp[x] = mp[son[x]] + 1;
}

ll sum[maxn], *head = sum, *f[maxn];
void dfs2(int x)
{
	top[x] = son[fa[x]] == x ? top[fa[x]] : x;
	if (top[x] == x)
	{
		f[x] = head; head = head + mp[x];
	}
	else f[x] = f[fa[x]] + 1;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa[x]) dfs2(iter -> to);
}
std::vector<std::pair<int, int> > v[maxn];
ll ans[maxn];
bool vis[maxn];
void dfs3(int x)
{
	vis[x] = 1;
	if (son[x]) dfs3(son[x]);
	f[x][0] += p[x];
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to])
		{
			dfs3(iter -> to);
			for (int i = 0; i < mp[iter -> to]; ++i)
				f[x][i + 1] += f[iter -> to][i];
		}
	//printf("x = %d\n", x);
	//for (int i = 0; i < mp[x]; ++i) printf("%lld ", f[x][i]); puts(" fff");
	for (auto it : v[x])
	{
		//if (it.first <= mp[x]) printf("%d %d %d\n", x, it.first, it.second);
		ans[it.second] += it.first >= mp[x] ? 0 : f[x][it.first];
	}
}
int main()
{
	fread(_S, 1, 1 << 25, stdin);
	int n = F();
	for (int i = 1; i <= n; ++i) p[i] = F();
	for (int i = 1; i < n; ++i)
	{
		int a = F(), b = F();
		link(a, b);
	}
	dfs1(1); dfs2(1);
	int q = F();
	for (int qq = 1; qq <= q; ++qq)
	{
		int x = F(), k = F();
		for (int ck = k, cur = x; ck >= 0; )
		{
			v[cur].emplace_back(ck, qq);
			if (ck > 0) v[cur].emplace_back(ck - 1, qq);
			if (cur == 1) ck -= 2;
			else cur = fa[cur], ck--;
		}
	}
	dfs3(1);
	for (int i = 1; i <= q; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
