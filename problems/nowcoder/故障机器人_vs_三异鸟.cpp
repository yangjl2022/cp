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

vector<Z> inv, fac, infac;
void initFac(int n) {
    n = min(n, P-1);
    inv.resize(n+1, 1);
    fac.resize(n+1, 1);
    infac.resize(n+1, 1);
    for(int i=2; i<=n; ++i) {
        fac[i] = fac[i-1] * i;
        inv[i] = -P/i * inv[P%i];
        infac[i] = infac[i-1] * inv[i];
    }
}
Z binom(int n, int m) {// n,m<P
    if(m < 0 or n < m) return 0;
    assert(n < fac.size());
    return fac[n] * infac[m] * infac[n-m];
}

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x:v) is>>x;
    return is;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // debug(Z(500000014).find_Fraction());
    int x;
    cin>>x;
    x = (x+2)/3;
    initFac(3*x);

    vector<Z> pre(3*x);
    vector<Z> pre2(3*x);
    for(int i=1; i<3*x; ++i) {
        pre[i] = pre[i-1] + power(2*Cinv<3>,i)*binom(i-1, x-1);
        pre2[i] = pre2[i-1] + i*power(2*Cinv<3>,i)*binom(i-1, x-1);
    }

    Z f = 0;
    for(int i=1; i<3*x; ++i) {
        f += power(Cinv<2>, i)*binom(i-1-x, x-1)
            * ((i-2)*pre[i-1] + pre2[i-1]);
    }

    f*=6;
    cout<< f +(3*x-1);
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85910/C
组合数学，公式推导，前缀和，概率
x <- ceil(x/3)
那么一共3x个回合
枚举杀死第一只鸟的位置i，杀死第一只鸟的位置j，通过组合数学计算当前状态概率，统计期望
推导公式+前缀和，把双层循环优化为一层循环。

*/