#include <bits/stdc++.h>
#ifdef YJL
#include "debug.h"
#else
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x : v) is >> x;
    return is;
}

namespace tri {
    using T = int;
    constexpr int m = sizeof(T) * 8;
    vector<array<int, 2>> ch;
    vector<int> cnt;
    int idx;
    void init(int n) {
        const int SZ = n * (m + 1) + 10;
        ch.assign(SZ, array<int, 2>{});
        cnt.assign(SZ, 0);
        idx = 1;
    }
    int newNode(int from) {
        ch[idx] = ch[from];
        cnt[idx] = cnt[from];
        idx++;
        return idx - 1;
    }
    int ins(int u, T x, int v = 1) {
        int root = u = newNode(u);
        for(int i = m - 1; i >= 0; --i) {
            int w = x >> i & 1;
            ch[u][w] = newNode(ch[u][w]);
            cnt[u = ch[u][w]] += v;
        }
        return root;
    }
    // tr[u] - tr[v]
    T xorMax(int u, int v, T x) {// return max(x^y)
        T ans = 0;
        for(int i = m - 1; i >= 0; --i) {
            int w = x >> i & 1;
            if(cnt[ch[u][w ^ 1]] - cnt[ch[v][w ^ 1]]) {
                ans += (T(1) << i);
                u = ch[u][w ^ 1];
                v = ch[v][w ^ 1];
            } else {
                u = ch[u][w];
                v = ch[v][w];
            }
            if(!u) break;
        }
        return ans;
    }
    T xorMax(int u1, int v1, int u2, int v2, T x) {// return max(x^y)
        T ans = 0;
        for(int i = m - 1; i >= 0; --i) {
            int w = x >> i & 1;
            if(cnt[ch[u1][w ^ 1]] - cnt[ch[v1][w ^ 1]]
                + cnt[ch[u2][w ^ 1]] - cnt[ch[v2][w ^ 1]]) {
                ans += (T(1) << i);
                u1 = ch[u1][w ^ 1];
                v1 = ch[v1][w ^ 1];
                u2 = ch[u2][w ^ 1];
                v2 = ch[v2][w ^ 1];
            } else {
                u1 = ch[u1][w];
                v1 = ch[v1][w];
                u2 = ch[u2][w];
                v2 = ch[v2][w];
            }
            if(!u1 and !u2) break;
        }
        return ans;
    }
}// namespace tri

struct Dsu {
    vector<int> fa;
    Dsu(int n) : fa(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if(x == y) return false;
        fa[x] = y;
        return true;
    }
    int get(int x) {
        return fa[x] == x ? x : fa[x] = get(fa[x]);
    }
};

constexpr int N = 2e5 + 10;
vector<pair<int, int>> g[N];

int s, t, circle, inCir[N];
bool dfs_circle(int u, int fa) {
    // g[u].erase(remove(ALL(g[u]), fa), g[u].end());
    inCir[u] = 1;
    if(u == t) return true;
    for(auto [v, w] : g[u]) {
        if(v == fa) {
            continue;
        }
        circle ^= w;
        if(dfs_circle(v, u)) {
            return true;
        }
        circle ^= w;
    }
    inCir[u] = 0;
    return false;
}

int pre[N];
void dfs_pre(int u, int fa) {
    for(auto [v, w] : g[u]) {
        if(v == fa) {
            continue;
        }
        pre[v] = pre[u] ^ w;
        dfs_pre(v, u);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    assert(2 <= n and n <= int(2e5));
    assert(1 <= k and k < n);

    Dsu ds(n + 1);
    int huan = 0;
    for(int i = 0; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        assert(u != v);
        assert(1 <= w and w <= int(1e9));
        if(!ds.unite(u, v)) {
            huan++;
            s = u;
            t = v;
            circle = w;
            continue;
        }
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    assert(huan == 1);
    dfs_circle(s, 0);
    dfs_pre(s, 0);

    int ans = 0;
    tri::init(n + n);
    vector<int> rt(n + 1);
    for(int i = 1; i <= n; ++i) {
        rt[i] = tri::ins(rt[i - 1], pre[i], 1);
        ans = max(ans, tri::xorMax(rt[i], rt[max(0, i - k - 1)], pre[i]));
    }

    for(int u = 1; u <= n; ++u) {
        if(inCir[u]) {
            ans = max(ans, tri::xorMax(rt[u], rt[max(0, u - k - 1)], pre[u] ^ circle));
            for(auto [v, w] : g[u]) {
                if(!inCir[v]) {
                    vector<int> nodes;
                    function<void(int, int)> dfs = [&](int u, int fa) {
                        nodes.push_back(u);
                        for(auto [v, w] : g[u]) {
                            if(v != fa and !inCir[v]) {
                                dfs(v, u);
                            }
                        }
                    };

                    dfs(v, u);
                    sort(ALL(nodes));
                    int sz = nodes.size();

                    vector<int> rtv(sz + 1);
                    for(int i = 0; i < sz; ++i) {
                        rtv[i + 1] = tri::ins(rtv[i], pre[nodes[i]], -1);
                    }

                    for(int i = 0; i < sz; ++i) {
                        int u = nodes[i];
                        int v = max(0, u - k - 1);
                        int j = upper_bound(ALL(nodes), v) - nodes.begin();
                        ans = max(ans, tri::xorMax(rt[u], rt[v], rtv[i + 1], rtv[j], pre[u] ^ circle));
                    }
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85350/F

注意：https://ac.nowcoder.com/discuss/1339568?type=101&order=0&pos=1&page=0&channel=-1&source_id=1

基环树，可持久化字典树，并查集

*/