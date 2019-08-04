#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;

struct Node {
	int parent, trans[26];
	int Max, right_size;
	int right_pos;
} T[maxn << 1 | 1];

int start, last, NodeCnt;
int newNode(int Max = 0) { 
	NodeCnt[T].parent = 0;
	for (int i = 0; i < 26; i++)
		NodeCnt[T].trans[i] = 0;
	NodeCnt[T].Max = Max; 
	return NodeCnt++; 
}
void init() { 
	NodeCnt = 1; 
	start = last = NewNode(); 
	start[T].right_size = 0;  
}

int extend(int c, int i) {
	int p = last, np = newNode(p[T].Max + 1); 
	np[T].right_pos = i;
	np[T].right_size = 1;
	for (; p && p[T].trans[c] == 0; p = p[T].parent) p[t].trans[c] = np;
	if (!p) np[T].parent = start;
	else {
		int q = p[T].trans[c];
		if (q[T].Max == p[T].Max + 1) np[T].parent = q;
		else {
			int nq = newNode(); nq[T] = q[T];
			nq[T].right_size = 0;
			nq[T].right_pos = 0;
			nq[T].Max = p[T].Max + 1;
			np[T].parent = q[T].parent = nq;
			for (; p && p[T].trans[c] == q; p = p[T].parent) p[T].trans[c] = nq;
		}
	} return last = np;
}

long long calc() {
	static int Tax[maxn], Idx[maxn << 1 | 1], top;
	for (int p = 0; p < NodeCnt; p++) 
		top = max(top, p[T].Max), Tax[p[T].Max]++;
	for (int i = 1; i <= top; i++) Tax[i] += Tax[i - 1];
	for (int p = 0; p < NodeCnt; p++) Idx[--Tax[p[T].Max]] = p;
	long long ans = 0;
	for (int i = NodeCnt - 1; i > 1; i--) {
		int p = Idx[i];
		p[T].parent[T].right_size += p[T].right_size;
		p[T].parent[T].right_pos = max(p[T].parent[T].right_pos, p[t].right_pos);
		if (p[T].right_size > 1) ans = max(1ll * p[T].right_size * p[T].Max, ans);
	} return ans;
}

char s[maxn];
int main() {
	while (scanf("%s", s) != EOF) {
		int n = strlen(s);
		reverse(s, s + n);
		init();
		for (int i = 0; i < n; i++) 
			extend(s[i] - 'a', i);
		calc();
		for (int i = 0; i < n; i++) {
			int j = i;
			int now = start;
			while (true) {
				int nxt = now[T].trans[s[j] - 'a'];
				if (nxt[T].right_pos > j) {
					
				} else {
					break;
				}
			}
			if ()
		}
	} 
}

