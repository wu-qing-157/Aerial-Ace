#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 10;
const int maxn2 = maxn * maxn;
const int inf = 1e9;

int f[maxn][maxn2];
int g[maxn][maxn2];
int a[maxn];

vector<int>s[2];

int main() {
	//freopen("polygon.in", "r", stdin);
	//freopen("polygon.out", "w", stdout);
	int n; scanf("%d", &n);
	
	for (int i = 0; i < maxn; i++)
		for (int j = 0; j < maxn2; j++)
			f[i][j] = -inf, g[i][j] = -1;
	
	f[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		int x; scanf("%d", &x);
		a[i] = x;
		for (int j = 0; j < maxn2; j++) {
			if (f[i][j] < f[i - 1][j]) {
				f[i][j] = f[i - 1][j];
				g[i][j] = -1;
			}
			if (j >= x) {
				if (f[i][j] < f[i - 1][j - x] + 1) {
					f[i][j] = f[i - 1][j - x] + 1;
					g[i][j] = 1;
				}
			}
			else {
				if (f[i][j] < f[i - 1][x - j] + 1) {
					f[i][j] = f[i - 1][x - j] + 1;
					g[i][j] = 2;
				}	
			}
			if (j + x < maxn2) {
				if (f[i][j] < f[i - 1][j + x] + 1) {
					f[i][j] = f[i - 1][j + x] + 1;
					g[i][j] = 3;
				}
			} 
				
		}
	}
	
	int len = 0;
	
	int p1 = 0, p2 = 1;
	
	for (int i = n; i >= 1; i--) {
		if (g[i][len] == -1) continue;
		else if (g[i][len] == 1) {
			s[p1].push_back(i);
			len = len - a[i];
		} else if (g[i][len] == 2) {
			s[p1].push_back(i);
			swap(p1, p2);
			len = a[i] - len;
		} else if (g[i][len] == 3) {
			s[p2].push_back(i);
			len = a[i] + len;
		}
	}
	
	cout << s[0].size() + s[1].size() << endl;
	int y = 0, x = 0;
	for (int i = 0; i < s[0].size(); i++) {
		cout << x << ' ' << y << endl;
		x += a[s[0][i]];
		cout << x << ' ' << y << endl;
		y++;
	}
	
	for (int i = 0; i < s[1].size(); i++) {
		cout << x << ' ' << y << endl;
		x -= a[s[1][i]];
		cout << x << ' ' << y << endl;
		y++;
	}
	
	//for (int i = 0; i <= n; i++)
	//	for (int j = 0; j <= 5; j++)
	//		printf("f[%d][%d] = %d, g[%d][%d] = %d\n", i, j, f[i][j], i, j, g[i][j]);
	
}
/*
3
1 2 1
2
0 0
1 0
1 1
0 1
f[0][0] = 0, g[0][0] = -1
f[0][1] = -1000000000, g[0][1] = -1
f[0][2] = -1000000000, g[0][2] = -1
f[0][3] = -1000000000, g[0][3] = -1
f[0][4] = -1000000000, g[0][4] = -1
f[0][5] = -1000000000, g[0][5] = -1
f[1][0] = 0, g[1][0] = 0
f[1][1] = 1, g[1][1] = 0
f[1][2] = -999999999, g[1][2] = 1
f[1][3] = -999999999, g[1][3] = 2
f[1][4] = -999999999, g[1][4] = 3
f[1][5] = -999999999, g[1][5] = 4
f[2][0] = 0, g[2][0] = 0
f[2][1] = 2, g[2][1] = 1
f[2][2] = 1, g[2][2] = 0
f[2][3] = 2, g[2][3] = 1
f[2][4] = -999999998, g[2][4] = 2
f[2][5] = -999999998, g[2][5] = 3
f[3][0] = 3, g[3][0] = 1
f[3][1] = 2, g[3][1] = 1
f[3][2] = 3, g[3][2] = 1
f[3][3] = 2, g[3][3] = 3
f[3][4] = 3, g[3][4] = 3
f[3][5] = -999999997, g[3][5] = 4
*/
