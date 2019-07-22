#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

vector<pair<int, int> >G[maxn], F[maxn];

bool vis[maxn];

void work() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		G[i].push_back(make_pair((i * 2) % n, 0));
		G[i].push_back(make_pair((i * 2 + 1) % n, 1));
		F[(i * 2)].push_back(make_pair(i, 0));
		F[(i * 2 + 1)].push_back(make_pair(i, 1));
	}
	for (int i = 0; i < n; i++) vis[i] = false;
	int s0 = 0, s1 = 1;
	while (true) {
		int n00 = G[s0][0].first;
		int n01 = G[s0][1].first;
		int n10 = G[s1][0].first;
		int n11 = G[s1][1].first;
		if (vis[n00]) 
	}
}


int main() {
	int T; scanf("%d", &T);
	while (T--) work();
	return 0;
}
