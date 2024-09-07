#include "bits/stdc++.h"
#ifndef YJL
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

namespace str {
struct Z {
    static constexpr int P0 = 998244353, P1 = 1e9 + 7;
    int v0, v1;
    Z(int x = 0) : v0(x), v1(x) {
        v0 = (v0%P0+P0)%P0;  
        v1 = (v1%P1+P1)%P1;  
    }
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
vector<Z> hash(vector<int> const& s) {
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0; i<n; ++i) {
        cin>>a[i];
    }
    
    auto h = str::hash(a);

    for(int i=1; i<(n+1)/2; ++i) {
        int len = n-2*i;
        if(str::substrZ(h, 0, len-1) - str::substrZ(h, i, i+len-1)
        == str::substrZ(h, i, i+len-1) - str::substrZ(h, i*2, i*2+len-1)) {
            cout<<i;
            exit(0);
        }
    }
    cout<<(n+1)/2;
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85639/F
i个平行的等差数列，打包成整块也会成等差数列
因为  hash0 = a0 + a1 * p + a2 * p^2 + ...
     hash1 = b0 + b1 * p + b2 * p^2 + ...
     hash2 = c0 + c1 * p + c2 * p^2 + ...
hash1 - hash0 = (b0 - a0) + (b1 - a1) * p + ...
hash2 - hash1 = (c0 - b0) + (c1 - b1) * p + ...
由于 (c0 - b0) = (b0 - a0), (c1 - b1) = (b1 - a1), ...

所以 hash1 - hash0 = hash2 - hash1

所以可以用hash判断整体的等差数列
*/