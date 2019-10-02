#include <cstdio>
#include <ctime>
#include <cstdlib>

#define maxn 300010
const int mod1 = 20181125;
const int mod2 = 19260817;

int pw1[maxn], pw2[maxn];
struct Hash {
	int h1, h2;
	inline Hash operator + (const Hash &that) const {return (Hash) {(h1 + that.h1) % mod1, (h2 + that.h2) % mod2};}
	inline Hash operator - (const Hash &that) const {return (Hash) {(h1 - that.h1) % mod1, (h2 - that.h2) % mod2};}
	Hash(int v) : h1(v % mod1), h2(v % mod2) {}
	inline Hash operator << (const int &that) const {return (Hash) {int(1ll * h1 * pw1[that] % mod1), int(1ll * h2 * pw2[that] % mod2)};}
} ;
struct Treap {
	Treap *ls, *rs;
	Hash h1, h2;
	int size, val;
	bool rev;
	inline void update()
	{
		h1 = (ls -> h1 << (rs -> size + 1)) + (Hash(val) << rs -> size) + rs -> h1;
		h2 = (rs -> h2 << (ls -> size + 1)) + (Hash(val) << ls -> size) + ls -> h2;
		size = ls -> size + rs -> size + 1;
	}
	inline void set_rev()
	{
		rev ^= 1;
		std::swap(h1, h2);
		std::swap(ls, rs);
	}
	inline void pushdown()
	{
		if (rev)
		{
			ls -> set_rev();
			rs -> set_rev();
			rev = 0;
		}
	}
} mem[maxn * 60], *tot = mem, *null = mem, *last = mem;
Treap *new_node(int val)
{
	*++tot = (Treap) {null, null, Hash(val), Hash(val), 1, val, 0};
	return tot;
}
struct Pair {
	Treap *fir, *sec;
} ;
inline Treap *copy(Treap *x)
{
	if (x == null) return null;
	if (x > last) return x;
	*++tot = *x;
	return tot;
}
Pair split(Treap *x, int k)
{
	if (x == null) return (Pair) {null, null};
	Pair y; x -> pushdown();
	Treap *nw = copy(x);
	if (nw -> ls -> size >= k)
	{
		y = split(nw -> ls, k);
		nw -> ls = y.sec;
		nw -> update();
		y.sec = nw;
	}
	else
	{
		y = split(nw -> rs, k - nw -> ls -> size - 1);
		nw -> rs = y.fir;
		nw -> update();
		y.fir = nw;
	}
	return y;
}
Treap *merge(Treap *a, Treap *b)
{
	if (a == null) return b;
	if (b == null) return a;
	Treap *nw;
	if (rand() % (a -> size + b -> size) < a -> size)
	{
		a -> pushdown();
		nw = copy(a);
		nw -> rs = merge(nw -> rs, b);
	}
	else
	{
		b -> pushdown();
		nw = copy(b);
		nw -> ls = merge(a, nw -> ls);
	}
	nw -> update();
	return nw;
}
inline int lcp()
{
}
int main()
{
	int T; scanf("%d", &T);
	pw1[0] = pw2[0] = 1;
	for (int i = 1; i < maxn; ++i)
		pw1[i] = 1ll * pw1[i - 1] * 37 % mod1,
		pw2[i] = 1ll * pw2[i - 1] * 41 % mod2;
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n, m; scanf("%d%d", &n, &m); tot = last = mem;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), ban[i] = 0;
		for (int i = 1; i <= m; ++i)
		{
			int x; scanf("%d", &x);
			ban[x] = 1;
		}
		for (int i = 1; i <= n; ++i)
			if (!ban[i])
			{
				
			}
	}
	return 0;
}
