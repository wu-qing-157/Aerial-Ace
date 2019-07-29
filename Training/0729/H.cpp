#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;

int HP[maxn], ATK[maxn], TIM[maxn], ID[maxn];

bool cmp(int i, int j) {
	return 1ll * TIM[HP[i]] * ATK[j] < 1ll * TIM[HP[j]] * ATK[i];
}

void work() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) ID[i] = i;
	for (int i = 1; i <= n; i++) scanf("%d%d", &HP[i], &ATK[i]);
	sort(ID + 1, ID + 1 + n, cmp);
	long long t = 0;
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		t += TIM[HP[ID[i]]];
		ans += t * ATK[ID[i]];
	}
	printf("%lld\n", ans);
}

int main() {
	for (int i = 1, j = 0; j < int(1e5 + 10); i++) {
		for (int k = 1; k <= i; k++) 
			TIM[j + k] = TIM[j] + 1;
		j += i;
	}
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		printf("Case #%d: ", t);
		work();
	}
	return 0;	
}
/*
2
3
1 1
2 2
3 3
3
3 1
2 2
1 3
*/
