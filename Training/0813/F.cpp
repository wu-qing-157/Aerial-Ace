#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 1e6 + 10;

char s[maxn];
int extend[maxn];

#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
/*
void getnext(char *s, int len) {
	fail[1] = 0;
	int p = 0;
	memset(next, 0, (len + 2) << 2);
	for (int i = 2; i <= len; ++i) {
		while (p && s[p + 1] != s[i]) p = fail[p];
		s[p + 1] == s[i] ? ++p : 0;
		fail[i] = p;
		p ? cmax(next[i - p + 1], p) : 0;
	}
}

void getextend(char *s, int lens, char *t, int lent) {
	getnext(t, lent);
	int a = 1, p = 0;
	
	for (int i = 1; i <= lens; ++i) {
		if (i + next[i - a + 1] - 1 >= p) {
			cmax(p, i - 1);
			while (p < lens && p - i + 1 < lent && s[p + 1] == t[p - i + 2]) ++p;
			a = i;
			extend[i] = p - i + 1;
		}
		else extend[i] = next[i - a + 1];
	}
}*/

void exkmp(char *s, int *a, int n) {
	a[0] = n; int p = 0, r = 0;
	for (int i = 1; i < n; ++i) {
		a[i] = (r > i) ? std::min(r - i, a[i - p]) : 0;
		while (i + a[i] < n && s[i + a[i]] == s[a[i]]) ++ a[i];
		if (r < i + a[i]) r = i + a[i], p = i;
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		int n = strlen(s);
		//getextend(s, n, s, n);
		memset(extend, 0, (n + 1) << 2);
		exkmp(s, extend, n);
		long long ans = 0;
		for (int i = 1; i < n; i++) 
			ans += ((i + extend[i] == n) ? extend[i] : extend[i] + 1);
			//ans += extend[i] + 1;
		printf("%lld\n", ans);
	}
	return 0;
}
/*
3
_Happy_New_Year_
*/
