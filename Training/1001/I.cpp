#include <cstdio>
#include <vector>
#include <algorithm>

const int maxn = 2e5 + 10;

std::vector<int>G[maxn];

bool vis[maxn];

int nowRoot, nowSize, allSize;
int size[maxn], maxs[maxn];

void getRoot(int u, int f) {
	size[u] = 1;
	maxs[u] = 0;
	for (auto v : G[u]) {
		if (v == f || vis[v]) continue;
		getRoot(v, u);
		size[u] += size[v];
		maxs[u] = std::max(maxs[u], size[v]);
	}
	maxs[u] = std::max(maxs[u], allSize - size[u]);
	if (maxs[u] < nowSize)
		nowRoot = u, nowSize = maxs[u];
}

std::vector<int>pt;
void getList(int u, int f) {	
	pt.push_back(u);
	for (auto v : G[u]) {
		if (vis[v] || v == f) continue;
		getList(v, u);
	}
}
int getSize(int u, int f) {
	int s = 1;
	for (auto v : G[u]) {
		if (vis[v] || v == f) continue;
		s += getSize(v, u);
	} return s;
}

void setVis(int u, int f) {
	vis[u] = true; allSize--;
	for (auto v : G[u]) {
		if (vis[v] || v == f) continue;
		setVis(v, u);
	} 
}

std::vector<std::pair<int, int> >tmp;
std::vector<int>part1, part2;

void div() {
	part1.clear(); part2.clear();
	sort(tmp.begin(), tmp.end());
	reverse(tmp.begin(), tmp.end());
	int s1 = 0, s2 = 0;
	for (auto sth : tmp) {
		if (s1 < s2) {
			s1 += sth.first;
			part1.push_back(sth.second);
		} else {
			s2 += sth.first;
			part2.push_back(sth.second);
		}
	}
}

void solve_2(int u, int n) {
	if (n == 1) {
		printf("! %d\n", u);
		fflush(stdout);
		return;
	}
	if (n == 2) {
		pt.clear();
		getList(u, -1);
		u = pt[0];
		int v = pt[1];
		printf("? 1 %d %d\n", u, v);
		fflush(stdout);
		int rtn; scanf("%d", &rtn);
		if (rtn == 0) printf("! %d\n", v);
		else printf("! %d\n", u);
		fflush(stdout);
		return;
	}
}

void solve(int u, int n) {

	if (n <= 2) {
		solve_2(u, n);
		return;
	}
	allSize = n;
	nowRoot = 0;
	nowSize = n;
	getRoot(u, -1);
	u = nowRoot;
	tmp.clear();
	for (auto v : G[u]) {
		if (vis[v])	continue;
		int s = getSize(v, u);
		tmp.push_back(std::make_pair(s, v));
	}
	
	div();
	
	printf("? %d ", (int)part1.size());
	printf("%d ", u); 
	for (auto v : part1) printf("%d ", v);
	puts("");
	fflush(stdout);
	
	int rtn; scanf("%d", &rtn);
	if (rtn == 1) 
		for (auto v : part1) 	
			setVis(v, u);
	else 
		for (auto v : part2)	
			setVis(v, u);
	
	solve(u, allSize);
}



int main()
{
	int n; scanf("%d", &n);
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	solve(1, n);
	return 0;
}
