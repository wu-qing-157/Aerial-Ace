#include <bits/stdc++.h>
using namespace std;

const int maxn = 12;
const int maxm = 24;

int w[maxn][maxn];
char c[maxn * 2][maxn * 2];
int f[1 << maxm];
int d[1 << maxm];

void cmin(int &x, int y) { x = x > y ? y : x; }

struct {
	int x, y, z;
} c1[maxm], c2[maxm];

int main() {
	//cout << sizeof(f) / 1024 / 1024 << endl;
	d[0] = 0;
	for (int i = 1; i < 1 << maxm; i++) d[i] = d[i >> 1] + (i & 1);
	int n; while (scanf("%d", &n) != EOF) {
		int m = n * 2, N = (1 << n) - 1, M = (1 << m) - 1;
		for (int i = n - 1; i >= 0; i--) 
			scanf("%s", c[i]);
		for (int i = n - 1; i >= 0; i--)
			for (int j = 0; j < n; j++)
				scanf("%d", &w[i][j]);
		memset(f, 0x3f, (1 << m) << 2);
		f[(1 << n) - 1] = 0;
		for (int s = (1 << n) - 1; s < (1 << m); s++) {
			if (d[s] != n) continue;
			//printf("f[%d] = %d\n", s, f[s]);
			int cnt1 = 0, cnt2 = 0;
			for (int x = n, y = 0, z = 0; z < m - 1; z++) {
				if (s >> z & 1) x--; else y++;
				if (x == n) continue;
				if ((s >> z & 3) == 1) {
					if (c[x][y] == '.') 
						cmin(f[(s ^ (3 << z)) & M], f[s]);
					else {
						cmin(f[(s ^ (3 << z)) & M], f[s] + w[x][y]);
						if (c[x][y] == 'B')
							c1[cnt1++] = {x, y, z};
						else 
							c2[cnt2++] = {x, y, z};
					}
				}
			}
			
			for (int i = 0; i < cnt1; i++)
				for (int j = 0; j < cnt2; j++)
					cmin(f[s ^ (3 << c1[i].z) ^ (3 << c2[j].z)], f[s] + abs(w[c1[i].x][c1[i].y] - w[c2[j].x][c2[j].y]));
		}
		printf("%d\n", f[N << n]);
	}
	return 0;	
}
