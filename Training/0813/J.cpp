#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>

#define maxn 400010
int a[maxn], b[maxn];
std::set<int> s;
int mn[maxn << 2], mx[maxn << 2];
inline void update(int o)
{
	mn[o] = std::min(mn[o << 1], mn[o << 1 | 1]);
	mx[o] = std::max(mx[o << 1], mx[o << 1 | 1]);
}
void build(int o, int l, int r)
{
	if (l == r)
	{
		mn[o] = mx[o] = b[l];
		return ;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	update(o);
}
int ql, qr;
int query_mn(int o, int l, int r)
{
	if (ql <= l && r <= qr) return mn[o];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret = std::min(query_mn(o << 1, l, mid), ret);
	if (mid < qr) ret = std::min(query_mn(o << 1 | 1, mid + 1, r), ret);
	return ret;
}
int query_mx(int o, int l, int r)
{
	if (ql <= l && r <= qr) return mx[o];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret = std::max(query_mx(o << 1, l, mid), ret);
	if (mid < qr) ret = std::max(query_mx(o << 1 | 1, mid + 1, r), ret);
	return ret;
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n);
		for (int i = 1; i <= 2 * n; ++i) s.insert(i);
		memset(b, 0, (n + 1) << 3);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		int t1 = 0, t2 = n;
		for (int i = 1; i <= n; ++i)
		{
			if (a[i] < 0)
				if (b[1] == 0 || -a[i] < b[1])
				{
					while (b[t1 + 1]) ++t1;
					b[++t1] = -a[i];
				}
				else b[n + i - 1] = a[i];
			else b[n + i - 1] = a[i];
			s.erase(a[i] < 0 ? -a[i] : a[i]);
		}
		//for (int i = 1; i <= 2 * n; ++i) printf("%d%c", b[i], " \n"[i == 2 * n]);
		t2 = 2 * n - 1;
		bool fail = 0;
		for (auto it : s)
		{
			if (it < b[1])
			{
				while (b[t2 + 1]) ++t2;
				b[++t2] = it;
			}
			else
			{
				while (b[t1 + 1]) ++t1;
				b[++t1] = it;
			}
		}
		s.clear();
		for (int i = 1; i <= 2 * n; ++i) if (!b[i]) {puts("-1"); fail = 1; break;}
		if (!fail)
			for (int i = 1; i <= 2 * n; ++i) printf("%d%c", b[i], " \n"[i == 2 * n]);
	}
	return 0;
}
