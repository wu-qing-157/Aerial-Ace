#include <iostream>
#include <bits/stdc++.h>

const int maxn = 2e3 + 10;
std::pair<int, int>seg1[maxn], seg2[maxn];

int f[maxn][maxn];

int q[maxn];

void work() {
	int n, m, k; scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++) 
		scanf("%d%d", &seg1[i].first, &seg1[i].second);
	sort(seg1 + 1, seg1 + 1 + m);
	int t = 0, mx = 0;
	for (int i = 1, j; i <= m; i = j) {
		j = i + 1;
		while (j <= m && seg1[i].first == seg1[j].first) j++;
		i = j - 1;
		if (seg1[i].second > mx) 
			mx = seg1[i].second, seg2[++t] = seg1[i];
	}
	k = std::min(k, t);
	for (int i = 1; i <= t; i++) f[i][1] = seg2[i].second - seg2[i].first + 1;
	for (int j = 2; j <= k; j++) {
		int head = 1, tail = 1; q[1] = 1; f[1][j] = f[1][j - 1];
		for (int i = 2, p = 0, now = 0; i <= t; i++) {
			while (p + 1 < i && seg2[p + 1].second < seg2[i].first) {
				now = std::max(now, f[p + 1][j - 1]);
				if (head <= tail && q[head] <= p + 1) head++;
				p = p + 1;
			}
			f[i][j] = now + seg2[i].second - seg2[i].first + 1;
			if (head <= tail) 
				f[i][j] = std::max(f[i][j], f[q[head]][j - 1] + seg2[i].second - seg2[q[head]].second);
			while (head <= tail && f[i][j - 1] - seg2[i].second >= f[q[tail]][j - 1] - seg2[q[tail]].second) tail--;
			q[++tail] = i;
		}
		for (int i = 1; i <= t; i++) f[i][j] = std::max(f[i][j], f[i][j - 1]);
	}
	int ans = 0;
	for (int i = 1; i <= t; i++)
		ans = std::max(ans, f[i][k]);
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) 
		printf("Case #%d: ", t), work();
	return 0;
}
