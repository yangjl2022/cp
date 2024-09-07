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
    for(auto& x:v) is>>x;
    return is;
}

struct Tarjan {
    int n,dn,bn,index;
    vector<vector<tuple<int,int,int>>> g;
    vector<vector<int>> ecc;
    vector<int> dfn,low,bel;
    stack<int> st;
    Tarjan(int n):n(n),dn(0),bn(0),index(0),g(n),dfn(n),low(n),bel(n) {}
    void addEdge(int u,int v,int w) {
        g[u].emplace_back(v,w,index++);
        g[v].emplace_back(u,w,index++);
    }
    void tarjan(int u,int index) {
        dfn[u]=low[u]=++dn;
        st.push(u);
        for(auto [v,w,i]:g[u]) {
            if((i^1)==index)// 防止立马回头
                continue;
            if(!dfn[v]) {
                tarjan(v,i);
                low[u]=min(low[u], low[v]);
                // if(dfn[u]<low[v]) {}// 割边
            }else {
                low[u]=min(low[u], dfn[v]);// 返祖边
            }
        }
        if(dfn[u]==low[u]) {
            vector<int> cur;
            for(int v=-1; v!=u; ) {
                v=st.top();
                st.pop();
                bel[v]=bn;
                cur.push_back(v);// 连通分量的信息
            }
            ecc.emplace_back(cur);
            bn++;
        }
    }
    void converge() {
        for(int i=0; i<n; ++i)
            if(!dfn[i]) tarjan(i,-1);
    }
    auto newForest() {
        vector<tuple<int,int,int>> e;
        for(int u=0; u<n; ++u)
            for(auto [v,w,i]:g[u])
                if(bel[u]!=bel[v]) {
                    if(u < v) {
                        e.emplace_back(w, bel[u]+1, bel[v]+1);
                    }
                }
        return e;
    }
};

namespace krt {// index-1
    constexpr int N = 1e5 * 2 + 10, LOG = __lg(N);// 开节点数的两倍
    using EType = int;// 边权类型
    constexpr bool ASC = true;// 边权从小到大排序
    int n, nn, f[LOG+1][N];
    EType val[N];
    vector<int> g[N];
    int sq[N], sn, L[N], R[N];
    void build(int n, vector<tuple<EType,int,int>> e) {
        assert(n*2 < N);
        nn = krt::n = n;
        fill_n(g, n*2, vector<int>());
        vector<int> rt(n*2);// [1, 2*n-1]
        iota(rt.begin(), rt.end(), 0);
        function<int(int)> get = [&](int u) {
            return rt[u] == u ? u : rt[u] = get(rt[u]);
        };
        if constexpr(ASC) sort(e.begin(), e.end());
        else sort(e.begin(), e.end(), greater());
        for(auto& [w,u,v]:e) {
            if((u = get(u)) == (v = get(v))) continue;
            val[++nn] = w;
            f[0][v] = f[0][u] = rt[u] = rt[v] = nn;
            g[nn].push_back(u);
            g[nn].push_back(v);
        }
        // 预处理倍增数组
        for(int i=1; i<=LOG; ++i)
            for(int u=1; u<=nn; ++u)
                f[i][u] = f[i-1][f[i-1][u]];
        // 处理 dfs 序（只有叶子拥有序号）
        sn = 0;
        function<void(int)> dfs = [&](int u) {
            L[u] = sn+1;
            if(u <= n) sq[++sn] = u;
            for(int v:g[u]) dfs(v);
            R[u] = sn;
        };
        for(int i=1; i<=nn; ++i)
            if(!f[0][i]) dfs(i);
    }
    // 在lim的限制下最高能跳到哪一个节点
    int jumpUp(int u, EType lim) {
        for(int i=LOG; i>=0; --i) {
            if constexpr (ASC) {
                if(f[i][u] and val[f[i][u]]<=lim) u = f[i][u];
            }else {
                if(f[i][u] and val[f[i][u]]>=lim) u = f[i][u];
            }
        }
        return u;
    }
}

