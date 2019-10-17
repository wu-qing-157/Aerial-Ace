#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

const int N = 110, M = 1100;
int n, m, cnt[N], ans;
bool need[N][M];
std::pair<int, int> ab[N];

void dfs(int cur) {
    if (cur > m) {
        int cans = 0;
        for (int i = 1; i <= n; i++)
            if (cnt[i] == 0)
                cans++;
        //printf("result    ");
        //for (int i = 1; i <= n; i++)
            //printf("%d%c", cnt[i], " \n"[i == n]);
        ans = std::max(ans, cans);
        return;
    }
    dfs(cur + 1);
    bool n1, n2;
    for (int i = 1; i <= n; i++) {
        if (!(n1 = need[i][ab[cur].first]) & !(n2 = need[i][ab[cur].second]))
            continue;
        need[i][ab[cur].first] = need[i][ab[cur].second] = false;
        cnt[i] -= n1 + n2;
        //printf("in  %d -> %d\n", cur, i);
        dfs(cur + 1);
        //printf("out %d -> %d\n", cur, i);
        need[i][ab[cur].first] = n1, need[i][ab[cur].second] = n2;
        cnt[i] += n1 + n2;
    }
}

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d", &n, &m);
        memset(need, 0, sizeof need);
        ans = 0;
        for (int i = 1; i <= n; i++) {
            static int cur;
            scanf("%d", cnt + i);
            for (int j = 1; j <= cnt[i]; j++)
                scanf("%d", &cur), need[i][cur] = true;
        }
        for (int i = 1; i <= m; i++) {
            static int num;
            scanf("%d", &num);
            if (num == 1)
                scanf("%d", &ab[i].first), ab[i].second = 0;
            else
                scanf("%d%d", &ab[i].first, &ab[i].second);
        }
        dfs(1);
        printf("Case #%d: %d\n", cas, ans);
    }
    return 0;
}
