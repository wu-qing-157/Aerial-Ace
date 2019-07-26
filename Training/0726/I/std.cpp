#include <bits/stdc++.h>

using namespace std;
const int N = 20010;
const int M = 110;
const int INF = 1e9;
int _w;

int n, m, dis[N], c[N], r[N], p[N];

struct Event {
	int L, R, cost;
	Event() {}
	Event( int LL, int RR, int cc ):
		L(LL), R(RR), cost(cc) {}
};

vector<Event> event[N];

void init_event() {
	for( int i = 0; i <= n+1; ++i )
		event[i].clear();
	for( int i = 1; i <= n; ++i ) {
		int L = dis[i] - r[i];
		int R = dis[i] + r[i];
		Event now;
		int pos = int(lower_bound(dis+1, dis+n+1, L) - dis);
		now.L = pos-1;
		pos = int(upper_bound(dis+1, dis+n+1, R) - dis);
		now.R = pos;
		now.cost = p[i];
		event[now.L].push_back(now);
		event[now.R].push_back(now);
	}
}

int f[M][N];

namespace SGT {
	int addv[N*4], minv[N*4];
	int ql, qr, qv;

	void _query( int o, int L, int R, int ad ) {
		if( L >= ql && R <= qr ) {
			qv = min(qv, minv[o] + ad);
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			ad += addv[o];
			if( ql <= M ) _query(lc, L, M, ad);
			if( qr > M ) _query(rc, M+1, R, ad);
		}
	}
	int query( int l, int r ) {
		ql = l, qr = r, qv = INF;
		_query(1, 0, n, 0);
		return qv;
	}
	void _add( int o, int L, int R ) {
		if( L >= ql && R <= qr ) {
			addv[o] += qv;
			minv[o] += qv;
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			if( ql <= M ) _add(lc, L, M);
			if( qr > M ) _add(rc, M+1, R);
			minv[o] = min( minv[lc], minv[rc] ) + addv[o];
		}
	}
	void add( int l, int r, int v ) {
		ql = l, qr = r, qv = v;
		_add(1, 0, n);
	}
	void build( int *a ) {
		memset(addv, 0, sizeof addv);
		memset(minv, 0, sizeof minv);
		for( int i = 0; i <= n; ++i )
			add(i, i, a[i]);
	}
}

int lastcost[N];

void solve_lastcost() {
	int last = 0;
	for( int i = n; i >= 1; --i ) {
		for( auto ev : event[i] ) {
			if( i == ev.L ) {
				last += ev.cost;
			}
		}
		lastcost[i] = last;
	}
}

int solve() {
	int ans = 0;
	for( int i = 1; i <= n; ++i )
		ans += p[i];
	init_event();
	f[0][0] = 0;
	for( int i = 1; i <= n; ++i )
		f[0][i] = INF;
	for( int j = 1; j <= m; ++j ) {
		SGT::build( f[j-1] );
		f[j][0] = 0;
		for( int i = 1; i <= n; ++i ) {
			for( auto ev : event[i] ) {
				if( i == ev.R ) {
					SGT::add(0, ev.L, ev.cost);
				}
			}
			f[j][i] = c[i] + SGT::query(0, i-1);
		}
	}
	solve_lastcost();
	for( int j = 1; j <= m; ++j )
		for( int i = 1; i <= n; ++i )
			ans = min( ans, f[j][i] + lastcost[i] );
	return ans;
}

int main() {
	int kase = 0;
	while(1) {
		_w = scanf( "%d%d", &n, &m );
		if( n == 0 && m == 0 ) break;
		for( int i = 2; i <= n; ++i )
			_w = scanf( "%d", dis+i );
		dis[1] = 0;
		for( int i = 1; i <= n; ++i )
			_w = scanf( "%d", c+i );
		for( int i = 1; i <= n; ++i )
			_w = scanf( "%d", r+i );
		for( int i = 1; i <= n; ++i )
			_w = scanf( "%d", p+i );
		printf( "Case %d: %d\n", ++kase, solve() );
	}
	return 0;
}
