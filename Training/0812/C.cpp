#include <cstdio>
#include <cstring>
#include <vector>

#define maxn 1010
#define maxm 10010
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
const int inf = 0x7fffffff;
std::vector<int> ee[maxn];
inline void link(int a, int b)
{
	ee[a].push_back(b);
	ee[b].push_back(a);
}

int dep[maxn], q[maxn];
void bfs(int x, int n) {
	memset(dep, -1, (n + 1) << 2);
	int head = 0, tail = 1;
	dep[q[1] = x] = 0;
	while (head < tail) {
		int u = q[++head];
		for (int v : ee[u]) {
			if (dep[v] == -1) dep[v] = dep[u] + 1, q[++tail] = v;
		}
	}
}

struct Edge {
	Edge *next, *rev;
	int to, cap;
} *last[maxn], e[maxm << 2], *ecnt = e, *cur[maxn];
int s, t, ans;
inline void link(int a, int b, int w)
{
	*++ecnt = (Edge) {last[a], ecnt + 1, b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, a, 0}; last[b] = ecnt;
}
inline bool bfs()
{
	int head = 0, tail = 1;
	memset(dep, -1, (t + 1) << 2);
	dep[q[1] = t] = 0;
	while (head < tail)
	{
		int now = q[++head];
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (iter -> rev -> cap && dep[iter -> to] == -1)
				dep[q[++tail] = iter -> to] = dep[now] + 1;
	}
	return dep[s] != -1;
}
int dfs(int x, int f)
{
	if (x == t) return f;
	int used = 0;
	for (Edge* &iter = cur[x]; iter; iter = iter -> next)
		if (iter -> cap && dep[iter -> to] + 1 == dep[x])
		{
			int v = dfs(iter -> to, dmin(f - used, iter -> cap));
			iter -> cap -= v;
			iter -> rev -> cap += v;
			used += v;
			if (used == f) return f;
		}
	return used;
}
inline void dinic()
{
	while (bfs())
	{
		memcpy(cur, last, sizeof cur);
		ans += dfs(s, inf);
	}
}
int main()
{
	int n, m; scanf("%d%d", &n, &m);
	
	for (int i = 1; i <= m; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		link(a, b);
	}
	
	for (int i = 1; i <= n; ++i)
	{
		bfs(i, n);
		bool flag = 0;
		for (int j = 1; j <= n; ++j)
			flag |= (dep[j] >= 3) || (dep[j] == -1);
		if (flag) continue;
		
		int cnt1 = 0, cnt2 = 0;
		for (int j = 1; j <= n; ++j) { 
			if (dep[j] == 1) cnt1++;
			if (dep[j] == 2) cnt2++;
		}
		if (cnt1 < cnt2) continue;
		
		s = 0; t = n + 1;
		memset(last, 0, sizeof last); ecnt = e;
		for (int j = 1; j <= n; ++j)
			if (dep[j] == 1)
			{
				link(s, j, 1);
				for (int it : ee[j]) if (dep[it] == 2) link(j, it, 1);
			}
			else link(j, t, 1);
		ans = 0;
		dinic();
		if (ans == cnt2)
		{
			puts("Yes");
			printf("%d %d\n", i, cnt1);
			for (Edge *iter = last[s]; iter; iter = iter -> next)
				if (iter -> rev -> cap)
				{
					for (Edge *iter2 = last[iter -> to]; iter2; iter2 = iter2 -> next)
						if (iter2 -> rev -> cap)
						{
							printf("%d %d\n", iter -> to, iter2 -> to);
							break;
						}
				}
				else printf("%d -1\n", iter -> to);
			return 0;
		}
	}
	puts("No");
	return 0;
}
/*
5 4
1 2
2 3
3 4
4 5

4 4
1 2
2 3
3 4
4 1

4 3
1 2
2 3
3 1
*/
