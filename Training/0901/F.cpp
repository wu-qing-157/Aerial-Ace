#include <cstdio>
#include <set>

#define maxn 100010
int a[maxn];
std::set<int> s;
int prev[maxn], f[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, k; scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		int l = 1, r = 1; s.clear();
		for (int i = 1; i <= n; ++i)
		{
			while (r <= n && r <= i + k) s.insert(a[r++]);
			while (i - l > k) s.erase(a[l++]);
			auto it = s.lower_bound(a[i]);
			if (it != s.begin()) prev[a[i]] = *--it;
			else prev[a[i]] = 0;
			// printf("l %d r %d = %d\n", l, r, prev[a[i]]);
		}
		for (int i = 1; i <= n; ++i) printf("%d%c", f[i] = f[prev[i]] + 1, " \n"[i == n]);
	}
	return 0;
}
