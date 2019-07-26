#include <bits/stdc++.h>
using namespace std;

const int maxn = 26 * 100 * 200 * 2;

int nxt[maxn][26];
int fal[maxn];
int cnt[maxn];
int cnt_ptr, root;
vector<int>id[maxn];

int newNode() {
	for (int i = 0; i < 26; i++) nxt[cnt_ptr][i] = 0;
	fal[cnt_ptr] = 0; id[cnt_ptr].clear();
	return cnt_ptr++;
}

void insert(char *s, int ID) {
	int now = root;
	for (int i = 0; s[i]; i++) {
		if (!nxt[now][s[i] - 'a'])
			nxt[now][s[i] - 'a'] = newNode();
		now = nxt[now][s[i] - 'a'];
	}
	id[now].push_back(ID);
}

queue<int>q;
void build() {
	for (int i = 0; i < 26; i++) {
		if (nxt[root][i]) q.push(nxt[root][i]);
		nxt[root][i][fal] = root;
	}
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; i++) {
			if (!nxt[u][i]) {
				nxt[u][i] = nxt[fal[u]][i];
			}
			else {
				q.push(nxt[u][i]);
				fal[nxt[u][i]] = nxt[fal[u]][i];
			}
		}
	}
}

void calc(char *t) {
	int now = root;
	for (int i = 0; t[i]; i++) {
		now = nxt[now][t[i] - 'a'];
		for (int j = now; j; j = fal[j]) {
			for (auto ID : id[j])
				cnt[ID]++;
		}
	}
}

char s[200][100];
char t[int(1e6 + 10)];
void work(int n) {
	cnt_ptr = 0;
	root = newNode();
	for (int i = 1; i <= n; i++) {
		cnt[i] = 0;
		scanf("%s", s[i]);
		insert(s[i], i);
	}
	
	scanf("%s", t);
	build();
	calc(t);
	
	int max_ans = 0;
	for (int i = 1; i <= n; i++) 
		max_ans = max(max_ans, cnt[i]);
	
	printf("%d\n", max_ans);
	for (int i = 1; i <= n; i++)
		if (max_ans == cnt[i])
			printf("%s\n", s[i]);
}

int main() {
	int n; 
	while(scanf("%d", &n) != EOF) {
		if (n == 0) break;
		work(n);
	}
	return 0;
}

/*
2
aba
bab
ababababac
6
beta
alpha
haha
delta
dede
tata
dedeltalphahahahototatalpha
2
aba
bab
ababababac
0
*/
