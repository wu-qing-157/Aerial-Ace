#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

char s[maxn];

int main() {
	cout << 100 << endl;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 1e5; j++)
			putchar(rand() % 10 + '0');
		puts("");
		for (int j = 0; j < 1e5; j++)
			putchar(rand() % 10 + '0');
		puts("");
		for (int j = 0; j < 1e5; j++)
			putchar(rand() % 10 + '0');
		puts("");
	}
}
