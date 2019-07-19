#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const int maxn = 1500 + 10;
const int maxn_2 = maxn * maxn;
using number = double;
const number eps = 1e-10;
int sign(double x) {
	return (x > eps) - (x < -eps);
}
 
struct Fun {
	int a, b, c, id;
	long long f(long long x) {
		return a * x * x + b * x + c;
	}
	long long y, dy;
} fun[maxn];
 
bool cmp(Fun a, Fun b) {
	return a.y == b.y ? a.dy < b.dy : a.y < b.y;
}
 
vector<pair<number, pair<int, int> > > point;
 
void cross(int f, int g) {
	if (fun[f].a == fun[g].a) {
		if (fun[f].b == fun[g].b) {
			;
		} else {
			number x = -1.0 * (fun[f].c - fun[g].c) / (fun[f].b - fun[g].b);
			if (x <= -1e5 + eps || x >= 1e5 - eps) {
			
			} else point.push_back(make_pair(x, make_pair(fun[f].id, fun[g].id)));
		}
	} else {
		ll a = fun[f].a - fun[g].a;
		ll b = fun[f].b - fun[g].b;
		ll c = fun[f].c - fun[g].c;
		ll delta = b * b - 4 * a * c;
		if (delta <= 0) {
		
		} else {
			number x1 = (-b + sqrt(number(delta))) / a / 2;
			number x2 = (-b - sqrt(number(delta))) / a / 2;
			point.push_back(make_pair(x1, make_pair(fun[f].id, fun[g].id)));
			point.push_back(make_pair(x2, make_pair(fun[f].id, fun[g].id)));
		}
	}
}
 
vector<pair<double, int> > up;
 
int pos[maxn];
 
void work() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%d%d%d", &fun[i].a, &fun[i].b, &fun[i].c), fun[i].id = i;
		
	std::sort(fun + 1, fun + n + 1, [](auto a, auto b) { return a.a == b.a ? (a.b == b.b ? a.c < b.c : a.b < b.b) : a.a < b.a; });
	n = std::unique(fun + 1, fun + n + 1, [](auto a, auto b) { return a.a == b.a && a.b == b.b && a.c == b.c; }) - fun - 1;
	
	for (int i = 1; i <= n; i++) 
		for (int j = i + 1; j <= n; j++) 	
			cross(i, j);
			
	sort(point.begin(), point.end(), [](auto a, auto b){ return sign(a.first - b.first) < 0; } );
	
	for (int i = 1; i <= n; i++) {
		fun[i].y = fun[i].f(int(-1e5));
		fun[i].dy = 2ll * fun[i].a * int(-1e5) + fun[i].b;
	}
	
	sort(fun + 1, fun + 1 + n, cmp);
	for (int i = 1; i <= n; i++) pos[fun[i].id] = i;
	
	up.push_back(make_pair(-1e5, fun[n].id));
	
	for (auto p : point) {
		number x = p.first;
		int i = p.second.first;
		int j = p.second.second;
		swap(fun[pos[i]], fun[pos[j]]);
		swap(pos[i], pos[j]);
 		if (pos[i] == n || pos[j] == n) up.push_back(make_pair(x, fun[n].id));
	}
	
	// for (auto i : up) printf("up %f %d\n", i.first, i.second);
	
	int q; scanf("%d", &q);
	while (q--) {
		int x; scanf("%d", &x);
		int f = (upper_bound(up.begin(), up.end(), make_pair(x, 100000), [](auto a, auto b) { return sign(a.first - b.first) < 0; } ) - 1)->second;
		printf("%d %lld\n", f - 1, fun[pos[f]].f(x));
	}
}
 
int main() {
    freopen("parabolas.in", "r", stdin);
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		up.clear();
		point.clear();
		printf("Case %d:\n", t);
		work();
	}
	return 0;
}
/*
1
7
-4 8 0
-4 20 -24 
-4 28 -48
-2 24 -64 
-2 36 -154
-1 8 -7
1 -10 0
16
-1 
-2
0
1
2
3
4
5
6
7
8
9
10
11
12
13
*/
