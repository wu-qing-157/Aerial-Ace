#include <cstdio>
#include <utility>
#include <vector>

const int N = 1e6 + 10;
int n, k;
char s[N], t[N];
std::vector<std::pair<char, int>> a, b;

void p(char *s, std::vector<std::pair<char, int>> &a) {
    for (int i = 0; i < n; i++) {
        if (a.empty() || a.back().first != s[i]) {
            a.emplace_back(s[i], 1);
        } else {
            if (++a.back().second == k) a.pop_back();
        }
    }
}

int main() {
    scanf("%d%d%s%s", &n, &k, s, t);
    if (k == 1) {
        puts("Yes");
    } else {
        p(s, a);
        p(t, b);
        puts(a == b ? "Yes" : "No");
    }
    return 0;
}
