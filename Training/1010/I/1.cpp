#include <cstdint>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <initializer_list>

const int N = 1e5 + 10;
int n, add, ans, to[N][3], dp[N][3][3];
char s[N];
std::initializer_list<int> li = {0, 1, 2};

void min(int &a, int b) {
    if (a > b) a = b;
}

int main() {
    to['Y'][0] = 0, to['Y'][1] = 0, to['Y'][2] = 0;
    to['V'][0] = 0, to['V'][1] = 0, to['V'][2] = 1;
    to['G'][0] = 0, to['G'][1] = 0, to['G'][2] = 2;
    to['C'][0] = 1, to['C'][1] = 1, to['C'][2] = 1;
    to['X'][0] = 0, to['X'][1] = 1, to['X'][2] = 1;
    to['Z'][0] = 1, to['Z'][1] = 1, to['Z'][2] = 2;
    to['T'][0] = 2, to['T'][1] = 2, to['T'][2] = 2;
    to['F'][0] = 0, to['F'][1] = 2, to['F'][2] = 2;
    to['D'][0] = 1, to['D'][1] = 2, to['D'][2] = 2;
    to['B'][0] = 0, to['B'][1] = 1, to['B'][2] = 2;
    while (scanf("%s", s + 1) != EOF) {
        add = n = int(strlen(s + 1));
        n = std::unique(s + 1, s + n + 1) - (s + 1);
        for (int i = 1; i <= n; i++)
            for (int j : li) for (int k : li)
                dp[i][j][k] = INT32_MAX >> 2;
        ans = INT32_MAX >> 2;
        do dp[1][to[s[1]][1]][to[s[1]][2]] = 3;
        while (std::next_permutation(to[s[1]], to[s[1]] + 3));
        for (int i = 2; i <= n; i++) {
            do {
                for (int nj : li) for (int nk : li)
                    min(dp[i][to[s[i]][1]][to[s[i]][2]], dp[i - 1][nj][nk] + 3);
                for (int nj : li)
                    min(dp[i][to[s[i]][1]][to[s[i]][2]], dp[i - 1][nj][to[s[i]][0]] + 2);
                min(dp[i][to[s[i]][1]][to[s[i]][2]], dp[i - 1][to[s[i]][0]][to[s[i]][1]] + 1);
            } while (std::next_permutation(to[s[i]], to[s[i]] + 3));
        }
        for (int j : li) for (int k : li) min(ans, dp[n][j][k]);
        printf("%d\n", ans + add);
    }
    return 0;
}
