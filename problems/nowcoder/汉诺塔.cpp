#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

template<int P>
struct MInt {
    int x;
    constexpr MInt(): x(0) {}
    template<class T>
    constexpr MInt(T x): x(norm(x%P)) {}
    constexpr static int norm(int x) {
        return x<0? x+P: x>=P? x-P: x;
    }
    constexpr MInt inv() const{
        int a=x, b=P, u=1, v=0;
        while(b) {
            int t = a/b;
            swap((a-=t*b), b);
            swap((u-=t*v), v);
        }
        return u;
    }
    constexpr MInt operator-() const{
        return MInt()-*this;
    }
    constexpr MInt& operator+=(const MInt& a) {
        x=norm(x+a.x);
        return *this;
    }
    constexpr MInt& operator-=(const MInt& a) {
        x=norm(x-a.x);
        return *this;
    }
    constexpr MInt& operator*=(const MInt& a) {
        x=1ll*x*a.x%P;
        return *this;
    }
    constexpr MInt& operator/=(const MInt& a) {
        return *this*=a.inv();
    }
    constexpr friend MInt operator+(MInt l,const MInt& r) {
        return l+=r;
    }
    constexpr friend MInt operator-(MInt l,const MInt& r) {
        return l-=r;
    }
    constexpr friend MInt operator*(MInt l,const MInt& r) {
        return l*=r;
    }
    constexpr friend MInt operator/(MInt l,const MInt& r) {
        return l/=r;
    }
    constexpr explicit operator bool()const {
        return x!=0;
    }
    constexpr bool operator!()const {
        return x==0;
    }
    friend ostream& operator<<(ostream& os,const MInt& a) {
        return os<<a.x;
    }
    string find_Fraction()const {
        for(int i=1; i<=1000000; ++i) {
            if((*this*i).x<=100) {
                return to_string((*this*i).x) + "/" + to_string(i);
            }
        }
        return "not find.";
    }
};
constexpr int P=1e9+7;

using Z=MInt<P>;
constexpr Z power(Z a, ll b) {
    Z ans(1);
    for(; b; b>>=1, a*=a)
        if(b&1) ans*=a;
    return ans;
}
template<int V>// Cinv<2> * 2 == 1 mod P
constexpr Z Cinv = power(V,P-2);

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x:v) is>>x;
    return is;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int> a(n);
    vector pw(n+1, Z(1));
    for(int i=0; i<n; ++i) {
        cin>>a[i];
        --a[i];
        pw[i+1] = pw[i]*2;
    }
    reverse(ALL(a));
    vector dp(n+1, array<Z,3>{});
    for(int i=0; i<n; ++i) {
        for(int j=0; j<3; ++j) {
            if(j == a[i]) {
                dp[i+1][j] = dp[i][j];
            }else {
                // all -> other : dp[i][other]
                // i -> j : 1
                // all(size = i) -> j : 2^size - 1
                int t = 0^1^2^j^a[i];
                dp[i+1][j] = dp[i][t] + pw[i];
            }
        }
    }
    cout<<dp[n][2];
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85333/C
汉诺塔升级版
首先得知道3-汉诺塔最小步数 2^size-1 的结论
然后就可以贪心的从小往大考虑
DP解决

*/