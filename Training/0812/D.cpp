#include <cstdio>
#include <algorithm>
#include <random>

#define maxn 400010
struct Node *null;
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
struct Node {
	Node *ch[2], *fa;
	int size;
	inline bool type()
	{
		return fa -> ch[1] == this;
	}
	inline void pushup()
	{
		size = ch[0] -> size + ch[1] -> size + 1;
	}
	inline void rotate()
	{
		bool d = type(); Node *f = fa, *gf = f -> fa;
		(fa = gf, f -> fa != null) ? fa -> ch[f -> type()] = this : 0;
		(f -> ch[d] = ch[!d]) != null ? ch[!d] -> fa = f : 0;
		(ch[!d] = f) -> fa = this;
		f -> pushup();
	}
	inline void splay()
	{
		for (; fa != null; rotate())
			if (fa -> fa != null)
				(type() == fa -> type() ? fa : this) -> rotate();
		pushup();
	}
} mem[maxn], *root = mem;
int find_rk(Node *x)
{
	x -> splay();
	root = x;
	return x -> ch[0] -> size + 1;
}
Node *insert(Node *x, int pos, Node *qv)
{
	if (x == null) return qv;
	Node *nw;
	if (x -> ch[0] -> size < pos)
	{
		nw = insert(x -> ch[1], pos - x -> ch[0] -> size - 1, qv);
		x -> ch[1] = nw;
	}
	else
	{
		nw = insert(x -> ch[0], pos, qv);
		x -> ch[0] = nw;
	}
	nw -> fa = x;
	x -> pushup();
	return x;
}
struct Treap {
	Treap *ls, *rs;
	int size, id;
	inline void update()
	{
		size = ls -> size + rs -> size + 1;
	}
} mm[maxn], *rt[maxn], *nl = mm;
struct Pair {
	Treap *fir, *sec;
} ;
inline unsigned randint()
{
	return (unsigned) rand() << 15 | (unsigned) rand();
}
Treap *merge(Treap *a, Treap *b)
{
	if (a == nl) return b;
	if (b == nl) return a;
	if (randint() % (a -> size + b -> size) < a -> size)
	{
		a -> rs = merge(a -> rs, b);
		a -> update();
		return a;
	}
	else
	{
		b -> ls = merge(a, b -> ls);
		b -> update();
		return b;
	}
}
Pair split(Treap *now, int k)
{
	if (now == nl) return (Pair) {nl, nl};
	Pair t = (Pair) {nl, nl};
	if (k <= now -> ls -> size)
	{
		t = split(now -> ls, k);
		now -> ls = t.sec;
		now -> update();
		t.sec = now;
	}
	else
	{
		t = split(now -> rs, k - now -> ls -> size - 1);
		now -> rs = t.fir;
		now -> update();
		t.fir = now;
	}
	return t;
}
int sz;
int query(Treap *nw, int k)
{
	if (nw == nl) return 0x7fffffff;
	int rank = find_rk(mem + nw -> id);
	if (rank >= k) return std::min(query(nw -> ls, k), rank);
	else
	{
		sz += nw -> ls -> size + 1;
		return query(nw -> rs, k);
	}
}
int query_size(Treap *x, int nwpos)
{
	if (x == nl) return 0;
	int rank = find_rk(mem + x -> id);
	if (rank >= nwpos) return query_size(x -> ls, nwpos);
	else return x -> ls -> size + 1 + query_size(x -> rs, nwpos);
}
void Print_tree(Node *x)
{
	if (x == null) return ;
	Print_tree(x -> ch[0]);
	printf("%d ", x - mem);
	Print_tree(x -> ch[1]);
}
void Print_treap(Treap *x)
{
	if (x == nl) return ;
	Print_treap(x -> ls);
	printf("%d ", x -> id);
	Print_treap(x -> rs);
}
int main()
{
	null = mem; null -> ch[0] = null -> ch[1] = null -> fa = null;
	nl = mm; nl -> ls = nl -> rs = nl;
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		int c, a; scanf("%d%d", &c, &a);
		mm[i] = (Treap) {nl, nl, 1, i};
		mem[i] = (Node) {null, null, null, 1};
		if (!rt[c])
		{
			rt[c] = mm + i;
			if (root == mem) root = mem + i;
			else
			{
				insert(root, i - 1, mem + i);
				(mem + i) -> splay(); root = mem + i;
			}
		}
		else
		{
			sz = 0;
			int pos = query(rt[c], i - a - 1), nwpos;
			if (pos == i - a - 1) nwpos = pos + 1, ++sz;
			else nwpos = pos;
			Pair t = split(rt[c], sz);
			rt[c] = merge(t.fir, merge(mm + i, t.sec));
			insert(root, nwpos - 1, mem + i);
			(mem + i) -> splay(); root = mem + i;
		}
	}
	Print_tree(root); puts("");
	return 0;
}
