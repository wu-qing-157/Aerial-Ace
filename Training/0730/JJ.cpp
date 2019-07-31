#include <cstdio>
#include <algorithm>

#define maxn 1000
int a[maxn], b[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		int *aa = a, *bb = b;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= m; ++i)
		{
			for (int j = 1; j <= n; ++j)
				bb[j] = bb[j - 1] ^ aa[j];
			std::swap(aa, bb);
		}
		for (int i = 1; i <= n; ++i) printf("%d ", aa[i]); puts("");
	}
	return 0;
}
