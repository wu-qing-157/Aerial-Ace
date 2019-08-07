#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

char T[maxn];

int s[maxn];

int get(int l, int r) {
	return s[r] - s[l - 1];
}

int chk(char c) {
	if (c == 'a') return 1;
	if (c == 'e') return 1;
	if (c == 'i') return 1;
	if (c == 'o') return 1;
	if (c == 'u') return 1;
	return 0;
}

int solve(int l, int r, bool inv) {
	//cout << l << ' ' << r << endl;
	if (get(l, r) == 0) return 1;
	else {
		if (inv ? !chk(T[r]) : !chk(T[l])) return 0;
		if (get(l, r) == 1) return r - l + 1;
		else {
			if (!inv) {
				int R = r;
				while (!chk(T[R])) R--;
				return solve(l + 1, R, inv ^ 1);
			} else {
				int L = l;
				while (!chk(T[L])) L++;
				return solve(L, r - 1, inv ^ 1);
			}
		}
	} 
}

int main() {
	scanf("%s", T + 1);
	
	int n = strlen(T + 1);
	for (int i = 1; i <= n; i++) s[i] = chk(T[i]);
	for (int i = 1; i <= n; i++) s[i] += s[i - 1];
	
	cout << solve(1, n, false) << endl;
}
