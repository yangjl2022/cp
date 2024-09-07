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
    for(auto& x:v) is>>x;
    return is;
}

template<class T>
int sgn(const T& v) {
    static constexpr T eps = 1e-8;
    return v>eps ? 1 : v<-eps ? -1 : 0;
}
template<class T>
struct Point {// Point or Vector
    T x,y;
    Point() {}
    Point(T x, T y): x(x), y(y) {}
    template<class U>
    operator Point<U> () const {
        return Point<U>(U(x),U(y));
    }
    Point operator+(const Point& o) const {
        return Point(x+o.x, y+o.y);
    }
    Point operator-(const Point& o) const {
        return Point(x-o.x, y-o.y);
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    Point operator*(const T& v) const {
        return Point(x*v, y*v);
    }
    friend Point operator*(const T& v, const Point<T>& o) {
        return Point(o.x*v, o.y*v);
    }
    Point operator/(const T& v) const {
        return Point(x/v, y/v);
    }
    Point operator+=(const Point& o) {
        x += o.x, y += o.y;
        return *this;
    }
    Point operator-=(const Point& o) {
        x -= o.x, y -= o.y;
        return *this;
    }
    Point operator*=(const T& v) {
        x *= v, y *= v;
        return *this;
    }
    Point operator/=(const T& v) {
        x /= v, y /= v;
        return *this;
    }
    bool operator==(const Point& o) const {
        return sgn(x-o.x)==0 and sgn(y-o.y)==0;
    }
    bool operator!=(const Point& o) const {
        return sgn(x-o.x)!=0 or sgn(y-o.y)!=0;
    }
    bool operator<(const Point& o) const {
        return sgn(x-o.x)<0 or sgn(x-o.x)==0 and sgn(y-o.y)<0;
    }
    bool operator>(const Point& o) const {
        return sgn(x-o.x)>0 or sgn(x-o.x)==0 and sgn(y-o.y)>0;
    }
    T square() const {
        return x*x + y*y;
    }
    T interSquare(const Point& o) const {
        return (*this-o).square();
    }
    friend istream& operator>>(istream& in, Point& o) {
        return in>>o.x>>o.y;
    }
    friend ostream& operator<<(ostream& out, const Point<T>& o) {
        return out<<"("<<o.x<<","<<o.y<<")";
    }
    // 涉及浮点数
    double length() const {
        return sqrtl(square());
    }
    double distance(const Point& o) const {
        return (*this-o).length();
    }
    T absDistance(const Point& o) const {
        return abs(x-o.x)+abs(y-o.y);
    }
    /// @brief 两向量夹角范围是 [0,PI]
    double ang(const Point& o) const {
        return acosl(max(-1.0l,min(1.0l,dot(o)/(length()*o.length()))));
    }
    /// @brief 逆时针旋转 rad
    Point rotate(double rad) const {
        return Point(x*cos(rad)-y*sin(rad), x*sin(rad)+y*cos(rad));
    }
    Point rotate(double cosr, double sinr) const {
        return Point(x*cosr-y*sinr, x*sinr+y*cosr);
    }
};

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
        assert(a);
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
        for(int i=1; i<=1000000; ++i)
            if((*this*i).x<=100)
                return to_string((*this*i).x) + "/" + to_string(i);
        return "not find.";
    }
};
constexpr int P = 998244353;
using Z=MInt<P>;
constexpr Z power(Z a, ll b) {
    Z ans(1);
    for(; b; b>>=1, a*=a)
        if(b&1) ans*=a;
    return ans;
}
template<int V>// invV<2> * 2 ==1 mod P
constexpr Z invV=power(V,P-2);

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
auto lsh(vector<T>& A) {// return lsh's function
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    return [&](const T& x) {
        return lower_bound(A.begin(), A.end(), x)-A.begin();
    };
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<vector<Point<int>>> a(n, vector<Point<int>>(2));
    vector<int> posx,posy;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<2; ++j) {
            cin>>a[i][j];
            posx.push_back(a[i][j].x);
            posy.push_back(a[i][j].y);
        }
    }

    auto lsx = lsh(posx);
    auto lsy = lsh(posy);
    // debug(posx);
    // debug(posy);

    vector<vector<int>> s(posx.size()+1, vector<int>(posy.size()+1));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<2; ++j) {
            a[i][j].x = lsx(a[i][j].x);
            a[i][j].y = lsy(a[i][j].y);
        }
        s[a[i][0].x][a[i][0].y]++;
        s[a[i][0].x][a[i][1].y]--;
        s[a[i][1].x][a[i][0].y]--;
        s[a[i][1].x][a[i][1].y]++;
    }

    vector<Z> sum(n+1);// sum[i] : i个矩形重叠的格子，的面积总和
    for(int i=0; i+1<posx.size(); ++i) {
        for(int j=0; j+1<posy.size(); ++j) {
            s[i][j] += (j>0?s[i][j-1]:0)+(i>0?s[i-1][j]:0)-(i>0 and j>0 ? s[i-1][j-1] : 0);
            sum[s[i][j]] += 1ll*(posx[i+1]-posx[i])*(posy[j+1]-posy[j]);
        }
    }

    initFac(n);
    for(int j=1; j<=n; ++j) {
        Z ans = 0;
        for(int i=1; i<=n; ++i) {
            ans += sum[i] * (binom(n, j) - binom(n-i, j));
        }
        ans /= binom(n, j);
        cout<<ans<<"\n";
    }
    return 0;
}
/*
https://acm.hdu.edu.cn/showproblem.php?pid=7444
求解在 n 个矩形中随机选取 k=1~n 个不同的矩形，其所有覆盖部分的并集的面积的期望值
离散化，分别对每个格子考虑对 ans1 ~ ansn的贡献
1. 对格子分类，按格子叠的矩形数量分类，统计面积和 f[1]~f[n]
2. 推公式，总面积 ans[k] = sum{i=1~n} f[i] * sum{j=1~i} binom(i, j) * binom(n-i, k-j)
            = sum{i=1~n} f[i] * (binom(n, k) - binom(n-i, k) ) -> 其实就是总方案减去该格子没被选到的方案数。

*/