#include <bits/stdc++.h>
using namespace std;

using number = long double;

const int maxn = 50 + 1;
const int maxv = 1e4 + 1;
const number eps = 1e-11;

number f[2][maxn * maxv];
bitset<maxn * maxv>g[maxn];

int a[maxn], b[maxn];

int sign(number x) {
	return (x > eps) - (x < -eps);
}

int cmp(number x, number y) {
	return sign(x - y);
}

bool ch[maxn];

int main() {
	//cout << ( sizeof (f) + sizeof (g) )/ 1024 / 1024 << endl;
	freopen("discount.in", "r", stdin);
	freopen("discount.out", "w", stdout);
	int n, x;
	cin >> n >> x;
	
	int sum = 0;	
	
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		sum += a[i];
	}
	
	for (int i = 0; i <= sum; i++) f[0][i] = f[1][i] = -1;
	f[0][0] = 1;
	
	for (int i = 0; i < n; i++) {
		int ci = i & 1, ni = !ci;
		for (int j = 0; j <= sum; j++) f[ni][i] = -1;
		for (int j = 0; j <= sum; j++) {
			if (f[ci][j] < 0) continue;
			if (cmp(f[ni][j], -1) == 0 || f[ci][j] < f[ni][j]) {
				g[i + 1][j] = false;
				f[ni][j] = f[ci][j];
			}
			if (cmp(f[ni][j + a[i + 1]], -1) == 0 || f[ci][j] * (1 - number(b[i + 1]) / 100) < f[ni][j + a[i + 1]]) {
				g[i + 1][j + a[i + 1]] = true;
				f[ni][j + a[i + 1]] = f[ci][j] * (1 - number(b[i + 1]) / 100);
			}
		}
	}
	
	number ans = 1e9 + 10; int ans_a = -1;
	for (int i = 0; i <= sum; i++) 
		if (cmp(f[n & 1][i], -1) != 0 && ans > x * f[n & 1][i] - (sum - i)) 
			ans = x * f[n & 1][i] - (sum - i), ans_a = i;
	
	assert(ans_a != -1);
	
	for (int i = n; i >= 1; i--) {
		if (g[i][ans_a]) {
			ch[i] = true;
			ans_a = ans_a - a[i];
		} else {
			ch[i] = false;
		}
	}
	
	for (int i = 1; i <= n; i++) if (ch[i]) 
		cout << i << ' ' << "reverse" << endl;
		
	for (int i = 1; i <= n; i++) if (!ch[i]) 
		cout << i << ' ' << "front" << endl;
	
	return 0;
}

