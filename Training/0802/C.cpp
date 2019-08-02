#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 10;

int A[maxn];

int pos[maxn];

int L[maxn], R[maxn];

int tmp1[100], tmp2[100];

bool ok[maxn];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n, k;
		scanf("%d%d", &n, &k);
		memset(L, 0, sizeof L);
		memset(R, 0, sizeof R);
		memset(pos, 0, sizeof pos);
		for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
		for (int i = 1; i <= n; i++) pos[A[i]] = i;
		
		R[0] = n + 1;
		L[n + 1] = 0;
		
		memset(ok, 0, sizeof ok);
		ok[0] = ok[n + 1] = true;
		
		long long ans = 0;
		
		for (int i = n; i >= 1; i--) {
			int p = pos[i];
			ok[p] = true;
			int len = 1;
			while (!ok[p - len] && !ok[p + len]) len++;
			if (ok[p - len]) {
				L[p] = p - len;
				R[p] = R[L[p]];

			} else {
				R[p] = p + len;
				L[p] = L[R[p]];	
			}
			R[L[p]] = p;
			L[R[p]] = p;
			
			tmp1[0] = tmp2[0] = 0;
			tmp1[++tmp1[0]] = p;
			int now = p;
			for (int j = 0; j < k; j++) {
				now = L[now];
				tmp1[++tmp1[0]] = now;
				if (now <= 0 || now >= n + 1) break;
			}
			now = p;
			tmp2[++tmp2[0]] = p;
			for (int j = 0; j < k; j++) {
				now = R[now];
				tmp2[++tmp2[0]] = now;
				if (now <= 0 || now >= n + 1) break;
			}
			
			//for (int j = 1; j <= tmp1[0]; j++) printf("%d ", tmp1[j]); puts("");
			//for (int j = 1; j <= tmp2[0]; j++) printf("%d ", tmp2[j]); puts("");
				
			for (int l = 1; l <= k; l++) {
				int r = k - l + 1;
				if (l >= tmp1[0] || r >= tmp2[0]) continue;
				int L = (tmp1[l] - tmp1[l + 1]);
				int R = (tmp2[r + 1] - tmp2[r]);
				//cout << "L = " << L << ' ' << "R = " << R << endl;
				ans += 1ll * L * R * i;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
