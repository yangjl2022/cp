/**
 *    author:  yangjl
 *    created: 2024.13.08 22:20:02
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

// using T = ll;
template<class T>
struct DynamicConvex {
    // inf <= MAX/2，防止 Point::operator< 中的减法溢出
    static constexpr T inf = numeric_limits<T>::max() / 2;
    struct HalfConvex {
        int expect;// 从左到右期望的 toLeft 值, -1 or 1
        set<Point<T>> s;
        T L, R;
        HalfConvex(int expect) : expect(expect), L(inf), R(-inf) {
            s.emplace(-inf, 0);
            s.emplace(inf, 0);// 哨兵
        }
        bool exist(typename set<Point<T>>::iterator it) {
            return it->x != inf and it->x != -inf;
        }
        bool add(Point<T> const& o, bool join) {
            auto b = s.lower_bound(o);
            if(o.x == prev(b)->x) {
                b--;
            }
            if(sgn(o.x - L) >= 0 and sgn(o.x - R) <= 0) {
                if(sgn(o.x - L) == 0) {
                    if(sgn(o.y - next(s.begin())->y) != -expect) {
                        return false;
                    }
                } else if(Point<T>(*b - *prev(b)).toLeft(o - *prev(b)) != -expect) {
                    return false;
                }
            }
            if(!join) {
                return true;
            }
            if(exist(b)) {
                while(exist(next(b)) and Point<T>(*b - o).toLeft(*next(b) - *b) != expect) {
                    b = s.erase(b);
                }
            }
            if(auto f = prev(b); exist(f)) {
                while(exist(prev(f)) and Point<T>(*f - *prev(f)).toLeft(o - *f) != expect) {
                    f = --s.erase(f);
                }
            }
            s.insert(o);
            L = min(L, o.x);
            R = max(R, o.x);
            return true;
        }
    };
    HalfConvex up, down;
    DynamicConvex() : up(-1), down(1) {}
    bool outside(Point<T> const& p, bool join = false) {
        bool t0 = up.add(p, join), t1 = down.add(p, join);
        return t0 or t1;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    DynamicConvex<ll> dc;
    int tt;
    cin >> tt;
    while(tt--) {
        int op;
        Point<ll> o;
        cin >> op >> o;
        if(op == 1) {
            dc.outside(o, true);
        } else {
            cout << (!dc.outside(o) ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/28770/G
动态凸包，二分

题意：
多从操作
1. 凸包加点
2. 询问点是否在凸包内

使用 set 分别维护上凸壳和下凸壳

1. 加点
    - 如果点严格在凸包左边或右边，以右边为例，那么对凸包上下分别右后往前toLeft判断 pop 即可
    - 否则，如果点位于凸包上方或者下方，以下方为例，二分找到该点射线在下凸壳的切点，删除两切点之间的点
    - 否则就是凸包内，不操作
2. 询问
    - 判断上面三种情况即可

*/