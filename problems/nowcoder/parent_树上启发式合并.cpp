#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

namespace str {
struct Z {
    static constexpr int P0 = 998244353, P1 = 1e9 + 7;
    int v0, v1;
    Z(int x = 0) : v0(x), v1(x) {}
    constexpr Z(int x, int y) : v0(x), v1(y) {}
    friend Z operator+(Z lhs, Z const& rhs) {
        if((lhs.v0 += rhs.v0) >= P0) lhs.v0 -= P0;
        if((lhs.v1 += rhs.v1) >= P1) lhs.v1 -= P1;
        return lhs;
    }
    friend Z operator-(Z lhs, Z const& rhs) {
        if((lhs.v0 -= rhs.v0) < 0) lhs.v0 += P0;
        if((lhs.v1 -= rhs.v1) < 0) lhs.v1 += P1;
        return lhs;
    }
    friend Z operator*(Z lhs, Z const& rhs) {
        lhs.v0 = 1ll * lhs.v0 * rhs.v0 % P0;
        lhs.v1 = 1ll * lhs.v1 * rhs.v1 % P1;
        return lhs;
    }
    bool operator==(Z const& o) const {
        return v0 == o.v0 and v1 == o.v1;
    }
    bool operator<(Z const& o) const {
        return v0 < o.v0 or v0 == o.v0 and v1 < o.v1;
    }
};

vector<Z> powz(1, 1);
vector<Z> hash(string const& s) {
    static constexpr Z base(114514, 1919810);
    while(powz.size() < s.size())
        powz.emplace_back(powz.back() * base);
    vector<Z> h(s.size()+1);
    for(int i=0; i<s.size(); ++i)
        h[i+1] = h[i] * base + s[i];
    return h;
}
Z substrZ(vector<Z> const& h, int l, int r) {
    return h[r+1] - h[l] * powz[r-l+1];
}
// return length of lcp(s0[l0:], s1[l1:])
int lcp(vector<Z> const& h0, vector<Z> const& h1, int l0, int l1) {
    int l = 0, r = min(h0.size() - 1 - l0, h1.size() - 1 - l1), ans = -1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(substrZ(h0, l0, l0+mid) == substrZ(h1, l1, l1+mid)) {
            ans = mid;
            l = mid+1;
        }else r = mid-1;
    }
    return ans + 1;
}

}// namespace str

template<class T>
auto lsh(vector<T>& A) {// return lsh's function
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    return [&](const T& x) {
        return lower_bound(A.begin(), A.end(), x)-A.begin();
    };
}

constexpr int N = 2e5 + 10;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin>>n>>q;
    assert(1<=n and n<=int(1e5));
    assert(1<=q and q<=int(1e5));
    
    string s;
    cin>>s;
    auto hs = str::hash(s);
    vector<pair<str::Z,int>> a;// <hash val, k>
    vector<str::Z> hv;
    vector<int> lens;
    int sumTlen = 0;
    for(int i=0; i<q; ++i) {
        string t;
        int k;
        cin>>t>>k;
        sumTlen += t.size();
        assert(1<=k and k<=int(1e5));
        --k;
        auto w = str::hash(t).back();
        a.emplace_back(w, k);
        lens.push_back(t.size());
        hv.push_back(w);
    }
    assert(1<=sumTlen and sumTlen<=int(1e5));

    auto lens_id = lsh(lens);
    auto hv_id = lsh(hv);

    vector<int> sz(hv.size());
    vector qry(hv.size(), vector<pair<int,int>>());
    for(int i=0; i<q; ++i) {
        auto& [v, k] = a[i];
        int i0 = hv_id(v);
        qry[i0].emplace_back(k, i);
    }
    for(int i=0; i<qry.size(); ++i) {
        sort(ALL(qry[i]), greater());
    }

    vector<int> ans(a.size(), -1);
    for(int i=0; i<n; ++i) {
        for(int l:lens) {
            if(i-l+1 < 0) break;
            auto t = str::substrZ(hs, i-l+1, i);
            int i0 = hv_id(t);
            if(i0 < hv.size() and hv[i0] == t) {
                while(qry[i0].size() and sz[i0] == qry[i0].back().first) {
                    ans[qry[i0].back().second] = i+1;
                    qry[i0].pop_back();
                }
                sz[i0]++;
            }
        }
    }

    for(int i=0; i<q; ++i) {
        cout<<ans[i]<<'\n';
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85251/F
T的长度总和<=1e5 -> T的不同长度只有300种
有效匹配只有3e7个
记录有效匹配

用哈希判断匹配
*/