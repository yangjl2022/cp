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

namespace sgt {
    struct Node {
        int lc, rc;
        int cnt;
        void pushup(Node const& lc, Node const& rc) {
            cnt = lc.cnt + rc.cnt;
        }
        // change(i, args...)
        void change(int i) {
            cnt++;
        }
        // mergeLeaf(o, args...)
        void mergeLeaf(Node const& o, ll w) { }
    };

    vector<Node> tr;
    int L, R, idx;

    // op_num : change 总次数
    void init(int op_num, int l, int r) {
        tr.resize(op_num * (__lg(r - l + 1) + 2) + 10, {});
        L = l, R = r, idx = 0;
    }

    template<class ...T>
    void change(int& u, int l, int r, int p, T const&...args) {
        assert(++idx < tr.size());
        tr[idx] = tr[u];
        u = idx;
        if(l == r) {
            tr[u].change(l, args...);
            return;
        }
        int mid = (l + r) / 2;
        if(p <= mid) change(tr[u].lc, l, mid, p, args...);
        else change(tr[u].rc, mid + 1, r, p, args...);
        tr[u].pushup(tr[tr[u].lc], tr[tr[u].rc]);
    }
    template<class ...T>
    void change(int& u, int p, T const&...args) {
        assert(L <= p and p <= R);
        change(u, L, R, p, args...);
    }

    template<class ...T>
    void merge(int& u, int v, int l, int r, T const&...args) {
        if(!u or !v) u = u | v;
        else if(l == r) {
            tr[u].mergeLeaf(tr[v], args...);
        } else {
            int mid = (l + r) / 2;
            merge(tr[u].lc, tr[v].lc, l, mid, args...);
            merge(tr[u].rc, tr[v].rc, mid + 1, r, args...);
            tr[u].pushup(tr[tr[u].lc], tr[tr[u].rc]);
        }
    }
    template<class ...T>
    void merge(int& u, int v, T const&... with_args) {
        merge(u, v, L, R, with_args...);
    }

    int lfind(int u, int v, int l, int r, int ql, int qr, int& w) {
        if(l == ql and r == qr) {
            if(tr[u].cnt - tr[v].cnt < w) {
                w -= tr[u].cnt - tr[v].cnt;
                return r - l + 1;
            }
            if(l == r) return 0;
        }
        int mid = (l + r) / 2;
        if(qr <= mid) return lfind(tr[u].lc, tr[v].lc, l, mid, ql, qr, w);
        if(ql > mid) return lfind(tr[u].rc, tr[v].rc, mid + 1, r, ql, qr, w);

        int len = lfind(tr[u].lc, tr[v].lc, l, mid, ql, mid, w);
        if(len == mid - ql + 1) len += lfind(tr[u].rc, tr[v].rc, mid + 1, r, mid + 1, qr, w);
        return len;
    }
}// namespace sgt

constexpr int N = 2e5 + 10;
int a[N], ans[N];
vector<int> ids[N];
int rt[N];
vector<pair<int, int>> qry[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        ids[a[i]].push_back(i);
    }
    for(int i = 0; i < q; ++i) {
        int p, x;
        cin >> p >> x;
        qry[x].emplace_back(p, i);
    }

    sgt::init(n, 1, n);
    for(int i = N - 1; i >= 1; --i) {
        rt[i] = rt[i + 1];
        for(int p : ids[i]) {
            sgt::change(rt[i], p);
        }
    }

    for(int x = 1; x <= n; ++x) {
        if(qry[x].size() == 0) {
            continue;
        }

        sort(ALL(qry[x]), greater());
        int p = 0, h = 1;
        while(true) {
            int w = x;
            int len = sgt::lfind(rt[h], 0, 1, n, p + 1, n, w) + 1;
            p += len;
            while(qry[x].size() and qry[x].back().first <= p) {
                auto [pos, id] = qry[x].back();
                qry[x].pop_back();
                ans[id] = h <= a[pos];
            }

            h++;
            if(p >= n) break;
        }
    }

    for(int i = 0; i < q; ++i) {
        cout << (ans[i] ? "YES" : "NO") << "\n";
    }
    return 0;
}
/*
https://codeforces.com/contest/1997/problem/E
动态开点线段树，树上二分，离线，调和级数

注意到枚举 k，那么 h 的总变化次数为 sum{k=1~n} n/k = nlogn
对于每一次变化，考虑二分找到变化位置，同时离线处理询问
注意到每次二分找的是当前位置右边第k个 >= h 的位置，与 h 息息相关
不妨通过 h 为标记建立线段树进行树上二分：
1. 使用动态开点线段树，对 h 从大到小建树，tr[h] 继承自 tr[h+1]，这样 tr[h] 的信息包括了 >=h 的所有信息
对于 tr[h], 在 a[p] = h 的位置 p 处 +1
2. 每次变化的需求就是从 l 开始在树上二分，找到第一个 query[l,p] == k 到位置 p

总复杂度 O(nlognlogn)

*/