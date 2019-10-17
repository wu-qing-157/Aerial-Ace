#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

int W[maxn], D[maxn];

long long a[maxn * 10], b[maxn * 10];
priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > >pq;

void work() {
	int L, N, M; scanf("%d%d%d", &L, &N, &M);
	for (int i = 1; i <= N; i++) scanf("%d", &W[i]);
	for (int i = 1; i <= M; i++) scanf("%d", &D[i]);
	
	while (pq.size()) pq.pop();
	for (int i = 1; i <= N; i++) pq.push(make_pair(W[i], W[i]));
	for (int i = 1; i <= L; i++) {
		long long t1 = pq.top().first; int t2 = pq.top().second; pq.pop();
		a[i] = t1; pq.push(make_pair(t1 + t2, t2));
	}
	
	while (pq.size()) pq.pop();
	for (int i = 1; i <= M; i++) pq.push(make_pair(D[i], D[i])); 
	for (int i = 1; i <= L; i++) {
		long long t1 = pq.top().first; int t2 = pq.top().second; pq.pop();
		b[i] = t1; pq.push(make_pair(t1 + t2, t2));
	}
	
	//for (int i = 1; i <= L; i++) printf("%lld ", a[i]); puts("");
	//for (int i = 1; i <= L; i++) printf("%lld ", b[i]); puts("");
	
	reverse(b + 1, b + 1 + L);
	long long ans = 0;
	for (int i = 1; i <= L; i++) ans = std::max(ans, a[i] + b[i]);
	printf("%lld\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++)
		printf("Case #%d: ", t), work();
	return 0;
}
