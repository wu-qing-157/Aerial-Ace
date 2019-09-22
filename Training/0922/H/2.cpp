#include <cstdint>
#include <cstdio>
#include <queue>

const int N = 1e5 + 10;
int n, a[N], b[N], op, cur;
int64_t las;
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q1, a1, q2, a2;
std::priority_queue<std::pair<int, int>> q3, a3, q4, a4, q5, a5;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        las = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d%d", a + i, b + i);
        while (!q1.empty()) q1.pop();
        while (!a1.empty()) q1.pop();
        while (!q2.empty()) q2.pop();
        while (!a2.empty()) q2.pop();
        while (!q3.empty()) q3.pop();
        while (!a3.empty()) a3.pop();
        while (!q4.empty()) q4.pop();
        while (!a4.empty()) a4.pop();
        while (!q5.empty()) q5.pop();
        while (!a5.empty()) a5.pop();
        for (int i = 0; i < n; i++) q3.emplace(a[i], i), q5.emplace(a[i] + b[i], i);
        for (int k = 1; k <= 2 * n; k++) {
            cur = INT32_MIN;
            if (!q3.empty()) if (cur < q3.top().first) cur = q3.top().first, op = 1;
            if (!q4.empty()) if (cur < q4.top().first) cur = q4.top().first, op = 2;
            if (!q1.empty() && !q5.empty()) if (cur < q5.top().first - q1.top().first) cur = q5.top().first - q1.top().first, op = 3;
            if (!q2.empty() && !q5.empty()) if (cur < q5.top().first - q2.top().first) cur = q5.top().first - q2.top().first, op = 4;
            int id1, id2;
            if (op == 1) {
                id1 = q3.top().second; q3.pop();
                while (!a3.empty() && a3.top() == q3.top()) a3.pop(), q3.pop();
                a5.emplace(a[id1] + b[id1], id1);
                while (!a5.empty() && a5.top() == q5.top()) a5.pop(), q5.pop();
                q2.emplace(a[id1], id1);
                q4.emplace(b[id1], id1);
            } else if (op == 2) {
                id1 = q4.top().second; q4.pop();
                while (!a4.empty() && a4.top() == q4.top()) a4.pop(), q4.pop();
                a2.emplace(a[id1], id1);
                while (!a2.empty() && a2.top() == q2.top()) a2.pop(), q2.pop();
                q1.emplace(b[id1], id1);
            } else if (op == 3) {
                id1 = q5.top().second; q5.pop();
                while (!a5.empty() && a5.top() == q5.top()) a5.pop(), q5.pop();
                id2 = q1.top().second; q1.pop();
                while (!a1.empty() && a1.top() == q1.top()) a1.pop(), q1.pop();
                a3.emplace(a[id1], id1);
                while (!a3.empty() && a3.top() == q3.top()) a3.pop(), q3.pop();
                q1.emplace(b[id1], id1);
                q2.emplace(a[id2], id2);
                q4.emplace(b[id2], id2);
            } else {
                id1 = q5.top().second; q5.pop();
                while (!a5.empty() && a5.top() == q5.top()) a5.pop(), q5.pop();
                id2 = q2.top().second; q2.pop();
                while (!a2.empty() && a2.top() == q2.top()) a2.pop(), q2.pop();
                a3.emplace(a[id1], id1);
                while (!a3.empty() && a3.top() == q3.top()) a3.pop(), q3.pop();
                a4.emplace(b[id2], id2);
                while (!a4.empty() && a4.top() == q4.top()) a4.pop(), q4.pop();
                q1.emplace(b[id1], id1);
                q3.emplace(a[id2], id2);
                q5.emplace(a[id2] + b[id2], id2);
            }
            las += cur;
            printf("%lld%c", las, " \n"[k == 2 * n]);
        }
    }
    return 0;
}
