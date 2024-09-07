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

template<class T>
auto lsh(vector<T>& A) {// return lsh's function
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    return [&](const T& x) {
        return lower_bound(A.begin(), A.end(), x) - A.begin();
    };
}

struct Data {
    ll sum, minh;
    void init(int i) {
        sum = 0, minh = 0;
    }
    // add(const T& args... )
    void add(int sig, int val) {
        sum += val * sig;
        if(sum) minh = val;
    }
    friend Data operator+(const Data& lhs, const Data& rhs) {
        Data re;
        re.sum = lhs.sum + rhs.sum;
        re.minh = max(lhs.minh, rhs.minh - lhs.sum);
        return re;
    }
};
struct Segtree {
#define u1 (u<<1)
#define u2 (u<<1|1)
    vector<Data> tr;
    vector<int> mp;
    int Lpoint, Rpoint;
    template<class ...T>
    Segtree(int L, int R, const T&...args) :Lpoint(L), Rpoint(R)
        , tr(4 << __lg(R - L + 1)), mp(R - L + 1) {// a[L~R]建树
        build(1, L, R, args...);
    }
    template<class ...T>
    void build(int u, int l, int r, const T&...args) {
        if(l == r) {
            tr[u].init(l, args...);
            mp[l - Lpoint] = u;
            return;
        }
        int mid = (l + r) >> 1;
        build(u1, l, mid, args...);
        build(u2, mid + 1, r, args...);
        tr[u] = tr[u1] + tr[u2];
    }
    template<class ...T>
    void change(int pos, const T&...args) {
        int u = mp[pos - Lpoint];
        tr[u].add(args...);
        for(u >>= 1; u; u >>= 1) tr[u] = tr[u1] + tr[u2];
    }
    Data query(int l, int r) {
        return query(1, Lpoint, Rpoint, l, r);
    }
    Data query(int u, int l, int r, int ql, int qr) {
        if(l == ql && r == qr) return tr[u];
        int mid = (l + r) >> 1;
        if(qr <= mid) return query(u1, l, mid, ql, qr);
        if(ql > mid) return query(u2, mid + 1, r, ql, qr);
        return query(u1, l, mid, ql, mid) + query(u2, mid + 1, r, mid + 1, qr);
    }
    // 返回 check 成功的区间长度
    template<class Func>
    int lfind(int u, int l, int r, int ql, int qr, Func const& chk) {
        if(l == ql and r == qr) {
            if(chk(tr[u])) return r - l + 1;
            if(l == r) return 0;
        }
        int mid = (l + r) / 2;
        if(qr <= mid) return lfind(u1, l, mid, ql, qr, chk);
        if(ql > mid) return lfind(u2, mid + 1, r, ql, qr, chk);
        int len = lfind(u1, l, mid, ql, mid, chk);
        if(len == mid - ql + 1) len += lfind(u2, mid + 1, r, mid + 1, qr, chk);
        return len;
    }
    template<class Func>
    int rfind(int u, int l, int r, int ql, int qr, Func const& chk) {
        if(l == ql and r == qr) {
            if(chk(tr[u])) return r - l + 1;
            if(l == r) return 0;
        }
        int mid = (l + r) / 2;
        if(qr <= mid) return rfind(u1, l, mid, ql, qr, chk);
        if(ql > mid) return rfind(u2, mid + 1, r, ql, qr, chk);
        int len = rfind(u2, mid + 1, r, mid + 1, qr, chk);
        if(len == qr - mid) len += rfind(u1, l, mid, ql, mid, chk);
        return len;
    }
#undef u1
#undef u2
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin >> tt;
    assert(1 <= tt and tt <= int(5e4));
    int sn = 0;

    while(tt--) {
        int n, x;
        cin >> n >> x;
        assert(1 <= n and n <= int(1e5));
        assert(1 <= x and x <= int(1e9));
        sn += n;

        vector<array<int, 3>> a;
        vector<int> ys;
        for(int i = 0; i < n; ++i) {
            int l, r, y;
            cin >> l >> r >> y;
            assert(1 <= l and l < r and r <= int(1e9));
            assert(1 <= y and y <= int(1e9));

            ys.push_back(y);
            a.push_back({l, 1, y});
            a.push_back({r, -1, y});
        }

        auto ls = lsh(ys);
        sort(ALL(a));

        ll ans = 0;
        Segtree tr(0, ys.size() - 1);
        for(auto [p, sig, e] : a) {
            tr.change(ls(e), sig, e);
            ll h = x;
            tr.lfind(1, 0, ys.size() - 1, 0, ys.size() - 1, [&](Data const& data) {
                if(h >= data.minh) {
                    h += data.sum;
                    return true;
                }
                return false;
            });
            ans = max(ans, h);
        }
        cout << ans << '\n';
    }
    assert(1 <= sn and sn <= int(1e5));
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/88455/G
利用差分做到离散化的作用，对于同一段相同状态只计算一个
对于一个鱼儿分布状态，显然从小吃到大最优
使用线段树维护吃完重量在 [l,r] 的鱼需要的最小重量，以及在该区间的重量增长
于是可以在树上二分求出最终会在哪里停下来。

*/