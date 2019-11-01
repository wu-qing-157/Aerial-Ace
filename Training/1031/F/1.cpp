#include <cassert>
#include <cstdio>
#include <cstring>
#include <set>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

const int N = 120;
const std::string lambda = "lambda";
char s[N];
int n, br[N];
std::set<std::string> ans;
std::vector<std::string> a;

bool is_char(char c) {
    return c == '-' || c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void tokenize() {
    a.clear();
    for (int i = 0; i < n; ) {
        if (s[i] == '(') {
            a.push_back("(");
            i++;
        } else if (s[i] == ')') {
            a.push_back(")");
            i++;
        } else if (is_char(s[i])) {
            a.emplace_back(s + i, 1);
            while (is_char(s[++i])) a.back() += s[i];
        } else {
            i++;
        }
    }
}

void process(const std::unordered_set<std::string> &lim, int l, int r) {
    if (a[l] == "(") {
        assert(a[r - 1] == ")");
        if (a[l + 1] == lambda) {
            assert(a[l + 2] == "(");
            assert(a[l + 3] != lambda);
            auto next_lim = lim; next_lim.insert(a[l + 3]);
            assert(a[l + 4] == ")");
            process(next_lim, l + 5, r - 1);
        } else {
            if (a[l + 1] == "(") {
                int mid = br[l + 1] + 1;
                process(lim, l + 1, mid);
                process(lim, mid, r - 1);
            } else {
                process(lim, l + 1, l + 2);
                process(lim, l + 2, r - 1);
            }
        }
    } else {
        assert(r - l == 1);
        if (!lim.count(a[l])) ans.insert(a[l]);
    }
}

int main() {
    static int T;
    scanf("%d", &T);
    fgets(s, N, stdin);
    for (int cas = 1; cas <= T; cas++) {
        ans.clear();

        fgets(s, N, stdin);
        n = int(strlen(s));
        tokenize();
        n = int(a.size());

        static std::stack<int> stack;
        for (int i = 0; i < n; i++) {
            if (a[i] == "(") stack.push(i);
            else if (a[i] == ")") br[stack.top()] = i, stack.pop();
        }

        process(std::unordered_set<std::string>(), 0, n);

        printf("Case #%d:", cas);
        for (auto s : ans)
            printf(" %s", s.c_str());
        puts("");
    }
    return 0;
}
