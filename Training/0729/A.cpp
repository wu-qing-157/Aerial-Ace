#include <bits/stdc++.h>
using namespace std;

int n, p, q, m;
unsigned int SA, SB, SC;
unsigned int rng61() {
	SA ^= SA << 16;
	SA ^= SA >> 5;
	SA ^= SA << 1;
	unsigned int t = SA;
	SA = SB;
	SB = SC;
	SC ^= t ^ SA;
	return SC;
}

typedef long long ll;

ll ans;

int id;

const int maxn = 5e6 + 10;

int stk[maxn];
int val[maxn];
int top;


void PUSH(int x) {
	//cout << "PUSH " << x << endl;
	id++;
	if (!top) {
		val[1] = x;
		stk[1] = x;
		top = 1;
	} else {
		stk[top + 1] = x;
		val[top + 1] = max(val[top], x);
		top++;
	}
	//cout << id * val[top] << endl;
	ans = ans ^ (1ll * id * val[top]);
}

void POP() {
	//cout << "POP" << endl;
	id++;
	if (top) top--;
	ans = ans ^ (1ll * id * val[top]);
}

void gen() {
	scanf("%d%d%d%d%u%u%u", &n, &p, &q, &m, &SA, &SB, &SC);
	for (int i = 1; i <= n; i++) {
		if (rng61() % (p + q) < p) 
			PUSH(rng61() % m + 1);
		else POP();
	}
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		ans = 0;
		id = 0;
		top = 0;
		gen();		
		printf("Case #%d: %lld\n", t, ans);
	}

}
/*
2
4 1 1 4 23333 66666 233333
4 2 1 4 23333 66666 233333
*/
