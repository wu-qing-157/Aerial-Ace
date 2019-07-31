#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 3e5 + 10;

int n;
ll k;

int p[maxn], q[maxn], a[maxn], b[maxn];

int main() {
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &q[i]);
	
	for (int i = 1; i <= n; i++) a[p[i]] = i;
	for (int i = 1; i <= n; i++) b[q[i]] = i - 1;
	
	//for (int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
	//for (int i = 1; i <= n; i++) printf("%d ", b[i]); puts("");
		
	for (int i = 1; i <= n; i++) {
		//cout << "k = " << k << endl;
		int x = p[i];
		if (n - x <= k) 
			a[x] = -n, k -= n - x;
		else {
			for (int j = 1; j <=n && k > 0; j++) {
				if (q[j] > x) {
					k--;
					a[x] = -b[q[j]] - 1;
				}
			}
		}
		if (k == 0) break;
	}
	puts("Yes");
	for (int i = 1; i <= n; i++) printf("%d ", a[i]); 
	puts("");
	for (int i = 1; i <= n; i++) printf("%d ", b[i]); 
	puts("");
	return 0;
}
/*
5 3
3 5 1 2 4
3 1 5 4 2

*/
