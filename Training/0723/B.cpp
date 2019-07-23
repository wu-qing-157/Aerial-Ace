#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

int f[maxn], g[maxn], a[maxn];

struct Node {
	int son[2];
	int mx_id;
} T[maxn * 120];

int root = 1, cnt = 2;

void insert(int &p, int l, int r, int x, int v) {
	if (!p) p = cnt++;
	if (f[T[p].mx_id] < f[v]) {
		T[p].mx_id = v;
	}
	if (l == r) {
		return;	
	} else {
		int mid = (l + r) >> 1;
		if (x <= mid) insert(T[p].son[0], l, mid, x, v);
		else insert(T[p].son[1], mid + 1, r, x, v);
	}
}

int ask(int p, int l, int r, int L, int R) {
	if (!p) return 0;
	if (l == L && R == r) return T[p].mx_id;
	else {
		int mid = (l + r) >> 1;
		if (R <= mid) return ask(T[p].son[0], l, mid, L, R);
		else if (L > mid) return ask(T[p].son[1], mid + 1, r, L, R);
		else {
			int a1 = ask(T[p].son[0], l, mid, L, mid);
			int a2 = ask(T[p].son[1], mid + 1, r, mid + 1, R);
			return f[a1] > f[a2] ? a1 : a2;
		}
	}
}

stack<int>ans;

int main() {
	cout << sizeof(T) / 1024 / 1024 << endl;
	//freopen("financial.in", "r", stdin);
	//freopen("financial.out", "w", stdout);
	int n, k; scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);
	
	for (int i = 1; i <= n; i++) {
		int a1 = 0, a2 = 0;
		if (a[i] - k >= 1)
			a1 = ask(root, 1, 1e9, 1, a[i] - k);
		if (a[i] + k <= 1e9)
			a2 = ask(root, 1, 1e9, a[i] + k, 1e9);
		
		if (f[a1] > f[a2]) 
			f[i] = f[a1] + 1, g[i] = a1;
		else 
			f[i] = f[a2] + 1, g[i] = a2;
		
		insert(root, 1, 1e9, a[i], i);
	}
	
	int mx_ans = -1, pos = 0;
	
	for (int i = 1; i <= n; i++) 
		if (f[i] > mx_ans)
			mx_ans = f[i], pos = i;
	
	while (pos) {
		ans.push(a[pos]);
		pos = g[pos];
	}
	
	printf("%d\n", int(ans.size()));
	while (ans.size())
		printf("%d ", ans.top()), ans.pop();
		
}
/*
6
15
1014 1024 1034 1045 1030 998
*/
