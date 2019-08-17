#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 1000010
struct Base {
	int base[32], tim[32];
	inline void insert(int x, int pos)
	{
		for (; x; )
		{
			int tmp = 31 - __builtin_clz(x);
			if (!base[tmp])
			{
				base[tmp] = x;
				tim[tmp] = pos;
				return ;
			}
			if (tim[tmp] < pos)
			{
				std::swap(pos, tim[tmp]);
				std::swap(x, base[tmp]);
			}
			x ^= base[tmp];
		}
		return ;
	}
} b[maxn];
int a[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			memcpy(b[i].base, b[i - 1].base, sizeof (b[i].base));
			memcpy(b[i].tim, b[i - 1].tim, sizeof (b[i].tim));
			b[i].insert(a[i], i);
		}
		int ans = 0;
		for (; m; --m)
		{
			int opt; scanf("%d", &opt);
			if (!opt)
			{
				int l, r; scanf("%d%d", &l, &r);
				(l ^= ans) %= n; (r ^= ans) %= n; ++l; ++r;
				if (l > r) std::swap(l, r);
				ans = 0;
				for (int i = 30; ~i; --i)
					if (b[r].tim[i] >= l)
						if ((b[r].base[i] ^ ans) > ans)
							ans ^= b[r].base[i];
				printf("%d\n", ans );
			}
			else
			{
				int x; scanf("%d", &x); x ^= ans;
				++n;
				memcpy(b[n].base, b[n - 1].base, sizeof (b[n].base));
				memcpy(b[n].tim, b[n - 1].tim, sizeof (b[n].tim));
				b[n].insert(x, n);
			}
		}
	}
	return 0;
}