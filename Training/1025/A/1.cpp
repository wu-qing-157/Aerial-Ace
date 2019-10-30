#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

const int N = 20;
int n;
char s[N];
std::vector<std::pair<bool, int>> v0, v;

void decode(const char *s, std::vector<std::pair<bool, int>> &v) {
    v.clear();
    int n = int(strlen(s));
    for (int i = 0; i < n; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z') v.emplace_back(1, s[i]);
        else {
            int cur = 0;
            for (int j = i; true; j++) {
                if (j == n || s[j] >= 'A' && s[j] <= 'Z' || s[j] >= 'a' && s[j] <= 'z') {
                    v.emplace_back(0, cur);
                    i = j - 1;
                    break;
                }
                (cur *= 10) += s[j] - '0';
            }
        }
    }
}

int main() {
    scanf("%d%s", &n, s);
    decode(s, v0);
    while (n--) {
        scanf("%s", s);
        decode(s, v);
        if (v < v0) puts("-");
        else puts("+");
    }
    return 0;
}
