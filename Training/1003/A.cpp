#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	while (n--) {
		int ans = 0;
		for (int i = 0; i < 4; i++) {
			int x; scanf("%d", &x);
			if (x > 0) ans++;
		}
		if (ans == 0) puts("Typically Otaku");
		if (ans == 1) puts("Eye-opener");
		if (ans == 2) puts("Young Traveller");
		if (ans == 3) puts("Excellent Traveller");
		if (ans == 4) puts("Contemporary Xu Xiake");
	}
} 
