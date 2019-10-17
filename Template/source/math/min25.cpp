namespace min25 {
    const int maxq = 2e5 + 10;
    const int mod = 1e9 + 7, inv6 = 166666668, inv2 = 500000004, inv3 = 333333336;
    int P[maxq], cnt; 
    bool isNotP[maxq];

    inline ll f1(ll pk) { pk %= mod; return pk % mod; }
    inline ll f2(ll pk) { pk %= mod; return pk * pk % mod; }
    inline ll f(ll pk) { return (f2(pk) - f1(pk) + mod) % mod; }

    inline ll sf1(ll pk) { pk %= mod; return (pk + 1) % mod * pk % mod * inv2 % mod; }
    inline ll sf2(ll pk) { pk %= mod; return pk % mod * (pk + 1) % mod * (2 * pk + 1) % mod * inv6 % mod; }
    inline ll sf(ll pk) { pk %= mod; return (sf2(pk) - sf1(pk) + mod) % mod; }
    int sfp1[maxq], sfp2[maxq];

    void sieve(int n) {
        for (int i = 2; i <= n; i++) {
            if (!isNotP[i]) {
                P[++cnt] = i;
                sfp1[cnt] = (sfp1[cnt - 1] + f1(i)) % mod;
                sfp2[cnt] = (sfp2[cnt - 1] + f2(i)) % mod;
            }
            for (int j = 1; j <= cnt && i * P[j] <= n; j++) {
                isNotP[i * P[j]] = true;
                if (i % P[j] == 0) break;
            }
        }
    }

    ll w[maxq];
    int id1[maxq], id2[maxq]; 
    ll N;
    int SQRT;
    int id(ll x) {
        return x <= SQRT ? id1[x] : id2[N / x];
    }
    int g1[maxq], g2[maxq];

    int s(ll n, int x) {
        if (P[x] >= n) return 0; 
        int k = id(n);
        int ans = (0ll + g2[k] - g1[k] + sfp1[x] - sfp2[x]) % mod;
        for (int k = x + 1; k <= cnt && 1ll * P[k] * P[k] <= n; k++) {
            ll Pe = P[k];
            for (int e = 1; Pe <= n; e++, Pe *= P[k]) 
                (ans += f(Pe) * (s(n / Pe, k) + (e != 1)) % mod) %= mod;
        }
        return ans < 0 ? ans + mod : ans;
    }

    int solve(ll n) {
        N = n; SQRT = sqrt(n); sieve(SQRT);
        int m = 0;

        for (ll i = 1, j; i <= n; i = j + 1) {
            j = n / (n / i); w[++m] = n / i; 
            g1[m] = (sf1(w[m]) - f1(1) + mod) % mod;
            g2[m] = (sf2(w[m]) - f2(1) + mod) % mod;
            if (w[m] <= SQRT) id1[w[m]] = m; else id2[n / w[m]] = m;
        }

        for (int j = 1; j <= cnt; j++) 
            for (int i = 1; i <= m && 1ll * P[j] * P[j] <= w[i]; i++) {
                int k = id(w[i] / P[j]);
                (g1[i] -= f1(P[j]) * (g1[k] - sfp1[j - 1]) % mod) %= mod; 
                (g2[i] -= f2(P[j]) * (g2[k] - sfp2[j - 1]) % mod) %= mod; 
                g1[i] < 0 ? g1[i] += mod : 0; g2[i] < 0 ? g2[i] += mod : 0;
            }
        return (s(n, 0) + 1) % mod; // f(1) = 1
    }
    
}