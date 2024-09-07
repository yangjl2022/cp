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
using i128 = __int128_t;

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

constexpr int MI = numeric_limits<int>::max();

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<Point<ll>> a(n);
    for(auto& x:a) cin>>x;
    sort(a.begin(), a.end());

    int q;
    cin>>q;
    vector<pair<ll,ll>> li;
    {
        vector<ll> G(3*q+1);
        ll Ra,Rb;
        cin>>G[0]>>Ra>>Rb;
        for(int i=0; i<3*q; ++i) {
            G[i+1] = (48271*G[i])%MI;
        }
        for(int i=0; i<q; ++i) {
            int j = i+1;
            ll A = -Ra + (G[3*j-2] % (2*Ra+1));
            ll B = -Rb + (G[3*j-1]*MI + G[3*j]) % (2*Rb+1);
            li.emplace_back(A,B);
        }
    }

    struct Node {
        int i,j;
        Point<ll> v;
    };
    vector<Node> all;
    all.reserve(n*n);
    vector<int> id(n), pos(n);
    for(int i=0; i<n; ++i) {
        id[i] = i;
        for(int j=0; j<n; ++j) {
            if(a[i].x < a[j].x) {
                all.push_back({i, j, a[j]-a[i]});
            }
        }
    }

    sort(all.begin(), all.end(), [&](const Node& u,const Node& v) {
        ll cro = u.v.cross(v.v);
        if(cro != 0) return cro > 0;
        if(a[u.i].x != a[v.i].x) return a[u.i].x < a[v.i].x;
        return a[u.j].x<a[v.j].x;
    });
    // sort(id.begin(), id.end(), [&](const int& i,const int& j) {
    //     if(a[i].y != a[j].y) return a[i].y < a[j].y;
    //     return a[i].x > a[j].x;
    // });
    for(int i=0; i<n; ++i)
        pos[id[i]] = i;

    sort(li.begin(), li.end());

    int p = 0;
    ll ans = 0;
    for(int i=0; i<q; ++i) {
        auto [e,f] = li[i];
        while(p<all.size() and all[p].v.x*e >= all[p].v.y) {
            auto& [p0,p1,tt] = all[p];
            swap(id[pos[p0]], id[pos[p1]]);
            swap(pos[p0], pos[p1]);
            p++;
        }
        int t = (partition_point(id.begin(), id.end(), [&](int j) {
            return a[j].y <  e*a[j].x + f;
        })-id.begin());
        ans += n-t;
        debug(id);
    }
    cout<<ans;
    return 0;
}
/*

hack:
7
-3 1
-2 1
-2 3
0 1
2 1
3 -1
3 1
5
664042067 2 0

ans:
25

Geo:
0 0 O
-3 1 0
-2 1 1
-2 3 2
0 1 3
2 1 4
3 -1 5
3 1 6

https://atcoder.jp/contests/abc344/tasks/abc344_g
*/