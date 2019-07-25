#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 20;

bool lead[26];

char s[maxn];

int cnt[26][maxn];

int p[26];

const int P = 1e9 + 7;

int mx = 0;

bool cmp(int x, int y) {
	for (int i = mx; i >= 0; i--) 
		if (cnt[x][i] != cnt[y][i])
			return cnt[x][i] < cnt[y][i];
	return false;
}

int calc(int x, int y) {
	//cout << char(x + 'a') << ' ' << y << endl;
	int ans = 0;
	for (int i = mx; i >= 1; i--) 
		ans = (ans * 26ll + y * cnt[x][i]) % P;
	return ans;
}

void work(int n) {
	memset(lead, 0, sizeof lead);
	mx = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%s", s);
		int m = strlen(s);
		mx = max(mx, m);
		if (m != 1)
			lead[s[0] - 'a'] = true;
		for (int i = 0; i < m; i++)
			cnt[s[i] - 'a'][m - i]++; 
	}
	
	mx += 10;
	
	for (int j = 0; j < 26; j++)
		for (int i = 0; i < mx; i++) 
			cnt[j][i + 1] += cnt[j][i] / 26, cnt[j][i] %= 26;
	
	for (int i = 0; i < 26; i++) p[i] = i;
	
	sort(p, p + 26, cmp);
	
	int j = -1;
	for (int i = 0; i < 26; i++)
		if (!lead[p[i]]) {
			j = p[i];
			break;
		}
	
	int ans = 0;
	for (int i = 25, k = 25; i >= 0; i--) 
		if (j != p[i]) 
			ans = (ans + calc(p[i], k)) % P, k--;
	
	printf("%d\n", ans);
	
	for (int j = 0; j < 26; j++)
		memset(cnt[j], 0, sizeof(int) * (mx + 1));
	
}

int main() {
	int t = 0, n;
	while (scanf("%d", &n) != EOF) {
		printf("Case #%d: ", ++t);
		work(n);
	}
	return 0;	
}
