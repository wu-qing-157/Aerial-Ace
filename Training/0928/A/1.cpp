#include <cstdio>
#include <set>
#include <list>

const int N = 1e5 + 10;

int n, k, tar;
std::multiset<int> to[N];
std::set<int> set;
std::list<int> ans;
std::list<int>::iterator it[N];

void ln(int u, int v) {
    to[u].insert(v);
    to[v].insert(u);
}

void rm(int u, int v) {
    to[u].erase(to[u].find(v));
    to[v].erase(to[v].find(u));
}

void find(int start, int cur, std::list<int>::iterator lit) {
    ans.insert(++lit, cur);
    it[cur] = --lit;
    if (start == cur) {
        if (to[cur].empty()) set.erase(cur);
        else set.insert(cur);
        return;
    }
    int nxt = *to[cur].begin();
    rm(cur, nxt);
    if (to[cur].empty()) set.erase(cur);
    else set.insert(cur);
    find(start, nxt, lit);
}

int main() {
    freopen("achromatic.in", "r", stdin);
    freopen("achromatic.out", "w", stdout);
    scanf("%d", &n);
    for (k = 1; true; k++) {
        tar = k / 2 * k;
        if (n < tar) {
            --k;
            tar = k / 2 * k;
            if (k & 1 && n - tar == 1) --k;
            break;
        }
    }
    tar = 0;
    printf("%d\n", k);
    for (int i = 1; i <= k; i++)
        for (int j = i + 1; j <= k; j++)
            ln(i, j), tar++;
    if (k & 1) {
        while (tar < n - 1)
            ln(1, 2), ln(1, 2), tar += 2;
        if (tar == n - 1)
            rm(1, 2), ln(1, 3), ln(2, 3), tar++;
    } else {
        for (int i = 1; i <= k; i += 2)
            ln(i, i + 1), tar++;
        while (tar < n - 1)
            ln(1, 2), ln(1, 2), tar += 2;
        if (tar == n - 1)
            rm(1, 2), ln(1, 3), ln(2, 3), tar++;
    }
    set.insert(1);
    ans.push_back(1);
    it[1] = ans.begin();
    while (!set.empty()) {
        int start = *set.begin();
        int v = *to[start].begin();
        rm(start, v);
        find(start, v, it[start]);
    }
    ans.pop_back();
    for (auto it = ans.begin(); it != ans.end(); ) {
        printf("%d", *it);
        putchar(" \n"[++it == ans.end()]);
    }
    return 0;
}
