#include <bits/stdc++.h>
#ifdef YJL
#include "debug.h"
using ll = long long;
#else
using ll = unsigned long long;
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x:v) is>>x;
    return is;
}


namespace sgt {
struct Node {
    int lc, rc;
    ll cnt = 0;
    ll s2 = 0;
    void pushup(Node const& lc, Node const& rc) {
        cnt = lc.cnt + rc.cnt;
        s2 = lc.s2 + rc.s2;
    }
    // change(i, args...)
    void change(ll v) {
        cnt++;
        s2 += v*v;
    }
    // mergeLeaf(o, args...)
    void mergeLeaf(Node const& o) {
        cnt += o.cnt;
        s2 += o.s2;
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
ll merge(int &u, int v,  int l, int r, T const&...args) {
    ll cur = 0;
    if(!u or !v) u = u | v;
    else if(l == r) {
        cur += (tr[u].s2 * tr[v].cnt + tr[v].s2 * tr[u].cnt);
        tr[u].mergeLeaf(tr[v], args...);
    } else {
        int mid = (l + r) / 2;
        cur += 2*(tr[tr[u].lc].cnt * tr[tr[v].rc].s2 + tr[tr[u].rc].s2 * tr[tr[v].lc].cnt);
        cur += merge(tr[u].lc, tr[v].lc, l, mid, args...);
        cur += merge(tr[u].rc, tr[v].rc, mid+1, r, args...);
        tr[u].pushup(tr[tr[u].lc], tr[tr[u].rc]);
    }
    return cur;
}
template<class ...T>
auto merge(int &u, int v) {
    return merge(u, v, L, R);
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

}// namespace sgt

constexpr int N = 5e5 + 10;
vector<int> g[N];
int a[N];

ll ans;
ll sa[N];
ll f[N];
int rt[N];
void dfs(int u,int fa) {
    sa[u] = a[u];
    f[u] = sa[u] * sa[u];
    sgt::change(rt[u], a[u]);
    for(int v:g[u]) {
        if(v==fa) continue;
        dfs(v, u);
        f[u] += f[v] + sgt::merge(rt[u], rt[v]);
        sa[u] += sa[v];
    }
    ll tmp = f[u] - sa[u]*sa[u];
    ans ^= tmp;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i=1; i<n; ++i) {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1; i<=n; ++i) {
        cin>>a[i];
    }

    sgt::init(n, 1, 1e6);
    dfs(1, 0);
    
    cout<<ans<<'\n';
    return 0;
}
/*
https://acm.hdu.edu.cn/showproblem.php?pid=7435
f[u] = sum{v1 in subtree[u], v2 in subtree[u]} max^2(a[v1],a[v2]) - (sum{v in subtree[u]} a[v])^2

使用线段树合并维护 sum max^2(a[v1],a[v2])
*/