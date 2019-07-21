#include <bits/stdc++.h>
using namespace std;
/*
using number = long double;

const int maxn = 5e5 + 10;
const number eps = 1e-12;

int sign(number x) {
	return (x > eps) - (x < -eps);
}

int cmp(number x, number y) {
	return sign(x - y);
}

number f[maxn];
*/

int a[100], b[100], id[100];

bool cmp(int p, int q) {
	return ((double) b[p] / 100.0 / a[p]) < ((double) b[q] / 100.0 / a[q]);
}

int main() {
	freopen("discount.in", "r", stdin);
	freopen("discount.out", "w", stdout);
	int n, x;
	cin >> n >> x;
	
	for (int i = 1; i <= n; i++) 
		cin >> a[i] >> b[i], id[i] = i;
	
	sort(id + 1, id + 1 + n, cmp);
	
	long double ans = 1e9 + 10; int k = -1;
	
	for (int i = 0; i <= n; i++) {
		long double now_ans = x;
		//cout << now_ans << endl;
		for (int j = n; j > i; j--) {
			now_ans *= (1.0 - (double)b[id[j]] / 100.0);
		}
		for (int j = i; j > 0; j--) {
			now_ans -= a[id[j]];
		}
		if (now_ans <= ans) 
			ans = now_ans, k = i;
	}
	
	int i = k;
	
	//cout << ans << endl;	
		
	for (int j = n; j > i; j--) {
		//now_ans *= (1 - b[id[j]] / 100);
		cout << id[j] << ' ' << "reverse" << endl;
	}
	for (int j = i; j > 0; j--) {
		//now_ans -= a[id[j]];
		cout << id[j] << ' ' << "front" << endl;
	}
		
	
	return 0;
}
/*
3 1000
10 1
20 1
10 2

*/
