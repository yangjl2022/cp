#include<iostream>
#include<cmath>
#include<cstring>
#include<cassert>
#include<string>
#include<queue>
#include<deque>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<map>
#include<vector>
#include<set>
#include<unordered_set>
#include<bitset>
#include<climits>
#include<numeric>
#include<functional>
#include<iomanip>
#ifdef YJL
#include<debug.h>
#else
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
constexpr int P=998244353;

using Z=MInt<P>;
constexpr Z power(Z a, ll b) {
    Z ans(1);
    for(; b; b>>=1, a*=a)
        if(b&1) ans*=a;
    return ans;
}
template<int V>// invV<2> * 2 ==1 mod P
constexpr Z invV=power(V,P-2);

constexpr int N = 1e6 + 10;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n;
    cin>>n;
    Z p[2];
    p[0] = 1;
    Z ans[2];
    for(int i=0; i<n; ++i) {
        Z p1 = Z(n)/(n+i), p2 = 1 - p1;
        Z p0 = Z(n-i)/n;
        Z s1 = (1-p0)/(p0*(2-p0));
        Z s2 = (1-p0)*s1;
        Z r[2];
        for(int j=0; j<2; ++j) {
            ans[j] += p[j]*s1;
            ans[!j] += p[j]*s2;
            for(int k=0; k<2; ++k) {
                if((j+k)&1) {
                    r[k] += p[j]*p1;
                }else {
                    r[k] += p[j]*p2;
                }
            }
        }
        p[0] = r[0];
        p[1] = r[1];
        debug(p);
    }

    cout << ans[0] << " " << ans[1];
    return 0;
}
/*




*/