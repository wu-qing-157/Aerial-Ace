#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5 + 10;

const pii P(19260817, int(1e9 + 7));
const int B = 233;
pii W[maxn];

struct Hash {
	pii H[maxn];
	void build(char *s, char c, int n) {
		H[0] = make_pair(0, 0);
		for (int i = 1; i <= n; i++) {
			H[i].first = (H[i - 1].first * 1ll * B + (s[i] == c)) % P.first;
			H[i].second = (H[i - 1].second * 1ll * B + (s[i] == c)) % P.second;
		}
	}
	pii getH(int l, int r) {
		int h1 = (H[r].first - 1ll * H[l - 1].first * W[r - l + 1].first) % P.first;
		int h2 = (H[r].second - 1ll * H[l - 1].second * W[r - l + 1].second) % P.second;
		if (h1 < 0) h1 += P.first;
		if (h2 < 0) h2 += P.second;
		return make_pair(h1, h2);
	}
} hs;

pii ht[100];

char s[maxn], t[maxn];
int nxt[maxn][100];
int pos[100];

bool ans[maxn];
vector<int> tmp;
int main() {
	//freopen("substring.in", "r", stdin);
	//freopen("substring.out", "w", stdout);
	scanf("%s%s", s + 1, t + 1);
	int n = strlen(s + 1);
	int m = strlen(t + 1);
	for (int i = 1; i <= n; i++) s[i] -= 32;
	for (int i = 1; i <= m; i++) t[i] -= 32;
	
	W[0].first = W[0].second = 1;
	for (int i = 1; i <= n; i++) {
		W[i].first = 1ll * W[i - 1].first * B % P.first;
		W[i].second = 1ll * W[i - 1].second * B % P.second;
	}
	
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j < 100; j++) {
			ht[j].first = (ht[j].first * 1ll * B + (t[i] == j)) % P.first;
			ht[j].second = (ht[j].second * 1ll * B + (t[i] == j)) % P.second;
		}
	}
	
	for (int j = 1; j < 100; j++) pos[j] = n + 1;
	for (int i = n; i >= 1; i--) {
		pos[s[i]] = i;
		for (int j = 1; j < 100; j++)
			nxt[i][j] = pos[j];
	}
	memset(ans, true, sizeof ans);
	for (char sc = 1; sc < 100; sc++) {
		hs.build(s, sc, n);
		for (int i = 1; i + m - 1 <= n; i++) {
			if (!ans[i]) continue;
			int p = nxt[i][sc];
			if (p - i + 1 > m) continue;
			int tc = t[p - i + 1];
			pii x = hs.getH(i, i + m - 1);
			if (ht[tc] != hs.getH(i, i + m - 1))
				ans[i] = false;
		}
	}
	for (int i = 1; i + m - 1 <= n; i++) 
		if (ans[i]) tmp.push_back(i);
	printf("%d\n", (int)tmp.size());
	for (int i = 0; i < tmp.size(); i++)
		printf("%d%c", tmp[i], i == tmp.size() - 1 ? '\n' : ' ');
}/*
abacabadabacaba
love
aba
*/
