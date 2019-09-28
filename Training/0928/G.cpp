#include <cstdio>
#include <deque>

#define maxn 200010
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
}
int ty[maxn], val[maxn];
int ans[maxn];
std::deque<int> q;
void dfs(int x)
{
	if (x)
	{
		if (ty[x] == 1)
			q.push_back(val[x]);
		else ans[x] = q.front(), q.pop_front();
	}
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		dfs(iter -> to);
	if (ty[x] == 1)
		q.pop_back();
	else q.push_front(ans[x]);
}
int main()
{
//	freopen("queue.in", "r", stdin);
//	freopen("queue.out", "w", stdout);
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		int v; scanf("%d%d", ty + i, &v);
		if (ty[i] == 1)
			scanf("%d", val + i);
		link(v, i);
	}
	dfs(0);
	for (int i = 1; i <= n; ++i)
		if (ty[i] == -1) printf("%d\n", ans[i]);
	return 0;
}
/*
10
1 0 1
1 1 2
1 2 3
1 2 4
-1 3
-1 5
-1 6
-1 4
-1 8
-1 9
*/
