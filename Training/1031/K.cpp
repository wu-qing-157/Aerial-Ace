#include <bits/stdc++.h>

using namespace std;

template <typename T>
bool chkmin(T &a, const T b) { return a > b ? a = b, true : false; }

template <typename T>
bool chkmax(T &a, const T b) { return a < b ? a = b, true : false; }


const int maxn = 2e5 + 10;
struct Point {
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
} a[maxn], b[maxn];
int ca[maxn], cb[maxn];
int ida[maxn], idb[maxn], ans_id[maxn];
bool cmpa(int x, int y) { return ca[x] < ca[y]; }
bool cmpb(int x, int y) { return cb[x] < cb[y]; }

long long disof(const Point &a, const Point &b) {
	long long dx = a.x - b.x, dy = a.y - b.y;
	return dx * dx + dy * dy;
}
	
namespace KD_Tree {
const long long inf = (long long)1e18;
const double Alpha = 0.8;
struct Node {
	Node *son[2];	
	int d;
	int id, size;
	Point pos;
#define L first
#define R second
	pair<int, int> segx, segy;
	
	friend int get_size(Node *a) { return a == NULL ? 0 : a->size; }
	
	bool is_balanced() {
		return get_size(son[0]) < size * Alpha && get_size(son[1]) < size * Alpha;
	}
	
	void maintain() {
		size = 1;
		segx = make_pair(pos.x, pos.x);
		segy = make_pair(pos.y, pos.y);
		for (int i = 0; i < 2; i++) if (son[i] != NULL) {
			chkmin(segx.L, son[i]->segx.L),
			chkmin(segy.L, son[i]->segy.L),
			chkmax(segx.R, son[i]->segx.R),
			chkmax(segy.R, son[i]->segy.R),
			size += son[i]->size;
		}
	}
	void init(Point p, int i) {
		son[0] = son[1] = NULL;
		d = rand() % 2; 
		pos = p; id = i;	
		maintain();
	}
	
	long long get_dis(Point pos) {
		long long ans = inf;
		if (segx.L <= pos.x && pos.x <= segx.R && segy.L <= pos.y && pos.y <= segy.R) return 0;
		if (segx.L <= pos.x && pos.x <= segx.R)
			chkmin(ans, 1ll * abs(pos.y - segy.L) * abs(pos.y - segy.L)),
			chkmin(ans, 1ll * abs(pos.y - segy.R) * abs(pos.y - segy.R));
		if (segy.L <= pos.y && pos.y <= segy.R) 
			chkmin(ans, 1ll * abs(pos.x - segx.L) * abs(pos.x - segx.L)),
			chkmin(ans, 1ll * abs(pos.x - segx.R) * abs(pos.x - segx.R));
		long long dx = min(abs(pos.x - segx.L), abs(pos.x - segx.R));
		long long dy = min(abs(pos.y - segy.L), abs(pos.y - segy.R));
		ans = min(ans, dx * dx + dy * dy);
		return ans;
	}
	
} mem[maxn], *tot = mem, *root; 
 

bool cmpx(Node *a, Node *b) { return a->pos.x < b->pos.x; }
bool cmpy(Node *a, Node *b) { return a->pos.y < b->pos.y; }

bool (*cmp[2])(Node *, Node *) = {cmpx, cmpy};

Node *tmp[maxn]; int top;

Node *build(int l, int r) {
	if (l > r) return NULL;
	int mid = l + r >> 1, d = rand() % 2;
	nth_element(tmp + l, tmp + mid, tmp + r + 1, cmp[d]);
	tmp[mid]->son[0] = build(l, mid - 1);
	tmp[mid]->son[1] = build(mid + 1, r);
	tmp[mid]->maintain();
	tmp[mid]->d = d;
	return tmp[mid];
}

void travel(Node *x) {
	if (x == NULL) return;
	tmp[++top] = x;
	travel(x->son[0]);
	travel(x->son[1]);
}

void rebuild(Node **x) {
	top = 0, travel(*x);
	*x = build(1, top);
}

Node **insert(Node * &x, Node *y) {		
	if (x == NULL) {
		x = y; return NULL;
	} else {
		Node **node = insert(x->son[cmp[x->d](x, y)], y);
		x->maintain();
		if (!x->is_balanced()) node = &x;
		return node;
	}
}

void insert(Point pos, int id) {
	Node *cur = tot++;
	cur->init(pos, id);
	Node **node = insert(root, cur);
	if (node != NULL) rebuild(node);
}

pair<long long, int> ask_id(Node *x, Point pos, pair<long long, int> ans) {
	if (!x) return ans;
	chkmin(ans, make_pair(disof(x->pos, pos), x->id));
	if (x->son[0] && x->son[1]) {
		long long disL = x->son[0]->get_dis(pos);
		long long disR = x->son[1]->get_dis(pos);
		if (disL < disR) {
			if (disL <= ans.first) 
				chkmin(ans, ask_id(x->son[0], pos, ans));
			if (disR <= ans.first)
				chkmin(ans, ask_id(x->son[1], pos, ans)); 
		}
		else {
			if (disR <= ans.first)
				chkmin(ans, ask_id(x->son[1], pos, ans)); 
			if (disL <= ans.first) 
				chkmin(ans, ask_id(x->son[0], pos, ans));
		}
	} else {
		if (x->son[0]) 
			chkmin(ans, ask_id(x->son[0], pos, ans));
		if (x->son[1])
			chkmin(ans, ask_id(x->son[1], pos, ans));
	}
	return ans;
}

int ask(Point pos) {
	return ask_id(root, pos, make_pair(inf, 0)).second;
}

}
using namespace KD_Tree;

void work() {
	tot = mem; root = NULL;
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) 
		scanf("%d%d%d", &a[i].x, &a[i].y, &ca[i]), ida[i] = i;
	for (int i = 1; i <= m; i++) 
		scanf("%d%d%d", &b[i].x, &b[i].y, &cb[i]), idb[i] = i;
	
	sort(ida + 1, ida + 1 + n, cmpa);
	sort(idb + 1, idb + 1 + m, cmpb);
	
	for (int i = 1, j = 1; j <= m; j++) {
		while (i <= n && ca[ida[i]] <= cb[idb[j]]) insert(a[ida[i]], ida[i]), i++;
		ans_id[idb[j]] = ask(b[idb[j]]);
	}
	for (int i = 1; i <= m; i++)
		printf("%d %d %d\n", a[ans_id[i]].x, a[ans_id[i]].y, ca[ans_id[i]]);
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
/*
2
3 3
1 1 1
3 2 3
2 3 2
2 2 1
2 2 2
2 2 3
5 5
1 4 4
2 1 2
4 5 3
5 2 1
3 3 5
3 3 1
3 3 2
3 3 3
3 3 4
3 3 5
*/
/*
1 1 1
2 3 2
3 2 3
5 2 1
2 1 2
2 1 2
1 4 4
3 3 5
*/

/*
4 1
2 1 2
4 5 3
5 2 1
3 3 5
3 3 3
*/

