#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

struct Car {
	int l, m, r, v;
	double p, t;
} car[maxn];

typedef pair<pair<double, double>, pair<int, int> > node;

priority_queue<node, vector<node>, greater<node> >pq;

int pre[maxn], nxt[maxn], n;

void crash(int x, int y) {
	if (car[x].v >= car[y].v) return;
	double nowt = max(car[x].t, car[y].t);
	double xp = car[x].p - car[x].v * (nowt - car[x].t);
	double yp = car[y].p - car[y].v * (nowt - car[y].t);
	double s = yp - (xp + car[x].r);
	double t = s / (car[y].v - car[x].v);
	double p = xp - t * car[x].v;
	//cout << nowt + t << ' ' << p << ' ' << x << ' ' << y << endl;
	pq.push(make_pair(make_pair(nowt + t, p), make_pair(x, y)));
}

struct MFS {
	int fa[maxn];
	void init() {
		for (int i = 1; i <= n; i++) fa[i] = i;
	}
	int find(int x) {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	void merge(int x, int y) {
		fa[find(x)] = find(y);
	}
} mfs;

void merge(int x, int y, double t, double p) {
	pre[y] = pre[x];
	nxt[pre[y]] = y;
	mfs.merge(x, y);
	car[y].t = t;
	car[y].p = p;
	car[y].l = 0;
	car[y].m = car[x].r + car[y].m;
	car[y].r = car[x].r + car[y].r;
	car[y].v = car[x].v;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		n = n + 1; mfs.init();
		for (int i = 1; i <= n; i++) scanf("%d", &car[i].r);
		for (int i = 1; i <= n; i++) scanf("%lf", &car[i].p);
		for (int i = 1; i <= n; i++) scanf("%d", &car[i].v);
		
		reverse(car + 1, car + 1 + n);
		for (int i = 1; i <= n; i++) car[i].l = car[i].m = 0, car[i].t = 0;
		for (int i = 1; i <= n; i++) pre[i] = i - 1, nxt[i] = i + 1;
		//for (int i = 1; i <= n; i++) del[i] = false;
		
		while (pq.size()) pq.pop();
		for (int i = 1; i < n; i++) crash(i, i + 1);
		
		while (true) {
			double ans = double(car[n].p + car[n].m) / car[n].v + car[n].t;
			if (!pq.size() || ans <= pq.top().first.first) {
				printf("%.10f\n", ans);
				break;
			} else {
				int x = pq.top().second.first;
				int y = pq.top().second.second;
				pq.pop();
				if (mfs.find(x) == mfs.find(y)) continue;
				double t = pq.top().first.first;
				double p = pq.top().first.second;
				
				merge(x, y, t, p);
				
				if (pre[y] > 0)
					crash(pre[y], y);
				if (nxt[y] <= n)
					crash(y, nxt[y]);
			}
		}
	}
	return 0;	
}
/*
1
2 2
7 1
2 1
2
1 2 2
10 7 1
6 2 1
*/
