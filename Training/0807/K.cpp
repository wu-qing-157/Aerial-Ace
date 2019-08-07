#include <bits/stdc++.h>
using namespace std;
char s[100000];
int x[2];
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= m; j++) {
			if (s[j] == 'o') {
				x[(i + j) & 1]++;
			}
		}
	}
	if (n * m % 2) {
		if (x[1] + 2 == x[0]) {
			printf("Y\n");
		} else {
			printf("N\n");
		}
	} else {
		if (x[1] == x[0]) {
			printf("Y\n");
		} else {
			printf("N\n");
		}
	}
	return 0;
}
