#include <cstdio>
#include <queue>

const int N = 50;
int d[N][N];
std::queue<std::pair<std::pair<int, int>, int>> q;

void fill(int i, int j, int v) {
    if (d[i][j] == 0) {
        d[i][j] = v;
        q.emplace(std::make_pair(i, j), v);
    }
}

int main() {
    d[25][25] = 1, q.emplace(std::make_pair(25, 25), 1);
    for (int n = 1; n <= 10; n++) {
        int cnt = 0;
        while (q.front().second == n) {
            auto p = q.front().first;
            q.pop();
            fill(p.first + 2, p.second + 1, n + 1);
            fill(p.first + 2, p.second - 1, n + 1);
            fill(p.first + 1, p.second + 2, n + 1);
            fill(p.first + 1, p.second - 2, n + 1);
            fill(p.first - 1, p.second + 2, n + 1);
            fill(p.first - 1, p.second - 2, n + 1);
            fill(p.first - 2, p.second + 1, n + 1);
            fill(p.first - 2, p.second - 1, n + 1);
        }
        for (int i = 0; i < N; i++)//, puts(""))
            for (int j = 0; j < N; j++) {
                if (d[i][j]) {
                    //putchar('+');
                    cnt++;
                } else {
                    //putchar(' ');
                }
            }
        printf("%d %d\n", n, cnt);
    }
    return 0;
}
