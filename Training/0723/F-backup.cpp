#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5 + 10;

bool match[maxn];

struct KMP {
	int fail[maxn];
	void build(char *t, char c, int m) {
		for (int i = 2, j = 0; i <= m; i++) {
			for (; j && (t[j + 1] == c) != (t[i] == c); j = fail[j]);
			(t[i] == c) == (t[j + 1] == c) ? ++j : 0;
			fail[i] = j;
		}
	}
	void work(char *s, char *t, char sc, char tc, int n, int m) {
		for (int i = 1, j = 0; i <= n; i++) {
			for (; j && (t[j + 1] == tc) != (s[i] == sc); j = fail[j]);
			(s[i] == sc) == (t[j + 1] == tc) ? ++j : 0;
			if (j == m) {
				cout << i - m + 1 << ' ';
				match[i - m + 1] = true;
				j = fail[j];
			}
		}
		cout << endl;
	}
} t01[100];

char s[maxn], t[maxn];
int nxt[maxn][100];
int pos[100];

bool ans[maxn];
vector<int>tmp;

int main() {
	scanf("%s%s", s, t);
	int n = strlen(s);
	int m = strlen(t);
	
	for (int i = 0; i < n; i++) s[i] -= 32;
	for (int i = 0; i < m; i++) t[i] -= 32;
	
	for (int i = n - 1; i >= 0; i--) {
		pos[s[i]] = i;
		for (int j = 1; j < 100; j++) 
			nxt[i][j] = pos[j];
	}

	for (int j = 1; j < 100; j++) t01[j].build(t, j, m);
	
	memset(ans, true, sizeof ans);
	
	for (int sc = 1; sc < 100; sc++) {

		}
		for (int i = 1; i + m - 1 <= n; i++)
			ans[i] &= match[i], match[i] = false;
	}
	int cnt = 0;
	for (int i = 1; i + m - 1 <= n; i++)
		if (ans[i]) cnt++, tmp.push_back(i);
	
	printf("%d\n", cnt);
	for (int i = 0; i < tmp.size(); i++)
		printf("%d%c", tmp[i], i == tmp.size() - 1 ? '\n' : ' ');
}
/*
abacabadabacaba
aba

*/
