#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 10;

char h[maxn][maxn], a[maxn][maxn], tmp[maxn][maxn];

void rotate(int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			tmp[i][n - 1 - j] = h[j][i];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			h[i][j] = tmp[i][j];
}

void print(int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (h[i][j] == 'O')
				putchar(a[i][j]);			
}

int main() {
	int n;
	while (true) {
		scanf("%d", &n);
		if (n == 0) 
			break;
		for (int i = 0; i < n; i++)
			scanf("%s", h[i]);
		for (int i = 0; i < n; i++) 
			scanf("%s", a[i]);
		print(n);
		rotate(n);
		print(n);
		rotate(n);
		print(n);
		rotate(n);
		print(n);
		rotate(n);
		putchar('\n');
	}
}
