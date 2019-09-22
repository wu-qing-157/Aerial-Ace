#include <bits/stdc++.h>
using namespace std;

typedef __int128 ll;

void read(ll &x) {
	char c = getchar(); x = 0;
	while (!isdigit(c)) c = getchar();
	while ( isdigit(c)) 
		x = x * 10 + c - '0', c = getchar();
}

ll tmp[30][30], fac[30];
ll S[30][30], G[30][30];
ll C(int n, int m) {
	return fac[n] / fac[m] / fac[n - m];
}
void init() {
	fac[0] = 1;
	for (int i = 1; i <= 26; i++)
		fac[i] = fac[i - 1] * i;
	
	for (int k1 = 0; k1 <= 26; k1++)
		for (int k2 = 0; k2 <= 26; k2++) {
			tmp[k1][k2] = 0;
			for (int k3 = 0; k3 <= min(k1, k2); k3++)
				tmp[k1][k2] += C(k1, k3) * C(k2, k3) * fac[k3];
		}
	S[0][0] = 1;
	for (int i = 1; i <= 26; i++) {
		S[i][0] = 0;
		for (int j = 1; j <= i; j++)
			S[i][j] = S[i - 1][j] * j + S[i - 1][j - 1];
	}
	for (int i = 0; i <= 26; i++)
		for (int j = 1; j <= 26; j++) 
			for (int k = 1; k <= j; k++) 
				G[i][j] += tmp[i][k] * S[j][k];
	for (int i = 0; i <= 5; i++) {
		for (int j = 0; j <= 5; j++)
			cout << '(' << i << ' ' << j << ' ' << int(G[i][j]) << ')';
		cout << endl;
	}
			
		
}



void work() {
	int n; scanf("%d", &n);
	ll k; read(k);
	int all = 0;
	for (int i = 1; i <= n; i++) {
		bool out = false;
		for (int now = 1; now <= all && !out; now++) {
			if (k > tmp[all][n - i]) 
				k -= tmp[all][n - i];
			else {
				putchar(now + 'A' - 1);
				out = true;
			}
		}
		if (!out) {
			all++;
			putchar(all + 'A' - 1);
		}
	}
	puts("");
}

int main() {
	init();
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		printf("Case #%d: ", t);
		work();
	}
	return 0;
}
