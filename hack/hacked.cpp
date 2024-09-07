/**
 *    author:  yangjl
 *    created: 2024.08.30 19:17:06
**/
#include <bits/stdc++.h>
#ifdef YJL
#include "debug.h"
#else
#define debug(...)0
#endif
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
vector<Z> inv, fac, infac;
void initFac(int n) {
    n = min(n, P - 1);
    inv.resize(n + 1, 1);
    fac.resize(n + 1, 1);
    infac.resize(n + 1, 1);
    for(int i = 2; i <= n; ++i) {
        fac[i] = fac[i - 1] * i;
        inv[i] = -P / i * inv[P % i];
        infac[i] = infac[i - 1] * inv[i];
    }
}
Z binom(int n, int m) {// n,m<P
    if(m < 0 or n < m) return 0;
    assert(n < fac.size());
    return fac[n] * infac[m] * infac[n - m];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    initFac(1e6);
    int tt;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        [&]() {
            vector<pair<int, int>> as;
            stack<int> st;
            for(int i = 0; i < n * 4; ++i) {
                if(s[i] == '0') {
                    if(st.size() and s[st.top()] == '1') {
                        cout << "0\n";
                        return;
                    }
                    st.push(i);
                } else {
                    if(st.size() < 2) {
                        cout << "0\n";
                        return;
                    }
                    if(s[st.top()] == '1') {
                        st.pop();
                        st.pop();
                        int l = st.top();
                        st.pop();
                        as.emplace_back(l, i);
                    } else {
                        st.push(i);
                    }
                }
            }

            debug(as);

            if(st.size()) {
                cout << "0\n";
                return;
            }

            assert(as.size() == n);

            sort(as.begin(), as.end(), [&](const pair<int, int>& x, const pair<int, int>& y) {
                return x.second - x.first < y.second - y.first;
            });

            as.emplace_back(-1, 4 * n);

            set<array<int, 3>> sp;
            vector<Z> dp(as.size());
            vector<int> sz(as.size());
            for(int i = 0; i < as.size(); ++i) {
                auto [l, r] = as[i];

                dp[i] = 1;
                auto it = sp.lower_bound(array<int, 3>{l, r, i});
                while(it != sp.end() and it->at(1) < r) {
                    int v = it->at(2);
                    dp[i] *= infac[sz[v]];
                    dp[i] *= dp[v];
                    sz[i] += sz[v];
                    it = sp.erase(it);
                }

                dp[i] *= fac[sz[i]];
                sz[i]++;
                sp.insert({l, r, i});
            }

            assert(sp.size() == 1);

            debug(dp);
            debug(sz);

            cout << dp.back() << '\n';
        }();
    }
    return 0;
}
/*


*/