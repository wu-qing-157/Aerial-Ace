#include <bits/stdc++.h>
using namespace std;

int dp[30][5000][6];

struct Node {
	int x, y, s;
	Node(int x, int y, int s) : x(x), y(y), s(s) {}
};

int rs[6] = {4, 1, 0, 3, 5, 2};
int ls[6] = {2, 1, 5, 3, 0, 4};
int us[6] = {3, 0, 2, 5, 4, 1};
int ds[6] = {1, 5, 2, 0, 4, 3};

int sp[6] = {0, 2, 1, 4, 3, 5};

void init() {
	queue<Node>q;
	q.push(Node(0, 0, 0));
	memset(dp, -1, sizeof dp);
	dp[0][0][0] = 0;
	while (q.size()) {
		Node u = q.front(); q.pop();
		int x = u.x, y = u.y, s = u.s;
		int nx, ny, ns;
		{
			nx = x + 1, ny = y;
			ns = rs[s];
			if (nx > ny) swap(nx, ny), ns = sp[ns];
			if (nx >= 0 && nx < 30 && ny >= 0 && ny < 5000) 
			if (dp[nx][ny][ns] == -1) {
				dp[nx][ny][ns] = dp[x][y][s] + 1;
				q.push(Node(nx, ny, ns));
			}
		}
		{
			nx = x - 1, ny = y;
			ns = ls[s];
			if (nx > ny) swap(nx, ny), ns = sp[ns];
			if (nx >= 0 && nx < 30 && ny >= 0 && ny < 5000) 
			if (dp[nx][ny][ns] == -1) {
				dp[nx][ny][ns] = dp[x][y][s] + 1;
				q.push(Node(nx, ny, ns));
			}
		}
		{
			nx = x, ny = y + 1;
			ns = us[s];
			if (nx > ny) swap(nx, ny), ns = sp[ns];
			if (nx >= 0 && nx < 30 && ny >= 0 && ny < 5000) 
			if (dp[nx][ny][ns] == -1) {
				dp[nx][ny][ns] = dp[x][y][s] + 1;
				q.push(Node(nx, ny, ns));
			}
		}
		{
			nx = x, ny = y - 1;
			ns = ds[s];
			if (nx > ny) swap(nx, ny), ns = sp[ns];
			if (nx >= 0 && nx < 30 && ny >= 0 && ny < 5000) 
			if (dp[nx][ny][ns] == -1) {
				dp[nx][ny][ns] = dp[x][y][s] + 1;
				q.push(Node(nx, ny, ns));
			}
		}
	}
}

int ask(int x, int y) {
	if (x > y) swap(x, y);
	if (x > 4 && y > 4) return x + y;
	else {
		//cout << "ask " << x << ' ' << y << ' ' << dp[x][y][0] << endl; 
		return dp[x][y][0];
	}
}

int g[16][16];

int x[16], y[16];

int s[1 << 16][16];

int main() {
	init();
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		for (int i = 0; i < n; i++) 
			scanf("%d%d", &x[i], &y[i]);
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++) 
				g[i][j] = ask(abs(x[i] - x[j]), abs(y[i] - y[j]));
		
		memset(s, 0x3f, sizeof s);
		for (int i = 0; i < n; i++)
			s[1 << i][i] = ask(abs(x[i]), abs(y[i]));
		
		for (int S = 0; S < 1 << n; S++) 
			for (int i = 0; i < n; i++) if (S >> i & 1)
				for (int j = 0; j < n; j++) if (S >> j & 1 && i != j)
					s[S][j] = min(s[S][j], g[i][j] + s[S ^ (1 << j)][i]);
		
		int ans = 1e9;
		for (int i = 0; i < n; i++)
			ans = min(s[(1 << n) - 1][i], ans);
		printf("%d\n", ans);
	}
	return 0;
}
