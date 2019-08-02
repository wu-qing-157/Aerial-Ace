#include <bits/stdc++.h>
using namespace std;

const int maxn = 19;
const int MOD = 998244353;

int A[1 << maxn], B[1 << maxn], C[1 << maxn];

int a[20][1 << maxn];
int b[20][1 << maxn];
int c[20][1 << maxn];
int cnt[1 << maxn], U;

void fwt(int n, int *x, bool inv = false) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= U; j++)
			if ((j >> i) & 1) {
				int p = x[j ^ (1 << i)], q = x[j];
				if (!inv) {
					x[j ^ (1 << i)] = p;
					x[j] = p + q;
					if (x[j] >= MOD)
						x[j] -= MOD;
				} else {
					x[j ^ (1 << i)] = p;
					x[j] = q - p;
					if (x[j] < 0)
						x[j] += MOD;
				}
			}
}

int main() {
	int n; scanf("%d", &n);
	U = (1 << n) - 1;
	for (int i = 0; i <= U; i++) scanf("%d", &A[i]);
	for (int i = 0; i <= U; i++) scanf("%d", &B[i]);
	for (int i = 0; i <= U; i++) 
		if (i < (U ^ i)) 
			//swap(A[i], A[U ^ i]),
			swap(B[i], B[U ^ i]);
	
	cnt[0] = 0;
	for (int j = 1; j <= U; j++) 
		cnt[j] = cnt[j >> 1] + (j & 1);
	
	for (int i = 0; i <= U; i++) 
		a[cnt[i]][i] = 1ll * A[i] * (1ll << cnt[i]) % MOD,
		b[cnt[i]][i] = B[i];
	
	for (int i = 0; i <= n; i++)
		fwt(n, a[i], false), fwt(n, b[i], false);

	for (int x = 0; x <= n; x++)
		for (int y = 0; y <= n; y++) {
			if (x + y > n) continue;
			for (int i = 0; i <= U; i++)
				(c[x + y][i] += 1ll * a[x][i] * b[y][i] % MOD) %= MOD;
		}
			
	for (int i = 0; i <= n; i++)
		fwt(n, c[i], true);
	
	for (int i = 0; i <= U; i++)
		C[i] = c[cnt[i]][i];
	
	for (int i = 0; i <= U; i++)
		if (i < (U ^ i)) 
			swap(C[i], C[U ^ i]);
		
	int ans = 0;
	for (int i = 0, p1526 = 1; i <= U; i++)	
		ans = (ans + 1ll * C[i] * p1526 % MOD) % MOD, p1526 = (1ll * p1526 * 1526) % MOD;
	
	printf("%d\n", ans);
	/*
	for (int i = 0; i <= U; i++)
		printf("%d ", A[i]);
	puts("");
	for (int i = 0; i <= U; i++)
		printf("%d ", B[i]);
	puts("");
	for (int i = 0; i <= U; i++)
		printf("%d ", C[i]);
	puts("");	
	*/
}

/*
2
1 2 3 4        
5 6 7 8
11891226
4 3 2 1 
8 7 6 5 
20 24 42 32
*/
