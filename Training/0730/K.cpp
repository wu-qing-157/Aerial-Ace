#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e7 + 10;

short f[maxn];

int main() {
	f[1] = 1; f[2] = 2; f[3] = 2;
	
	for (int i = 3, j = 1, k = 4; k < maxn; i++) {
		if (f[i] == 2) {
			f[k] = j;
			k++;
			f[k] = j;
			k++;
			j = 3 - j;	
		}
		else {
			f[k] = j;
			k++;
			j = 3 - j;
		}
	}
	
	int T;
	for (scanf("%d", &T); T--; ) {
		int x; scanf("%d", &x);
		printf("%d\n", f[x]);
	}
		
	
	return 0;
}
