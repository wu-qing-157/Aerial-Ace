#include <bits/stdc++.h>
using namespace std;

const int maxn = 4e5 + 10;
const int inf = 1e9;

vector<int>T1[maxn], T2[maxn];

int Ra[maxn];
int dfn[maxn], L[maxn], M[maxn], R[maxn], dfc, root[maxn];
bool fa1[maxn];

int n, m, q, t = 0;

struct Node {
	int max_ang;
	int add_tag;
} S[maxn * 4]; 

#define ls (p << 1)
#define rs (p << 1 | 1)

void pushup(int p) {
	S[p].max_ang = max(S[ls].max_ang, S[rs].max_ang);
}
void pushdown(int p) {
	S[ls].max_ang += S[p].add_tag;
	S[ls].add_tag += S[p].add_tag;
	
	S[rs].max_ang += S[p].add_tag;
	S[rs].add_tag += S[p].add_tag;
	
	S[p].add_tag = 0;
}

void add(int p, int l, int r, int _L, int _R, int v) {
	if (_L == l && r == _R) {
		S[p].max_ang += v;
		S[p].add_tag += v;
	} else {
		pushdown(p);
		int mid = (l + r) >> 1;
		if (_R <= mid) add(ls, l, mid, _L, _R, v);
		else if (_L > mid) add(rs, mid + 1, r, _L, _R, v);
		else 
			add(ls, l, mid, _L, mid, v),
			add(rs, mid + 1, r, mid + 1, _R, v);
		pushup(p);
	}
	
}

int ask(int p, int l, int r, int _L, int _R) {
	if (l == _L && r == _R) return S[p].max_ang;
	else {
		pushdown(p);
		int mid = (l + r) >> 1;
		if (_R <= mid) return ask(ls, l, mid, _L, _R);
		else if (_L > mid) return ask(rs, mid + 1, r, _L, _R);
		else return max(
			ask(ls, l, mid, _L, mid),
			ask(rs, mid + 1, r, mid + 1, _R)
		);
	}
}


void dfs(int u, int w) {
	//cout << u << ' ' << w << endl;
	dfn[++dfc] = u; 
	L[u] = dfc;
	add(1, 1, n, L[u], L[u], w);
	
	for (auto v : T1[u]) 
		if (!L[v]) {
			fa1[v] = true;
			root[v] = root[u];
			dfs(v, w + Ra[u] - Ra[v]);
		}
	M[u] = dfc;
	
	for (auto v : T2[u]) 
		if (!L[v]) {
			root[v] = root[u];
			dfs(v, w);
		}
	R[u] = dfc;
}

int log_2(int x) {
	return (int)round(log2(x));
}

void work() {
	for (int i = 1; i <= n; i++) T1[i].clear(), T2[i].clear();
	for (int i = 1; i <= n * 4; i++) S[i].max_ang = S[i].add_tag = 0;
	memset(dfn, 0, sizeof(dfn[0]) * (n + 1));
	dfc = 0;
	memset(L, 0, sizeof(L[0]) * (n + 1));
	memset(M, 0, sizeof(M[0]) * (n + 1));
	memset(R, 0, sizeof(R[0]) * (n + 1));
	memset(fa1, 0, sizeof(fa1[0]) * (n + 1));
	memset(root, 0, sizeof(root[0]) * (n + 1));
	
	
	for (int i = 1; i <= n; i++) scanf("%d", &Ra[i]), Ra[i] = log_2(Ra[i]);
	
	for (int i = 1; i <= m; i++) {
		int a, x, y;
		scanf("%d%d%d", &a, &x, &y);
		if (a == 1) 
			T1[x].push_back(y), T1[y].push_back(x);
		else 
			T2[x].push_back(y), T2[y].push_back(x);
	}
	for (int i = 1; i <= n; i++) 
		if (!L[i]) 
			root[i] = i, dfs(i, 0);
			
	while (q--) {
		int a, x, y;
		scanf("%d%d%d", &a, &x, &y);
		if (a == 1) {
			int _R = log_2(y);
			//cout << "GG" << endl;
			if (fa1[x]) {
				add(1, 1, n, L[x], R[x], Ra[x] - _R);
				if (L[x] < M[x])
					add(1, 1, n, L[x] + 1, M[x], _R - Ra[x]);
			}
			else {
				//cout << "gg2" << endl;
				if (L[x] < M[x]) {
				//	cout << " ##" << L[x] + 1 << ' ' << R[x] << _R - Ra[x] << endl;
					add(1, 1, n, L[x] + 1, M[x], _R - Ra[x]);
				}
			}	
			Ra[x] = _R;
		}
		else {
			int w1 = ask(1, 1, n, L[x], L[x]);
			int w2 = ask(1, 1, n, L[root[x]], R[root[x]]);
		//	cout << root[x] << ' ' << L[root[x]] << ' ' << R[root[x]] << endl;
		//	cout << w1 << ' ' << w2 << endl;
			printf("%.3f\n", log(y) + (w2 - w1) * log(2));
		}
		//for (int i = 1; i <= n; i++)
		//	printf("v%d = %d\n", i, ask(1, 1, n, L[i], L[i]));
		//cout << "=-----------" << endl;
	}
}

int main() {

	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		printf("Case #%d:\n", ++t);
		work();
	}
	return 0;	
}
/*
4 3 4
1 4 16 2
1 2 4
1 2 3
2 1 4
1 1 16
1 2 4
2 4 4
*/
