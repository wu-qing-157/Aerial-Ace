#include <cstdio>
#include <algorithm>

int main()
{
//	freopen("katryoshka.in", "r", stdin);
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n, m, k; scanf("%d%d%d", &n, &m, &k);
		int ans = std::min(std::min(m, n) + std::max(n - m, 0) / 2, k);
		printf("Case %d: %d\n", Cas, ans);
	}
	return 0;
}
