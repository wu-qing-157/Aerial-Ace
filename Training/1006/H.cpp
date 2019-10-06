#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define maxn 800010
#define maxm 3000010
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
typedef long long ll;
ll A[maxn], B[maxn], C[maxn];
int Q;
struct P {
	ll x, y;
	inline P operator - (const P &that) const {return (P) {x - that.x, y - that.y};}
	inline ll operator ^ (const P &that) const {return 1ll * x * that.y - 1ll * y * that.x;}
} ;
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int dfn[maxn], timer, pos[maxn], inv[maxn];
void dfs(int x)
{
	dfn[x] = ++timer; pos[timer] = x;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!dfn[iter -> to]) dfs(iter -> to);
	inv[x] = timer;
}
struct Opt {
	int type; ll val; int x, id;
	inline bool operator < (const Opt &that) const {return val < that.val || (val == that.val && type < that.type);}
} q[maxm], t[maxm];
inline bool cmp(const Opt &a, const Opt &b)
{
	if (a.type != b.type) return a.type < b.type;
	if (a.type == 0) return a.val > b.val;
	else return dfn[a.x] < dfn[b.x];
	return 0;
}
const ll inf = ~0ULL >> 1;
ll ans[maxm]; int n;
inline ll cmp(const P &a, const P &b, const P &c)
{
	return (b - a) ^ (c - a);
}
inline double slope(const P &a, const P &b)
{
	return (b.y - a.y) / (double) (b.x - a.x);
}
struct Seg {
	std::vector<P> v;
	int it;
	inline void add(const P &that)
	{
		int top = v.size();
		P *v = this -> v.data() - 1;
		while (top > 1 && slope(v[top - 1], v[top]) >= slope(v[top - 1], that)) --top;
		this -> v.erase(this -> v.begin() + top, this -> v.end());
		this -> v.push_back(that);
	}
	inline ll query(ll k)
	{
		if (v.empty()) return inf;
		while (it < v.size() - 1 && slope(v[it], v[it + 1]) <= k) ++it;
		return v[it].y - v[it].x * k;
	}
	inline void clear()
	{
		v.clear(); it = 0;
	}
} tr[maxn << 2];
int ql, qr, qv;
void modify(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		tr[o].add((P) {B[qv], A[qv]});
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) modify(o << 1, l, mid);
	if (mid < qr) modify(o << 1 | 1, mid + 1, r);
}
void query(int o, int l, int r, int k, ll &tar)
{
	ll tmp = tr[o].query(-k);
	cmin(tar, tmp);
	if (l == r) return ;
	int mid = l + r >> 1;
	if (ql <= mid) query(o << 1, l, mid, k, tar);
	else query(o << 1 | 1, mid + 1, r, k, tar);
}
void clear(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		tr[o].clear();
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) clear(o << 1, l, mid);
	if (mid < qr) clear(o << 1 | 1, mid + 1, r);
}
void solve(int left, int right)
{
	if (left == right) return ;
	int mid = left + right >> 1;
	solve(left, mid);
	solve(mid + 1, right);

	// printf("ll %d right %d\n", left, right);
	for (int i = mid + 1; i <= right; ++i)
		if (q[i].type == 1)
		{
			ql = dfn[q[i].x]; qr = inv[q[i].x]; qv = q[i].x;
			// printf("==modi %d %d %d\n", ql, qr, q[i].x);
			modify(1, 1, n);
		}
	for (int i = left; i <= mid; ++i)
		if (q[i].type == 0)
		{
			ql = dfn[q[i].x];
			query(1, 1, n, q[i].val, ans[q[i].id]);
			// printf("que %d %d ans %lld\n", ql, q[i].id, ans[q[i].id]);
		}
	for (int i = mid + 1; i <= right; ++i)
		if (q[i].type == 1)
		{
			ql = dfn[q[i].x]; qr = inv[q[i].x];
			clear(1, 1, n);
		}
	for (int i = left, j = mid + 1, k = 0; i <= mid || j <= right; )
	{
		if (i <= mid && (j > right || cmp(q[i], q[j])))
			t[k++] = q[i++];
		else
			t[k++] = q[j++];
	}
	for (int i = left, k = 0; i <= right; ++i, ++k)
		q[i] = t[k];
}
int main()
{
	int qq; scanf("%d%d", &n, &qq);
	for (int i = 1; i <= n; ++i) scanf("%lld", A + i);
	for (int i = 1; i <= n; ++i) scanf("%lld", B + i);
	for (int i = 1; i <= n; ++i) scanf("%lld", C + i), q[++Q] = (Opt) {1, C[i], i, 0};
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		link(a, b);
	}
	dfs(1);
	for (int i = 1; i <= qq; ++i)
	{
		int v; ll t; scanf("%d%lld", &v, &t);
		q[++Q] = (Opt) {0, t, v, i};
		ans[i] = inf;
	}
	std::sort(q + 1, q + Q + 1);
	// for (int i = 1; i <= Q; ++i) printf("%d %d %d\n", q[i].type, q[i].val, q[i].x);
	solve(1, Q);
	for (int i = 1; i <= qq; ++i) printf("%lld\n", ans[i]);
	return 0;
}
