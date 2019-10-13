#include <bits/stdc++.h>

const int maxn = 1e3 + 10;
const int maxg = 12;

int c[maxn], cc[maxn];
bool vis[maxn];
std::vector<int> p[maxn];
std::set<int> seg;
std::multiset<int> nowans;

struct ST {
	int data[maxg][maxn], log_2[maxn];
	void init(int *a, int n) {
		for (int i = 1; i <= n; i++) data[0][i] = a[i];
		log_2[0] = -1;
		for (int i = 1; i <= n; i++) log_2[i] = log_2[i >> 1] + 1;
		for (int j = 1; j < maxg; j++)
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
				data[j][i] = std::max(data[j - 1][i], data[j - 1][i + (1 << (j - 1))]);
	}
	int ask(int l, int r) {
		if (r < l) return 0;
		int k = log_2[r - l + 1];
		return std::max(data[k][l], data[k][r - (1 << k) + 1]);
	}
} st;


int maxr[maxn], maxlen[maxn];

int calc_case1(int n, int m) {
	int ans = 0;
	for (int l = 1; l <= n; l++) {
		for (int i = 1; i <= m; i++) vis[i] = false;
		for (int r = l; r <= n; r++) {
			if (vis[c[r]]) break;
			else {
				vis[c[r]] = true;
				maxr[l] = r;
				ans = std::max(ans, r - l + 1);
			}
		}
		maxlen[l] = maxr[l] - l + 1;
	} 
	return ans;
}

int calc_seg(int l, int r) {
	int x = std::lower_bound(maxr + l + 1, maxr + r, r) - maxr;
	return std::max(st.ask(l + 1, x - 1), r - x);
}

int calc_case2(int n, int m) {
	st.init(maxlen, n);
	int ans = 0;
	for (int l = 3; l <= n; l++) {
		for (int i = 1; i <= m; i++) vis[i] = false;
		seg.clear();
		nowans.clear();
		seg.insert(0);
		seg.insert(l);
		nowans.insert(calc_seg(0, l));
		//std::cout << "ins " << 0 << ' ' << l << ' ' << calc_seg(0, l) << std::endl;
		for (int r = l; r <= n; r++) {
			if (vis[c[r]]) break;
			else {
				vis[c[r]] = true;
				for (int pos : p[c[r]]) {
					if (pos >= l) break;
					auto p = seg.lower_bound(pos);
					int R = *p;
					int L = *(--p);
					int segans = calc_seg(L, R);
					//std::cout << "del " << L << ' ' << R << ' ' << segans << std::endl;
					nowans.erase(nowans.find(segans));
					if (R - pos > 1) {
						nowans.insert(calc_seg(pos, R));
						//std::cout << "ins " << pos << ' ' << R << ' ' << calc_seg(pos, R) << std::endl;
					}
					if (pos - L > 1) {
						nowans.insert(calc_seg(L, pos));
						//std::cout << "ins " << L << ' ' << pos << ' ' << calc_seg(L, pos) << std::endl;
					}
					seg.insert(pos);
				}
			}
			if (nowans.size()) ans = std::max(ans, *nowans.rbegin() + r - l + 1);
		}
		
		//std::cout << "----------------------------------------" << std::endl;
	}
	return ans;
}

void work() {
	int n; scanf("%d", &n); 
	for (int i = 0; i < maxn; i++) p[i].clear();
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]), cc[i] = c[i];
	//std::cout << __LINE__ << " GG" << std::endl;
	std::sort(cc + 1, cc + 1 + n);
	int m = std::unique(cc + 1, cc + 1 + n) - cc - 1;
	//std::cout << __LINE__ << " GG" << std::endl;
	for (int i = 1; i <= n; i++) c[i] = std::lower_bound(cc + 1, cc + 1 + m, c[i]) - cc;
	for (int i = 1; i <= n; i++) p[c[i]].push_back(i);
	
	//std::cout << __LINE__ << " GG" << std::endl;
	
	int ans = 0;
	ans = std::max(ans, calc_case1(n, m));
	ans = std::max(ans, calc_case2(n, m));
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++)
		printf("Case #%d: ", t), work();
	return 0;
}
/*
1
8
3 1 2 1 6 1 2 5
*/
