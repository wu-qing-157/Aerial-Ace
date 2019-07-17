#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>

#define maxn 8010
struct Node *null;
struct Node {
	Node *ch[2], *fa;
	bool rev;
	inline bool type()
	{
		return fa -> ch[1] == this;
	}
	inline bool check()
	{
		return fa -> ch[type()] == this;
	}
	inline void pushdown()
	{
		if (rev)
		{
			ch[0] -> rev ^= 1;
			ch[1] -> rev ^= 1;
			std::swap(ch[0], ch[1]);
			rev ^= 1;
		}
	}
	inline void pushdownall()
	{
		if (check()) fa -> pushdownall();
		pushdown();
	}
	inline void rotate()
	{
		bool d = type(); Node *f = fa, *gf = f -> fa;
		(fa = gf, f -> check()) ? fa -> ch[f -> type()] = this : 0;
		(f -> ch[d] = ch[!d]) != null ? ch[!d] -> fa = f : 0;
		(ch[!d] = f) -> fa = this;
	}
	inline void splay(bool need = 1)
	{
		if (need) pushdownall();
		for (; check(); rotate())
			if (fa -> check())
				(type() == fa -> type() ? fa : this) -> rotate();
	}
	inline Node *access()
	{
		Node *i = this, *j = null;
		for (; i != null; i = (j = i) -> fa)
		{
			i -> splay();
			i -> ch[1] = j;
		}
		return j;
	}
	inline void make_root()
	{
		access();
		splay();
		rev ^= 1;
	}
	inline void link(Node *that)
	{
		make_root();
		fa = that;
		splay(0);
	}
	inline void cut(Node *that)
	{
		make_root();
		that -> access();
		that -> splay(0);
		that -> ch[0] = fa = null;
	}
} ;
struct LCT {
	Node mem[maxn];
	inline void link(int a, int b)
	{
		(mem + a) -> link(mem + b);
	}
	inline void cut(int a, int b)
	{
		(mem + a) -> cut(mem + b);
	}
	inline bool check(int a, int b)
	{
		(mem + a) -> make_root();
		(mem + a) -> access();
		return (mem + b) -> access() == mem + a;
	}
} tr[110];
std::map<std::pair<int, int>, int> col;
int deg[110][maxn];
int main()
{
	int n, m, c, t;
	null = new Node; null -> ch[0] = null -> ch[1] = null;
	while (scanf("%d%d%d%d", &n, &m, &c, &t) != EOF)
	{
		if (!n && !m && !c && !t) return 0;
		col.clear();
		for (int i = 1; i <= c; ++i)
			for (int j = 1; j <= n; ++j)
				tr[i].mem[j] = (Node) {null, null, null, 0}, deg[i][j] = 0;
		for (int i = 1; i <= m; ++i)
		{
			int a, b, c; scanf("%d%d%d", &a, &b, &c);
			tr[c].link(a, b);
			col[std::make_pair(a, b)] = c; ++deg[c][a]; ++deg[c][b];
		}
		for (int i = 1; i <= t; ++i)
		{
			int a, b, c; scanf("%d%d%d", &a, &b, &c);
			if (!col[std::make_pair(a, b)]) puts("No such cable.");
			else if (col[std::make_pair(a, b)] == c) puts("Already owned.");
			else if (deg[c][a] >= 2 || deg[c][b] >= 2) puts("Forbidden: monopoly.");
			else if (tr[c].check(a, b)) puts("Forbidden: redundant.");
			else
			{
				puts("Sold.");
				int cc = col[std::make_pair(a, b)];
				tr[cc].cut(a, b);
				--deg[cc][a]; --deg[cc][b];
				tr[c].link(a, b);
				col[std::make_pair(a, b)] = c;
				++deg[c][a]; ++deg[c][b];
			}
		}
		puts("");
	}
	return 0;
}
/*
4 5 3 5
1 2 1
2 3 1
3 4 2
1 4 2
1 3 3
1 2 3
1 2 3
1 4 3
2 3 3
2 4 3

2 1 1 1
1 2 1
1 2 1

4 5 3 5
1 2 1
2 3 1
3 4 2
1 4 2
1 3 3
1 2 3
1 2 3
1 4 3
2 3 3
2 4 3

2 1 1 1
1 2 1
1 2 1

0 0 0 0
*/
