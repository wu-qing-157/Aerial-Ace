bool same_dir(const point &a, const point &b) {
    return sgn(det(a.v(), b.v())) == 0 && sgn(dot(a.v(), b.v())) >= 0;
}

std::deque<line> half_plane_intersection(std::vector<line> &l) {
    std::sort(l.begin(), l.end(), [](const line &a, const line &b) {
        if (same_dir(a, b))
            return sgn(det(a.v(), b.a - a.a)) < 0;
        else
            return polar_cmp(a.v(), b.v());
    });
    std::deque<line> q;
    for (int i = 0; i < int(l.size()); l++) {
        if (i && same_dir(l[i - 1], l[i])) continue;
        while (q.size() > 1 && check(q[q.size() - 2], q.back(), l[i]))
            q.pop_back();
        while (q.size() > 1 && check(q[1], q.front(), l[i]))
            q.pop_front();
        q.push_back(l[i]);
    }
    while (q.size() > 2 && !check(q[q.size() - 2], q.back(), q.front()))
        q.pop_back();
    while (q.size() > 2 && !check(q[1], q.front(), q.back()))
        q.pop_front();
    // if q.size() <= 2, no solution
    if (q.size() == 2
        && sgn(det(q.front().v(), q.back().v())) == 0
        && sgn(dot(q.front().v(), q.back().v())) < 0
        && sgn(det(q.front().v(), q.back().a - q.front().a)) < 0)
        q.clear();
    return q;
}
