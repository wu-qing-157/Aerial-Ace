#include <bits/stdc++.h>

const int maxn = 2e5 + 10;
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
} mem[maxn << 2], *tot = mem, *st[maxn << 2];
int top;
void link(Node *a, Node *b)
{
	a -> link(b);
}
void cut(Node *a, Node *b)
{
	a -> cut(b);
}
bool check(Node *a, Node *b)
{
	a -> make_root();
	a -> access();
	return b -> access() == a;
}
Node *new_node()
{
	if (top) return st[top--];
	*++tot = (Node) {mem, mem, mem, 0};
	return tot;
}
void del_node(Node *x)
{
	st[++top] = x;
	*x = (Node) {null, null, null, 0};
}

std::pair<int, int>loop_edge;
std::stack<std::pair<std::pair<int, int>, int> >edge;

std::vector<int>G[maxn];

std::map<int, int> color[maxn];
std::map<int, int> deg[maxn];
std::map<int, Node*> node[maxn];

int ans = 0;

void my_cut(int u, int v, int c) {
	color[u][v] = 0;
	cut(node[u][c], node[v][c]); ans++;
	if (--deg[u][c] == 0) 
		ans--, del_node(node[u][c]), node[u][c] = NULL;
	if (--deg[v][c] == 0) 
		ans--, del_node(node[v][c]), node[v][c] = NULL;
}

void my_link(int u, int v, int c) {
	color[u][v] = c;
	if (deg[u][c]++ == 0) node[u][c] = new_node(), ans++;
	if (deg[v][c]++ == 0) node[v][c] = new_node(), ans++;
	link(node[u][c], node[v][c]); ans--;
}

int get_ans() {
	int u = loop_edge.first, v = loop_edge.second, c = color[u][v];
	int now = ans;
	if (deg[u][c] == 0) now++;
	if (deg[v][c] == 0) now++;
	if (!deg[u][c] || !deg[v][c] || !check(node[u][c], node[v][c])) now--;
	return now;
}

bool vis[maxn];
bool find_loop_edge(int u, int f) {
	vis[u] = true;
	for (auto v : G[u]) {
		if (v == f) continue;
		if (vis[v]) {
			loop_edge = std::make_pair(std::min(u, v), std::max(v, u));
			return true;
		} else {
			if (find_loop_edge(v, u)) return true;
		}
	} return false;
}

void work() {
	int n, q; scanf("%d%d", &n, &q);
	
	for (int i = 1; i <= n; i++) G[i].clear();
	for (int i = 1; i <= n; i++) color[i].clear();
	for (int i = 1; i <= n; i++) deg[i].clear();
	for (int i = 1; i <= n; i++) node[i].clear();
	
	ans = 0; top = 0; tot = mem;
	
	for (int i = 1; i <= n; i++) {
		int u, v, c; scanf("%d%d%d", &u, &v, &c);
		if (u > v) std::swap(u, v);
		edge.push(std::make_pair(std::make_pair(u, v), c));
		G[u].push_back(v);
		G[v].push_back(u);
	}
	
	memset(vis, 0, sizeof (vis[0]) * (n + 1));
	find_loop_edge(1, -1); 
	
	while (edge.size()) {
		int u = edge.top().first.first, v = edge.top().first.second, c = edge.top().second;
		edge.pop();
		if (u == loop_edge.first && v == loop_edge.second) color[u][v] = c;
		else my_link(u, v, c);
	}
	
	while (q--) {
		int u, v, c; scanf("%d%d%d", &u, &v, &c);
		if (u > v) std::swap(u, v);
		if (u == loop_edge.first && v == loop_edge.second) {
			color[u][v] = c;	
		} else {
			my_cut(u, v, color[u][v]);
			my_link(u, v, c);
		}
		printf("%d\n", get_ans());
	}
}

int main() {
	null = mem; null -> ch[0] = null -> ch[1] = null;
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++)
		printf("Case #%d:\n", t), work();
	return 0;
}
