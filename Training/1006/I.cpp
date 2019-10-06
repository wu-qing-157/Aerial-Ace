#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
const int mod = 998244353;

int a[maxn], f[maxn], g[maxn];

int A1[maxn], F1[maxn], G1[maxn];
int A2[maxn], F2[maxn], G2[maxn];

int A[maxn], G[maxn], F[maxn];

namespace BIT {
	int bit[maxn];
	void clear() {
		memset(bit, 0, sizeof (bit));
	}
	int ask(int v) {
		int ans = 0;
		for (int i = v; i; i -= i & -i)	 
			ans = max(ans, bit[i]);
		return ans;
	}	
	void upd(int v, int vf) {
		for (int i = v; i < maxn; i += i & -i)
			bit[i] = max(bit[i], vf);
	}
}

struct Node {
	int lson, rson, sum;
} mem[maxn * 100];
int root[maxn], NodeCnt = 0;

void insert(int &cur, int l, int r, int pos, int val) {
	if (!cur) cur = ++NodeCnt;
	if (l == r) {
		cur[mem].sum = val;
	} else {
		int mid = (l + r) >> 1;
		if (pos <= mid) insert(cur[mem].lson, l, mid, pos, val);
		else insert(cur[mem].rson, mid + 1, r, pos, val);
		cur[mem].sum = (cur[mem].lson[mem].sum + cur[mem].rson[mem].sum) % mod;
	}
}

int ask(int cur, int l, int r, int pos) {
	if (!cur) return 0;
	if (r <= pos) return cur[mem].sum;
	if (l == r)	{
		return cur[mem].sum;
	} else {
		int mid = (l + r) >> 1;
		if (pos <= mid) return ask(cur[mem].lson, l, mid, pos);
		else return 
			(ask(cur[mem].lson, l, mid, pos) + ask(cur[mem].rson, mid + 1, r, pos)) % mod;
	}	
}

void work(int n) {
	NodeCnt = 0;
	memset(mem, 0, sizeof mem);
	memset(root, 0, sizeof root);
	BIT::clear();
	insert(root[0], 1, n, 0, 1);
	for (int i = 1; i <= n; i++) {
		f[i] = BIT::ask(a[i]) + 1;
		BIT::upd(a[i], f[i]);
		g[i] = ask(root[f[i] - 1], 1, n, a[i]);
		insert(root[f[i]], 1, n, a[i], g[i]);
	}	
}

int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	
	work(n);
	
	//for (int i = 1; i <= n; i++) 
	//	printf("a[%d] = %d, f[%d] = %d, g[%d] = %d\n", i, a[i], i, f[i], i, g[i]);
	
	for (int i = 1; i <= n; i++) 
		A[i] = A1[i] = a[i], F1[i] = f[i], G1[i] = g[i];
	
	reverse(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) a[i] = n + 1 - a[i];
	//for (int i = 1; i <= n; i++)
	//	printf("%d ", a[i]);
	work(n);

	for (int i = 1; i <= n; i++ )
		A2[i] = a[n - i + 1], F2[i] = f[n - i + 1], G2[i] = g[n - i + 1];
	
	//for (int i = 1; i <= n; i++) 
	//	printf("a[%d] = %d, f[%d] = %d, g[%d] = %d\n", i, a[n - i + 1], i, f[n - i + 1], i, g[n - i + 1]);
	
	for (int i = 1; i <= n; i++)
		F[i] = F1[i] + F2[i] - 1, G[i] = 1ll * G1[i] * G2[i] % mod;
	
	//for (int i = 1; i <= n; i++) 
	//	printf("a[%d] = %d, f[%d] = %d, g[%d] = %d\n", i, A[i], i, F[i], i, G[i]);
		
	
	
	return 0;
}
