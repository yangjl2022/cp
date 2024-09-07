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

struct Tarjan {
    int n, dn, rt;
    vector<vector<int>> g;
    vector<vector<int>> vcc;
    vector<int> dfn, low, cut;
    stack<int> st;
    Tarjan(int n) :n(n), dn(0), g(n), dfn(n), low(n), cut(n) { }
    void addEdge(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void tarjan(int u) {
        dfn[u] = low[u] = ++dn;
        st.push(u);
        int chd = 0;
        for(int v : g[u]) {
            if(!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
                if(dfn[u] <= low[v]) {
                    if(u != rt || ++chd > 1) cut[u] = 1;// 割点
                    vcc.push_back({ u });
                    for(int x = -1; x != v; st.pop())
                        vcc.back().push_back(x = st.top());
                }
            }
            else {// 返祖边
                // 求vcc判不判回头边无所谓
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(u == rt && chd == 0)// 孤点
            vcc.push_back({ u });
    }
    void converge() {
        for(rt = 0; rt < n; ++rt)
            if(!dfn[rt]) tarjan(rt);
    }
    // 圆方树/森林
    auto newForest() {
        vector<vector<int>> tr(n + vcc.size());// 注意孤点影响
        for(int i = 0; i < vcc.size(); ++i)
            for(int x : vcc[i]) {
                tr[n + i].push_back(x);// 方点向圆点连边
                tr[x].push_back(n + i);
            }
        return tr;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    assert(2 <= n and n <= 1000);
    assert(2 <= m and m <= 1000);
    Tarjan tar(n * m);
    vector a(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> a[i][j];
            assert(-1 <= a[i][j] and a[i][j] <= int(1e9));
            if(i and a[i - 1][j] != -1 and a[i][j] != -1) {
                tar.addEdge((i - 1) * m + j, i * m + j);
            }
            if(j and a[i][j - 1] != -1 and a[i][j] != -1) {
                tar.addEdge(i * m + j - 1, i * m + j);
            }
        }
    }

    int sz = n * m;
    tar.converge();
    auto tr = tar.newForest();

    vector<int> vis(tar.vcc.size());
    function<bool(int, int)> dfs = [&](int u, int fa) {
        if(u >= sz) {
            vis[u - sz] = 1;
        }
        if(u == sz - 1) {
            return true;
        }
        for(int v : tr[u]) {
            if(v == fa) {
                continue;
            }
            if(dfs(v, u)) {
                return true;
            }
        }
        if(u >= sz) {
            vis[u - sz] = 0;
        }
        return false;
    };

    if(!dfs(0, -1)) {
        cout << "0";
        exit(0);
    }

    ll ans = 0;
    for(int i = 0; i < sz; ++i) {
        for(int v : tr[i]) {
            if(vis[v - sz]) {
                ans += a[i / m][i % m];
                break;
            }
        }
    }
    cout << ans;
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/87652/F
根据连通性建图
题目要求的就是所有s->t的简单路径的并集的点权和
圆方树有以下结论：
考虑两圆点在圆方树上的路径，与路径上经过的方点相邻的圆点的集合，就等于原图中两点简单路径上的点集。

*/