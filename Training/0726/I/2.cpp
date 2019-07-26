#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e4 + 10;


struct Node {
	int min, tag;
};

const int INF = ~0U >> 2;

int n, m;

struct segtree {
#define ls p << 1
#define rs p << 1 | 1
	Node T[maxn << 2];
	void pushup(int p) {
		T[p].min = min(T[ls].min, T[rs].min);
	}
	void pushdown(int p) {
		T[ls].tag += T[p].tag;
		T[rs].tag += T[p].tag;
		T[ls].min += T[p].tag;
		T[rs].min += T[p].tag;
		T[p].tag = 0;
	}
		
	void build(int p, int l, int r) {
		T[p].min = 0;
        T[p].tag = 0;
		if (l != r) {
			int mid = (l + r) >> 1;
			build(ls, l, mid);
			build(rs, mid + 1, r);
		}
	}

	void add(int p, int l, int r, int L, int R, int val) {
		if (l == L && r == R) {
			T[p].min += val;
			T[p].tag += val;
		}
		else {
			pushdown(p);
			int mid = (l + r) >> 1;
			if (R <= mid) add(ls, l, mid, L, R, val);
			else if (L > mid) add(rs, mid + 1, r, L, R, val);
			else {
				add(ls, l, mid, L, mid, val);
				add(rs, mid + 1, r, mid + 1, R, val);
			}
			pushup(p);
		}
	}

	int ask(int p, int l, int r, int L, int R) {
		if (l == L && r == R) return T[p].min;
		else {
			pushdown(p);
			int mid = (l + r) >> 1;
			if (R <= mid) return ask(ls, l, mid, L, R);
			else if (L > mid) return ask(rs, mid + 1, r, L, R);
			else return min(
				ask(ls, l, mid, L, mid),
				ask(rs, mid + 1, r, mid + 1, R)
			);
		}
	}
} st[110];

int D[maxn], R[maxn];
int ans, C[maxn], P[maxn];
vector<pair<int, int> >seg[maxn];

int main() {
    for (int cas = 1; scanf("%d%d", &n, &m), n && m; cas++) {
        for (int i = 2; i <= n; i++) scanf("%d", &D[i]);
        for (int i = 1; i <= n; i++) scanf("%d", &C[i]);
        for (int i = 1; i <= n; i++) scanf("%d", &R[i]);
        for (int i = 1; i <= n; i++) scanf("%d", &P[i]);

        for (int i = 1; i <= n; i++) {
            int l = D[i] - R[i], r = D[i] + R[i];
            l = lower_bound(D + 1, D + n + 1, l) - D;
            r = upper_bound(D + 1, D + n + 1, r) - D - 1;
            seg[r].emplace_back(l, P[i]);
        }

        for (int j = 0; j <= m; j++) st[j].build(1, 0, n);
		st[0].add(1, 0, n, 1, n, INF);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++)
                st[j].add(1, 0, n, i, i, st[j - 1].ask(1, 0, n, 0, i - 1) + C[i]);
            for (const auto &p : seg[i])
                for (int j = 0; j <= m; j++)
                    st[j].add(1, 0, n, 0, p.first - 1, p.second);
        }
        ans = INF;
        for (int j = 0; j <= m; j++)
            ans = std::min(ans, st[j].ask(1, 0, n, 0, n));
        printf("Case %d: %d\n", cas, ans);
	}
	return 0;
}

