#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

#define maxn 10010
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
int deg[maxn];
inline void link(int a, int b)
{
	++deg[a]; ++deg[b];
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
struct Node {
	int x, d;
	inline bool operator < (const Node &that) const {return (d < that.d) || (d == that.d && x < that.x);}
} ;
std::set<Node> s;
int r[maxn], c[maxn]; bool vis[maxn];
int main()
{
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%*d%*d");
	for (int i = 1; i <= m; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		link(a, b);
	}
	for (int i = 1; i <= n; ++i) s.insert((Node) {i, deg[i]});
	for (int i = 1; i <= n; ++i)
	{
		Node top = *s.begin(); s.erase(top);
		assert(top.d <= 3);
		r[i] = top.x; vis[top.x] = 1;
		for (Edge *iter = last[top.x]; iter; iter = iter -> next)
			if (!vis[iter -> to])
			{
				s.erase((Node) {iter -> to, deg[iter -> to]});
				--deg[iter -> to];
				s.insert((Node) {iter -> to, deg[iter -> to]});
			}
	}
	std::reverse(r + 1, r + n + 1);
	for (int i = 1; i <= n; ++i)
	{
		bool col[5] = {0}; vis[r[i]] = 0;
		for (Edge *iter = last[r[i]]; iter; iter = iter -> next)
			if (!vis[iter -> to])
				col[c[iter -> to]] = 1;
		for (int j = 1; j <= 4; ++j)
			if (!col[j]) {c[r[i]] = j; break;}
	}
	for (int i = 1; i <= n; ++i) printf("%d\n", c[i]);
	return 0;
}
