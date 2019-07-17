#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 10;

typedef long long ll;


int a[5 * maxn], p[6];

int nxt[6][maxn * 5];
bool vis[6][5 * maxn];
ll stp[6];
int rnd[6][5 * maxn];


static int P[10];

ll extend_gcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) { x = 1; y = 0; return a; } 	
	ll res = extend_gcd(b, a % b, x, y);
	ll t = y;
	y = x - a / b * y; x = t; return res;
}

bool CRT(ll &r1, ll &m1, ll r2, ll m2) {
	ll x, y, g = extend_gcd(m1, m2, x, y);
	if ((r2 - r1) % g != 0) return false;
	x = (1ll * (r2 - r1) % m2 * x % m2) % m2;
	if (x < 0) x += m2;
	x /= g;
	r1 += m1 * x;
	m1 *= m2 / g;
	return true;
}

ll solve(int I) {
	static ll tmp[10];
	for (int i = 1; i <= 5; i++)
		tmp[i] = P[i] + (I - 1) * 5;
		
	//for (int i = 1; i <= 5; i++)
	//	printf("(%lld, %lld) ", tmp[i], stp[i]);
		
	for (int i = 1; i <= 5; i++)
		if (rnd[i][tmp[i]] == -1) 
			return -1;
		else 
			tmp[i] = rnd[i][tmp[i]];
	ll r1 = tmp[1], m1 = stp[1];
	for (int i = 2; i <= 5; i++)
		if (!CRT(r1, m1, tmp[i], stp[i]))
			return -1;
	return r1 == 0 ? m1 : r1;
}

void work(int n) {
	for (int i = 1; i <= n * 5; i++) {
		scanf("%d", &a[i]);
		if (a[i] <= 5)
			p[a[i]] = i;
	}
	//for (int i = 1; i <= 5; i++)
	//	cout << p[i] << ' '; 
	//cout << endl;
	memset(vis, 0, sizeof  vis);
	for (int i = 1; i <= 5; i++) {
		int now = p[i], step = 0;
		nxt[i][step++] = now;
		vis[i][now] = true;
		while (true) {
			if (now <= n * 2)
				now = (now + 1) / 2 * 5 - now % 2 - 3;
			else if (now <= n * 4) 
				now = (now - n * 2 + 1) / 2 * 5 - now % 2 - 1;
			else 
				now = (now - n * 4) * 5;
			if (vis[i][now]) break;
			vis[i][now] = true;
			nxt[i][step++] = now;
		}
		stp[i] = step;
		//cout << stp[i] << ' ';
	}
	//cout << endl;
	
	
	
	memset(rnd, -1, sizeof rnd);
	for (int i = 1; i <= 5; i++) 
		for (int j = 0; j < stp[i]; j++) 
			rnd[i][nxt[i][j]] = j;
	
	for (int i = 1; i <= 5; i++) P[i] = i;
	
	pair<int, ll> ans = make_pair(-1, -1);
	
	for (int i = 1; i <= n; i++) {
		do {
			ll tmp = solve(i);
			if (tmp != -1 && (ans.second == -1 || ans.second > tmp))
				ans = make_pair(i, tmp);
		} while (next_permutation(P + 1, P + 1 + 5));
	}
	if (ans.first != -1) 
		printf("Player %d wins game number %lld.\n", ans.first, ans.second);
	else 	
		printf("Neverending game.\n");
}

int main() {
	int n; 
	while (true) {
		scanf("%d", &n);
		if (n == 0)
			break;
		else
			work(n);
	}
	return 0;	
}
/*
2
2 3 9 7 4 8 5 1 10 6
2
2 6 9 7 4 8 5 1 10 3
5
16 12 18 11 20 15 19 24 8 6 25 1 7 22 14 2 3 10 13 17 4 5 21 9 23
*/
