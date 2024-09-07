#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

namespace sgt {
struct Node {
    int lc=0,rc=0;
    int sz = 0;
    ll sd = 0;
    ll ans = 0;
    void pushup(Node const& lc, Node const& rc) {
        ans = lc.ans + rc.ans;
    }
    // update(i, args...)
    void change(int i, int d) {
        sz ++;
        sd += d;
    }
    // mergeLeaf(o, args...)
    void mergeLeaf(Node const& o, ll da) {
        ans += o.ans + sz * o.sd + o.sz * sd -2ll * da * o.sz * sz;
        sz += o.sz;
        sd += o.sd;
    }
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

auto query(int u, int l, int r, int x, int y) {
    if(!u or l > y or r < x) return 0ll;
    if(l>=x and r<=y) return tr[u].ans;
    int mid = (l + r) / 2;
    return query(tr[u].lc, l, mid, x, y) + query(tr[u].rc, mid+1, r, x, y);
}
auto query(int u, int l, int r) {
    return query(u, L, R, l, r);
}

// // 在 tr[u] - tr[v] 上二分: sum<=w 最多多少个数
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

}// namespace sgt

constexpr int N = 2e5 + 10;
int a[N];
vector<int> g[N];
int rt[N];

void dfs(int u,int fa, int dep = 0) {
    sgt::change(rt[u], a[u], dep);
    for(int v:g[u]) {
        if(v == fa) continue;
        dfs(v, u, dep+1);
        sgt::merge(rt[u], rt[v], dep);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    sgt::init(n, 1, n);
    for(int i=1; i<n; ++i) {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1; i<=n; ++i) {
        cin>>a[i];
    }

    dfs(1, 0);
    cout<<sgt::query(rt[1], 1, n);
    return 0;
}
/*
https://atcoder.jp/contests/abc359/tasks/abc359_g
线段树合并

*/