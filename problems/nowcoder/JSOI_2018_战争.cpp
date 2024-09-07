/**
 *    author:  yangjl
 *    created: 2024.17.08 22:56:09
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
    bool operator<(const Point& o) const {
        return sgn(x - o.x) < 0 or sgn(x - o.x) == 0 and sgn(y - o.y) < 0;
    }
    bool operator>(const Point& o) const {
        return sgn(x - o.x) > 0 or sgn(x - o.x) == 0 and sgn(y - o.y) > 0;
    }
    static bool argcmp(const Point& a, const Point& b) {
        static auto get = [&](const Point& o) {
            if(sgn(o.x) == 0 and sgn(o.y) == 0) return 0;
            if(sgn(o.y) > 0 or sgn(o.y) == 0 and sgn(o.x) < 0) return 1;
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
template<class T>
struct Polygon {
    int n;
    vector<Point<T>> p;
    // p 以逆时针顺序存储 2 遍
    Polygon(vector<Point<T>> const& p_) : n(p_.size()), p(p_) {
        p.insert(p.end(), p_.begin(), p_.end());
    }
    // 返回 回转数 = 逆时针转头圈数-顺时针转头圈数
    // 1e9 在多边形上 | 0 不在多边形内 | !=0 在多边形内
    int contain(const Point<T>& o) const {
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            Point<T> const& u = p[i], v = p[i + 1];
            Line<T> const l(u, v);
            if(l.contain(o)) return 1e9;
            cnt += l.toLeft(o) > 0 and sgn(u.y - o.y) < 0 and sgn(v.y - o.y) >= 0;
            cnt -= l.toLeft(o) < 0 and sgn(u.y - o.y) >= 0 and sgn(v.y - o.y) < 0;
        }
        return cnt;
    }
    // 多边形面积的两倍，可用于判断点的存储顺序是顺时针或逆时针（逆正顺负）
    T area() const {
        T sum = 0;
        for(int i = 0; i < n; ++i)
            sum += p[i].cross(p[i + 1]);
        return sum;
    }
    // 多边形的周长
    double perimeter() const {
        double sum = 0;
        for(int i = 0; i < n; ++i)
            sum += p[i].distance(p[i + 1]);
        return sum;
    }
};

// using T = ll;
template<class T>
struct Convex : Polygon<T> {
    using Polygon<T>::n;
    using Polygon<T>::p;
    Convex(vector<Point<T>> const& p, bool keepRaw) : Polygon<T>(p) {}
    Convex(vector<Point<T>> const& p_) : Polygon<T>(andrew(p_)) {}
    // 对点集 p 求凸包
    static auto andrew(vector<Point<T>> p) {
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        if(p.size() <= 1) return p;
        vector<Point<T>> st;
        for(auto& e : p) {
            while(st.size() > 1 and
                (st.back() - st.end()[-2]).toLeft(e - st.back()) <= 0)
                st.pop_back();
            st.push_back(e);
        }
        int sz = st.size();
        for(int i = (int)p.size() - 2; i >= 0; --i) {
            while(st.size() > sz and
                (st.back() - st.end()[-2]).toLeft(p[i] - st.back()) <= 0)
                st.pop_back();
            st.push_back(p[i]);
        }
        st.pop_back();
        return st;
    }
    // O(logn)判断点是否在凸多边形内
    // -1 在边界上 | 0 在外部 | 1 严格在内部
    int contain(const Point<T>& o) const {
        if(n == 1) return p[0] == o ? -1 : 0;
        int fTo = (p[1] - p[0]).toLeft(o - p[0]);
        int bTo = (p.back() - p[0]).toLeft(o - p[0]);
        if(fTo == -1 or bTo == 1) return 0;
        if(fTo == 0) return sgn((o - p[0]).dot(o - p[1])) <= 0 ? -1 : 0;
        if(bTo == 0) return sgn((o - p[0]).dot(o - p.back())) <= 0 ? -1 : 0;

        int i = partition_point(p.begin() + 2, p.begin() + n, [&](Point<T> const& v) {
            return (v - p[0]).toLeft(o - p[0]) >= 0;
        }) - p.begin();
        Line<T> const l(p[i - 1], p[i]);
        return l.contain(o) ? -1 : l.toLeft(o) == 1;
    }
    // O(logn) 二分找到 f 方向上的切点 i，满足 p[i]-p[i-1],f(p[i]),p[i+1]-p[i] 逆时旋转
    template<class Func>
    int extreme(Func const& f) {
        assert(n > 2);
        Point<ll> const divVec = f(p[0]);
        bool const flag = (p[0] - p[n - 1]).toLeft(divVec) < 0;
        return partition_point(p.begin(), p.begin() + n, [&](Point<T> const& a) {
            if(divVec.toLeft(a - p[0]) > 0) return flag;
            return (*(&a + 1) - a).toLeft(f(a)) > 0;
        }) - p.begin();
    }
    // O(logn) 二分找到 v 方向 和 -v 方向上的切点，返回值切点下标 in [0,n-1]
    array<int, 2> tangentByLine(Point<T> const& v) {
        int i = extreme([&](...) {return v; });
        int j = extreme([&](...) {return -v; });
        return {i,j};
    }
    // O(logn) 过点 o 向凸包做两条切线（先左后右），返回值切点下标 in [0,n-1]
    // 需要保证 o 在凸包外面
    array<int, 2> tangentByPoint(Point<T> const& o) {
        int i = extreme([&](Point<T> const& a) {return o - a; });
        int j = extreme([&](Point<T> const& a) {return a - o; });
        return {i, j};
    }
};
template<class T>
Convex<T> MinkowskiSum(Convex<T> const& A, Convex<T> const& B) {
    auto cmp = [&](Point<T> const& a, Point<T> const& b) {
        return a.y > b.y or a.y == b.y and a.x < b.x;
    };
    int a = min_element(A.p.begin(), A.p.begin() + A.n, cmp) - A.p.begin();
    int b = min_element(B.p.begin(), B.p.begin() + B.n, cmp) - B.p.begin();
    Point<T> s(A.p[a] + B.p[b]);
    vector<Point<T>> ps(1, s);
    auto popC = [&](Point<T> const& e, Point<T> const& f) {
        return (e - f).toLeft(s - e) == 0 and sgn((e - f).dot(s - e)) >= 0;
    };
    auto f = [&](int owner, int i) {
        return !owner ? A.p[a + i + 1] - A.p[a + i] : B.p[b + i + 1] - B.p[b + i];
    };
    for(int i = 0, j = 0; i < A.n or j < B.n; ) {
        if(j >= B.n or i < A.n and Point<T>::argcmp(f(0, i), f(1, j))) s += f(0, i++);
        else s += f(1, j++);
        while(ps.size() > 1 and popC(ps.back(), ps.end()[-2])) ps.pop_back();
        ps.emplace_back(s);
    }
    ps.pop_back();
    return Convex<T>(ps, true);
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, q;
    cin >> n >> m >> q;
    vector<Point<ll>> a(n), b(m);
    cin >> a >> b;
    for(auto& p : b) {
        p = -p;
    }
    Convex<ll> ve(MinkowskiSum<ll>(a, b));
    // debug(ve.p, ve.n);

    while(q--) {
        Point<ll> x;
        cin >> x;
        cout << (ve.contain(x) != 0) << '\n';
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/28770/J
闵可夫斯基和，凸包，二分

题意：凸包 A,B，多次询问，每次给一个向量 d，问凸包 A 和 B+d 是否有交集

A == B+d <=> A-B = d

对 A-B 求闵可夫斯基和之后，多次判断一个点是否在凸包内

本题数据水了，写了有bug居然过了，现在改好了

*/