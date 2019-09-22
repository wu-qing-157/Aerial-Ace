#include <bits/stdc++.h>
using namespace std;

const int maxn = 4e5 + 10;
const int maxm = 1e6 + 10;

char A[maxn], B[maxn], C[maxn];
int a[maxn], b[maxn], c[maxn];

using ll = long long;

const ll MOD = 1e17 + 23;

struct MAP {
	struct Node {
		Node *next;
		ll key;
		int val;
	} node[maxn], *head[maxm], *cur;
	void insert(ll x, int y) {
		int _x = x % maxm;
		cur->next = head[_x];
		cur->key = x;
		cur->val = y;
		head[_x] = cur;
		++cur;
	}
	int count(ll x) {
		int _x = x % maxm;
		for (Node *now = head[_x]; now != NULL; now = now->next) 
			if (now->key == x) return true;
		return false;
	}
	int ask(ll x) {
		int _x = x % maxm;
		for (Node *now = head[_x]; now != NULL; now = now->next) 
			if (now->key == x) return now->val;
	}
	void clear() {
		cur = node;
		memset(head, 0, sizeof head);
	}
} mp;

//unordered_map<ll, int>mp;

int cnt = 0;

bool check(int x, int y, int z, int N) {
	cnt++;
	int M = max({x, y, z}) + N + 10;
	memset(a, 0, M << 2);
	memset(b, 0, M << 2);
	memset(c, 0, M << 2);
	int n;
	for (int i = 0; i < x; i++) a[i] = 0;
	n = strlen(A);
	for (int i = n - 1, j = x; i >= 0; i--, j++)
		a[j] = A[i] - '0';
	for (int i = 0; i < y; i++) b[i] = 0;
	n = strlen(B);
	for (int i = n - 1, j = y; i >= 0; i--, j++)
		b[j] = B[i] - '0';
	for (int i = 0; i < z; i++) c[i] = 0;
	n = strlen(C);
	for (int i = n - 1, j = z; i >= 0; i--, j++)
		c[j] = C[i] - '0';
	
	for (int i = 0; i < M; i++) a[i] += b[i];
	for (int i = 0; i < M; i++) a[i + 1] += a[i] / 10, a[i] %= 10;
	for (int i = 0; i < M; i++) if (a[i] != c[i]) return false;
	return true;
}

void work() {
	scanf("%s%s%s", A, B, C);
	ll A0 = 0, B0 = 0, C0 = 0;
	for (int i = 0; A[i]; i++)
		A0 = (A0 * 10 + A[i] - '0') % MOD; 
	for (int i = 0; B[i]; i++)
		B0 = (B0 * 10 + B[i] - '0') % MOD;
	for (int i = 0; C[i]; i++)
		C0 = (C0 * 10 + C[i] - '0') % MOD;
	int N = (int)max({strlen(A), strlen(B), strlen(C)});
	ll C1 = C0, A1 = A0, B1 = B0;
	mp.clear();
	//mp.reserve(4e5);
	for (int z = 0; z < N * 2 + 10; z++) 
		mp.insert(C1, z), C1 = C1 * 10 % MOD;
	
	for (int x = 0; x < N * 2 + 10; x++) {
		ll C2 = (A1 + B0) % MOD;
		int z;
		if (mp.count(C2) && check(x, 0, z = mp.ask(C2), N)) {
			printf("%d %d %d\n", x, 0, z);
			return;
		}
		A1 = A1 * 10 % MOD;
	}
	
	for (int y = 0; y < N * 2 + 10; y++) {
		ll C2 = (A0 + B1) % MOD;
		int z;
		if (mp.count(C2) && check(0, y, z = mp.ask(C2), N)) {
			printf("%d %d %d\n", 0, y, z);
			return;
		}
		B1 = B1 * 10 % MOD;
	}
	puts("-1");
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();

	//cout << cnt << endl;
	return 0;
}

