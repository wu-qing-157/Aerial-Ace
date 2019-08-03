#include <cstdio>
#include <cstring>

#define maxn 500010
typedef long long ll;
int tr[maxn * 30][2], size[maxn * 30], size2[maxn * 30], tot;
ll cnt[33][2];
int a[maxn];
int new_node()
{
	++tot; tr[tot][0] = tr[tot][1] = 0; size[tot] = 0;
	return tot;
}
ll ans;
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n); tot = 0; tr[0][0] = tr[0][1] = 0;
		memset(cnt, 0, sizeof (cnt)); ans = 0;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			int now = 0;
			for (int j = 29; ~j; --j)
			{
				int d = a[i] >> j & 1;
				if (!tr[now][d]) tr[now][d] = new_node();
				now = tr[now][d];
				++size[now];
			}
		}
		memcpy(size2, size, (tot + 1) << 2);
		memset(size, 0, (tot + 1) << 2);
		for (int i = 1; i <= n; ++i)
		{
			int now = 0;
			for (int j = 29; ~j; --j)
			{
				int d = a[i] >> j & 1;
				cnt[j][d ^ 1] -= size[tr[now][d ^ 1]];
				now = tr[now][d];
				--size2[now];
			}
			for (int j = 29; ~j; --j)
				ans += cnt[j][a[i] >> j & 1];
			/*for (int j = 2; j >= 0; --j) printf("%lld %lld\n", cnt[j][0], cnt[j][1]);
			printf("%lld\n", ans);
			puts("");*/
			
			/*for (int j = 1; j <= tot; ++j)
			{
				int d = a[i] >> dep[j] & 1;
				ans += size[tr[j][d]] * (size2[tr[j][d ^ 1]] - size[tr[j][d ^ 1]]);
			}*/
			
			now = 0;
			for (int j = 29; ~j; --j)
			{
				int d = a[i] >> j & 1;
				cnt[j][d] += size2[tr[now][d ^ 1]] - size[tr[now][d ^ 1]];
				cnt[j][d ^ 1] -= size[tr[now][d ^ 1]];
				now = tr[now][d];
				++size[now];
			}
			now = 0;
			for (int j = 29; ~j; --j)
			{
				int d = a[i] >> j & 1;
				cnt[j][d ^ 1] += size[tr[now][d ^ 1]];
				now = tr[now][d];
				++size2[now];
			}
			
		}
		printf("%lld\n", ans);
	}
	return 0;
}
