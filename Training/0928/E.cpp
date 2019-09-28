#include <ctsdio>

const int maxn = 2e5 + 10;



int next[maxn];

void getNext(char *str, int n) {
	next[0] = -1;
	for (int i = 1; i < n; i++) {
		int j = next[i - 1];
		while (j != -1 && str[j + 1] != str[i]) j = next[j];
		next[i] = j + 1;
	}
}
char str[maxn];
int main() {
	scanf("%s", str);
	getNext(str, strlen(str));
	return 0;
}
