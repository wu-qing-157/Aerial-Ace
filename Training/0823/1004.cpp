#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>

#define maxn 50010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
typedef long long ll;
std::vector<std::pair<int, int> > e[maxn];
struct Queue {
	int x, pos; ll val;
	inline bool operator < (const Queue &that) const {return val > that.val;}
} ;
std::priority_queue<Queue> q;
ll ans[maxn];
int qr[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m, Q, mk = 0; scanf("%d%d%d", &n, &m, &Q);
		while (!q.empty()) q.pop();
		for (int i = 1; i <= n; ++i) e[i].clear();
		for (int i = 1; i <= m; ++i)
		{
			int a, b, w; scanf("%d%d%d", &a, &b, &w);
			e[a].emplace_back(w, b);
		}
		for (int i = 1; i <= n; ++i)
			std::sort(e[i].begin(), e[i].end());
		for (int i = 1; i <= Q; ++i) scanf("%d", qr + i), cmax(mk, qr[i]);
		for (int i = 1; i <= n; ++i) if (e[i].size()) q.push((Queue) {i, 0, e[i][0].first});
		for (int p = 1; mk; --mk, ++p)
		{
			Queue tp = q.top(); q.pop();
			ans[p] = tp.val;
			if  (tp.pos < e[tp.x].size() - 1)
			{
				q.push((Queue) {tp.x, tp.pos + 1, tp.val + e[tp.x][tp.pos + 1].first - e[tp.x][tp.pos].first});
			}
			int to = e[tp.x][tp.pos].second;
			if (e[to].size())
			{
				q.push((Queue) {to, 0, tp.val + e[to][0].first});
			}
		}
		for (int i = 1; i <= Q; ++i) printf("%lld\n", ans[qr[i]]);
	}
	return 0;
}
