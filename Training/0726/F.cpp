#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
const int64_t MOD = 998244353, G = 3;

int64_t powMod(int64_t x, int64_t y) {
	int64_t ans = 1;
	while (y) {
		if (y & 1)
			ans = ans * x % MOD;
		y >>= 1;
		x = x * x % MOD;
	}
	return ans;
}

int rev[N];
void NTT(int64_t *p, int n, int idft) {
	for (int i = 0; i < n; i++) if (i < rev[i]) 
		std::swap(p[i], p[rev[i]]);
	
	for (int j = 1; j < n; j <<= 1) {
		static int64_t wn1, w, t0, t1;
		wn1 = powMod(G, (MOD - 1) / (j << 1));
		if (idft == -1) wn1 = powMod(wn1, MOD - 2);
		for (int i = 0; i < n; i += j << 1) {
			w = 1;
			for (int k = 0; k < j; k++) {
				t0 = p[i + k];
				t1 = w * p[i + j + k] % MOD;
				p[i + k] = (t0 + t1) % MOD;
				p[i + j + k] = (t0 - t1 + MOD) % MOD;
				(w *= wn1) %= MOD;
			}
		}
	}
	if (idft == -1) {
		int nInv = powMod(n, MOD - 2);
		for (int i = 0; i < n; i++) 
			(p[i] *= nInv) %= MOD;
	}
}

int64_t *ntt_main(int64_t *a, int64_t *b, int n, int m) {
	static int64_t aa[N], bb[N]; static int nn, len;
	len = 0; for (nn = 1; nn < (n + m); nn <<= 1) len++;
	for (int i = 0; i < n; i++) aa[i] = a[i];
	for (int i = 0; i < m; i++) bb[i] = b[i];
	for (int i = n; i < nn; i++) aa[i] = 0;
	for (int i = m; i < nn; i++) bb[i] = 0;

	rev[0] = 0;
	for (int i = 1; i < nn; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
	NTT(aa, nn, 1);
	NTT(bb, nn, 1);
	for (int i = 0; i < nn; i++) (aa[i] *= bb[i]) %= MOD;
	NTT(aa, nn, -1);
	return aa;
}

char s[N], t[N];
int64_t a[N], b[N], *c;
int64_t sa[N], sb[N];

vector<int>ans;

pair<int, int>H[N];
pair<int, int>W[N];

set<pair<int, int> >st;

void work(int k) {
	scanf("%s%s", s, t);
	int n = strlen(s);
	int m = strlen(t);
	
	//reverse(t, t + m);
	
	for (int i = 0; i < n; i++) a[i] = (s[i] == 'a' ? 1 : 0);
	for (int i = 0; i < m; i++) b[i] = (t[m - i - 1] == 'a' ? 1 : 0);
	
	sa[0] = a[0] * a[0];
	sb[0] = b[0] * b[0];
	for (int i = 1; i < n; i++) sa[i] = sa[i - 1] + a[i] * a[i];
	for (int i = 1; i < m; i++) sb[i] = sb[i - 1] + b[i] * b[i];
	
	c = ntt_main(a, b, n, m);
	
	ans.clear();
	
	for (int i = 0; i + m <= n; i++) {
		int now_k = 0;
		now_k += sa[i + m - 1] - (i == 0 ? 0 : sa[i - 1]);
		now_k += sb[m - 1];
		now_k -= 2 * c[i + m - 1];
		if (now_k <= k)
			ans.push_back(i);
	}
	
	const int P1 = 1e9 + 7, P2 = 1e9 + 9;
	const int B = 59;
	H[0].first = H[0].second = s[0];
	W[0].first = W[0].second = 1;
	for (int i = 1; i < n; i++) {
		H[i].first = (1ll * H[i - 1].first * B + s[i]) % P1;
		H[i].second = (1ll * H[i - 1].second * B + s[i]) % P2;
		W[i].first = W[i - 1].first * 1ll * B % P1;
		W[i].second = W[i - 1].second * 1ll * B % P2;
	}
	
	st.clear();
	
	for (auto p : ans) {
		if (p == 0) st.insert(H[m - 1]);
		else {
			int h1 = (H[p + m - 1].first - 1ll * H[p - 1].first * W[m].first) % P1;
			int h2 = (H[p + m - 1].second - 1ll * H[p - 1].second * W[m].second) % P2;
			if (h1 < 0) h1 += P1;
			if (h2 < 0) h2 += P2;
			st.insert(make_pair(h1, h2));
		}
	}
	
	printf("%d\n", (int)st.size());
		
}

int main() {
	int k, t = 0; 
	while (true) {
		scanf("%d", &k);
		if (k == -1) break;
		printf("Case %d: ", ++t);
		work(k);
	}
	return 0;
}
/*
0
aabbab
ab
1
aabbab
ab
2
aabbab
ab
-1
*/
