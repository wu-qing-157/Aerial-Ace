#include <cstdio>
#include <queue>

#define maxn 100010
std::priority_queue<std::pair<int, int> > q;
int a[maxn], ch[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			ch[i] = 0;
			ch[i] += 2 * i <= n;
			ch[i] += 2 * i + 1 <= n;
			if (ch[i] == 0) q.push(std::make_pair(a[i], i));
		}
		long long ans[2] = {0};
		int type = 0;
		while (!q.empty())
		{
			std::pair<int, int> now = q.top(); q.pop();
			//printf("%d %d\n", now.first, now.second);
			int p = now.second;
			ans[type] += now.first; type ^= 1;
			if (--ch[p >> 1] == 0) q.push(std::make_pair(a[p >> 1], p >> 1));
		}
		printf("%lld %lld\n", ans[0], ans[1]);
	}
	return 0;
}
