#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

long long ans = 0;
int a[maxn], b[maxn];


struct Node {
	Node *ls, *rs;	
	int val, id;
	long long sum, ans;
	int size;
	void update() {
		sum = ls->sum + rs->sum + val;
		size = ls->size + rs->size + 1;
		ans = ls->ans + (val + rs->sum) * (ls->size + 1) + rs->ans;
	}
	void pushdown() {
		
	}
} mem[maxn * 2], *tot = mem, *null = mem;


Node *merge(Node *x, Node *y) {
	if (x == null) return y;
	if (y == null) return x;
	if (rand() % (x->size + y->size) < x->size) {
		x->pushdown();
		x->rs = merge(x->rs, y);
		x->update();
		return x;
	} else {
		y->pushdown();
		y->ls = merge(x, y->ls);
		y->update();
		return y;
	} 
}
Node *merge(Node *a, Node *b, Node *c) {
	return merge(a, merge(b, c));
}

typedef pair<Node*, Node*> Pair;

Pair split(Node *now, int k) { 
	if (now == null) return make_pair(null, null);
	Pair t = make_pair(null, null);
	now.pushdown();
	if (k <= now->ls->size) {
		t = split(now->ls, k);
		now->ls = t.second;
		now->update();
		t.second = now;
	} else {
		t = split(now->rs, k - now->ls->size - 1);
		now->rs = t.first;
		now->update();
		t.first = now;
	} return t;
}

namespace Solve2 {
	
}







namespace Solve1 {

Node *root[maxn];
Node *c[maxn];

int id[maxn];

bool cmp(int x, int y) {
	return c[x]->val > c[y]->val;
}

void solve(int G, int W, int Q) {		
	tot = mem;
	
	for (int i = 0; i < G; i++) {
		c[i].ls = c[i].rs = null;
		c[i].ans = c[i].sum = c[i].val = a[i];
		c[i].size = 1; c[i].id = i;
		id[i] = i;
	}
	
	sort(id + 1, id + 1 + G, cmp);
	
	int S = (G + W - 1) / W;
	for (int i = 0; i < S; i++) {	
		root[i] = null;
		for (int j = 0; j < W; j++) 
			root[i] = merge(root[i], c[id]);
	}
	
	
	
	while (Q--) {
		int x, y; scanf("%d%d", &x, &y);
		int z = a[x];
	}
}
}



void work() {
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	int G, W, S, Q; scanf("%d%d", &G, &W), S = sqrt(G + 1);
	ans = 0;
	for (int i = 0; i < G; i++) scanf("%d", &a[i]), b[i] = a[i];
	sort(b + 1, b + 1 + G);
	reverse(b + 1, b + 1 + G);
	for (int i = 0; i < G; i++) ans += ((i / W) + 1ll) * b[i];
	scanf("%d", &Q);
	if (W >= S) 
		solve1(G, W, Q);
	else 
		solve2(G, W, Q);
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++)
		printf("Case %d:\n", t), work();
	return 0;
}
