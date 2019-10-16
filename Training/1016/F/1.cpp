#include <cassert>
#include <cstdio>
#include <vector>

const int N = 20;
int n, m, a[N], csize;
std::vector<std::vector<double>> A;
std::vector<double> b, c;

const double eps = 1e-8;
std::vector<double> simplex() {
    int n = int(A.size()), m = int(A[0].size()) + 1, r = n, s = m - 1;
    std::vector<std::vector<double>> D(n + 2, std::vector<double>(m + 1));
    std::vector<int> ix(n + m);
    for (int i = 0; i < n + m; i++) ix[i] = i;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) D[i][j] = -A[i][j];
        D[i][m - 1] = 1;
        D[i][m] = b[i];
        if (D[r][m] > D[i][m]) r = i;
    }
    for (int j = 0; j < m - 1; j++) D[n][j] = c[j];
    D[n + 1][m - 1] = -1;
    for (double d; true; ) {
        if (r < n) {
            std::swap(ix[s], ix[r + m]);
            D[r][s] = 1. / D[r][s];
            for (int j = 0; j <= m; j++) if (j != s) D[r][j] *= -D[r][s];
            for (int i = 0; i <= n + 1; i++) if (i != r) {
                for (int j = 0; j <= m; j++)
                    if (j != s) D[i][j] += D[r][j] * D[i][s];
                D[i][s] *= D[r][s];
            }
        }
        r = s = -1;
        for (int j = 0; j < m; j++) if (s < 0 || ix[s] > ix[j])
            if (D[n + 1][j] > eps || D[n + 1][j] > -eps && D[n][j] > eps)
                s = j;
        if (s < 0) break;
        for (int i = 0; i < n; i++) if (D[i][s] < -eps)
            if (r < 0 || (d = D[r][m] / D[r][s] - D[i][m] / D[i][s]) < eps || d < eps && ix[r + m] > ix[i + m])
                r = i;
        if (r < 0) assert(false);
    }
    if (D[n + 1][m] < -eps) assert(false);
    std::vector<double> x(m - 1);
    for (int i = m; i < n + m; i++)
        if (ix[i] < m - 1)
            x[ix[i]] = D[i - m][m];
    return x;
}

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        csize = 0;
        A.clear();
        for (int i = 0; i < n; i++) A.emplace_back();
        b.resize(n);
        for (int i = 0; i < (1 << n); i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) if (i & (1 << j)) sum += a[j];
            if (sum > m) continue;
            ++csize;
            for (int j = 0; j < n; j++) A[j].push_back((i & (1 << j)) > 0);
        }
        for (int j = 0; j < n; j++) A[j].push_back(-1), b[j] = 0;
        A.emplace_back(csize);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < csize; j++)
                A.back()[j] -= A[i][j];
        A.back().push_back(n);
        b.push_back(0);
        std::vector<double> f1, f2;
        for (int i = 0; i < csize; i++)
            f1.push_back(1), f2.push_back(-1);
        f1.push_back(0), f2.push_back(0);
        A.emplace_back(std::move(f1));
        A.emplace_back(std::move(f2));
        b.push_back(1);
        b.push_back(-1);
        c.clear();
        c.resize(csize);
        c.push_back(1);

        auto ret = simplex();
        printf("Case #%d: %.10f\n", cas, ret[csize]);
    }
    return 0;
}
