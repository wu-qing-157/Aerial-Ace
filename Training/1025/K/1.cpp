#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

const int N = 5e3 + 10;
int n, a[N], b[N], c[N];
std::multiset<int> sa, sb;
std::vector<int> vec;

int calc_target() {
    int ret = 0;
    for (auto it1 = sa.begin(), it2 = sb.begin(); it1 != sa.end(); it1++, it2++) {
        while (it2 != sb.end() && *it2 <= *it1) it2++;
        if (it2 == sb.end()) break;
        else ret++;
    }
    return ret;
}

int check(int x) {
    sb.erase(sb.find(x));
    int ret = calc_target();
    sb.insert(x);
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), sa.insert(a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", b + i), sb.insert(b[i]);
    for (int i = 1; i <= n; i++) {
        int target = calc_target();
        sa.erase(sa.find(a[i]));
        vec.clear();
        for (int i : sb) vec.push_back(i);
        auto it = std::upper_bound(vec.begin(), vec.end(), a[i]);
        if (it != vec.end() && check(*it) + 1 == target) {
            int l = int(it - vec.begin()), r = int(vec.size() - 1);
            while (l < r) {
                int m = (l + r + 1) >> 1;
                if (check(vec[m]) + 1 == target)
                    l = m;
                else
                    r = m - 1;
            }
            sb.erase(sb.find(c[i] = vec[l]));
        } else {
            int l = 0, r = int(it - vec.begin() - 1);
            while (l < r) {
                int m = (l + r + 1) >> 1;
                if (check(vec[m]) == target)
                    l = m;
                else
                    r = m - 1;
            }
            sb.erase(sb.find(c[i] = vec[l]));
        }
    }
    for (int i = 1; i <= n; i++) printf("%d%c", c[i], " \n"[i == n]);
    return 0;
}
