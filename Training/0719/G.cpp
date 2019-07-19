#include <cstdio>
#include <cmath>

typedef double db;
const db pi = acos(-1.0);
int main()
{
freopen("glorious.in", "r", stdin);
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int R, K, N; scanf("%d%d%d", &N, &R, &K);
		printf("Case %d: %.5lf\n", Cas, (K * tan(pi / K) - pi) * R * R * (1 - 1.0 / pow(cos(pi / K), 2 * N)) / (1 - 1.0 / pow(cos(pi / K), 2)));
	}
	return 0;
}
