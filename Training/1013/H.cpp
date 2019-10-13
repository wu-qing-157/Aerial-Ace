#include <cstdio>

#define maxn 100010
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
typedef long long ll;
struct Trie {
	Trie *ch[2];
	int size, id;
	inline void update()
	{
		size = ch[0] -> size + ch[1] -> size;
	}
} mem[maxn * 64], *tot = mem, *rta, *rtb;
ll ans;
inline Trie *new_node()
{
	*++tot = (Trie) {mem, mem, 0, 0};
	return tot;
}
void dfs(Trie *a, Trie *b, int step, int val)
{
	if (!a -> size || !b -> size) return ;
	if (step < 0)
	{
		int s = dmin(a -> size, b -> size);
		ans += 1ll * val * s;
		a -> size -= s;
		b -> size -= s;
		// printf("%d %d\n", a -> id, b -> id);
		return ;
	}
	dfs(a -> ch[0], b -> ch[1], step - 1, val | (1 << step)); a -> update(); b -> update();
	dfs(a -> ch[1], b -> ch[0], step - 1, val | (1 << step)); a -> update(); b -> update();
	dfs(a -> ch[0], b -> ch[0], step - 1, val); a -> update(); b -> update();
	dfs(a -> ch[1], b -> ch[1], step - 1, val); a -> update(); b -> update();
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n); tot = mem; ans = 0;
		rta = new_node(); rtb = new_node();
		for (int i = 1; i <= n; ++i)
		{
			int x; scanf("%d", &x);
			Trie *now = rta;
			for (int j = 30; ~j; --j)
			{
				int d = x >> j & 1;
				++now -> size;
				if (now -> ch[d] == mem) now -> ch[d] = new_node();
				now = now -> ch[d];
			}
			++now -> size;
			now -> id = x;
		}
		for (int i = 1; i <= n; ++i)
		{
			int x; scanf("%d", &x);
			Trie *now = rtb;
			for (int j = 30; ~j; --j)
			{
				int d = x >> j & 1;
				++now -> size;
				if (now -> ch[d] == mem) now -> ch[d] = new_node();
				now = now -> ch[d];
			}
			++now -> size;
			now -> id = x;
		}
		dfs(rta, rtb, 30, 0);
		printf("%lld\n", ans);
	}
	return 0;
}
/*
2
4
1 2 3 4
1 2 3 4
5
10 20 30 40 50
15 25 35 45 55
*/
