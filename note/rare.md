- [常用头文件](#常用头文件)
- [最长上升子序列](#最长上升子序列)
- [手写高精度](#手写高精度)
- [离散化](#离散化)
- [手写链表](#手写链表)
- [网格遍历](#网格遍历)
- [数据结构维护最大子段和](#数据结构维护最大子段和)
- [逆波兰表达式](#逆波兰表达式)
- [int取模](#int取模)
- [long取模](#long取模)
- [多项式sin和cos](#多项式sin和cos)
- [FWT扩展运算](#fwt扩展运算)
- [李超线段树动态开点](#李超线段树动态开点)
- [前缀和](#前缀和)
- [treap](#treap)
- [splay](#splay)
- [ST表](#st表)
- [可删除堆](#可删除堆)
- [最优匹配](#最优匹配)
- [有向无环图上的支配树](#有向无环图上的支配树)
- [模拟费用流](#模拟费用流)
- [上下界最大流](#上下界最大流)
- [有负环的费用流](#有负环的费用流)
- [斯坦纳树](#斯坦纳树)
- [最小树形图](#最小树形图)
- [最小直径生成树](#最小直径生成树)
- [k短路](#k短路)
- [弦图](#弦图)
- [稳定婚姻系统](#稳定婚姻系统)
- [一般图最大权匹配](#一般图最大权匹配)
- [全局最小割](#全局最小割)
- [01bfs](#01bfs)
- [矩阵变长版本](#矩阵变长版本)
  - [分数类](#分数类)
  - [完全二叉树上计数](#完全二叉树上计数)
  - [区间交集并集](#区间交集并集)
- [异或不等式](#异或不等式)


# 常用头文件
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
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
#include<list>
#include<bitset>
#include<climits>
```

# 最长上升子序列
**Dilworth定理**：任意偏序集中，最长正链的长度 = 最少反链条数
```cpp
int d[N];
template<class Arr>
int getLen(const Arr& a, int l, int r) {
    int dn=0;
    for (int i=l; i<=r; ++i) {
        int id=lower_bound(d, d+dn, a[i])-d;
        if (id>=dn) d[dn++]=a[i];
        else d[id]=a[i];
    }
    return dn;
}
```

# 手写高精度  
[P1601 A+B Problem（高精）](https://www.luogu.com.cn/problem/P1601)  
[P2142 高精度减法](https://www.luogu.com.cn/problem/P2142)  
[P1303 A*B Problem](https://www.luogu.com.cn/problem/P1303)  
[P2005 A/B Problem II](https://www.luogu.com.cn/problem/P2005)
（二分check a>=b*mid可能更快）
 
```cpp
class bigInt {
    #define vec vector<int>
    #define pb emplace_back
    #define sz(x) (int)x.size()
    bigInt() {}
public:
    vec v;
    bigInt(long long x) {
        if(!x) v.assign(1, 0);
        for(; x; x/=10)
            v.pb(x%10);
    }
    bigInt(const string& s):v(s.rbegin(),s.rend()) {
        for(int& c:v)
            c^=48;
        if(v.empty()) v.pb(0);
        clean();
    }
    template<class T>
    bigInt operator+(const T& b) const{
        bigInt B(b), C;
        for(int i=0, g=0; g||i<sz(v)||i<sz(B.v); ++i) {
            if(i<sz(v)) g+=v[i];
            if(i<sz(B.v)) g+=B.v[i];
            C.v.pb(g%10);
            g/=10;
        }
        return C;
    }
    template<class T>
    bigInt operator-(const T& b) const{
        bigInt B(b), C;
        for(int i=0, g=0; i<sz(v); ++i) {
            g=v[i]-g;
            if(i<sz(B.v)) g-=B.v[i];
            C.v.pb((g+10)%10);
            g=(g<0);
        }
        C.clean();
        return C;
    }
    bigInt operator*(const bigInt& B) const{
        bigInt C;
        C.v.resize(sz(v)+sz(B.v), 0);
        for(int i=0; i<sz(v); ++i)
            for(int j=0; j<sz(B.v); ++j)
                C.v[i+j]+=v[i]*B.v[j];
        for(int i=0; i<sz(C.v)-1; ++i)
            if(C.v[i]>9) {
                C.v[i+1]+=C.v[i]/10;
                C.v[i]%=10;
            }
        C.clean();
        return C;
    }
    bigInt operator*(long long b) const{
        bigInt C;
        long long g=0;
        for(int i=0; g||i<sz(v); ++i) {
            if(i<sz(v)) g+=b*v[i];
            C.v.pb(g%10);
            g/=10;
        }
        return C;
    }
    // A/B=C...R
    pair<bigInt,bigInt> div(const bigInt& B) const{
        bigInt C, R(0);
        C.v.resize(sz(v));
        for(int i=sz(v)-1; i>=0; --i) {
            R=R*10;
            R.v[0]=v[i]; // R+=v[i]
            while(R.cmp(B)>=0) {
                R=R-B;
                C.v[i]++;
            }
        }
        C.clean();
        return {C, R};
    }
    // A/b=C...r
    pair<bigInt,long long> div(long long b) const{
        bigInt C;
        C.v.resize(sz(v));
        long long r=0;
        for(int i=sz(v)-1; i>=0; --i) {
            r=(r<<3)+(r<<1)+v[i];
            C.v[i]=r/b;
            r%=b;
        }
        C.clean();
        return {C, r};
    }
    template<class T>
    int cmp(const T& b) const{
        bigInt B(b);
        if(sz(v)!=sz(B.v))
            return sz(v)>sz(B.v)?1:-1;
        for(int i=sz(v)-1; i>=0; --i) {
            if(v[i]!=B.v[i])
                return v[i]>B.v[i]?1:-1;
        }
        return 0;
    }
    bool operator<(const bigInt& a) const {
        return cmp(a)==-1;
    }
    void clean() {
        while(sz(v)>1&&!v.back())
            v.pop_back();
    }
    long long vtoll() const{ //vec 转 long long
        long long x=0;
        for(int i=sz(v)-1; i>=0; --i)
            x=(x<<3)+(x<<1)+v[i];
        return x;
    }
    string vtostr() const{ //vec 转 string
        string s(v.rbegin(),v.rend());
        for(char& c:s)
            c^=48;
        if(s.empty()) s+='0';
        return s;
    }
    friend istream& operator>>(istream& in,bigInt& a) {
        string s;
        in>>s;
        a=s;
        return in;
    }
    friend ostream& operator<<(ostream& out,const bigInt& a) {
        return out<<a.vtostr();
    }
};
```

# 离散化
```cpp
template<class T>
auto lsh(vector<T>& A) {// polish A
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    return [&](T x) {
        return lower_bound(A.begin(), A.end(), x)-A.begin();
    };
}
```

# 手写链表
```cpp
// 与STL不同，这里的end表示最后一个元素的指针
// 不要忘记 mylist::init()
template<class T>
struct mylist {
    struct Node{
        T data;
        Node *prev,*next;
    };
    using iter=Node*;
    static Node node[1000006];
    static int en;
    static void init() {en=-1;}
    static iter newNode(T data,iter pre,iter nxt) {
        node[++en].data=data;
        node[en].prev=pre;
        node[en].next=nxt;
        return &node[en];
    }
    iter begin,end;
    int size;
    mylist(): begin(nullptr),end(nullptr),size(0) {}
    T& front()const {
        assert(size);
        return begin->data;
    }
    T& back()const {
        assert(size);
        return end->data;
    }
    iter first_push(T data) {
        begin=end=newNode(data,nullptr,nullptr);
        ++size;
        return begin;
    }
    iter push_front(T data) {
        if(!size)
            return this->first_push(data);
        // it,begin
        iter it=newNode(data,nullptr,begin);
        begin=begin->prev=it;
        ++size;
        return begin;
    }
    void pop_front() {
        assert(size);
        if(size==1) {
            begin=end=nullptr;
            size=0;
            return;
        }
        // begin,newBigin
        begin=begin->next;
        begin->prev=nullptr;
        --size;
    }
    iter push_back(T data) {
        if(!size)
            return this->first_push(data);
        // end,it
        iter it=newNode(data,end,nullptr);
        end=end->next=it;
        ++size;
        return end;
    }
    void pop_back() {
        assert(size);
        if(size==1) {
            begin=end=nullptr;
            size=0;
            return;
        }
        // newEnd,end
        end=end->prev;
        end->next=nullptr;
        --size;
    }
    void splice(mylist<T>& q) {
        if(!q.size)
            return;
        if(!this->size)
            return swap(*this,q);
        this->end->next=q.begin;
        q.begin->prev=this->end;
        this->end=q.end;
        size+=q.size;
        q.clear();
    }
    void clear() {
        *this=mylist<T>();
    }
    iter insert_after(iter it,T data) {
        assert(it!=nullptr);
        // it,p,it->next
        iter p=newNode(data,it,it->next);
        if(it==end)
            end=p;
        else
            it->next->prev=p;
        it->next=p;
        ++size;
        return p;
    }
    vector<T> getInfo()const {
        vector<T> datas;
        for(iter it=begin; it!=nullptr; it=it->next)
            datas.push_back(it->data);
        return datas;
    }
};
template<typename T>
int mylist<T>::en;
template<typename T>
typename mylist<T>::Node mylist<T>::node[1000006];
```

# 网格遍历
```cpp
const vector<int> dx{0,1,0,-1};
const vector<int> dy{1,0,-1,0};
#if 0
for(int idx=0; idx<dx.size(); ++idx) {
    int nx=x+dx[idx], ny=y+dy[idx];
    if(nx<1 || nx>n || ny<1 || ny>m)
        continue;
}
#endif
```

# 数据结构维护最大子段和
```cpp
struct Node {
    int sum,mx,mn;
    int lmax,lmin;
    int rmax,rmin;
    Node() {}
    explicit Node(int x)
    :sum(x),mx(max(0,x)),mn(min(0,x)),lmax(mx),lmin(mn),rmax(mx),rmin(mn){}
    friend Node operator+(const Node& lhs,const Node& rhs) {
        Node re;
        re.sum=lhs.sum+rhs.sum;
        re.mx=max({lhs.mx,rhs.mx,lhs.rmax+rhs.lmax});
        re.mn=min({lhs.mn,rhs.mn,lhs.rmin+rhs.lmin});
        re.lmax=max(lhs.lmax,lhs.sum+rhs.lmax);
        re.lmin=min(lhs.lmin,lhs.sum+rhs.lmin);
        re.rmax=max(rhs.rmax,rhs.sum+lhs.rmax);
        re.rmin=min(rhs.rmin,rhs.sum+lhs.rmin);
        return re;
    }
};
```


# 逆波兰表达式
```cpp
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <heltim7/debug>
#else
#define debug(...) 7
#endif

#define endl '\n'
using LL=long long;

string shunting_yard(string &s) {
    // 是否为基础值
    auto is_ident=[](char x) {
        return isdigit(x)||x=='x';
    };

    // 是否为操作符
    auto is_oper=[](char x) {
        const static string op="+-*";
        return find(op.begin(),op.end(),x)!=op.end();
    };

    // 是否为函数
    auto is_func=[](char x) {
        return x=='s';
    };

    // 是否左结合
    auto left_assoc=[](char x) {
        const static string op="+-*";
        return find(op.begin(),op.end(),x)!=op.end();
    };

    // 运算优先级 优先级越高，值越小
    auto prio=[](char x) {
        if(x=='*') return 1;
        if(x=='+') return 2;
        if(x=='-') return 3;
        return 4;
    };

    string res,stk;
    for(auto x:s) {
        if(is_ident(x)) res.push_back(x);
        else if(is_func(x)) stk.push_back(x);
        else if(is_oper(x)) {
            while(stk.size()&&is_oper(stk.back())) {
                char y=stk.back();
                if (
                    prio(y)<prio(x)||
                    left_assoc(x)&&prio(x)==prio(y)
                ) stk.pop_back(),res.push_back(y);
                else break;
            }
            stk.push_back(x);
        }
        else if(x=='(') stk.push_back(x);
        else if(x==')') {
            while(stk.size()&&stk.back()!='(')
                res.push_back(stk.back()),stk.pop_back();
            assert(stk.size());
            stk.pop_back();
            if(stk.size()&&is_func(stk.back()))
                res.push_back(stk.back()),stk.pop_back();
        }
        else assert(0);
    }

    while(stk.size()) {
        assert(stk.back()!='(');
        res.push_back(stk.back());
        stk.pop_back();
    }
    return res;
}

LL cal(string s,int v) {
    debug(s);
    vector<LL> stk;
    for(char x:s) {
        if(isdigit(x)) stk.emplace_back(x-'0');
        else if(x=='x') stk.emplace_back(v);
        else if(x=='s') stk.back()=sqrt(stk.back());
        else {
            LL a=stk.end()[-1];
            LL b=stk.end()[-2];
            stk.pop_back();
            if(x=='*') stk.back()=b*a;
            else if(x=='+') stk.back()=b+a;
            else if(x=='-') stk.back()=b-a;
            else assert(0);
        }
        debug(stk);
    }
    return stk.back();
}

void solve() {
    string s;
    cin>>s;
    cout<<cal(shunting_yard(s),2)<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
```

# int取模
```cpp
namespace Modulus {
    constexpr int P=998244353;
    inline int norm(int x) {
        return x<0? x+P: x>=P? x-P: x;
    }
    template<class ...T>
    int sum(T...args) {// 比 一个一个norm() 慢
        long long res=(0ll+...+args);
        while(res>=P) res-=P;
        while(res<0) res+=P;
        return res;
    }
    int qmi(int a,long long b) {
        int ans=1;
        for(; b; b>>=1,a=1ll*a*a%P)
            if(b&1) ans=1ll*ans*a%P;
        return ans;
    }
    int inverse(int a) {
        int u=0,v=1,m=P;
        while(a!=0) {
            int t=m/a;
            m-=t*a, swap(a,m);
            u-=t*v, swap(u,v);
        }
        return (u%P+P)%P;
    }
} using namespace Modulus;
```

# long取模
from jiangly 的 $Mlong$ 版本
```cpp
using i64 = long long;
template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<i64 P>
struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}
    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    explicit constexpr operator i64() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};
// template<>
// i64 MLong<0LL>::Mod = i64(1E18) + 9;
using Z = MLong<i64(1E18) + 9>;
```

# 多项式sin和cos
```cpp
const Z I=911660635,INVI=I.inv();// I=G^((mod-1)/4)
Poly Cos(const Poly& a,int m=-1) {
    assert(a[0].x==0);
    if(m==-1) m=a.size();
    Poly c=modxk(a,m);
    return (Exp(c*I)+Exp(c*(P-I)))*((1+P)>>1);
}
Poly Sin(const Poly& a,int m=-1) {
    assert(a[0].x==0);
    if(m==-1) m=a.size();
    Poly c=modxk(a,m);
    return (Exp(c*I)-Exp(c*(P-I)))*(((1+P)>>1)*INVI);
}
```

# FWT扩展运算
扩展:16种运算随意组合
```cpp
namespace {
    int opt[30]; //op(i,j,k)=opt[i]>>(j*2+k)&1
    using Poly=vector<ll>;
    void fwt(Poly& a,Poly& b) {
        for(int m=1,n=a.size(),k=0; m<n; m<<=1,++k)
            for(int i=0; i<n; i+=m<<1)
                for(int j=0; j<m; ++j) {
                    auto &a0=a[i+j],&a1=a[i+j+m],&b0=b[i+j],&b1=b[i+j+m];
                    switch (opt[k]) {
                        case 0:
                        a0+=a1,a1=0,b0+=b1,b1=0; break;
                        case 1:
                        a1+=a0,swap(a0,a1),b1+=b0,swap(b0,b1); break;
                        case 2:
                        a1+=a0,swap(a0,a1),b0+=b1; break;
                        case 3:
                        swap(a0,a1),b0=b1=b0+b1; break;
                        case 4:
                        a0+=a1,b1+=b0,swap(b0,b1); break;
                        case 5:
                        a0=a1=a0+a1,swap(b0,b1); break;
                        case 6:
                        a0+=a1,a1=a0-(a1<<1),b0+=b1,b1=b0-(b1<<1); break;
                        case 7:
                        a0+=a1,swap(a0,a1),b0+=b1,swap(b0,b1); break;
                        case 8:
                        a0+=a1,b0+=b1; break;
                        case 9:
                        a1+=a0,a0=a1-(a0<<1),swap(a0,a1),b0+=b1,
                        b1=b0-(b1<<1); break;
                        case 10:
                        a0=a1=a0+a1; break;
                        case 11:
                        a0+=a1,swap(a0,a1),b1+=b0; break;
                        case 12:
                        b0=b1=b0+b1; break;
                        case 13:
                        a1+=a0,b0+=b1,swap(b0,b1); break;
                        case 14:
                        a1+=a0,b1+=b0; break;
                        case 15:
                        a1+=a0,a0=0,b1+=b0,b0=0; break;
                    }
                }
    }
    void ifwt(Poly& c) {
        for(int m=1,n=c.size(),k=0; m<n; m<<=1,++k)
            for(int i=0; i<n; i+=m<<1)
                for(int j=0; j<m; ++j) {
                    auto &c0=c[i+j],&c1=c[i+j+m];
                    switch (opt[k]) {
                        case 1: case 2: case 4: case 8:
                            c0-=c1; break;
                        case 6: case 9: 
                            c0=(c0+c1)/2,c1=c0-c1; break;
                        case 7: case 11: case 13: case 14:
                            c1-=c0; break;
                        default: break;
                    }
                }
    }
    Poly op(Poly a,Poly b) {
        fwt(a,b);
        for(int i=0,n=a.size(); i<n; ++i) a[i]*=b[i];
        ifwt(a);
        return a;
    }
}
```

# 李超线段树动态开点

动态开点：  
不需要离散化，空间需要的更多
```cpp
namespace LcSeg {// 动态开点的李超线段树
    #define u1 lch[u],l,mid
    #define u2 rch[u],mid+1,r
    const double EPS = 1e-6;
    // TODO begin--------------
    using T = int;
    const T INF = numeric_limits<T>::max()/2;
    const bool MAX = true;
    const int UP = 1e9+1e5 + 10;
    const int rangeL = -UP;
    const int rangeR = UP;
    const int N = 2e5 + 10;
    // 如果修改一段区间，还需要开大概log倍的空间
    const int M = N * (__lg(rangeR-rangeL)+2);
    // TODO end----------------
    struct Line {
        T k, b;
        Line() {}
        Line(T k, T b): k(k), b(b) {}
        T get(T x) const{return k*x+b;}
    } line[M];
    int vis[M], lch[M], rch[M];
    int root, index;
    void clear() {
        for(; index; --index)
            vis[index]=lch[index]=rch[index]=0;
    }
    void add_segment(int& u,int l,int r,int ql,int qr,const Line& val) {
        if(!u) u=++index;
        int mid=(l+r)>>1;// 注意(l+r)溢出
        if (l==ql&&r==qr) {
            if (!vis[u]) {
                line[u]=val;
                vis[u]=1;
                return;
            }
            const T l0=val.get(l), r0=val.get(r);
            const T l1=line[u].get(l), r1=line[u].get(r);
            if (l1-l0>-EPS && r1-r0>-EPS )
                return;
            if (l0-l1>EPS && r0-r1>EPS ) {
                line[u]=val;
                return;
            }
            const T cross=(line[u].b-val.b)/(val.k-line[u].k);
            if (cross<=mid) {
                if (val.k-line[u].k<-EPS)
                    add_segment(u1, l, mid, val);
                else {
                    add_segment(u1, l, mid, line[u]);
                    line[u]=val;
                }
            } else {
                if (val.k-line[u].k>EPS)
                    add_segment(u2, mid+1, r, val);
                else {
                    add_segment(u2, mid+1, r, line[u]);
                    line[u]=val;
                }
            }
            return;
        }
        if (qr<=mid) add_segment(u1, ql, qr, val);
        else if (ql>mid) add_segment(u2, ql, qr, val);
        else add_segment(u1, ql, mid, val),
            add_segment(u2, mid+1, qr, val);
    }
    void add_segment(int l, int r, T k, T b) {
        const Line a= MAX ? Line(k, b) : Line(-k, -b);
        add_segment(root, rangeL, rangeR, l, r, a);
    }
    void add_line(T k, T b) {
        add_segment(rangeL, rangeR, k, b);
    }
    T query(int u, int l, int r, int x) {
        T res=(!u||!vis[u] ? -INF : line[u].get(x) );
        if (l==r) return res;
        int mid=(l+r)>>1;
        return max(res, x<=mid ? query(u1, x) : query(u2, x));
    }
    T query(int x) {
        return query(1, rangeL, rangeR, x) * (MAX ? 1 : -1 );
    }
    #undef u1
    #undef u2
}
```

可持久化：  
可以解决树上斜率优化问题（也可以用撤销法dfs解决）
```cpp
namespace LcSeg {// 可持久化李超线段树 index-1
    const double EPS = 1e-6;
    // TODO begin--------------
    using T = ll;
    const T INF = numeric_limits<T>::max()/2;
    const bool MAX = false;
    const int UP = 1e9+1e5 + 10;
    const int rangeL = -UP;
    const int rangeR = UP;
    const int N = 1e5 + 10;
    // 如果修改一段区间，M还需要开大概log倍的空间
    const int M = N * (__lg(rangeR-rangeL)+3);
    // TODO end----------------
    struct Line {
        T k, b;
        Line() {}
        Line(T k, T b): k(k), b(b) {}
        T get(T x) const{return k*x+b;}
    } line[M];
    int vis[M], lch[M], rch[M];
    int rt[N], index;
    void clear() {
        index=0;
    }
    void cpy(int i,int j) {
        line[i]=line[j];
        vis[i]=vis[j];
        lch[i]=lch[j];
        rch[i]=rch[j];
    }
    void add_segment(int& u,int v,int l,int r,int ql,int qr,const Line& val) {
        u=++index;
        cpy(u,v);
        int mid=(l+r)>>1;// 注意(l+r)溢出
        if (l==ql&&r==qr) {
            if (!vis[u]) {
                line[u]=val;
                vis[u]=1;
                return;
            }
            const T l0=val.get(l), r0=val.get(r);
            const T l1=line[u].get(l), r1=line[u].get(r);
            if (l1-l0>-EPS && r1-r0>-EPS )
                return;
            if (l0-l1>EPS && r0-r1>EPS ) {
                line[u]=val;
                return;
            }
            const T cross=(line[u].b-val.b)/(val.k-line[u].k);
            if (cross<=mid) {
                if (val.k-line[u].k<-EPS)
                    add_segment(lch[u],lch[v],l,mid,l,mid,val);
                else {
                    add_segment(lch[u],lch[v],l,mid,l,mid,line[u]);
                    line[u]=val;
                }
            } else {
                if (val.k-line[u].k>EPS)
                    add_segment(rch[u],rch[v],mid+1,r,mid+1,r,val);
                else {
                    add_segment(rch[u],rch[v],mid+1,r,mid+1,r,line[u]);
                    line[u]=val;
                }
            }
            return;
        }
        if (qr<=mid) add_segment(lch[u],lch[v],l,mid,ql,qr,val);
        else if (ql>mid) add_segment(rch[u],rch[v],mid+1,r,ql,qr,val);
        else add_segment(lch[u],lch[v],l,mid,ql,mid,val),
            add_segment(rch[u],rch[v],mid+1,r,mid+1,qr,val);
    }
    void add_segment(int verNumber,int preVer,int l,int r,T k,T b) {
        const Line a= MAX ? Line(k, b) : Line(-k, -b);
        add_segment(rt[verNumber],rt[preVer],rangeL,rangeR,l,r,a);
    }
    void add_line(int verNumber,int preVer,T k, T b) {
        add_segment(verNumber,preVer,rangeL,rangeR,k,b);
    }
    T query(int u, int l, int r, int x) {
        T res=(!u||!vis[u] ? -INF : line[u].get(x) );
        if (l==r) return res;
        int mid=(l+r)>>1;
        return max(res, x<=mid ? query(lch[u],l,mid,x) 
        : query(rch[u],mid+1,r,x));
    }
    T query(int verNumber,int x) {
        return query(rt[verNumber], rangeL, rangeR, x) * (MAX?1:-1);
    }
}
```


# 前缀和
```cpp
/// @tparam T 具有单位元 T()，结合律+，逆元-
template<class T>
struct PrefixSum {
    vector<T> sum;
    PrefixSum(const vector<T>& a): sum(a.size()+1) {
        for(int i=0; i<a.size(); ++i)
            sum[i+1]=sum[i]+a[i];
    }
    T get(int l,int r) {
        return -sum[l]+sum[r+1];
    }
};
struct Node {// ax+b,a=1,-1
    int a,b;
    Node():a(1),b(0) {}
    Node(int a,int b):a(a),b(b) {}
    Node operator+(const Node& o)const {
        return Node(o.a*a,o.a*b+o.b);
    }
    Node operator-()const {
        return Node(1/a,-b/a);
    }
};
```

# treap
```cpp
const int SZ=1e6+10, INF=2e9+10;
struct Treap {
    struct node {
        int key, cnt;
        int siz;//树的大小
        int val;//随机值
        int ch[2];
    } t[SZ];
    int idx, root;
    void init() {
        idx=root=0;
    }
    int newNode(int key) {
        t[++idx]= {key, 1, 1, rand(), 0, 0};
        return idx;
    }
    void pushup(int u) {//更新size
        t[u].siz=t[t[u].ch[0]].siz + t[t[u].ch[1]].siz + t[u].cnt;
    }
    void rotate(int &u, int op) { //0:右旋 1:左旋
        int v=t[u].ch[op];
        t[u].ch[op]=t[v].ch[!op];
        t[v].ch[!op]=u;
        u=v;
        pushup(t[u].ch[!op]), pushup(u);
    }
    void insert(int key) {
        insert(root, key);
    }
    void insert(int &u, int key) {
        if (!u) u=newNode(key);
        else if (t[u].key==key) t[u].cnt++;
        else {
            int op=(t[u].key<key);
            insert(t[u].ch[op], key);
            if (t[t[u].ch[op]].val>t[u].val) rotate(u, op);
        }
        pushup(u);
    }
    bool erase(int key) {
        return erase(root, key);
    }
    bool erase(int &u, int key) {
        if (!u) return false; //没找到这个数
        int ok=true;
        if (t[u].key==key) {
            if (t[u].cnt>1) t[u].cnt--;
            else if (t[u].ch[0]||t[u].ch[1]) { //有左右孩子
                int op=(!t[u].ch[1]||t[t[u].ch[0]].val>t[u].val);
                rotate(u, !op), ok=erase(t[u].ch[op], key);
            } else u=0; //孩子节点
        } else ok=erase(t[u].ch[t[u].key<key], key);
        pushup(u);
        return ok;
    }
    int findPre(int key) {
        return findPre(root, key);
    }
    int findPre(int u, int key) { //找前驱节点
        if (!u) return -INF;
        if (t[u].key>=key) return findPre(t[u].ch[0], key);
        else return max(t[u].key, findPre(t[u].ch[1], key));
    }
    int findNext(int key) {
        return findNext(root, key);
    }
    int findNext(int u, int key) { //找后继节点
        if (!u) return INF;
        if (t[u].key<=key) return findNext(t[u].ch[1], key);
        else return min(t[u].key, findNext(t[u].ch[0], key));
    }
    int findKey(int Rank) {
        return findKey(root, Rank);
    }
    int findKey(int u, int Rank) { //给定名次找key
        if (!u) return INF;
        if (t[t[u].ch[0]].siz>=Rank) return findKey(t[u].ch[0], Rank);
        if (t[t[u].ch[0]].siz+t[u].cnt>=Rank) return t[u].key;
        return findKey(t[u].ch[1], Rank-t[t[u].ch[0]].siz-t[u].cnt);
    }
    int findRank(int key) {
        return findRank(root, key);
    }
    int findRank(int u, int key) { //给定key找排名
        if (!u) return 0;
        if (t[u].key==key) return t[t[u].ch[0]].siz+1;
        if (t[u].key>key) return findRank(t[u].ch[0], key);
        return t[t[u].ch[0]].siz+t[u].cnt+findRank(t[u].ch[1], key);
    }
};
```

# splay
```cpp
const int SZ=1e6+10, INF=2e9+10;
struct Splay {
    struct Node {
        int key, cnt, siz;
        int fa, ch[2];
    } t[SZ];
    int root, id;
    Splay() {
        init();
    }
    void init() {
        //插入哨兵，避免earse找不到前驱后继出现死循环
        root=id=0, insert(-INF), insert(INF);
    }
    void pushup(int u) {
        t[u].siz=t[t[u].ch[0]].siz+t[t[u].ch[1]].siz+t[u].cnt;
    }
    void rotate(int u) {
        int fa=t[u].fa, gfa=t[fa].fa;
        t[gfa].ch[t[gfa].ch[1]==fa]=u, t[u].fa=gfa;
        int k=(t[fa].ch[1]==u);//u是fa的 0:左孩子 1:右孩子
        t[fa].ch[k]=t[u].ch[k^1], t[t[u].ch[k^1]].fa=fa;
        t[u].ch[k^1]=fa, t[fa].fa=u;
        pushup(fa), pushup(u);
    }
    void splay(int u, int s=0) { //把u提到 s的儿子
        while (t[u].fa!=s) {
            int fa=t[u].fa, gfa=t[fa].fa;
            if (gfa!=s) {
                if ((t[fa].ch[1]==u)^(t[gfa].ch[1]==fa)) rotate(u); //之字形
                else rotate(fa);//一字型
            }
            rotate(u);
        }
        if (!s) root=u;
    }
    void insert(int key) {
        int u=root, fa=0;
        while (u) {
            if (t[u].key==key) {
                t[u].cnt++, t[u].siz++;
                return splay(u);
            }
            fa=u, u=t[u].ch[t[u].key<key];
        }
        u=++id;
        if (fa) t[fa].ch[t[fa].key<key]=u;
        t[u]= {key, 1, 1, fa, 0, 0};
        splay(u);
    }
    int max_of_less(int key) { //返回最大的 "小于key" 的节点下标
        int u=root, res=0;
        while (u) {
            if (key<=t[u].key) u=t[u].ch[0];
            else res=u, u=t[u].ch[1];
        }
        return res;
    }
    int min_of_greater(int key) { //返回最小的 "大于key" 的节点下标
        int u=root, res=0;
        while (u) {
            if (t[u].key<=key) u=t[u].ch[1];
            else res=u, u=t[u].ch[0];
        }
        return res;
    }
    bool erase(int key) {
        int u=max_of_less(key), v=min_of_greater(key);
        splay(u), splay(v, u);
        int o=t[v].ch[0];
        if (t[o].cnt>1) t[o].cnt--, t[o].siz--;
        else t[v].ch[0]=0;
        pushup(v), pushup(u);
        return o;
    }
    int get_pre(int key) {
        return t[max_of_less(key)].key;
    }
    int get_next(int key) {
        return t[min_of_greater(key)].key;
    }
    int get_kth(int Rank) { //返回从小到大的第Rank个，从1开始计数
        ++Rank;//因为插入过-INF
        int u=root;
        while (u) {
            if (t[t[u].ch[0]].siz>=Rank) u=t[u].ch[0];
            else if (t[t[u].ch[0]].siz+t[u].cnt>=Rank) return t[u].key;
            else Rank-=t[t[u].ch[0]].siz+t[u].cnt, u=t[u].ch[1];
        }
        return INF;//总共没有Rank个节点
    }
    int get_rank(int key) { //返回从小到大，key能排在多少名，尽管key不在树中
        int u=root, res=0;
        while (u) {
            if (t[u].key==key) {
                res+=t[t[u].ch[0]].siz;
                splay(u);
                return res;//因为插入过-INF
            }
            if (t[u].key<key) {
                res+=t[t[u].ch[0]].siz+t[u].cnt;
                u=t[u].ch[1];
            } else u=t[u].ch[0];
        }
        return res;
    }
};
```

# ST表

[o(n)预处理，O(1)查询的ST表 -- from jiangly](https://codeforces.com/contest/1913/submission/237794290)
```cpp
template<class T, class Cmp = std::less<T>>
struct RMQ {
    const Cmp cmp = Cmp();
    static constexpr unsigned B = 64;
    using u64 = unsigned long long;
    int n;
    std::vector<std::vector<T>> a;
    std::vector<T> pre, suf, ini;
    std::vector<u64> stk;
    RMQ() {}
    RMQ(const std::vector<T> &v) {
        init(v);
    }
    void init(const std::vector<T> &v) {
        n = v.size();
        pre = suf = ini = v;
        stk.resize(n);
        if (!n) {
            return;
        }
        const int M = (n - 1) / B + 1;
        const int lg = std::__lg(M);
        a.assign(lg + 1, std::vector<T>(M));
        for (int i = 0; i < M; i++) {
            a[0][i] = v[i * B];
            for (int j = 1; j < B && i * B + j < n; j++) {
                a[0][i] = std::min(a[0][i], v[i * B + j], cmp);
            }
        }
        for (int i = 1; i < n; i++) {
            if (i % B) {
                pre[i] = std::min(pre[i], pre[i - 1], cmp);
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            if (i % B != B - 1) {
                suf[i] = std::min(suf[i], suf[i + 1], cmp);
            }
        }
        for (int j = 0; j < lg; j++) {
            for (int i = 0; i + (2 << j) <= M; i++) {
                a[j + 1][i] = std::min(a[j][i], a[j][i + (1 << j)], cmp);
            }
        }
        for (int i = 0; i < M; i++) {
            const int l = i * B;
            const int r = std::min(1U * n, l + B);
            u64 s = 0;
            for (int j = l; j < r; j++) {
                while (s && cmp(v[j], v[std::__lg(s) + l])) {
                    s ^= 1ULL << std::__lg(s);
                }
                s |= 1ULL << (j - l);
                stk[j] = s;
            }
        }
    } 
    // query [l,r)
    T operator()(int l, int r) {
        if (l / B != (r - 1) / B) {
            T ans = std::min(suf[l], pre[r - 1], cmp);
            l = l / B + 1;
            r = r / B;
            if (l < r) {
                int k = std::__lg(r - l);
                ans = std::min({ans, a[k][l], a[k][r - (1 << k)]}, cmp);
            }
            return ans;
        } else {
            int x = B * (l / B);
            return ini[__builtin_ctzll(stk[r - 1] >> (l - x)) + l];
        }
    }
};
```


# 可删除堆
```cpp
struct Heap {
    priority_queue<int, vector<int>, greater<>> heap, discard;
    void norm() {
        while (discard.size() && heap.top() == discard.top())
            heap.pop(), discard.pop();
    }
    int top() {
        norm();
        return heap.size() ? heap.top() : 2e9;
    }
    void push(int x) {
        heap.push(x);
    }
    bool empty() {
        return heap.size()==discard.size();
    }
    int size() {
        return heap.size()-discard.size();
    }
    void del(int x) {
        discard.push(x);
    }
};
```

# 最优匹配
$KM$ 算法 $O(n^2*m)$  
```cpp
int e[N][N];// e[1~n][1~n]
int lx[N],visx[N];
int ly[N],visy[N],link[N];
bool find(int u,int n) {
    visx[u]=1;
    for(int v=1; v<=n; ++v) {
        if(visy[v]||lx[u]+ly[v]!=e[u][v]) continue;
        visy[v]=1;
        if( link[v]==-1 || find(link[v],n) ) {
            link[v]=u;
            return true;
        }
    }
    return false;
}
int KM(int n) {
    memset(link,-1,sizeof link);
    memset(lx,-0x3f,sizeof lx);
    memset(ly,0,sizeof ly);
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j)
            lx[i]=max(lx[i],e[i][j]);
    for(int u=1; u<=n; ++u) {
        while(1) {
            memset(visx,0,sizeof visx);
            memset(visy,0,sizeof visy);
            if(find(u, n)) break;
            int d=INT_MAX;
            for(int i=1; i<=n; ++i)
                if(visx[i])
                    for(int j=1; j<=n; ++j)
                        if(!visy[j])
                            d=min(d,lx[i]+ly[j]-e[i][j]);
            // if(d==INT_MAX) return d;// not find
            for(int i=1; i<=n; ++i) {
                if(visx[i]) lx[i]-=d;
                if(visy[i]) ly[i]+=d;
            }
        }
    }
    return accumulate(lx+1,lx+1+n,0)+accumulate(ly+1,ly+1+n,0);
}
```

# 有向无环图上的支配树
$O(nlogn)$
```cpp
struct DominatorTreeOnDAG {// index-1
    static const int N = 5e5 + 10;
    int n, s, in[N];
    vector<int> g[N], rg[N];
    void init(int _n,int _s=1) {
        n=_n, s=_s;
        for(int i=1; i<=n; ++i) {
            in[i]=0;
            g[i].clear();
            rg[i].clear();
        }
    }
    void addEdge(int u,int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
        ++in[v];
    }
	static const int LOG = __lg(N);
    int f[N][LOG+1], deep[N];
    /// @note 默认s号节点可以到达其他所有节点
    void buildTree() {
		topo(s);
        deep[s]=0;
        for(int i=1; i<top.size(); ++i) {
            int u=top[i];
            int fa=rg[u][0];// 直接支配点在支配树上前驱的lca处
            for(int v:rg[u])
                fa=lca(fa,v);
            // tr[fa].push_back(u);// 支配树
            deep[u]=deep[fa]+1;
            f[u][0]=fa;
            for(int j=1; (1<<j)<=deep[u]; ++j)
                f[u][j]=f[f[u][j-1]][j-1];
        }
    }
    bool dominate(int u,int v) {// u在支配树上是v的祖先
        if(deep[u]>deep[v])
            return false;
        int d=deep[v]-deep[u];
        for(int i=LOG; i>=0; --i)
            if(d>>i&1) v=f[v][i];
        return u==v;
    }
private:
    vector<int> top;
    void topo(int s) {
        top.clear();
        queue<int> q;
        q.push(s);
        while(q.size()) {
            int u=q.front();
            q.pop();
            top.push_back(u);
            for(int v:g[u])
                if(--in[v]==0)
                    q.push(v);
        }
    }
    int lca(int u,int v) {
        if(deep[u]<deep[v]) swap(u,v);
		int d=deep[u]-deep[v];
        for(int i=LOG; i>=0; --i)
            if(d>>i&1) u=f[u][i];
        if(u==v) return u;
        for(int i=LOG; i>=0; --i)
            if((1<<i)<=deep[u] && f[u][i]!=f[v][i])
                u=f[u][i], v=f[v][i];
        return f[u][0];
    }
} dag;
```

# 模拟费用流
[经典例题:雪灾与外卖](https://uoj.ac/problem/455)
```cpp
constexpr ll inf = 1e18;
struct Node {
    int flow;
    ll cost;
    bool operator<(const Node &o)const {
        return cost > o.cost;
    }
};
priority_queue<Node> mo, ho;
ll ans;
void meetMouse(int x) {
    ll w = inf;
    if(ho.size()) {
        w = ho.top().cost;
        int flow = ho.top().flow-1;
        ho.pop();
        if(flow) ho.push({flow, w});
    }
    ans += x+w;
    mo.push({1, -2*x-w});
}
void meetHole(int x,int w,int c) {
    int remain = c;
    while(mo.size() and remain) {
        auto [flow, cost] = mo.top();
        ll temp = cost + w + x;
        if(temp >= 0) break;
        int rFlow = min(remain, flow);
        ans += rFlow * temp;
        remain -= rFlow;
        mo.pop();
        if(flow -= rFlow) mo.push({flow, cost});
        ho.push({rFlow, -2*x-cost});
    }
    if(remain < c) mo.push({c-remain, -x-w});
    if(remain) ho.push({remain, -x+w});
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin>>n>>m;
    vector<int> x(n), y(m), w(m), c(m);
    for(int i=0; i<n; ++i) cin>>x[i];
    ll sum=0;
    for(int i=0; i<m; ++i) cin>>y[i]>>w[i]>>c[i], sum+=c[i];
    if(sum<n) cout<<"-1",exit(0);
    for(int i=0, j=0; i<n or j<m; ) {
        if(j>=m or i<n and x[i]<y[j])
            meetMouse(x[i]),i++;
        else
            meetHole(y[j], w[j], c[j]), j++;
    }
    cout<<ans;
    return 0;
}
```


# 上下界最大流
上下界最大流 [116. 有源汇有上下界最大流](https://loj.ac/p/116)
```cpp
cin >> n >> m >> s0 >> t0;
initGraph();
while (m--) {
    int u, v, low, up;
    cin >> u >> v >> low >> up;
    addEdge(u, v, up - low);
    deg[u] += low;
    deg[v] -= low;
}
int sum = 0;
for (int i = 1; i <= n; ++i) {
    if (deg[i] > 0) {
        sum += deg[i];
        addEdge(i, t1, deg[i]);
    } else if (deg[i] < 0) {
        addEdge(s1, i, -deg[i]);
    }
}
addEdge(t0, s0, INF);
if (dinic(s1, t1) != sum) {
    cout << "please go home to sleep";
    exit(0);
}
int flow = edge[en - 1].l;
edge[en - 1].l = edge[en - 2].l = 0;
cout << flow + dinic(s0, t0);
```

上下界最小费用可行流 [支线剧情](https://www.luogu.com.cn/problem/P4043)
```cpp
cin>>n;
initGraph();
int s1=n+1,t1=s1+1;
int ans=0;
for(int i=1; i<=n; ++i) {
    int k,a,b;
    cin>>k;
    while(k--) {
        cin>>a>>b;
        addEdge(i,a,INF,b);
        deg[i]+=1;
        deg[a]-=1;
        ans+=b;
    }
}
for(int i=1; i<=n; ++i) {
    addEdge(i,1,INF,0);
}
for(int i=1; i<=n; ++i) {
    if(deg[i]>0)
        addEdge(i,t1,deg[i],0);
    if(deg[i]<0)
        addEdge(s1,i,-deg[i],0);
}
minCostMaxFlow(s1,t1);
cout<<ans+fee;
```

# 有负环的费用流
利用上下界最小费用最大流
```cpp
int n, m;
cin>>n>>m>>s0>>t0;
initGraph();
vector<int> df(n+1);
int ans = 0;
while(m--) {
    int u,v,f,c;
    cin>>u>>v>>f>>c;
    if(c>=0) {
        addEdge(u,v,f,c);
    }else {
        addEdge(v,u,f,-c);
        df[u] += f;
        df[v] -= f;
        ans += f*c;
    }
}
int s1 = n+1, t1 = s1+1;
for(int i=1; i<=n; ++i) {
    if(df[i]>0) addEdge(i, t1, df[i], 0);
    if(df[i]<0) addEdge(s1, i, -df[i], 0);
}
addEdge(t0, s0, INF, 0);
minCostMaxFlow(s1, t1);
ans += fee;
minCostMaxFlow(s0, t0);
ans += fee;
cout << maxf << " " << ans;
```

# 斯坦纳树
$O(3^k n + 2^k nm)$
```cpp
struct SteinerTree {// index-1
    static constexpr int N = 1000  + 10;
    static constexpr int K = 10;// 关键点个数
    vector<pair<int,int>> g[N];
    int n, m, k, f[1<<K][N];
    void readGraph() {
        cin>>n>>m>>k;
        for(int i=0; i<m; ++i) {
            int u,v,w;
            cin>>u>>v>>w;
            g[u].emplace_back(v,w);
            g[v].emplace_back(u,w);
        }
        memset(f, 0x3f, sizeof f);
        memset(f[0], 0, sizeof f[0]);// 防止k=0输出0x3f
        for(int i=0,x; i<k; ++i) {
            // cin>>c[i];
            cin>>x;
            f[1<<i][x]=0;
        }
    }
    bool vis[N];
    int minSteinerTree() {
        for(int S=1; S<(1<<K); ++S) {
            for(int T=S&(S-1); T>(S^T); T=(T-1)&S)
                for(int i=1; i<=n; ++i)
                    f[S][i]=min(f[S][i],f[T][i]+f[S^T][i]);
            queue<int> q;
            for(int i=1; i<=n; ++i)
                if(f[S][i]!=0x3f3f3f3f)
                    q.push(i), vis[i]=true;
            while(q.size()) {
                int u=q.front();
                q.pop(), vis[u]=false;
                for(auto& [v,w]:g[u])
                    if(f[S][u]+w<f[S][v]) {
                        f[S][v]=f[S][u]+w;
                        if(!vis[v])
                            q.push(v), vis[v]=true;
                    }
            }
        }
        return *min_element(f[(1<<k)-1]+1,f[(1<<k)-1]+1+n);
    }

    // int c[K];// c[i]:关键点i的类别
    // int h[1<<K];
    // int minSteinerForest() {
    //     minSteinerTree();
    //     int tong[k]={}, has[k]={}, ln=0;
    //     for(int i=0; i<k; ++i) {
    //         int p=find(tong,tong+ln,c[i])-tong;
    //         has[p]^=1<<i;
    //         if(p==ln) tong[ln++]=c[i];
    //     }
    //     // 有效状态是相同颜色的节点要么全在里面，要么全不在里面
    //     bool ban[1<<k]={};
    //     for(int i=0; i<(1<<k); ++i)
    //         for(int j=0; !ban[i] && j<ln; ++j)
    //             if((i&has[j])!=0 && (i&has[j])!=has[j])
    //                 ban[i]=true;

    //     for(int i=0; i<(1<<k); ++i) {
    //         if(ban[i]) continue;
    //         // h[i] 只取最小的花费
    //         h[i]=*min_element(f[i]+1,f[i]+1+n);
    //         // 划分连通块
    //         for(int j=(i-1)&i; j>(j^i); j=(j-1)&i) {
    //             if(ban[j] || ban[i^j]) continue;
    //             h[i]=min(h[i],h[j]+h[i^j]);
    //         }
    //     }
    //     return h[(1<<k)-1];
    // }
} steiner;
```


# 最小树形图
朱刘算法$O(n*m)$
```cpp
struct DMST {// index-1
    static constexpr int N = 100 + 10;
    static constexpr int inf = 0x3f3f3f3f;
    int n,m,r;
    vector<tuple<int,int,int>> e;
    void readGragh() {
        cin>>n>>m>>r;
        for(int i=0,u,v,w; i<m; ++i) {
            cin>>u>>v>>w;
            if(u^v) e.emplace_back(u,v,w);
        }
    }
    int ine[N],ind[N];
    int ances[N],col[N],cn;
    int mst() {
        int ans=0;
        while(1) {
            fill_n(ine+1,n,inf);
            fill_n(ances+1,n,0);
            fill_n(col+1,n,0), cn=0;
            // 每个点只有一个入点，可能会形成 树形图 （+一颗外向基环树）
            for(auto& [u,v,w]:e)
                if(v!=r && w<ine[v]) {
                    ine[v]=w;
                    ind[v]=u;
                }
            ine[r]=0;
            for(int i=1; i<=n; ++i) {
                if(ine[i]==inf) return -1;// no solution
                ans+=ine[i];
            }
            for(int i=1; i<=n; ++i) {
                if(i==r) continue;
                int u=ind[i];
                for(ances[i]=i; u!=r && !ances[u]; u=ind[u])
                    ances[u]=i;
                if(ances[u]==i) {// circle
                    for(++cn; !col[u]; u=ind[u])
                        col[u]=cn;
                    break;
                }
            }
            if(!cn) return ans;// no circle
            for(int i=1; i<=n; ++i)
                if(!col[i]) col[i]=++cn;
            int idx=0;
            for(int i=0; i<e.size(); ++i) {
                auto [u,v,w]=e[i];
                w-=ine[v];
                u=col[u];
                v=col[v];
                if(u^v) e[idx++]={u,v,w};
            }
            e.resize(idx);
            n=cn, r=col[r];
        }
        return -1;
    }
} dm;
```

[左偏树或启发式合并堆+并查集优化的算法$O(m+n\log n)$](https://www.luogu.com.cn/problem/U210116)  
注意，如果想求一个root到尽量多节点，但不保证能到所有节点的最小树形图，此模板无法实现，所以要预先dfs判断哪些节点能到，对节点重新标号并且删掉无用边。
```cpp
template<class T, class Info>
struct min_heap {
    priority_queue<pair<T, Info>, vector<pair<T, Info>>, greater<>> pq;
    T lazy = 0;
    void push(pair<T, Info> v) {
        pq.emplace(v.first - lazy, v.second);
    }
    pair<T, Info> top() {
        return make_pair(pq.top().first + lazy, pq.top().second);
    }
    void join(min_heap& rgt) {
        if(pq.size() < rgt.pq.size()) {
            swap(pq, rgt.pq);
            swap(lazy, rgt.lazy);
        }
        while(!rgt.pq.empty()) {
            push(rgt.top());
            rgt.pop();
        }
    }
    void pop() {
        pq.pop();
    }
    bool empty() {
        return pq.empty();
    }
    void add_lazy(T v) {
        lazy += v;
    }
};
struct E { int s, t; ll w; };
ostream& operator<<(ostream& os, const E& o) {
    return os << "(" << o.s <<"," <<o.t <<"," << o.w <<")";
}
/// @brief index-0, 返回最小树形图的边编号, sum(e[ans[i]].w)即边权和
vector<int> dmst(const vector<E>& e, int n, int root) {
    vector<min_heap<ll, int>> h(n*2);
    for(int i=0; i<e.size(); ++i)
        h[e[i].t].push({e[i].w, i});
    Dsu dsu(n*2);// @warning unite(x, y): fa[x] = y
    vector<int> v(n*2, -1), pa(n*2, -1), r(n*2);
    v[root] = n + 1;
    int pc = n;
    for(int i=0; i<n; ++i) {
        if(~v[i]) continue;
        for(int p=i; v[p]==-1 || v[p]==i; p=dsu.get(e[r[p]].s)) {
            if(v[p] == i) {
                int q = p; p = pc++;
                do {
                    h[q].add_lazy(-h[q].top().first);
                    pa[q] = p, dsu.unite(q, p), h[p].join(h[q]);
                } while((q = dsu.get(e[r[q]].s)) != p);
            }
            v[p] = i;
            while(!h[p].empty() && dsu.get(e[h[p].top().second].s) == p)
                h[p].pop();
            if(h[p].empty()) return {}; // no solution
            r[p] = h[p].top().second;
        }
    }
    vector<int> ans;
    for(int i=pc-1; i>=0; --i)
        if(i != root && v[i] != n) {
            for(int f=e[r[i]].t; ~f && v[f]!=n; f=pa[f])
                v[f] = n;
            ans.push_back(r[i]);
        }
    return ans;
}
```

# 最小直径生成树
求出一颗直径最小的生成树$O(n^3)$
```cpp
struct MDST {// index-1
    static constexpr int N = 200 + 10;
    static constexpr int inf = 0x3f3f3f3f;
    struct EDGE {
        int u,v,w;
    } e[N*N];
    int n,d[N][N],rk[N][N],en;
    void init(int _n) {
        n=_n, en=0;
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j) {
                rk[i][j]=j;
                d[i][j]=(i^j?inf:0);
            }
    }
    void addEdge(int u,int v,int w) {
        if(w>=d[u][v]) return;
        e[en++]={u,v,w};
        d[u][v]=d[v][u]=w;
    }
    void floyd() {
        for(int k=1; k<=n; ++k)
            for(int i=1; i<=n; ++i)
                for(int j=1; j<=n; ++j)
                    if(i!=j&&i!=k&&j!=k&&d[i][k]+d[k][j]<d[i][j])
                        d[i][j]=d[i][k]+d[k][j];
    }
    int diameter() {
        floyd();
        int ans=inf;
        for(int i=1; i<=n; ++i) {
            sort(rk[i]+1,rk[i]+1+n,[&](int x,int y){
                return d[x][i]>d[y][i];
            });
            ans=min(ans,d[rk[i][1]][i]*2);
        }
        for(int k=0; k<en; ++k) {
            auto& [u,v,w]=e[k];
            for(int j=1,i=2; i<=n; ++i)
                if(d[rk[u][i]][v]>d[rk[u][j]][v]) {
                    ans=min(ans,d[rk[u][j]][v]+w+d[rk[u][i]][u]);
                    j=i;
                }
        }
        return ans;
    }
    vector<pair<int,int>> mdst() {
        floyd();
        int ans=inf, c1=-1,c2=-1, d1=0,d2=0;
        for(int i=1; i<=n; ++i) {
            sort(rk[i]+1,rk[i]+1+n,[&](int x,int y){
                return d[x][i]>d[y][i];
            });
            if(d[rk[i][1]][i]*2 < ans) {
                ans=d[rk[i][1]][i]*2;
                c1=i;
            }
        }
        for(int k=0; k<en; ++k) {
            auto& [u,v,w]=e[k];
            for(int j=1,i=2; i<=n; ++i)
                if(d[rk[u][i]][v]>d[rk[u][j]][v]) {
                    if(d[rk[u][j]][v]+w+d[rk[u][i]][u] < ans) {
                        ans=d[rk[u][j]][v]+w+d[rk[u][i]][u];
                        c1=u, c2=v;
                        /// @note d1=ans/2-d[i][u],乘上2避免0.5
                        d1=ans-2*d[rk[u][i]][u];
                        d2=ans-2*d[rk[u][j]][v];
                    }
                    j=i;
                }
        }
        vector<bool> vis(n+1);
        vector<int> pre(n+1,-1);
        vector<int> dis(n+1,inf);
        if(c2==-1) {
            dis[c1]=0;
        }else {
            dis[c1]=d1;
            dis[c2]=d2;
            pre[c1]=c2;
        }
        vector<pair<int,int>> choose;
        for(int t=1; t<=n; ++t)  {
            int p=-1;
            for(int i=1; i<=n; ++i)
                if(!vis[i] && (p==-1 || dis[i]<dis[p]))
                    p=i;
            vis[p]=1;
            if(~pre[p]) choose.emplace_back(pre[p],p);
            for(int k=0; k<en; ++k) {
                auto& [u,v,w]=e[k];
                if(v==p) swap(u,v);
                if(u!=p) continue;
                if(dis[u]<dis[v]-w*2) {
                    dis[v]=dis[u]+w*2;
                    pre[v]=u;
                }
            }
        }
        return choose;
    }
} md;

# 同余最短路
使用转圈技巧跑同余最短路$O(A[0] * |A|)$
```cpp
template<class T>
struct CSP {
    vector<T> d;
    // a0*x0+a1*x1+a2*x2+.. = something (ai,xi>=0)
    CSP(vector<int> A) {
        A.erase(remove(ALL(A),0),A.end());
        if(A.empty()) return;
        sort(ALL(A));
        A.erase(unique(ALL(A)),A.end());
        d.resize(A[0],numeric_limits<T>::max()/2);
        d[0]=0;
        for(auto a:A)
            for(int j=0,num=gcd(a,d.size()); j<num; ++j)
                for(int k=j,c=0; c<2; c+=(k==j)) {
                    int p=(k+a)%d.size();
                    d[p]=min(d[p],d[k]+a);
                    k=p;
                }
    }
    // count(b) b = a0*x0+a1*x1+a2*x2+.. (b<=n)
    T count(T n) {
        T ans=0;
        for(T x:d)
            if(n>=x)
                ans+=(n-x)/d.size()+1;
        return ans;
    }
    T count(T l,T r) {
        return count(r)-count(l-1);
    }
};
```

使用dijkstra跑同余最短路$O(A[0] * |A|\log(A[0] * |A|))$
```cpp
template<class T>
struct CSP {
    vector<int> a;
    Dijkstra<T> g;
    // a0*x0+a1*x1+a2*x2+.. = something (ai,xi>=0)
    CSP(const vector<int>& _a):a(_a),g(0) {
        a.erase(remove(ALL(a),0),a.end());
        sort(ALL(a));
        a.erase(unique(ALL(a)),a.end());
        if(a.size()==0) return;
        g=Dijkstra<T>(a[0]);
        for(int i=0; i<a[0]; ++i)
            for(int x:a) g.addEdge(i,(i+x)%a[0],x);
        g.dij(0);
    }
    // count(b) b = a0*x0+a1*x1+a2*x2+.. (b<=n)
    T count(T n) {
        if(a.empty()) return 0;
        T ans=0;
        for(int i=0; i<a[0]; ++i)
            if(n>=g.dis[i])
                ans+=(n-g.dis[i])/a[0]+1;
        return ans;
    }
    T count(T l,T r) {
        return count(r)-count(l-1);
    }
};
```
后记：

同余最短路中每种数不限制使用个数，如果题中限制了使用个数，也能用类似思路求出所有数的 $lcm$，构造 $dp[i],i \in [0,lcm*n)$ 表示 $i+k*lcm$ 中 $k$ 的最大取值。[例题](https://codeforces.com/contest/1132/problem/E)


# k短路
$A*$算法最坏$O(nk\log n)$
```cpp
struct KthSP {// index-1
    static const int N = 5000 + 10;
    int n,s,t,cnt[N];
    vector<pair<int,double>> g[N],rg[N];
    void init(int _n,int _s,int _t) {
        n=_n, s=_s, t=_t;
        for(int i=1; i<=n; ++i) {
            g[i].clear();
            rg[i].clear();
            h[i]=inf;
            vis[i]=cnt[i]=0;
        }
    }
    void addEdge(int u,int v,double w) {
        g[u].emplace_back(v,w);
        rg[v].emplace_back(u,w);
    }
    struct Node {
        int u;
        double dis,f;
        bool operator<(const Node& o)const {
            return f>o.f;
        }
    };
    double kthShortPath(int k) {
        dij();
        priority_queue<Node> q;
        q.push({s,0,0+h[s]});
        while(q.size()) {
            auto [u,dis0,f0]=q.top();
            q.pop();
            if(++cnt[u]==k && u==t) return dis0;
            if(cnt[u]>k) continue;
            for(auto [v,w]:g[u]) {
                q.push({v,dis0+w,dis0+w+h[v]});
            }
        }
        return -1;
    }
private:
    const double inf = 1e18;
    double h[N];
    bool vis[N];
    void dij() {
        using pii=pair<double,int>;
        priority_queue<pii,vector<pii>,greater<>> q;
        h[t]=0, q.emplace(0,t);
        while(q.size()) {
            int u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto [v,w]:rg[u]) {
                if(h[v] > h[u]+w) {
                    h[v]=h[u]+w;
                    q.emplace(h[v],v);
                }
            }
        }
    }
} ksp;
```

可持久化可并堆优化 $O((n+m) \log n + k \log k)$
```cpp
namespace KthSP {
    const double eps=1e-8;
    const int maxn = 200010;
    int fa[maxn];
    struct Edge {
        int en, h[maxn], nxt[maxn], p[maxn];
        double w[maxn];
        void add_edge(int x, int y, double z) {
            ++en;
            nxt[en] = h[x];
            h[x] = en;
            p[en] = y;
            w[en] = z;
        }
    } e1, e2;
    double dist[maxn];
    bool tf[maxn], vis[maxn], ontree[maxn];
    struct node {
        int x;
        double v;
        node* operator=(node a) {
            x = a.x;
            v = a.v;
            return this;
        }
        bool operator<(node a) const { return v-eps > a.v; }
    } a;
    priority_queue<node> Q;
    void dfs(int x) {
        vis[x] = true;
        for (int j = e2.h[x]; j; j = e2.nxt[j])
            if (!vis[e2.p[j]] && abs(dist[e2.p[j]] - (dist[x] + e2.w[j]))<eps)
                fa[e2.p[j]] = x, ontree[j] = true, dfs(e2.p[j]);
    }
    struct LeftistTree {
        int cnt, rt[maxn], lc[maxn * 20], rc[maxn * 20], dist[maxn * 20];
        node v[maxn * 20];
        LeftistTree() { dist[0] = -1; }
        int newnode(node w) {
            cnt++;
            v[cnt] = w;
            return cnt;
        }
        int merge(int x, int y) {
            if (!x || !y) return x + y;
            if (v[x] < v[y]) swap(x, y);
            int p = ++cnt;
            lc[p] = lc[x];
            v[p] = v[x];
            rc[p] = merge(rc[x], y);
            if (dist[lc[p]]+eps < dist[rc[p]]) swap(lc[p], rc[p]);
            dist[p] = dist[rc[p]] + 1;
            return p;
        }
    } st;
    void dfs2(int x) {
        vis[x] = true;
        if (fa[x]) st.rt[x] = st.merge(st.rt[x], st.rt[fa[x]]);
        for (int j = e2.h[x]; j; j = e2.nxt[j])
            if (fa[e2.p[j]] == x && !vis[e2.p[j]]) dfs2(e2.p[j]);
    }
// public:
    int n, s, t, cnt;
    // double ene;// 花费不超过ene的能量
    // int num=0;// 最多能走几次
    void init(int _n,int _s,int _t) {
        n=_n,s=_s,t=_t;
    }
    void addEdge(int u,int v,double w) {
        e1.add_edge(u, v, w), e2.add_edge(v, u, w);
    }
    double kthShortPath(int k=1) {
        Q.push({t, 0});// 从t开始dijkstra
        while (!Q.empty()) {
            a = Q.top();
            Q.pop();
            if (tf[a.x]) continue;
            tf[a.x] = true;
            dist[a.x] = a.v;
            for (int j = e2.h[a.x]; j; j = e2.nxt[j])
                Q.push({e2.p[j], a.v + e2.w[j]});
        }
        // if(!tf[s] || (ene-=dist[s])<-eps) {
        //     return 0;
        // } else ++num;
        if (k == 1) {
            if (tf[s]) return dist[s];
            else return -1;
        }
        dfs(t);
        for (int i = 1; i <= n; i++)
            // if(i!=t)// 题目要求到达t就不能动了
            if (tf[i])
            for (int j = e1.h[i]; j; j = e1.nxt[j])
                if (!ontree[j] && tf[e1.p[j]])
                    st.rt[i] = st.merge(st.rt[i],
                        st.newnode({e1.p[j], dist[e1.p[j]] + e1.w[j] - dist[i]}));
        fill_n(vis+1,n,false);
        dfs2(t);
        if (st.rt[s]) Q.push({st.rt[s], dist[s] + st.v[st.rt[s]].v});
        while (!Q.empty()) {
            a = Q.top();
            Q.pop();
            // if((ene-=a.v)<-eps) return num;
            // ++num;
            if (++cnt == k - 1)
                return a.v;
            if (st.lc[a.x])  // 可并堆删除直接把左右儿子加入优先队列中
                Q.push({st.lc[a.x], a.v - st.v[a.x].v + st.v[st.lc[a.x]].v});
            if (st.rc[a.x])
                Q.push({st.rc[a.x], a.v - st.v[a.x].v + st.v[st.rc[a.x]].v});
            int x = st.rt[st.v[a.x].x];
            if (x) Q.push({x, a.v + st.v[x].v});
        }
        return -1;
    }
}
```

# 弦图
```cpp
struct Chord {
    int n;
    vector<vector<int>> g;
    vector<int> label, s, rk;
    Chord(int n) : n(n), g(n), label(n), s(n), rk(n, -1) {}
    void addEdge(int u,int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    /// @brief MCS求完美消除序列，调用其他函数之前先调用MCS()
    void MCS() {
        vector<vector<int>> st(n);
        vector<int> temp(n);
        iota(temp.begin(), temp.end(), 0), st[0] = temp;
        for(int i=n-1, p=0; i>=0; --i) {
            int u;
            while(true) {
                while(st[p].empty()) p--;
                for(; st[p].size(); st[p].pop_back()) {
                    u=st[p].back();
                    if(rk[u] == -1 && label[u] == p) break;
                }
                if(st[p].size()) break;
            }
            s[rk[u] = i] = u;
            for(int v:g[u]) {
                if(rk[v] != -1) continue;
                if(label[v] == p) p++;
                st[++label[v]].push_back(v);
            }
        }
    }
    /// @brief 判断该图是否为弦图
    bool isChord() {
        vector<bool> vis(n);
        for(int idx=0; idx<n; ++idx) {
            int u = s[idx], v = s[n-1], c0 = 0, c1 = 0;
            for(int x:g[u]) {
                if(rk[u] > rk[x]) continue;
                vis[x] = true, c0++;
                if(rk[x] < rk[v]) v = x;
            }
            if(!c0) continue;
            vis[v] = false, c0--;
            for(int x:g[v])
                c1 += vis[x];
            if(c0^c1) return false;
            for(int x:g[u])
                vis[x] = false;
        }
        return true;
    }
    /// @brief 弦图的色数X(G) = 最大团大小W(G)
    int maxClique() {
        int ans = 0;
        for(int i=0; i<n; ++i)
            ans = max(ans, label[i]+1);
        return ans;
    }
    /// @brief 最小点涂色方案
    vector<int> coloring() {
        vector<bool> vis(n);
        vector<int> col(n);
        for(int i=n-1; i>=0; --i) {
            for(int v:g[s[i]])
                if(rk[v]>i)
                    vis[col[v]]=true;
            int c = 0;
            while(vis[c]) c++;
            col[s[i]] = c;
            for(int v:g[s[i]])
                vis[col[v]]=false;
        }
        return col;
    }
    /// @brief 弦图的最大点独立集数a(G) = 最小团覆盖数k(G)
    vector<int> independentSet() {
        vector<bool> ban(n);
        vector<int> ans;
        for(int i=0; i<n; ++i) {
            if(ban[s[i]]) continue;
            ans.push_back(s[i]);// 团覆盖为 {s[i]}+N(s[i])
            for(int v:g[s[i]])
                ban[v]=true;
        }
        return ans;
    }
};
```

# 稳定婚姻系统
```cpp
struct Gale_Shapley {// 稳定婚姻系统，O(n^2)
    using vv=vector<vector<int>>;
    int n;// [0,n)
    vv st;// st[i][j]：i的第n-j位好感度最高的
    vv pref;// pref[i][j]：i对j的好感度
    vector<int> matchM,matchF;
    // mList[i][j]：第i位male的好感度排第j的female
    // fList[i][j]：第i位female的好感度排第j的male
    Gale_Shapley(int n,const vv& mList,const vv& fList):
    n(n),st(n),pref(n),matchM(n,-1),matchF(n,-1) {
        vector<int> free(n);
        for(int i=0; i<n; ++i) {
            free[i]=i;
            st[i].assign(mList[i].rbegin(),mList[i].rend());
            pref[i].resize(n);
            for(int j=0; j<n; ++j)
                pref[i][fList[i][j]]=n-j;
        }
        while(free.size()) {
            vector<int> newFree;
            for(int i:free) {
                int j=st[i].back();
                st[i].pop_back();
                if(matchF[j]==-1)// accept
                    matchF[j]=i;
                else if(pref[j][i]>pref[j][matchF[j]]) {// wrench
                    newFree.push_back(matchF[j]);
                    matchF[j]=i;
                }else
                    newFree.push_back(i);
            }
            free.swap(newFree);
        }
        for(int i=0; i<n; ++i)
            matchM[matchF[i]]=i;
    }
};
```

# 一般图最大权匹配
```cpp
template <class T, int V>
struct WeightedBlossomTree {// index-1, O(n*m*log(n))
    enum { N = V * 2 };
    static const T inf = numeric_limits<T>::max() >> 1;
    struct Q {
        int u, v;
        T w;
    } e[N][N];
    T lab[N];
    int n, m, id, h, t;
    int lk[N], sl[N], st[N], f[N], b[N][N], s[N], ed[N], q[N];
    vector<int> p[N];
    T d(const Q &x) {
        return lab[x.u] + lab[x.v] - e[x.u][x.v].w * 2;
    }
    void upd(int u, int v) {
        if (!sl[v] || d(e[u][v]) < d(e[sl[v]][v]))
            sl[v] = u;
    }
    void ss(int v) {
        sl[v] = 0;
        for (int u = 1; u <= n; u++)
            if (e[u][v].w > 0 && st[u] != v && !s[st[u]])
                upd(u, v);
    }
    void ins(int u) {
        if (u <= n)
            q[++t] = u;
        else
            for (int v : p[u])
                ins(v);
    }
    void mdf(int u, int w) {
        st[u] = w;
        if (u > n)
            for (int v : p[u])
                mdf(v, w);
    }
    int gr(int u, int v) {
        v = find(p[u].begin(), p[u].end(), v) - p[u].begin();
        if (v & 1) {
            reverse(p[u].begin() + 1, p[u].end());
            return (int)p[u].size() - v;
        }
        return v;
    }
    void stm(int u, int v) {
        lk[u] = e[u][v].v;
        if (u <= n)
            return;
        Q w = e[u][v];
        int x = b[u][w.u], y = gr(u, x);
        for (int i = 0; i < y; i++)
            stm(p[u][i], p[u][i ^ 1]);
        stm(x, v);
        rotate(p[u].begin(), p[u].begin() + y, p[u].end());
    }
    void aug(int u, int v) {
        int w = st[lk[u]];
        stm(u, v);
        if (!w)
            return;
        stm(w, st[f[w]]);
        aug(st[f[w]], w);
    }
    int lca(int u, int v) {
        for (++id; u || v; swap(u, v)) {
            if (!u)
                continue;
            if (ed[u] == id)
                return u;
            ed[u] = id;
            if (u = st[lk[u]])
                u = st[f[u]];
        }
        return 0;
    }
    void add(int u, int a, int v) {
        int x = n + 1, i, j;
        while (x <= m && st[x])
            ++x;
        if (x > m)
            ++m;
        lab[x] = s[x] = st[x] = 0;
        lk[x] = lk[a];
        p[x].clear();
        p[x].push_back(a);
        for (i = u; i != a; i = st[f[j]]) {
            p[x].push_back(i);
            j = st[lk[i]];
            p[x].push_back(j);
            ins(j);
        }
        reverse(p[x].begin() + 1, p[x].end());
        for (i = v; i != a; i = st[f[j]]) {
            p[x].push_back(i);
            j = st[lk[i]];
            p[x].push_back(j);
            ins(j);
        }
        mdf(x, x);
        for (i = 1; i <= m; i++)
            e[x][i].w = e[i][x].w = 0;
        memset(b[x] + 1, 0, n * sizeof b[0][0]);
        for (int u : p[x]) {
            for (v = 1; v <= m; v++)
                if (!e[x][v].w || d(e[u][v]) < d(e[x][v])) {
                    e[x][v] = e[u][v];
                    e[v][x] = e[v][u];
                }
            for (v = 1; v <= n; v++)
                if (b[u][v])
                    b[x][v] = u;
        }
        ss(x);
    }
    void ex(int u) {
        assert(s[u] == 1);
        for (int x : p[u])
            mdf(x, x);
        int a = b[u][e[u][f[u]].u];
        int r = gr(u, a);
        for (int i = 0; i < r; i += 2) {
            int x = p[u][i], y = p[u][i + 1];
            f[x] = e[y][x].u;
            s[x] = 1;
            s[y] = 0;
            sl[x] = 0;
            ss(y);
            ins(y);
        }
        s[a] = 1;
        f[a] = f[u];
        for (int i = r + 1; i < p[u].size(); i++) {
            s[p[u][i]] = -1;
            ss(p[u][i]);
        }
        st[u] = 0;
    }
    bool on(const Q &e) {
        int u = st[e.u], v = st[e.v], a;
        if (s[v] == -1) {
            f[v] = e.u;
            s[v] = 1;
            a = st[lk[v]];
            sl[v] = sl[a] = s[a] = 0;
            ins(a);
        } else if (!s[v]) {
            a = lca(u, v);
            if (!a) {
                aug(u, v);
                aug(v, u);
                return true;
            } else
                add(u, a, v);
        }
        return false;
    }
    bool bfs() {
        fill(s + 1, s + 1 + m, -1);
        fill(sl + 1, sl + 1 + m, 0);
        h = 1;
        t = 0;
        int i, j;
        for (i = 1; i <= m; i++)
            if (st[i] == i && !lk[i]) {
                f[i] = s[i] = 0;
                ins(i);
            }
        if (h > t)
            return 0;
        while (1) {
            while (h <= t) {
                int u = q[h++], v;
                if (s[st[u]] != 1)
                    for (v = 1; v <= n; v++)
                        if (e[u][v].w > 0 && st[u] != st[v]) {
                            if (d(e[u][v]))
                                upd(u, st[v]);
                            else if (on(e[u][v]))
                                return true;
                        }
            }
            T x = inf;
            for (i = n + 1; i <= m; i++)
                if (st[i] == i && s[i] == 1)
                    x = min(x, lab[i] >> 1);
            for (i = 1; i <= m; i++)
                if (st[i] == i && sl[i] && s[i] != 1)
                    x = min(x, d(e[sl[i]][i]) >> s[i] + 1);
            for (i = 1; i <= n; i++)
                if (s[st[i]] != -1)
                    if ((lab[i] += (s[st[i]] * 2 - 1) * x) <= 0)
                        return false;
            for (i = n + 1; i <= m; i++)
                if (st[i] == i && s[st[i]] != -1)
                    lab[i] += (2 - s[st[i]] * 4) * x;
            h = 1;
            t = 0;
            for (i = 1; i <= m; i++)
                if (st[i] == i && sl[i] && st[sl[i]] != i && !d(e[sl[i]][i]) &&
                    on(e[sl[i]][i]))
                    return true;
            for (i = n + 1; i <= m; i++)
                if (st[i] == i && s[i] == 1 && !lab[i])
                    ex(i);
        }
        return false;
    }
public:
    typedef tuple<int, int, T> E;
    // using lk[i] as matching of i.
    // no matching if lk[i]=0.
    T maxWeightedGeneralMatch(int x, const vector<E> &edges) {
        n = m = x;
        memset(ed + 1, 0, m * sizeof ed[0]);
        memset(lk + 1, 0, m * sizeof lk[0]);
        id = 0;
        iota(st + 1, st + n + 1, 1);
        int i, j;
        T wm = 0;
        T r = 0;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                e[i][j] = {i, j, 0};
        for (auto [u, v, w] : edges) {
            e[v][u].w = e[u][v].w = max(e[u][v].w, w);
            wm = max(wm, w);
        }
        for (i = 1; i <= n; i++)
            p[i].clear();
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                b[i][j] = i * (i == j);
        fill_n(lab + 1, n, wm);
        while (bfs())
            ;
        for (i = 1; i <= n; i++)
            if (lk[i])
                r += e[i][lk[i]].w;
        return r / 2;
    }
};
WeightedBlossomTree<int64_t, 405> wbt;
```

# 全局最小割
[博客学习](https://www.cnblogs.com/oyking/p/7339153.html)  
邻接矩阵方式复杂度 $O(n^3)$
```cpp
template<typename Int>
Int stoer_wagner(vector<vector<Int>>& e) {
    int n=e.size();
    if(n==2) return e[0][1];
    int s, t;
    vector<Int> sum(n);
    vector<bool> vis(n);
    for(int k=n; k>0; --k) {
        int mx=-1;
        for(int i=0; i<n; ++i)
            if(!vis[i] && (mx==-1 || sum[mx] < sum[i]))
                mx = i;
        if(k==2) s=mx;
        if(k==1) t=mx;
        vis[mx] = true;// 加入A集合
        for(int i=0; i<n; ++i)
            if(!vis[i])
                sum[i] += e[i][mx];
    }
    for(int i=0; i<n; ++i)// 合并 s,t
        e[s][i] = (e[i][s] += e[i][t]);
    if(t!=n-1) {
        for(int i=0; i<n; ++i) {
            swap(e[i][t], e[i][n-1]);
            swap(e[t][i], e[n-1][i]);
        }
    }
    e.pop_back();
    return min(sum[t], stoer_wagner(e));
}
```
邻接表加优先队列方式复杂度 $O(nm\log m)$  
[度度熊的王国战略,n=3000,m=1e5,7.5s](https://acm.hdu.edu.cn/showproblem.php?pid=6081)
```cpp
#include <ext/pb_ds/priority_queue.hpp>
struct StoerWagner {// index-1
    using Int = int;
    static constexpr int N = 3000 + 10;
    static constexpr int M = 100000 * 2 + 10;
    using PQ = __gnu_pbds::priority_queue<pair<Int, int>>;
    int head[N], tail[N], to[M], nxt[M], n, en;
    int vis[N], fa[N];
    Int l[M], sum[N];
    PQ::point_iterator it[N];
    PQ q;
    void init(int n) {
        this->n = n, en = 0;
        for(int i=1; i<=n; ++i) {
            head[i] = tail[i] = -1;
            fa[i] = i;
        }
    }
    void addEdge(int u, int v, Int w) {
        to[en]=v, l[en]=w, nxt[en]=-1;
        if(head[u]==-1) head[u] = tail[u] = en++;
        else nxt[tail[u]] = en, tail[u] = en++;
        if(en&1) addEdge(v,u,w);
    }
    Int minCut() {
        Int mCut = numeric_limits<Int>::max();
        for(int turn = n, s, t; turn>1; --turn) {
            fill_n(vis+1, n, 0);
            fill_n(sum+1, n, 0);
            it[get(1)] = q.push({0, get(1)});
            for(int k=turn; k>=1; --k) {
                if(q.empty()) return 0;// 图不连通
                int u = q.top().second;
                q.pop(), vis[u] = true, it[u] = nullptr;
                k==2 ? s = u : t = u;
                for(int i = head[u]; ~i; i=nxt[i]) {
                    int v = get(to[i]);
                    auto w = l[i];
                    if(vis[v]) continue;
                    if(it[v] != nullptr) q.modify(it[v], {sum[v] += w, v});
                    else it[v] = q.push(make_pair(sum[v] += w, v));
                }
            }
            mCut = min(mCut, sum[t]);
            unite(s, t);
        }
        return mCut;
    }
private:
    int get(int x) {
        return fa[x]==x ? x: fa[x]=get(fa[x]);
    }
    void unite(int x, int y) {
        x=get(x), y=get(y);
        if(x==y) return;
        if(head[x]==-1) swap(x,y);
        if(head[x]==-1) return;
        nxt[tail[x]] = head[y];
        if(~head[y]) tail[x] = tail[y];
        fa[y] = x;
    }
} sw;
```

# 01bfs
```cpp
vector<int> bfs01(const vector<vector<pair<int,int>>>& g,int s) {
    const int n=g.size();
    vector<int> dis(n,n);
    dis[s]=0;
    deque<int> q;
    q.push_back(s);
    while(q.size()) {
        int u=q.front();
        q.pop_front();
        for(auto [v,w]:g[u]) {
            int t=dis[u]+w;
            if(dis[v]>t) {
                dis[v]=t;
                if(w) q.push_back(v);
                else q.push_front(v);
            }
        }
    }
    return dis;
}
```

# 矩阵变长版本
```cpp
namespace mat {
    const int P = 9973;
    using Mat = vector<vector<int>>;
    Mat operator*(const Mat& a,const Mat& b) {
        int n=a.size(),m=a[0].size(),l=b[0].size();
        Mat res(n,vector<int>(l));
        for (int i=0; i<n; ++i)
            for (int j=0; j<l; ++j)
                for (int k=0; k<m; ++k)
                    res[i][j]=(res[i][j]+1ll*a[i][k]*b[k][j])%P;
        return res;
    }
    Mat operator^(Mat a,long long b) {
        int n=a.size();
        Mat res(n,vector<int>(n));
        for(int i=0; i<n; ++i)
            res[i][i]=1;
        for(; b; b>>=1,a=a*a)
            if(b&1) res=res*a;
        return res;
    }
}
```


## 分数类
```cpp
struct Frac {
    ll a,b;// a/b, b>0
    Frac(): a(0), b(1) {}
    Frac(ll a): a(a), b(1) {}
    Frac(ll a,ll b): a(a), b(b) {
        assert(b!=0);
        norm();
    }
    void norm() {
        auto g=gcd(a,b);
        a/=g;
        b/=g;
        if(b<0) swap(a,b);
    }
    Frac operator-()const {
        return Frac(-a,b);
    }
    Frac& operator+=(const Frac& o) {
        a=a*o.b+b*o.a;
        b*=o.b;
        norm();
        return *this;
    }
    Frac& operator-=(const Frac& o) {
        a=a*o.b-b*o.a;
        b*=o.b;
        norm();
        return *this;
    }
    Frac& operator*=(const Frac& o) {
        a*=o.a;
        b*=o.b;
        norm();
        return *this;
    }
    Frac& operator/=(const Frac& o) {
        assert(o.a!=0);
        a*=o.b;
        b*=o.a;
        norm();
        return *this;
    }
    friend Frac operator+(Frac lhs, const Frac& rhs) {
        return lhs+=rhs;
    }
    friend Frac operator-(Frac lhs, const Frac& rhs) {
        return lhs-=rhs;
    }
    friend Frac operator*(Frac lhs, const Frac& rhs) {
        return lhs*=rhs;
    }
    friend Frac operator/(Frac lhs, const Frac& rhs) {
        return lhs/=rhs;
    }
    explicit operator bool()const {
        return a!=0;
    }
    bool operator!()const {
        return a==0;
    }
    friend ostream& operator<<(ostream& os,const Frac& o) {
        return os << o.a << "/" << o.b;
    }
};
```

## 完全二叉树上计数
```cpp
// 一个标号为 1~n 的完全二叉树的计数问题
struct CompleteBT {
    ll n;
    vector<ll> number;// 子树不是满二叉树的那些节点
    vector<ll> leafs;// number子树下的最后一层叶子节点数
    CompleteBT(ll n) : n(n), number(1, n), leafs(1, 1) {
        for(int i=1; n>>i; ++i) {
            number.push_back(n>>i);
            leafs.push_back(leafs.back());
            if(n>>(i-1)&1)
                leafs.back() += 1ll<<i-1;
        }
        reverse(number.begin(), number.end());
        reverse(leafs.begin(), leafs.end());
    }
    /// @brief u子树下深度为deep的节点有多少个
    ll get_num(ll u, ll deep) {
        if(u<1 || u>n || deep<0) return 0;
        int real_dep = (__lg(n)-__lg(u));
        ll extra = number[__lg(u)]==u ? leafs[__lg(u)]
            : number[__lg(u)] < u ? 0
            : 1ll << real_dep;
        ll fang = deep<= real_dep-1 ? 1ll<<deep
            : deep == real_dep ? extra
            : 0;
        return fang;
    }
    // 计算完全二叉树上 端点为 x，长度为len的路径数量
    ll get_pathNum_by_vertex(ll x, ll len) {
        int d=__lg(x);
        ll ans=get_num(x, len);
        for(int i=1; i<=d; ++i) {// 路径lca在 x的i级祖先 处
            ll cur=x>>i;
            if(len==i) {
                ans+=1;
                break;
            }
            ans+=get_num(cur<<1 | ((x>>i-1)&1)^1, len-i-1);
        }
        return ans;
    }
};
```

## 区间交集并集
```cpp
namespace Intervals {
    struct Interval {
        int l,r;
        Interval(int lp=1,int rp=0):l(lp),r(rp){}
        bool isEmpty() const{return l>r;}
        int len() const{return isEmpty()?0:r-l+1;}
        bool haveCross(const Interval& it) const{
            if(isEmpty()||it.isEmpty()) return false;
            if(l<=it.l) return it.l<=r;
            return l<=it.r;
        }
        Interval operator&(const Interval& it) const{
            if(isEmpty()||it.isEmpty()) return Interval();
            return Interval(max(l,it.l),min(r,it.r));
        }
        Interval operator|(const Interval& it) {// haveCross
            return Interval(min(l,it.l),max(r,it.r));
        }
        bool operator<(const Interval& it) const{
            if(l^it.l) return l<it.l;
            return r<it.r;
        }
        friend istream& operator>>(istream& in, Interval& it) {
            return in>>it.l>>it.r;
        }
        friend ostream& operator<<(ostream& out, Interval it) {
            if(it.isEmpty()) return out<<"{}";
            return out<<"{"<<it.l<<","<<it.r<<"}";
        }
    };
    using Lines=vector<Interval>;
    bool isEmpty(const Interval& it) {return it.isEmpty();}
    Lines norm(Lines A) {// 去空，排序，求并集
        A.erase(remove_if(A.begin(),A.end(),isEmpty),A.end());
        sort(A.begin(),A.end());
        Lines res;
        for(const auto& a:A) {
            if(res.size() && res.back().haveCross(a)) 
                res.back()=res.back()|a;
            else res.push_back(a);
        }
        return res;
    }
    Lines operator&(const Lines& A,const Lines& B) {// norm
        Lines res;
        for(int i=0,j=0; i<A.size()&&j<B.size();) {
            if(A[i].haveCross(B[j])) {
                res.push_back(A[i]&B[j]);
                if(A[i].r<=B[j].r) i++;
                else j++;
            }else if(A[i].l<B[j].l) i++;
            else j++;
        }
        return res;
    }
    Lines operator|(const Lines& A,const Lines& B) {// norm
        Lines C;
        for(int i=0,j=0; i<A.size()||j<B.size(); ) {
            if(j>=B.size() || i<A.size() && A[i]<B[j]) {
                if(C.size() && C.back().haveCross(A[i]))
                    C.back()=C.back()|A[i];
                else C.push_back(A[i]);
                i++;
            }else {
                if(C.size() && C.back().haveCross(B[j]))
                    C.back()=C.back()|B[j];
                else C.push_back(B[j]);
                j++;
            }
        }
        return C;
    }
} using namespace Intervals;
```

带编号的线段操作
```cpp
namespace Intervals {
    struct Interval {
        int id,l,r;
        Interval(int id=-1,int l=1,int r=0):id(id),l(l),r(r){}
        bool isEmpty() const{return l>r;}
        int len() const{return isEmpty()?0:r-l+1;}
        bool haveCross(const Interval& it) const{
            if(isEmpty()||it.isEmpty()) return false;
            if(l<=it.l) return it.l<=r;
            return l<=it.r;
        }
        bool operator<(const Interval& it) const{
            if(l^it.l) return l<it.l;
            if(r^it.r) return r<it.r;
            return id<it.id;
        }
        friend ostream& operator<<(ostream& out, Interval it) {
            if(it.isEmpty()) return out<<"{"<<it.id<<",empty}";
            return out<<"{"<<it.id<<","<<it.l<<","<<it.r<<"}";
        }
    };
    using Lines=vector<Interval>;
    bool isEmpty(const Interval& it) {return it.isEmpty();}
    Lines norm(Lines A) {// 去空，排序，消除交集
        A.erase(remove_if(A.begin(),A.end(),isEmpty),A.end());
        sort(A.begin(),A.end());
        Lines res;
        for(auto [id,l,r]:A){
            if(res.empty() || res.back().r<l) 
                res.emplace_back(id,l,r);
            else if(res.back().r<r)
                res.emplace_back(id,res.back().r+1,r);
        }
        return res;
    }
    Lines operator|(const Lines& A,Lines B) {// norm
        // 为保证不分段，A中保留整段或者去掉，B中去掉左边或者右边一部分
        Lines res;
        for(int i=0,j=0; i<A.size()||j<B.size();) {
            if(j>=B.size()) res.push_back(A[i++]);
            else if(i>=A.size()) res.push_back(B[j++]);
            else if(A[i].haveCross(B[j])) {
                if(A[i].l<=B[j].l) {
                    if(A[i].r>=B[j].r) j++;
                    else B[j].l=A[i].r+1, res.push_back(A[i++]);
                }
                else {
                    if(A[i].r<=B[j].r) i++;
                    else B[j].r=A[i].l-1, res.push_back(B[j++]);
                }
            }else if(A[i].l<B[j].l) res.push_back(A[i++]);
            else res.push_back(B[j++]);
        }
        return res;
    }
} using namespace Intervals;
```

# 异或不等式
- $a \oplus x \le b$ : $log$ 段区间
- $a \oplus x > b$ : 上式的补集
- $x \oplus a \le x$ : 等价于 $x$ 的 $\_\_lg(a)$ 位为$1$
```cpp
// a^x<=b : x的取值为log段区间
Lines xorLess(int a,int b) {
    if(!a and !b) return {{0,0}};
    Lines re, suf;
    int cur=0;
    for(int i=__lg(max(a,b)); i>=0; --i) {
        if(b>>i&1) {
            int t = cur ^ (a&(1<<i));
            if(a>>i&1) suf.emplace_back(t, t+(1<<i)-1);
            else re.emplace_back(t, t+(1<<i)-1);
        }
        cur ^= ((a^b)>>i&1)<<i;
    }
    re.emplace_back(a^b,a^b);// xorLt 没有这一段
    re.insert(re.end(), suf.rbegin(), suf.rend());// 保证区间有序
    return re;
}
// a^x>=b : x的取值为log段区间
Lines xorGe(int a,int b) {
    Lines re0 = xorLt(a,b);
    Lines re;
    int lst = -1;
    for(auto [l,r]:re0) {
        if(lst+1 < l) re.emplace_back(lst+1, l-1);
        lst = r;
    }
    if(lst+1 < (1<<30))
        re.emplace_back(lst+1, (1<<30)-1);
    return re;
}
```






