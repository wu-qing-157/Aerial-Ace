#include <cstdio>
#include <deque>
#include <utility>

int n, m;
std::deque<std::pair<int, int>> ans;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        // printf("start %d %d\n", n, m);
        if (n == 1) {
            if (m == 1) {
                puts("YES");
                puts("1 1");
            } else {
                puts("NO");
            }
        } else if (n == 2) {
            if (m <= 2) {
                puts("NO");
            } else {
                puts("YES");
                ans.clear();
                ans.emplace_back(2, 3);
                ans.emplace_back(1, 1);
                ans.emplace_back(2, 2);
                ans.emplace_back(1, 3);
                ans.emplace_back(2, 1);
                ans.emplace_back(1, 2);
                for (int i = 4; i <= m; i++)
                    ans.emplace_back(i & 1 ? 1 : 2, i);
                for (int i = 4; i <= m; i++)
                    ans.emplace_front(i & 1 ? 2 : 1, i);
                for (auto p : ans)
                    printf("%d %d\n", p.first, p.second);
            }
        } else {
            if (m == 1) {
                puts("NO");
            } else if (m == 2) {
                puts("YES");
                ans.clear();
                ans.emplace_back(3, 2);
                ans.emplace_back(1, 1);
                ans.emplace_back(2, 2);
                ans.emplace_back(3, 1);
                ans.emplace_back(1, 2);
                ans.emplace_back(2, 1);
                for (int i = 4; i <= n; i++)
                    ans.emplace_back(i, i & 1 ? 1 : 2);
                for (int i = 4; i <= n; i++)
                    ans.emplace_front(i, i & 1 ? 2 : 1);
                for (auto p : ans)
                    printf("%d %d\n", p.first, p.second);
            } else {
                puts("YES");
                ans.clear();
                for (int i = 1; i <= n; i++) {
                    if (i & 1) {
                        for (int j = 1; j <= m; j += 2)
                            ans.emplace_back(i, j);
                    } else {
                        for (int j = m & 1 ? m - 1 : m; j > 0; j -= 2)
                            ans.emplace_back(i, j);
                    }
                }
                ans.emplace_front(3, 2);
                ans.emplace_front(2, 1);
                for (int j = 2; j <= m; j += 2)
                    ans.emplace_front(1, j);
                for (int j = m & 1 ? m : m - 1; j >= 3; j -= 2)
                    ans.emplace_front(2, j);
                for (int j = 4; j <= m; j += 2)
                    ans.emplace_front(3, j);
                for (int i = 4; i <= n; i++) {
                    if (i & 1) {
                        for (int j = 2; j <= m; j += 2)
                            ans.emplace_front(i, j);
                    } else {
                        for (int j = m & 1 ? m : m - 1; j > 0; j -= 2)
                            ans.emplace_front(i, j);
                    }
                }
                for (auto p : ans)
                    printf("%d %d\n", p.first, p.second);
            }
        }
    }
    return 0;
}
