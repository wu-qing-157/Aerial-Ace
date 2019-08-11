#include <cstdio>
#include <utility>

const int N = 3e5 + 10;
int n;
std::pair<int, int> a[N];

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d%d", &a[i].first, &a[i].second);
        for (int i = 0; i < n; i++) sum.first += a[i].first, sum.second += a[i].second;
        if (sum.first < sum.second) {
            for (int i = 0; i < n; i++) std::swap(a[i].first, a[i].second);
            std::swap(sum.first, sum.second);
        }
        std::sort(a, a + n, [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
                return a.first * b.second < a.second * b.first;
        });
        for (int i = 0; i < n; i++) {
            if (a[i].first < a[i].second) continue;
            if (sum.first - a[i].first <= sum.second + a[i].second) {
                 
            } else {
                sum.first -= a[i].first;
                sum.second += a[i].second;
            }
        }
    }
    return 0;
}
