#include <bits/stdc++.h>

const int maxn = 1000;

char s[maxn];

int cnt1[maxn], cnt2[maxn];

void work() {
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for (int i = 0; i < 26; i++) cnt1[i] = cnt2[i] = 0;
	for (int i = 1; i <= n; i++) {
		if (i & 1) cnt1[s[i] - 'a']++;
		else cnt2[s[i] - 'a']++;
	}
	int ans = n;
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++) 
			ans = std::min(ans, n - cnt1[i] - cnt2[j]);
	printf("%d\n", ans);
}

int main() {
	int T; 
	scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
