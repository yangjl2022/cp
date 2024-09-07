#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

namespace sgt {
struct Node {
    int lc, rc;
    bool cnt;
    void pushup(Node const& lc, Node const& rc) {
        cnt = lc.cnt or rc.cnt;
    }
    // change(i, args...)
    void change(int i) {
        cnt = true;
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

bool query(int u, int l, int r, int x, int y) {
    if(!u or l > y or r < x) return false;
    if(l>=x and r<=y) return tr[u].cnt;
    int mid = (l + r) / 2;
    return query(tr[u].lc, l, mid, x, y) or query(tr[u].rc, mid+1, r, x, y);
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

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x:v) is>>x;
    return is;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    sgt::init(n, 1, 1e9);
    vector v(n+1, vector<int>(1, 0));

    vector<int> a(n), st, f(n);
    for(int i=0; i<n; ++i) {
        cin>>a[i];

        auto it = lower_bound(ALL(st), a[i]);
        f[i] = it - st.begin()+1;
        if(it == st.end()) st.push_back(a[i]);
        else *it = a[i];
        
        v[f[i]].push_back(v[f[i]].back());
        sgt::change(v[f[i]].back(), a[i]);
    }

    int sz = st.size();
    vector<int> st2;
    for(int i=n-1,j=n-1; i>=0; --i) {
        if(i<n-1 and f[i] == sz) {
            cout<<sz+1;
            exit(0);
        }
        while(j>=i-1 and j>=0) {
            v[f[j]].pop_back();
            j--;
        }

        auto it = lower_bound(ALL(st2), a[i], greater());
        int g = it-st2.begin()+1;
        if(it == st2.end()) st2.push_back(a[i]);
        else *it = a[i];

        if(i>0 and g == sz) {
            cout<<sz+1;
            exit(0);
        }

        auto& rt = v[sz-g].back();
        if(sgt::query(rt, 1, a[i]-2)) {
            cout<<sz+1;
            exit(0);
        }
    }
    cout<<sz;
    return 0;
}
/*
https://atcoder.jp/contests/abc360/tasks/abc360_g
LIS 最长上升子序列
三条件：
1. f[i]+g[i] = sz
2. j <= i-2
3. a[j] <= a[i]-2
可持久化线段树维护前缀的状态，区间询问

注意改的是最前面和最后面的元素的情况
*/