#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e4 + 10;

struct Node {
	int min, tag;
};

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
		T[p].sum = T[p].tag = 0;
		if (l != r) {
			int mid = l + r >> 1;
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
			int mid = l + r >> 1;
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
			pushdwon(p);
			int mid = l + r >> 1;
			if (R <= mid) return ask(ls, l, mid, L, R);
			else if (L > mid) return ask(rs, mid + 1, r, L, R);
			else return min(
				ask(ls, l, mid, L, mid, val),
				ask(rs, mid + 1, r, mid + 1, R, val)
			);
		}
	}
} seg[110];

int f[maxn][110];
int D[maxn], C[maxn], R[maxn], P[maxn];
vector<pair<int, int> >seg[maxn];

void work(int n, int m) {
	for (int i = 2; i <= n; i++) scanf("%d", &D[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &C[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &R[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &P[i]);
	
	for (int i = 1; i <= n; i++) {
		int l = D[i] - R[i], r = D[i] + R[i];
		l = lower_bound(D + 1, D + 1 + n, l) - D - 1;
		r = lower_bound(D + 1, D + 1 + n, r) - D - 1;
		seg[r].push_back(make_pair(l, i));
	}
	
}

int main() {
	int n, m;
	while (true) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0)
			break;
		work(n, m);
	}
	return 0;
}

