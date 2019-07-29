#include <cstdio>

#define maxn 500010
struct Node {
	int val[4], num;
	Node *ch[4], *fa;
	bool leaf;
} mem[maxn], *root = mem, *tot = mem, *null;
Node *new_node(bool leaf)
{
	*++tot = (Node) {{0, 0, 0, 0}, 0, {null, null, null, null}, null, leaf};
    return tot;
}
void push_back(Node *x, int v, Node *ns)
{
	if (x == null)
	{
		Node *nt = new_node(0);
		nt -> ch[0] = root;
		x = root = nt;
	}
	for (int i = 0; i < x -> num; ++i)
		if (v < x -> val[i])
		{
			x -> ch[x -> num + 1] = x -> ch[x -> num];
			for (int j = x -> num; j > i; --j)
				x -> val[j] = x -> val[j - 1],
				x -> ch[j] = x -> ch[j - 1];
			x -> val[i] = v;
			x -> ch[i + 1] = ns;
			++x -> num;
			return ;
		}
	x -> val[x -> num] = v;
	++x -> num;
	x -> ch[x -> num] = ns;
}
void insert(Node *x, int v)
{
	if (x -> num == 3)
	{
		int mid = x -> val[1];
		Node *nw = new_node(x -> leaf);
		push_back(x -> fa, mid, nw);
		if (x -> fa == null) x -> fa = root;
		nw -> num = 1; nw -> val[0] = x -> val[2];
		nw -> fa = x -> fa;
		nw -> ch[0] = x -> ch[2]; nw -> ch[1] = x -> ch[3];
		nw -> ch[0] -> fa = nw; nw -> ch[1] -> fa = nw;
		x -> num = 1;
		x = x -> fa;
	}
	if (x -> leaf)
	{
		push_back(x, v, null);
		return ;
	}
	for (int i = 0; i < x -> num; ++i)
		if (v < x -> val[i])
		{
			insert(x -> ch[i], v);
			return ;
		}
	insert(x -> ch[x -> num], v);
}
void dfs(Node *x)
{
	if (!x) return ;
	//printf("now_node :%lld fa: %lld\n", x - mem, x -> fa - mem);
	for (int i = 0; i < x -> num; ++i) printf("%d%c", x -> val[i], " \n"[i == x -> num - 1]);
	/*printf("children\n");
	for (int i = 0; i <= x -> num; ++i)
		printf("%lld%c", x -> ch[i] - mem, " \n"[i == x -> num]);*/
	//puts("----");
	if (x -> leaf) return ;
	for (int i = 0; i <= x -> num; ++i)
		dfs(x -> ch[i]);
}
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		printf("Case #%d:\n", Cas);
		int n; scanf("%d", &n); tot = mem;
		null = mem;
		root = new_node(1);
		for (; n; --n)
		{
			int x; scanf("%d", &x);
			insert(root, x);
			//dfs(root);
			//puts("-------------");
		}
		dfs(root);
	}
}
/*
6
4
1 2 3 4
4
4 3 2 1
17
6 3 5 7 1 10 2 9 4 8 11 12 13 14 15 16 17
4
1 2 3 4
4
4 3 2 1
17
6 3 5 7 1 10 2 9 4 8 11 12 13 14 15 16 17
*/

