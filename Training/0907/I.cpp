#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

int p[maxn], w[maxn];

struct Node {
    int l, r, id;
    long long ans;
} qry[maxn];

bool cmpid(Node a, Node b) {
    return a.id < b.id;
}

bool cmpr(Node a, Node b) {
	return a.r < b.r;
}

long long bit[maxn];
void add(int p, long long x) {
    for (int i = p; i < maxn; i += i & -i)
        bit[i] += x;
}
long long ask(int p, long long x = 0) {
    for (int i = p; i; i -= i & -i)
        x += bit[i];
	return x;
}

vector<int>p1[maxn], p2[maxn];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
    for (int i = 1; i <= n; i++) w[p[i]] = i;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &qry[i].l, &qry[i].r);
        qry[i].id = i;
    }
    for (int i = 1; i <= n; i++)
    	for (int j = i * 2; j <= n; j += i)
    		p1[j].push_back(i), p2[i].push_back(j);
    
    sort(qry + 1, qry + 1 + m, cmpr);
    int R = 0;
    
    for (int i = 1; i <= m; i++) {
    	int l = qry[i].l, r = qry[i].r;
    	while (R < r) {
    		R++;
    		for (int v : p1[p[R]]) 
    			if (w[v] < R) 
    				add(w[v], 1);
    		for (int v : p2[p[R]])
    			if (w[v] < R) 
    				add(w[v], 1);
		}
		qry[i].ans = ask(r) - ask(l - 1);
	}
	sort(qry + 1, qry + 1 + m, cmpid);
	for (int i = 1; i <= m; i++) {
		printf("%lld\n", qry[i].ans);
		//cout << qry[i].id << endl;
	}
	
    return 0;
}
