int n;
circle a[N];
number ans[N];
std::pair<number, int> op[N << 1];

number circle_integral(const circle &x, double s, double t) {
    return x.r * (x.r * (t - s)
                  - x.o.y * (std::cos(t) - std::cos(s))
                  + x.o.x * (std::sin(t) - std::sin(s)));
}

void circle_union() {
    // remove circle with r = 0
    for (int i = 1; i <= n; i++) if (sgn(a[i].r) <= 0) std::swap(a[i], a[n--]);
    // remove coincident circle
    std::sort(a + 1, a + n + 1, [](const circle &a, const circle &b) {
        if (sgn(a.o.x) != sgn(b.o.x)) return a.o.x < b.o.x;
        if (sgn(a.o.y) != sgn(b.o.y)) return a.o.y < b.o.y;
        return cmp(a.r, b.r) < 0;
    });
    n = int(std::unique(a + 1, a + n + 1) - a - 1);
    for (int i = 1; i <= n; i++) {
        int cnt = 0, opcnt = 0;
        for (int j = 1; j <= n; j++) if (i != j) {
            point delta = a[j].o - a[i].o;
            number d = delta.len();
            if (cmp(d, a[i].r + a[j].r) >= 0) continue;
            if (cmp(d + a[j].r, a[i].r) <= 0) continue;
            if (cmp(d + a[i].r, a[j].r) <= 0) {
                // if only k = 1 needed, just continue@i
                cnt++;
                continue;
            }
            number t0 = delta.angle();
            number t1 = _acos((a[i].r * a[i].r + d * d - a[j].r * a[j].r) / (2 * a[i].r * d));
            number l = t0 - t1, r = t0 + t1;
            if (l < -pi) l += 2 * pi, cnt++;
            if (r > pi) r -= 2 * pi, cnt++;
            op[++opcnt] = {l, 1};
            op[++opcnt] = {r, -1};
        }
        op[0] = {-pi, 0}, op[++opcnt] = {pi, 0};
        std::sort(op + 1, op + opcnt);
        for (int j = 1; j <= opcnt; cnt += op[j++].second)
            ans[cnt + 1] += circle_integral(a[i], op[j - 1].first, op[j].first);
    }
    for (int i = 1; i <= n; i++) ans[i] /= 2;
}
