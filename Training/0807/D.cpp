#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

int cnt[maxn];

set<pair<pair<int, int>, int> >seg;

void split(int p) {
	auto iter = seg.lower_bound(make_pair(make_pair(p, 1e9), 0));
	--iter;
	int l = iter->first.first;
	int r = iter->first.second;
	int c = iter->second;
	if (p == l) return;
	seg.erase(iter);
	seg.insert(make_pair(make_pair(l, p - 1), c));
	seg.insert(make_pair(make_pair(p, r), c));
}

int main() {
	int L, C, N; scanf("%d%d%d", &L, &C, &N);
	cnt[1] = L;
	
	seg.insert(make_pair(make_pair(0, L - 1), 1));
	
	while (N--) {
		int P, X, A, B;
		scanf("%d%d%d%d", &P, &X, &A, &B);
		int S = cnt[P];
		int M1 = (A + 1ll * S * S) % L;
		int M2 = (A + 1ll * (S + B) * (S + B)) % L;
		if (M1 > M2) swap(M1, M2);
		if (M1 != 0)
			split(M1);
		if (M2 != L - 1)
			split(M2 + 1);
		auto p1 = seg.lower_bound(make_pair(make_pair(M1, 0), 0));
		auto p2 = seg.lower_bound(make_pair(make_pair(M2 + 1, 0), 0));		
		
		stack<pair<pair<int, int>, int> >stk;
		while (p1 != p2) {
			stk.push(*p1); 
			cnt[p1->second] -= p1->first.second - p1->first.first + 1;
			p1++;
		}
		
		while (stk.size()) seg.erase(stk.top()), stk.pop();
		
		seg.insert(make_pair(make_pair(M1, M2), X));
		cnt[X] += M2 - M1 + 1;
		//for (auto e : seg) 
		//	printf("[(%d, %d) %d ]", e.first.first, e.first.second, e.second);
		//puts("");
	}
	int ans = 0;
	for (int i = 1; i <= C; i++)
		ans = max(ans, cnt[i]);
	printf("%d\n", ans);
	return 0;
}
/*
7 10 8
10 6 5 6
5 1 7 5
9 9 10 1
3 2 6 7
8 3 4 8
3 7 7 4
9 3 9 7
1 1 8 1000
*/
