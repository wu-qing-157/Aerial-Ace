#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

unsigned x, y, z;
unsigned rng61()
{
	unsigned t;
	x ^= (x << 16);
	x ^= (x >> 5);
	x ^= (x << 1);
	t = x; x = y; y = z;
	z = (t ^ x) ^ y;
	return z;
}
const int maxn = 1e7 + 10;
unsigned a[maxn], b[110];
int cnt[65547], cnt2[65547];
bool vis[65547];
int id1[maxn];
inline bool cmp(int x, int y) {return a[x] < a[y];}
int main()
{
	unsigned n, m, A, B, C, Cas = 0;
	while (scanf("%u%u%u%u%u", &n, &m, &A, &B, &C) != EOF)
	{
		x = A; y = B; z = C;
		for (int i = 1; i <= m; ++i) scanf("%u", b + i), ++b[i];		
		memset(cnt, 0, 65536 << 2);
		memset(vis, 0, 65536);
		for (int i = 1; i <= n; ++i) a[i] = rng61(), ++cnt[a[i] >> 16 & 65535];
		for (int i = 1; i <= 65535; ++i) cnt[i] += cnt[i - 1];
		memcpy(cnt2, cnt, 65536 << 2);
		for (int i = n; i; --i) id1[cnt[a[i] >> 16 & 65535]--] = i;
		
		printf("Case #%d:", ++Cas);
		for (int i = 1; i <= m; ++i)
		{
			int id = std::lower_bound(cnt2, cnt2 + 65536, b[i]) - cnt2;
			int lst = !id ? 0 : cnt2[id - 1];
			if (!vis[id]) std::sort(id1 + lst + 1, id1 + cnt2[id] + 1, cmp), vis[id] = 1;
			printf(" %u", a[id1[b[i]]]);
		}
		puts("");
	}
	return 0;
}
/*
3 3 1 1 1
0 1 2
*/