namespace sgt {
struct Node {
    int lc, rc;
    int cnt;
    ll sum;
    void pushup(Node const& lc, Node const& rc) {
        cnt = lc.cnt + rc.cnt;
        sum = lc.sum + rc.sum;
    }
    // change(i, args...)
    void change(int i) {
        cnt++;
        sum += i;
    }
    // mergeLeaf(o, args...)
    void mergeLeaf(Node const& o, ll w) {}
};

vector<Node> tr;
int L, R, idx;

// op_num : change 总次数
void init(int op_num, int l, int r) {
    tr.resize(op_num * (__lg(r-l+1) + 2) + 10, {});
    L = l, R = r, idx = 0;
}

template<class ...T>
void change(int &u, int l, int r, int p, T const&...args) {
    assert(++idx < tr.size());
    tr[idx] = tr[u];
    u = idx;
    if(l == r) {
        tr[u].change(l, args...);
        return;
    }
    int mid = (l + r) / 2;
    if(p <= mid) change(tr[u].lc, l, mid, p, args...);
    else change(tr[u].rc, mid+1, r, p, args...);
    tr[u].pushup(tr[tr[u].lc], tr[tr[u].rc]);
}
template<class ...T>
void change(int &u, int p, T const&...args) {
    assert(L <= p and p <= R);
    change(u, L, R, p, args...);
}

template<class ...T>
void merge(int &u, int v,  int l, int r, T const&...args) {
    if(!u or !v) u = u | v;
    else if(l == r) {
        tr[u].mergeLeaf(tr[v], args...);
    } else {
        int mid = (l + r) / 2;
        merge(tr[u].lc, tr[v].lc, l, mid, args...);
        merge(tr[u].rc, tr[v].rc, mid+1, r, args...);
        tr[u].pushup(tr[tr[u].lc], tr[tr[u].rc]);
    }
}
template<class ...T>
void merge(int &u, int v, T const&... with_args) {
    merge(u, v, L, R, with_args...);
}

// auto query(int u, int l, int r, int x, int y) {
//     if(!u or l > y or r < x) return 0ll;
//     if(l>=x and r<=y) return tr[u].ans;
//     int mid = (l + r) / 2;
//     return query(tr[u].lc, l, mid, x, y) + query(tr[u].rc, mid+1, r, x, y);
// }
// auto query(int u, int l, int r) {
//     return query(u, L, R, l, r);
// }

// 在 tr[u] - tr[v] 上二分: sum<=w 最多多少个数
// auto binaryS(int u, int v, int l, int r, ll w) {
//     if(l == r) return min<ll>(tr[u].cnt - tr[v].cnt, w / l);
//     int mid = (l + r) / 2;
//     auto tmp = w - (tr[tr[u].lc].sum - tr[tr[v].lc].sum);
//     if(tmp <= 0) return binaryS(tr[u].lc, tr[v].lc, l, mid, w);
//     return binaryS(tr[u].rc, tr[v].rc, mid+1, r, tmp)
//         + tr[tr[u].lc].cnt - tr[tr[v].lc].cnt;
// }
// auto binaryS(int u, int v, ll w) {
//     return binaryS(u, v, L, R, w);
// }
// 在 tr[u] - tr[v] 上二分: cnt<=w
auto binaryS(int u, int v, int l, int r, ll w) {
    if(tr[u].cnt - tr[v].cnt < w) return -1;
    if(l == r) return l;
    int mid = (l + r) / 2;
    auto tmp = w - (tr[tr[u].lc].cnt - tr[tr[v].lc].cnt);
    if(tmp <= 0) return binaryS(tr[u].lc, tr[v].lc, l, mid, w);
    return binaryS(tr[u].rc, tr[v].rc, mid+1, r, tmp);
}
auto binaryS(int u, int v, ll w) {
    return binaryS(u, v, L, R, w);
}

}// namespace sgt

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    Tarjan tar(n);
    for(int i=0; i<m; ++i) {
        int u, v, w;
        cin>>u>>v>>w;
        --u,--v;
        tar.addEdge(u,v,w);
    }
    tar.converge();

    auto es = tar.newForest();
    int sz = tar.bn;
    krt::build(sz, es);

    vector<int> w(sz+1), rt(sz+1);
    sgt::init(sz, 1, 1e5);
    for(int i=1; i<=sz; ++i) {
        w[i] = tar.ecc[krt::sq[i]-1].size();
        sgt::change(rt[i] = rt[i-1], w[i]);
    }

    int tt;
    cin>>tt;
    while(tt--) {
        int u, x, k;
        cin>>u>>x>>k;
        --u;
        u = tar.bel[u]+1;
        u = krt::jumpUp(u, x);
        // query(w, l[u], r[u], k)
        cout<<sgt::binaryS(rt[krt::R[u]], rt[krt::L[u]-1], k)<<'\n';
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/87255/B
边双连通分量
Kruskal重构树
区间查询第k大

*/