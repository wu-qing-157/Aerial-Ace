#include <cstdio>
#include <set>
#include <vector>
#include <cstring>

#define maxn 1010
#define maxm 1010
std::vector<int> v[maxn];
struct Edge {
	Edge *next;
	int to, id;
} *last[maxn], e[maxm], *ecnt = e;
bool end[maxn];
int Fa[maxn];
int Find(int x) {return Fa[x] == x ? x : Fa[x] = Find(Fa[x]);}
inline void link(int a, int b, int id)
{
	*++ecnt = (Edge) {last[a], b, id}; last[a] = ecnt;
}
int st[maxn], top, col[maxn];
int s[maxn], len;
#define cmax(_a, _b) (_a < (_b) ? _a = (_b), 1 : 0)
void dfs1(int x)
{
	if (end[x])
	{
		cmax(len, top);
	}
	for (Edge *iter = last[x]; iter; iter = iter -> next)
	{
		st[++top] = iter -> id;
		dfs1(iter -> to);
		--top;
	}
}
void dfs2(int x)
{
	if (end[x])
	{
		for (int i = 1; i <= top; ++i)
			v[len + i - top].push_back(st[i]);
		if (len == top)
			memcpy(s + 1, st + 1, top << 2);
	}
	for (Edge *iter = last[x]; iter; iter = iter -> next)
	{
		st[++top] = iter -> id;
		dfs2(iter -> to);
		--top;
	}
}
int main()
{
freopen("suffix.in", "r", stdin);
freopen("suffix.out", "w", stdout);
	int n, m, k; scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; ++i)
	{
		int v; scanf("%d", &v);
		end[v] = 1;
	}
	for (int i = 1; i <= m; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		link(a, b, i); Fa[i] = i;
	}
	dfs1(1); dfs2(1);
	for (int i = 1; i <= m; ++i)
		if (v[i].size())
		{
			int x = v[i][0], f1 = Find(x), f2;
			for (auto it : v[i])
			{
				if ((f2 = Find(it)) != f1)
					Fa[f2] = f1;
			}
		}
	int ccc = 0;
	for (int i = 1; i <= m; ++i)
	{
		if (!col[Find(i)]) col[Find(i)] = ++ccc;
		col[i] = col[Find(i)];
	}
	printf("%d %d\n", len, ccc);
	for (int i = 1; i <= len; ++i) printf("%d%c", col[s[i]], " \n"[i == len]);
	for (int i = 1; i <= m; ++i) printf("%d%c", col[i], " \n"[i == m]);
	return 0;
}
/*
7 8 4
1 3 4 7
1 2
1 3
2 4
3 5
3 6
4 5
5 6
6 7
i = 1
2 2 2 1 1 
i = 2
5 4 3 3 
i = 3
8 7 6 
i = 4
8 7 
i = 5
8 
2 2 5 5 5 8 8 8 5 3
1 2 3 3 3
1 1 2 2 2 3 3 3
*/
