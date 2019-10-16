#include <cmath>
#include <cstdio>
#include <vector>

struct rotate {
    int i, j;
    double th;
    rotate() {}
    rotate(int i, int j, double th) : i(i), j(j), th(th) {}
};

const int N = 1e2 + 10;
int n, m;
double a[N][N];
std::vector<rotate> rot;

void rotat(double &a, double &b, double th) {
    static double aa, bb;
    aa = a * std::cos(th) - b * std::sin(th);
    bb = a * std::sin(th) + b * std::cos(th);
    a = aa, b = bb;
}

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d", &n, &m);
        printf("Case #%d: %d\n", cas, n + 1 - m);
        rot.clear();
        for (int i = 0; i <= n; i++) for (int j = 1; j <= n; j++) a[i][j] = 0;
        for (int j = 1; j <= n; j++) scanf("%lf", a[0] + j);
        for (int i = 1; i < m; i++)
            for (int j = 1; j <= n; j++)
                scanf("%lf", a[i] + j), a[i][j] -= a[0][j];

        for (int i = 1; i <= m; i++)
            for (int j = i + 1; j <= n; j++) {
                double th = std::atan2(a[i][j], a[i][i]);
                rot.emplace_back(i, j, th);
                for (int ii = i; ii <= m; ii++)
                    rotat(a[ii][i], a[ii][j], -th);
            }

        for (int i = m; i <= n; i++) {
            double sum = 0;
            for (int j = 1; j < i - 1; j++) a[i][j] = a[i - 1][j], sum += a[i][j] * a[i][j];
            if (i > 1) a[i][i - 1] = a[i - 1][i - 1] / i, sum += a[i][i - 1] * a[i][i - 1];
            a[i][i] = std::sqrt(1 - sum);
            for (int j = i + 1; j <= n; j++) a[j][j] = 0;
        }

        for (auto it = rot.rbegin(); it != rot.rend(); it++)
            for (int i = m; i <= n; i++) rotat(a[i][it->i], a[i][it->j], it->th);

        for (int i = m; i <= n; i++) for (int j = 1; j <= n; j++)
            printf("%.15f%c", a[i][j] + a[0][j], " \n"[j == n]);
    }
    return 0;
}
