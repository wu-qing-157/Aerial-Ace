#include <bits/stdc++.h>

const int maxn = 1e6 + 10;

typedef unsigned long long hash_t;
struct Hash {
	const int base = 213;
	hash_t hash[maxn], pow[maxn];
	void init(char *s) {
		pow[0] = 1;
		for (int i = 1; s[i]; i++)
			hash[i] = hash[i - 1] * base + s[i],
			pow[i] = pow[i - 1] * base;
	}
	hash_t get(int l, int r) {
		return hash[r] - hash[l - 1] * pow[r - l + 1];
	}
} hs, ht;


char s[maxn], t[maxn];
int p1[maxn], p2[maxn], n;

int p[maxn];
long long sp[maxn];

void manacher1() {
	int mx = 0, id;
	for (int i = 1; i <= n; i++) {
		if (mx >= i) p1[i] = std::min(mx - i, p1[(id << 1) - i]);
		else p1[i] = 1;
		for (; s[i + p1[i]] == s[i - p1[i]]; ++p1[i]);
		if (p1[i] + i - 1 > mx) id = i, mx = p1[i] + i - 1;
	}
}

void manacher2() {
	int mx = 0, id;
	for (int i = 1; i <= n; i++) {
		if (mx >= i) p2[i] = std::min(mx - i, p2[(id << 1) - i]);
		else p2[i] = 0;
		for (; s[i + p2[i] + 1] == s[i - p2[i]]; ++p2[i]);
		if (p2[i] + i > mx) id = i, mx = p2[i] + i;
	}
}


int main() {
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1); int m = strlen(t + 1);
	s[0] = '$'; s[n + 1] = '?';
	std::reverse(s + 1, s + 1 + n);
	manacher1();
	manacher2();
	for (int i = 1; i <= n; i++) {
		p[i]++;
		p[i + p1[i]]--;
		p[i + 1]++;
		p[i + p2[i] + 1]--;
	}
	for (int i = 1; i <= n; i++) p[i] += p[i - 1];
	hs.init(s);
	ht.init(t);
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		int L = 0, R = std::min(m, n - i + 1); 
		while (L < R) {
			int M = (L + R + 1) >> 1;
			if (hs.get(i, i + M - 1) == ht.get(1, M))
				L = M;
			else
				R = M - 1;
		}
		//printf("%d %d\n", i, L);
		ans += 1ll * p[i - 1] * L;
	}
	printf("%lld\n", ans);
}
