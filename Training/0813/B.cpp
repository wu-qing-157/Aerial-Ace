#include <cstdio>
#include <algorithm>

#define maxn 100010
struct Trie {
	Trie *ch[2];
	int size;
	inline void update()
	{
		size = ch[0] -> size + ch[1] -> size;
	}
} ;
struct Trie_Tree {
	Trie mem[maxn * 30], *rt, *tot;
	Trie *new_node()
	{
		*++tot = (Trie) {{mem, mem}, 0};
		return tot;
	}
	void init()
	{
		tot = mem;
		mem -> size = 0;
		mem -> ch[0] = mem -> ch[1] = mem;
		rt = new_node();
	}
	void insert(int x)
	{
		Trie *now = rt;
		for (int i = 29; ~i; --i)
		{
			++now -> size; int d = x >> i & 1;
			if (now -> ch[d] == mem) now -> ch[d] = new_node();
			now = now -> ch[d];
		}
		++now -> size;
	}
} tr[2];
int ans, aa[maxn];
void dfs(Trie *a, Trie *b, int dep, int value)
{
	if (!a -> size || !b -> size) return ;
	if (dep == -1)
	{
		for (; a -> size && b -> size; )
			aa[++ans] = value, --a -> size, --b -> size;
		return ;
	}
	dfs(a -> ch[0], b -> ch[0], dep - 1, value);
	a -> update(); b -> update();
	dfs(a -> ch[1], b -> ch[1], dep - 1, value);
	a -> update(); b -> update();
	dfs(a -> ch[1], b -> ch[0], dep - 1, value | (1 << dep));
	a -> update(); b -> update();
	dfs(a -> ch[0], b -> ch[1], dep - 1, value | (1 << dep));
	a -> update(); b -> update();
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n); ans = 0;
		tr[0].init(); tr[1].init();
		for (int i = 1; i <= n; ++i)
		{
			int x; scanf("%d", &x);
			tr[0].insert(x);
		}
		for (int i = 1; i <= n; ++i)
		{
			int x; scanf("%d", &x);
			tr[1].insert(x);
		}
		dfs(tr[0].rt, tr[1].rt, 29, 0);
		if (ans != n) printf("%d", 1 / 0);
		std::sort(aa + 1, aa + ans + 1);
		for (int i = 1; i <= n; ++i) printf("%d%c", aa[i], " \n"[i == n]);
	}
	return 0;
}
