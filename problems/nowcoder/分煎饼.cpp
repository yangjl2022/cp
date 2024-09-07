#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

template<class T>
int sgn(const T& v) {
    static constexpr T eps = 1e-18;
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

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x:v) is>>x;
    return is;
}

using P = Point<long double>;
struct Circle {
    int x,y,r;
    friend istream& operator>>(istream& is, Circle &o) {
        return is>>o.x>>o.y>>o.r;
    }
};

const long double PI = acos(-1);

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int> x(n),ra(n);
    for(int i=0; i<n; ++i) {
        cin>>x[i];
        int t;
        cin>>t;
        cin>>ra[i];
    }

    long double l = 0, r = 1e4, ans = -1;
    for(int turn=0; turn<100; ++turn) {
        long double mid = (l+r)/2;
        long double larea = 0, rarea = 0;
        for(int i=0; i<n; ++i) {
            long double S = PI*ra[i]*ra[i];
            if(x[i] + ra[i] <= mid + 1e-15) {
                larea += S;
            }else if(x[i] - ra[i] >= mid - 1e-15) {
                rarea += S;
            }else {
                long double d = abs(x[i]-mid);
                long double o = acos(d/ra[i]);
                long double small = o*ra[i]*ra[i] - d*sqrt(ra[i]*ra[i]-d*d);
                long double big = S-small;
                if(mid < x[i]) {
                    larea += small;
                    rarea += big;
                }else {
                    rarea += small;
                    larea += big;
                }
            }
        }
        if(larea < rarea) {
            ans = mid;
            l = mid;
        }else {
            r = mid;
        }
    }
    cout<<fixed<<setprecision(18);
    cout<<"1\n";
    cout<<"0\n";
    cout<<-ans;
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85333/L
竖着切，明显可以二分
计算几何

推公式计算圆被切下来多少面积

*/