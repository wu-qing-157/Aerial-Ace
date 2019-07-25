#include <bits/stdc++.h>
using namespace std;

struct hash_pair {
	size_t operator () (const std::pair<int, int> &p) const {
		return (p.first << 20) ^ (p.first >> 10) ^ (p.second);
	}
};

unordered_map<pair<int, int>, int, hash_pair>mp;

const int maxn = 1e6 + 10;
const int P = 1e9 + 7;

int fac[maxn], ifac[maxn];
int add(int x) {
	return x >= P ? x - P : x;
}
int sub(int x) {
	return x < 0 ? x + P : x;
}
int mul(int x, int y) {
	return 1ll * x * y % P;
}
int fpw(int x, int y) {
	int ans = 1;
	while (y) {
		if (y & 1)
			ans = 1ll * ans * x % P;
		x = 1ll * x * x % P;
		y >>= 1;
	} return ans;
}

int c(int n, int m) {
	return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P;
}

int solve(int l, int r) {
	if (!mp.count(make_pair(l, r))) return 0;
	int mid = mp[make_pair(l, r)];
	if (mid < l || mid > r) return 0;
	if (l == r) return 1;
	int ans = 1;
	if (mid != l) 
		ans = 1ll * ans * solve(l, mid - 1) % P;
	if (mid != r)
		ans = 1ll * ans * solve(mid + 1, r) % P;
	ans = 1ll * ans * c(r - l, mid - l) % P;
	return ans;
}

int L[maxn], R[maxn];

void work(int n) {
	mp.clear();
	for (int i = 1; i <= n; i++) scanf("%d", &L[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &R[i]);
	
	for (int i = 1; i <= n; i++) {
		if (mp.count(make_pair(L[i], R[i]))) {
			printf("0\n");
			return;
		}
		mp[make_pair(L[i], R[i])] = i;
	}
	
	printf("%d\n", solve(1, n));
}

void init() {
	fac[0] = 1;
	for (int i = 1; i < maxn; i++) 
		fac[i] = 1ll * fac[i - 1] * i % P;
	ifac[maxn - 1] = fpw(fac[maxn - 1], P - 2);
	for (int i = maxn - 1; i >= 1 ; i--)
		ifac[i - 1] = 1ll * ifac[i] * i % P;
}



int main() {
	int n, t = 0;
	init(); 
	while (scanf("%d", &n) != EOF) {
		printf("Case #%d: ", ++t);
		work(n);
	}
	return 0;
}
