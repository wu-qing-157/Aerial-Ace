#include <bits/stdc++.h>
using namespace std;

long long K;
char S[100], T[100];

int main() {
	cin >> K >> S;
	int n = strlen(S);
	int m = 0;
	for (long long k = K; k; k >>= 1)
		T[m++] = '0' + (k & 1);
	reverse(T, T + m);
	if (m > n) printf("0\n");
	else {
		//puts(S);
		//puts(T);
		bool ok = true;
		for (int i = 0, j = 0; i < m; i++, j++) {
			while (j < n && T[i] < S[j]) j++;
			if (j >= n) ok = false;
			if (S[j] < T[i] && m - i <= n - j) break;
		}
		if (ok) printf("%d\n", n - m);
		else printf("%d\n", n - m + 1);
	}
	return 0;
}
