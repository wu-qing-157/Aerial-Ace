#include <cstdio>
#include <vector>
#include <utility>

std::vector<std::pair<int, int>> ans;
int n, k;

void solve(int n, int k) {
    if (n == 0) return;
    if (k >> (n - 1) == 0) {
        for (int i = 1; i <= n; i++)
            ans.emplace_back(n, i);
    } else {
        k -= 1 << (n - 1);
    }
    solve(n - 1, k);
}

int main() {
    scanf("%d%d", &n, &k);
    solve(n, k);
    printf("%d\n", (int) ans.size());
    for (auto p : ans) printf("%d %d\n", p.first, p.second);
    return 0;
}
