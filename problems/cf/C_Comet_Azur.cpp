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

template<class T>
int sgn(const T& v) {
    static constexpr T eps = 1e-8;
    return v>eps ? 1 : v<-eps ? -1 : 0;
}
template<class T>
struct Point {// Point or Vector
    T x,y;
    Point(): x(0),y(0) {}
    Point(T x, T y): x(x), y(y) {}
    template<class U>
    explicit operator Point<U> () const {
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
    static bool argcmp(const Point& a, const Point& b) {
        static auto get=[&](const Point& o) {
            if(sgn(o.x)==0 and sgn(o.y)==0) return 0;
            if(sgn(o.y)>0 or sgn(o.y)==0 and sgn(o.x)<0) return 1;
            return -1;
        };
        int ta = get(a), tb = get(b);
        if(ta != tb) return ta < tb;
        return a.toLeft(b) == 1;// 不关注极径
        // int tole = a.toLeft(b);
        // if(tole != 0) return tole == 1;
        // return sgn(a.square()-b.square()) < 0;// 极角相同按极径排
    }
    T dot(const Point& o) const {
        return x*o.x + y*o.y;
    }
    T cross(const Point& o) const {
        return x*o.y - y*o.x;
    }
    int toLeft(const Point& o) const {
        return sgn(cross(o));
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
    friend ostream& operator<<(ostream& out, Point const& o) {
        return out<<"("<<o.x<<","<<o.y<<")";
    }
    // 涉及浮点数
    double length() const {
        return sqrtl(square());
    }
    double distance(const Point& o) const {
        return (*this-o).length();
    }
    // 逆时针旋转 rad
    template<class U>
    Point<U> rotate(U cosr, U sinr) const {
        return Point(x*cosr-y*sinr, x*sinr+y*cosr);
    }
    // 两向量夹角范围是 [0,PI]
    double ang(const Point& o) const {
        return acosl(max(-1.0l,min(1.0l,dot(o)/(length()*o.length()))));
    }
};
template<class T>
struct Line {// Line or Segment
    Point<T> a,b;// 方向向量为 a->b
    Line() {}
    Line(const Point<T>& a, const Point<T>& b): a(a),b(b) {}
    template<class U>
    Line(const Point<U>& a, const Point<U>& b): a(a),b(b) {}
    // Line ----------------------------------------------------------
    bool parallel(const Line& l) const {
        return sgn((b-a).cross(l.b-l.a)) == 0;
    }
    int toLeft(const Point<T>& o) const {
        return (b-a).toLeft(o-a);
    }
    // 涉及浮点数
    // 直线交点
    Point<double> lineIntersection(const Line& l) const {
        return Point<double>(a) + Point<double>(b-a) * 
            (1. * (l.b-l.a).cross(a-l.a) / (l.b-l.a).cross(a-b));
    }
    // 点到直线的距离
    double distanceLP(const Point<T>& o) const {
        return abs((a-b).cross(a-o)) / (a-b).length();
    }
    // 点在直线上的投影
    Point<T> projection(const Point<T>& o) const {
        return a + (b-a)*(1. * (b-a).dot(o-a) / (b-a).square());
    }
    // Segment ----------------------------------------------------------
    // -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
    int contain(const Point<T>& o) const {
        if(o==a or o==b) return -1;
        return (o-a).toLeft(o-b)==0 and sgn((o-a).dot(o-b)) < 0;
    }
    // 判断线段直线是否相交
    // 0 线段和直线不相交 | 1 线段和直线严格相交 | 2 仅在某一线段端点处相交 | 3 直线包含线段
    int interWithLine(const Line& l) const {
        int num = !l.toLeft(a) + !l.toLeft(b);
        if(num) return num+1;
        return l.toLeft(a) != l.toLeft(b);
    }
    // 判断两线段是否相交
    // 0 两线段不相交 | 1 两线段严格相交 | 2 仅在某一线段端点处相交 | 3 两线段有重叠
    int interWithSegment(Line s) const {
        if((a<b) != (s.a<s.b))
            swap(s.a, s.b);
        int num = (contain(s.a)!=0) + (contain(s.b)!=0) 
                + (s.contain(a)!=0) + (s.contain(b)!=0);
        if(parallel(s)) {
            if(!num) return 0;
            if(b==s.a or a==s.b) return 2;// -.-
            return 3;
        }
        if(num) return 2;
        return toLeft(s.a)*toLeft(s.b)==-1 and s.toLeft(a)*s.toLeft(b)==-1;
    }
    // 点到线段的距离
    double distanceSP(const Point<T>& o) const {
        if(sgn((o-a).dot(b-a)) < 0) return o.distance(a);
        if(sgn((o-b).dot(a-b)) < 0) return o.distance(b);
        return abs((a-b).cross(a-o)) / (a-b).length();
    }
    // 两线段间距离
    double distanceSS(const Line& s) const {
        if(interWithSegment(s)) return 0;
        return min({distanceSP(s.a),distanceSP(s.b),
                s.distanceSP(a),s.distanceSP(b)});
    }
};

const double PI = acos(-1), eps = 1e-8;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    Point<ll> o(0,0);
    vector<Point<ll>> a(n);
    vector<double> d(n), ang(n);
    for(int i=0; i<n; ++i) {
        cin>>a[i];
        d[i] = a[i].distance(o);
        ang[i] = atan2(a[i].y, a[i].x);
    }

    double ll = 0, rr = 1e9;
    for(int tt=0; tt<60; ++tt) {
        double mid = (ll+rr)/2;
        auto check = [&] () {

        vector<pair<double,int>> v;
        for(int i=0; i<n; ++i) {
            double d_ang = mid>=d[i] ? PI/2 : PI/2 - acos(mid/d[i]);
            double l = ang[i]-d_ang;
            double r = ang[i]+d_ang;
            if(l < -PI) l += 2*PI;
            if(r > PI) r -= 2*PI;
            v.emplace_back(l, 1);
            v.emplace_back(r, -1);
            if(l > r) {
                v.emplace_back(-PI, 1);
            }
        }
        sort(ALL(v));
        int ans = 0, pre = 0;
        for(auto [x,y]:v) {
            pre += y;
            ans = max(ans, pre);
        }
        return ans >= n/2;

        };

        if(check()) rr=mid;
        else ll=mid;
    }

    cout<<fixed<<setprecision(12);
    cout<<ll*2;
    return 0;
}
/*
计算几何
二分答案，求角度，排序统计
https://codeforces.com/gym/518619/problem/C


*/