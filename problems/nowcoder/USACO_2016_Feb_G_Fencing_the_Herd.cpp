/**
 *    author:  yangjl
 *    created: 2024.17.08 17:58:43
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
template<class T>
int sgn(const T& v) {
    static constexpr T eps = 1e-8;
    return v > eps ? 1 : v < -eps ? -1 : 0;
}
template<class T>
struct Point {// Point or Vector
    T x, y;
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    template<class U>
    explicit operator Point<U>() const {
        return Point<U>(U(x), U(y));
    }
    Point operator+(const Point& o) const {
        return Point(x + o.x, y + o.y);
    }
    Point operator-(const Point& o) const {
        return Point(x - o.x, y - o.y);
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    Point operator*(const T& v) const {
        return Point(x * v, y * v);
    }
    friend Point operator*(const T& v, const Point<T>& o) {
        return Point(o.x * v, o.y * v);
    }
    Point operator/(const T& v) const {
        return Point(x / v, y / v);
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
        return sgn(x - o.x) == 0 and sgn(y - o.y) == 0;
    }
    bool operator!=(const Point& o) const {
        return sgn(x - o.x) != 0 or sgn(y - o.y) != 0;
    }
    // bool operator<(const Point& o) const {
    //     return sgn(x - o.x) < 0 or sgn(x - o.x) == 0 and sgn(y - o.y) < 0;
    // }
    bool operator>(const Point& o) const {
        return sgn(x - o.x) > 0 or sgn(x - o.x) == 0 and sgn(y - o.y) > 0;
    }
    // static bool argcmp(const Point& a, const Point& b) {
    friend bool operator<(const Point& a, const Point& b) {
        static auto get = [&](const Point& o) {
            if(sgn(o.x) == 0 and sgn(o.y) == 0) return 0;
            if(sgn(o.y) > 0 or sgn(o.y) == 0 and sgn(o.x) < 0) return 1;
            return -1;
        };
        int ta = get(a), tb = get(b);
        if(ta != tb) return ta < tb;
        int tole = a.toLeft(b);
        if(tole != 0) return tole == 1;
        return sgn(a.square() - b.square()) < 0;// 极角相同按极径排
    }
    T dot(const Point& o) const {
        return x * o.x + y * o.y;
    }
    T cross(const Point& o) const {
        return x * o.y - y * o.x;
    }
    int toLeft(const Point& o) const {
        return sgn(cross(o));
    }
    T square() const {
        return x * x + y * y;
    }
    T interSquare(const Point& o) const {
        return (*this - o).square();
    }
    friend istream& operator>>(istream& in, Point& o) {
        return in >> o.x >> o.y;
    }
    friend ostream& operator<<(ostream& out, Point const& o) {
        return out << "(" << o.x << "," << o.y << ")";
    }
    // 涉及浮点数
    double length() const {
        return sqrtl(square());
    }
    double distance(const Point& o) const {
        return (*this - o).length();
    }
    // 逆时针旋转 rad
    template<class U>
    Point<U> rotate(U cosr, U sinr) const {
        return Point(x * cosr - y * sinr, x * sinr + y * cosr);
    }
    // 两向量夹角范围是 [0,PI]
    double ang(const Point& o) const {
        return acosl(max(-1.0l, min(1.0l, dot(o) / (length() * o.length()))));
    }
};
template<class T>
struct Line {// Line or Segment
    Point<T> a, b;// 方向向量为 a->b
    Line() {}
    Line(const Point<T>& a, const Point<T>& b) : a(a), b(b) {}
    template<class U>
    Line(const Point<U>& a, const Point<U>& b) : a(a), b(b) {}
    // Line ----------------------------------------------------------
    bool parallel(const Line& l) const {
        return sgn((b - a).cross(l.b - l.a)) == 0;
    }
    int toLeft(const Point<T>& o) const {
        return (b - a).toLeft(o - a);
    }
    // 涉及浮点数
    // 直线交点
    Point<double> lineIntersection(const Line& l) const {
        return Point<double>(a) + Point<double>(b - a) *
            (1. * (l.b - l.a).cross(a - l.a) / (l.b - l.a).cross(a - b));
    }
    // 点到直线的距离
    double distanceLP(const Point<T>& o) const {
        return abs((a - b).cross(a - o)) / (a - b).length();
    }
    // 点在直线上的投影
    Point<T> projection(const Point<T>& o) const {
        return a + (b - a) * (1. * (b - a).dot(o - a) / (b - a).square());
    }
    // Segment ----------------------------------------------------------
    // -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
    int contain(const Point<T>& o) const {
        if(o == a or o == b) return -1;
        return (o - a).toLeft(o - b) == 0 and sgn((o - a).dot(o - b)) < 0;
    }
    // 判断线段直线是否相交
    // 0 线段和直线不相交 | 1 线段和直线严格相交 | 2 仅在某一线段端点处相交 | 3 直线包含线段
    int interWithLine(const Line& l) const {
        int num = !l.toLeft(a) + !l.toLeft(b);
        if(num) return num + 1;
        return l.toLeft(a) != l.toLeft(b);
    }
    // 判断两线段是否相交
    // 0 两线段不相交 | 1 两线段严格相交 | 2 仅在某一线段端点处相交 | 3 两线段有重叠
    int interWithSegment(Line s) const {
        if((a < b) != (s.a < s.b))
            swap(s.a, s.b);
        int num = (contain(s.a) != 0) + (contain(s.b) != 0)
            + (s.contain(a) != 0) + (s.contain(b) != 0);
        if(parallel(s)) {
            if(!num) return 0;
            if(b == s.a or a == s.b) return 2;// -.-
            return 3;
        }
        if(num) return 2;
        return toLeft(s.a) * toLeft(s.b) == -1 and s.toLeft(a) * s.toLeft(b) == -1;
    }
    // 点到线段的距离
    double distanceSP(const Point<T>& o) const {
        if(sgn((o - a).dot(b - a)) < 0) return o.distance(a);
        if(sgn((o - b).dot(a - b)) < 0) return o.distance(b);
        return abs((a - b).cross(a - o)) / (a - b).length();
    }
    // 两线段间距离
    double distanceSS(const Line& s) const {
        if(interWithSegment(s)) return 0;
        return min({distanceSP(s.a),distanceSP(s.b),
                s.distanceSP(a),s.distanceSP(b)});
    }
};

// using T = ll;
template<class T>
struct DynamicConvex {
    /// @note operator< 使用极角序，并考虑极径
    Point<T> o;
    set<Point<T>> s; // 坐标扩大三倍，使得三角形中心为整数
    using Iter = decltype(s.begin());
    map<Point<T>, Iter> edge;
    auto nxt(Iter it) const {
        return next(it) == s.end() ? s.begin() : next(it);
    }
    auto pre(Iter it) const {
        return it == s.begin() ? --s.end() : prev(it);
    }
    bool contain(Point<T> const& a) const {
        if(s.size() == 0) return 0;
        if(s.size() == 1) return *s.begin() == a * 3;
        if(s.size() == 2) return Line<T>(*s.begin(), *s.rbegin()).contain(a);
        auto it = s.lower_bound(a * 3 - o);
        if(it == s.end()) it = s.begin();
        return (*it - *pre(it)).toLeft(a * 3 - o - *pre(it)) >= 0;
    }
    void add(Point<T> a) {
        if(s.size() <= 1) {
            s.insert(a * 3);
            return;
        }
        if(s.size() == 2) {
            auto u = *s.begin(), v = *s.rbegin();
            if((u - v).toLeft(a * 3 - v) == 0) return;
            o = (u + v + a * 3) / 3;
            s = {u - o, v - o, a * 3 - o};
            for(auto it = s.begin(); it != s.end(); ++it) addEdge(it, nxt(it));
            return;
        }
        if(contain(a)) return;
        a = a * 3 - o;
        auto it = s.insert(a).first, np = nxt(it), pp = pre(it);
        delEdge(pp, np);
        while(s.size() > 3 and ((*np - a).toLeft(*nxt(np) - *np)) != 1) {
            delEdge(np, nxt(np));
            s.erase(np);
            np = nxt(it);
        }
        while(s.size() > 3 and ((*pp - *pre(pp)).toLeft(a - *pp)) != 1) {
            delEdge(pre(pp), pp);
            s.erase(pp);
            pp = pre(it);
        }
        addEdge(pre(it), it);
        addEdge(it, nxt(it));
    }
    void addEdge(Iter it, Iter nit) {// s.size()>=3 时维护信息
        edge[*nit - *it] = it;
    }
    void delEdge(Iter it, Iter nit) {
        edge.erase(*nit - *it);
    }
    /// @note 调用前注意直线 ax+by=c 的坐标扩大三倍 ax+by=3c
    array<Point<T>, 2> extremeByLine(Point<T> const& v) const {
        assert(s.size() > 2);
        auto get = [&](Point<T> const& v) {
            auto it = edge.lower_bound(v);
            if(it == edge.end()) it = edge.begin();
            return *(it->second) + this->o;
        };
        return {get(v), get(-v)};
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    DynamicConvex<ll> dc;
    for(int i = 0; i < n; ++i) {
        Point<ll> p;
        cin >> p;
        dc.add(p);
    }

    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            Point<ll> p;
            cin >> p;
            dc.add(p);
        } else {
            ll a, b, c;
            cin >> a >> b >> c;
            c *= 3;
            Point<ll> v(-b, a);

            if(dc.s.size() == 1) {
                auto o = *dc.s.begin();
                if(a * o.x + b * o.y == c) {
                    cout << "NO\n";
                } else {
                    cout << "YES\n";
                }
                continue;
            }

            using P = Point<__int128_t>;
            P A, B;
            if(dc.s.size() == 2) {
                A = P(*dc.s.begin());
                B = P(*dc.s.rbegin());
            } else {
                auto [p1, p2] = dc.extremeByLine(v);
                A = P(p1);
                B = P(p2);
            }
            debug(A, B);


            P C(0, c), D(c, 0);
            int t0, t1;
            if(b != 0) {
                t0 = sgn(P(v).cross(b * A - C));
                t1 = sgn(P(v).cross(b * B - C));
            } else {
                t0 = sgn(P(v).cross(a * A - D));
                t1 = sgn(P(v).cross(a * B - D));
            }

            debug(t0, t1);
            if(t0 and t0 == t1) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/28770/I
动态凸包，二分，切线

题意
1. 凸包加点
2. 问凸包是否严格位于直线某一侧

直线形式为 ax+by=c，伴随凸包扩大三倍后 ax+by=3c
=> 方向向量 v = (-b, a)

二分得到两切点 p1,p2 后，判断 v.cross(p1-o) 和 v.cross(p2-o) 是不是同符号即可
其中，o 是直线上的一点。

考虑避免浮点运算
1. o = (0, c/b), if b!=0
    sgn(v.cross(p1-o)) = sgn(v.cross(p2-o)) <=>
    sgn(v.cross( b*p1 - P(0,c) )) = sgn(v.cross( b*p2 - P(0, c) ))
2. o = (c/a, 0), if b=0, 即直线为 ax = c
    sgn(v.cross( a*p1 - P(c,0) )) = sgn(v.cross( a*p2 - P(c, 0) ))


*/