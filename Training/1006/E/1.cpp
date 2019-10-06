#include <cstdint>
#include <cstdio>
#include <queue>

struct cmp1 {
    bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) const {
        return a.first == b.first ? a.second > b.second : a.first > b.first;
    }
};
struct cmp2 {
    bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) const {
        return a.second == b.second ? a.first > b.first : a.second > b.second;
    }
};

int n;
int64_t ans;
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, cmp1> setl, rml;
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, cmp2> setr, rmr;
std::priority_queue<int, std::vector<int>, std::greater<int>> chl, chr;

void insertl() {
    if (chr.empty() || setl.top().first <= setr.top().second + chr.top()) {
        auto p = setl.top();
        ans += p.first;
        rmr.push(p);
        setl.pop();
        while (!rml.empty() && setl.top() == rml.top()) setl.pop(), rml.pop();
        while (!rmr.empty() && setr.top() == rmr.top()) setr.pop(), rmr.pop();
        chl.push(p.second - p.first);
    } else {
        ans += chr.top();
        chl.push(-chr.top());
        chr.pop();
        auto p = setr.top();
        ans += p.second;
        rml.push(p);
        setr.pop();
        while (!rml.empty() && setl.top() == rml.top()) setl.pop(), rml.pop();
        while (!rmr.empty() && setr.top() == rmr.top()) setr.pop(), rmr.pop();
        chr.push(p.first - p.second);
    }
}

void insertr() {
    if (chl.empty() || setr.top().second <= setl.top().first + chl.top()) {
        auto p = setr.top();
        ans += p.second;
        rml.push(p);
        setr.pop();
        while (!rml.empty() && setl.top() == rml.top()) setl.pop(), rml.pop();
        while (!rmr.empty() && setr.top() == rmr.top()) setr.pop(), rmr.pop();
        chr.push(p.first - p.second);
    } else {
        ans += chl.top();
        chr.push(-chl.top());
        chl.pop();
        auto p = setl.top();
        ans += p.first;
        rmr.push(p);
        setl.pop();
        while (!rml.empty() && setl.top() == rml.top()) setl.pop(), rml.pop();
        while (!rmr.empty() && setr.top() == rmr.top()) setr.pop(), rmr.pop();
        chl.push(p.second - p.first);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n * 2; i++) {
        static int s, t;
        scanf("%d%d", &s, &t);
        setl.emplace(s, t);
        setr.emplace(s, t);
    }
    for (int i = 1; i <= n; i++) {
        insertl(), insertr();
        printf("%lld\n", ans);
    }
    return 0;
}
