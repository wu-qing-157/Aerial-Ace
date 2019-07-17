#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e4 + 10;

char mp[200][200];

vector<int>G[maxn];

#define ID(x, y) ((x) * m + (y))

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

int match[maxn];

bool vis1[maxn];

bool ans[maxn];

bool dfs1(int u) {
	if (vis1[u]) return false;
	vis1[u] = true;
	for (int v : G[u]) 
		if (match[v] == -1 || dfs1(match[v])) {
			match[v] = u; match[u] = v; 
			return true;
		}
	return false;
}

void dfs2(int u) {
	if (vis1[u]) return;
	vis1[u] = true;
	ans[u] = true;
	for (int v : G[u]) {
		if (match[v] == -1) continue; 
		dfs2(match[v]);
	}
}

void work(int n, int m) {
	for (int i = 0; i < n; i++) scanf("%s", mp[i]);
	for (int i = 0, mn = n * m; i < mn; i++) G[i].clear();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			if (mp[i][j] == 'X') continue;
			for (int k = 0; k < 4; k++) {
				int x = dx[k] + i; 
				int y = dy[k] + j;
				if (x < 0 || x >= n || y < 0 || y >= m) continue;
				if (mp[x][y] == 'X') continue;
				G[ID(x, y)].push_back(ID(i, j));
			}
		}
	for (int i = 0, mn = n * m; i < mn; i++) match[i] = -1;
	for (int i = 0; i < n; i++)	
		for (int j = 0; j < m; j++) {
			if (mp[i][j] == 'X') continue;
			if (match[ID(i, j)] != -1) continue;
			memset(vis1, 0, sizeof (bool) * n * m);
			dfs1(ID(i, j));
		}
	
	
	memset(ans, 0, sizeof (bool) * n * m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) 
			if (mp[i][j] != 'X' && match[ID(i, j)] == -1) {
				memset(vis1, 0, sizeof (bool) * n * m);
				ans[ID(i, j)] = true, dfs2(ID(i, j));
			}
			
				
	for (int i = 0; i < n; i++, putchar('\n')) 
		for (int j = 0; j < m; j++) 
			if (mp[i][j] == 'X')
				putchar('X');
			else 
				putchar(ans[ID(i, j)] ? 'B' : 'A');
				
	putchar('\n');
}

int main() {
	int n, m;
	while (true) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0)
			break;
		else 
			work(n, m);
	}
	return 0;	
}
/*
1 1 
.
1 3
...
3 3
...
.X.
...
1 4
....
3 3
X.X
...
X.X
5 8
........
.XX.XXX.
.X..X...
.X.XX.X.
........	
3 6
XXXX.X
......
XXXX.X
*/
