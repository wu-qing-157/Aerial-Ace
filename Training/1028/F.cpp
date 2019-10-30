#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;
long long A[maxn];
int B[maxn];

struct ST_max {
	pair<int, int> maxv[20][maxn];
	int log_2[maxn];
	void init(int *a, int n) {
		for (int i = 1; i <= n; i++) maxv[0][i] = make_pair(a[i], i);
		for (int j = 1; j < 20; j++)
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
				maxv[j][i] = max(maxv[j - 1][i], maxv[j - 1][i + (1 << (j - 1))]);
		log_2[0] = -1;
		for (int i = 1; i <= n; i++) log_2[i] = log_2[i >> 1] + 1;
	}
	pair<int, int> ask(int l, int r) {
		int k = log_2[r - l + 1];
		return max(maxv[k][l], maxv[k][r - (1 << k) + 1]);
	}
} st;

struct BIT {
	long long s[maxn];
	void add(int p, long long v) {
		while (p < maxn) s[p] += v, p += p & -p;
	}
	long long ask_sum(int p, long long v = 0) {
		while (p) v += s[p], p -= p & -p;
		return v;
	}
	long long ask_pos(int p) {
		return ask_sum(p) - ask_sum(p - 1);
	}
} bit;

vector<int>ans;

int main() {
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", &A[i]), A[i] += A[i - 1];
	int num = 0;
	for (int i = 1; i <= n; i++) if (A[i] <= m) num = i;
	for (int i = 1; i <= n; i++) scanf("%d", &B[i]);
	st.init(B, n);
	for (int i = 1; i <= n; i++) bit.add(i, B[i]);
	int L = 1, R = num;
	for (int i = 1; i <= n; i++) {
		if (A[i] > m) break;
		if (bit.ask_sum(num) > m) break;
		while (L <= R && bit.ask_sum(L) < A[i]) L++;
		if (L > R) break;
		pair<int, int> val = st.ask(L, R);
		ans.push_back(bit.ask_sum(val.second));
		bit.add(val.second, val.first);
	}
	if (bit.ask_sum(num) <= m) puts("-1");
	else {
		printf("%d\n", (int)ans.size());
		for (int i = 0; i < ans.size(); i++)
			printf("%d%c", ans[i], " \n"[i == ans.size() - 1]);
	}
	
	return 0;
}
