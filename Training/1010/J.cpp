#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e7 + 10;
const long long inf = ~0ULL >> 1;
long long solve(char *s, int n, int a, int b) {
	static int fail[maxn];
	fail[1] = 0;
	for (int i = 2; i <= n; i++) {
		int j = fail[i - 1];
		while (j && s[i] != s[j + 1]) j = fail[j];
		if (s[i] != s[j + 1]) j = 0; else j = j + 1;
		fail[i] = j;
	}
	long long ans = -inf;
	for (int i = 1; i <= n; i++) {
		if (s[i] == '.') break;
		ans = max(ans, 1ll * i * a - 1ll * b * (i - fail[i]));
	}
	return ans;
}

char s[maxn], t[maxn];

int main() {
	int a, b; while (scanf("%d%d", &a, &b) != EOF) {
		scanf("%s", s);
		int n = strlen(s);
		for (int i = 0; i < n; i++) t[n - i] = s[i];
		printf("%lld\n", solve(t, n, a, b));
	}
}
