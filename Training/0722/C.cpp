#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e3 + 10;
typedef long long ll;
const ll inf = 10000000000000000ll;

long long f[maxn][maxn];

int A[maxn], B[maxn], C[maxn];
bool pre[maxn][maxn * 4], aft[maxn][maxn * 4];

int tmp[maxn * 2];

void work() {
	int n, m; scanf("%d%d", &n, &m); tmp[0] = 0;
	for (int i = 1; i <= n; i++) scanf("%d", &A[i]), tmp[++tmp[0]] = A[i];
	for (int i = 1; i <= m; i++) scanf("%d", &B[i]), tmp[++tmp[0]] = B[i];
	for (int i = 1; i <= n; i++) scanf("%d", &C[i]);
	
	sort(tmp + 1, tmp + 1 + tmp[0]);
	tmp[0] = unique(tmp + 1, tmp + 1 + tmp[0]) - tmp - 1;
	for (int i = 1; i <= n; i++) 
		A[i] = lower_bound(tmp + 1, tmp + 1 + tmp[0], A[i]) - tmp;
	for (int i = 1; i <= m; i++)
		B[i] = lower_bound(tmp + 1, tmp + 1 + tmp[0], B[i]) - tmp;
	
	for (int i = 0; i <= n; i++) 
		for (int j = 0; j <= m; j++)
			f[i][j] = inf;
			
	f[0][0] = 0;
	for (int i = 1; i <= n; i++) 
		f[i][0] = f[i - 1][0] + C[i];

	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= tmp[0]; j++)
			pre[i][j] = aft[i][j] = false;

	for (int i = 0; i <= m; i++) {
		for (int j = 1; j <= i; j++) 
			pre[i][B[j]] = true;
		for (int j = m; j > i; j--)
			aft[i][B[j]] = true;
	}
	/*
	for (int i = 1; i <= n; i++) printf("%d ", A[i]);
	puts("");
	for (int i = 0; i <= m; i++)
		for (int j = 1; j <= tmp[0]; j++)
			printf("%d %d     %d %d\n", i, j, (int) pre[i][j], (int) aft[i][j]);
	*/
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (!pre[j][A[i]] || !aft[j][A[i]]) 
				f[i][j] = min(f[i][j], f[i - 1][j] + C[i]);//, printf("trans %d %d    %d %d    %d %d\n", i, j, j, A[i], (int) pre[j][A[i]], (int) aft[j][A[i]]);
			if (A[i] == B[j]) 
				f[i][j] = min(f[i][j], f[i - 1][j - 1]);
		}
		/*
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			printf("f[%d][%d] = %lld\n",i, j, f[i][j]);
		*/
	if (f[n][m] > inf / 100) puts("No");
	else printf("%lld\n", f[n][m]);
		
}

int main() {
	freopen("transform.in", "r", stdin);
	int T; scanf("%d", &T);
	while (T--) work();
	return 0;
}
/*
10000
6 3
1 2 2 1 2 1
1 2 1
1 100 2 1 -1 50
3 1
1 1 1
1 
-100 0 1
2 1
1 1
-2
-100 1


3 2
2 2 2
2 2 
1 -100 1

*/
