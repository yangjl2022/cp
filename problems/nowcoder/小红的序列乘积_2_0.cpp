/**
 *    author:  yangjl
 *    created: 2024.11.08 19:26:06
**/
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
    for(auto& x : v) {
        is >> x;
    }
    return is;
}
template<int P>
struct MInt {
    int x;
    constexpr MInt() : x(0) {}
    template<class T>
    constexpr MInt(T x) : x(norm(x% P)) {}
    constexpr static int norm(int x) {
        return x < 0 ? x + P : x >= P ? x - P : x;
    }
    constexpr MInt inv() const {
        int a = x, b = P, u = 1, v = 0;
        while(b) {
            int t = a / b;
            swap((a -= t * b), b);
            swap((u -= t * v), v);
        }
        return u;
    }
    constexpr MInt operator-() const {
        return MInt() - *this;
    }
    constexpr MInt& operator+=(const MInt& a) {
        x = norm(x + a.x);
        return *this;
    }
    constexpr MInt& operator-=(const MInt& a) {
        x = norm(x - a.x);
        return *this;
    }
    constexpr MInt& operator*=(const MInt& a) {
        x = 1ll * x * a.x % P;
        return *this;
    }
    constexpr MInt& operator/=(const MInt& a) {
        assert(a);
        return *this *= a.inv();
    }
    constexpr friend MInt operator+(MInt l, const MInt& r) {
        return l += r;
    }
    constexpr friend MInt operator-(MInt l, const MInt& r) {
        return l -= r;
    }
    constexpr friend MInt operator*(MInt l, const MInt& r) {
        return l *= r;
    }
    constexpr friend MInt operator/(MInt l, const MInt& r) {
        return l /= r;
    }
    constexpr explicit operator bool()const {
        return x != 0;
    }
    constexpr bool operator!()const {
        return x == 0;
    }
    friend ostream& operator<<(ostream& os, const MInt& a) {
        return os << a.x;
    }
    string find_Fraction()const {
        for(int i = 1; i <= 1000000; ++i)
            if((*this * i).x <= 100)
                return to_string((*this * i).x) + "/" + to_string(i);
        return "not find.";
    }
};
constexpr int P = 1e9 + 7;
using Z = MInt<P>;
constexpr Z power(Z a, ll b) {
    Z ans(1);
    for(; b; b >>= 1, a *= a)
        if(b & 1) ans *= a;
    return ans;
}
template<int V>// invV<2> * 2 ==1 mod P
constexpr Z invV = power(V, P - 2);


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<Z> p2{1};
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] %= 10;
        p2.push_back(p2.back() * 2);
    }
    vector<Z> dp(10);
    dp[1] = 1;
    Z ans = 0;
    for(int k = 0; k < n; ++k) {
        int x = a[k];
        vector<Z> re(dp);
        for(int i = 0; i < 10; ++i) {
            int u = (x * i) % 10;
            re[u] += dp[i];
            if(u == 6) {
                ans += dp[i] * p2[n - 1 - k];
            }
        }
        dp = move(re);
        debug(dp);
    }
    cout << ans;
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/87656/E
思维，DP
考虑DP的过程中统计答案，避免维护答案

dp[i][j] 表示前i个选若干个得到 r = j mod 10 的方案数
我们在选择了 ai 并且 r=6 mod 10 时统计贡献：
- if x*ai = 6 mod 10, dp[i-1][x] -> dp[i][6]

那么在 i 处得到 6 的总方案数为 dp[i-1][x] * 2^(n-i)
将答案加上此贡献即可

*/