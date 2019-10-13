#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e6 + 10;
int n;
std::vector<int> ch[N], ans;

void dfs(int cur, int v) {
    if (ch[cur].size() == 0) ans.push_back(v);
    else if (ch[cur].size() == 1) dfs(ch[cur].front(), v + 1);
    else for (int to : ch[cur]) dfs(to, 1);
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ans.clear();
        for (int i = 1; i <= n; i++) ch[i].clear();
        for (int i = 2; i <= n; i++) {
            static int fa;
            scanf("%d", &fa);
            ch[fa].push_back(i);
        }
        dfs(1, 1);
        bool f1 = false, f2 = true;
        for (int i : ans) {
            if (i == 1) f1 = true;
            if (i % 2 == 1) f2 = false;
        }
        puts(f1 || !f2 ? "Takeru" : "Meiya");
    }
    return 0;
}
