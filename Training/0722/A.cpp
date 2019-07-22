#include <bits/stdc++.h>
using namespace std;

vector<int>tmp;

int cnt[1 << 22];
int mod[1 << 22];

typedef long long ll;

void work() {
	int x, y, M, K; 
	cin >> x >> y >> M >> K;
	int n = (x + y) / 2;
	int m = (x + y) - n;
	
	long long ans = 0;
	
	for (int i = 0, mx = (1 << m); i < mx; i++) 
		mod[i] = (mod[i >> 1] * 2 + (i & 1)) % M;
	
	for (int pre1 = 1; pre1 <= x; pre1++) {
		tmp.clear();
		for (int i = 0, mx = (1 << n); i < mx; i++) 
			if (cnt[i] == x - pre1) 
				tmp.push_back(mod[i]);
		sort(tmp.begin(), tmp.end());
		
		for (int i = 0, mx = (1 << m); i < mx; i++) 
			if (cnt[i] == pre1 && (i >> (m - 1)) == 1) {
				int now = ((long long)(mod[i]) << n) % M;
				if (now <= K) {
					ans += (long long)(upper_bound(tmp.begin(), tmp.end(), M - 1 - now)
						- lower_bound(tmp.begin(), tmp.end(), (K - now + M) % M));
				}
				else {
					ans += (long long)(upper_bound(tmp.begin(), tmp.end(), M - 1 - now) - tmp.begin());
					ans += (long long)(tmp.end() - lower_bound(tmp.begin(), tmp.end(), (K - now + M) % M));
				}
			} 
	}
	
	printf("%lld\n", ans);
}

void init() {
	for (int i = 1; i < (1 << 22); i++) 
		cnt[i] = cnt[i >> 1] + (i & 1);
}

int main() {
	freopen("zeros.in", "r", stdin);
	init();
	int T; scanf("%d", &T);
	while (T--) work();
	return 0;
}
