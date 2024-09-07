#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

struct Tag {
    ll d;
    void init() {
        d = 0;
    }
    void unite(const Tag &val) {
        d += val.d;
    }
};
struct Data {
    ll mn;
    // init(l,args...)
    template<class T>
    void init(int i,const T& a) {
        mn = a[i] + a[i];
    }
    void add(const Tag &val,int l,int r) {
        if(val.d) {
            mn += val.d;
        }
    }
    friend Data operator+(const Data &lhs,const Data & rhs) {
        Data re;
        re.mn = min(lhs.mn, rhs.mn);
        return re;
    }
};
struct Segtree {
    #define u1 (u<<1)
    #define u2 (u<<1|1)
    vector<Data> tr;
    vector<Tag> lz;
    int Lpoint,Rpoint;
    template<class ...T>
    Segtree(int L,int R,const T&...args):Lpoint(L),Rpoint(R)
    ,tr(4<<__lg(R-L+1)),lz(tr.size()) {// a[L~R]建树
        build(1,L,R,args...);
    }
    template<class ...T>
    void build(int u,int l,int r,const T&...args) {
        lz[u].init();
        if(l==r) return tr[u].init(l,args...);
        int mid=(l+r)>>1;
        build(u1,l,mid,args...);
        build(u2,mid+1,r,args...);
        tr[u]=tr[u1]+tr[u2];
    }
    void push_lazy(int u,int l,int r) {
        tr[u].add(lz[u],l,r);
        if(l!=r) lz[u1].unite(lz[u]),lz[u2].unite(lz[u]);
        lz[u].init();
    }
    void change(int l,int r,const Tag &val) {
        if(Lpoint<=l&&l<=r&&r<=Rpoint)
            change(1,Lpoint,Rpoint,l,r,val);
    }
    void change(int u,int l,int r,int ql,int qr,const Tag &val) {
        push_lazy(u,l,r);
        if(l==ql&&r==qr) lz[u]=val;
        else {
            int mid=(l+r)>>1;
            if(qr<=mid) change(u1,l,mid,ql,qr,val);
            else if(ql>mid) change(u2,mid+1,r,ql,qr,val);
            else change(u1,l,mid,ql,mid,val),change(u2,mid+1,r,mid+1,qr,val);
            push_lazy(u1,l,mid),push_lazy(u2,mid+1,r);
            tr[u]=tr[u1]+tr[u2];
        }
    }
    Data query(int l,int r) {
        return query(1,Lpoint,Rpoint,l,r);
    }
    Data query(int u,int l,int r,int ql,int qr) {
        push_lazy(u,l,r);
        if(l==ql&&r==qr) return tr[u];
        int mid=(l+r)>>1;
        if(qr<=mid) return query(u1,l,mid,ql,qr);
        if(ql>mid) return query(u2,mid+1,r,ql,qr);
        return query(u1,l,mid,ql,mid)+query(u2,mid+1,r,mid+1,qr);
    }
    #undef u1
    #undef u2
};

template<typename Int>
struct SparseTable {
    vector<vector<int>> f;
    vector<Int> a;
    function<bool(Int,Int)> better;
    SparseTable(const vector<Int>& a, function<bool(Int,Int)> better)
    : a(a), better(better), f(a.size(),vector<int>(__lg(a.size())+1)) {
        int n=a.size(), lg=__lg(n);
        for(int i=0; i<n; ++i)
            f[i][0]=i;
        for (int k=1; k<=lg; ++k)
            for (int i=0; i+(1<<k)-1<n; ++i) {
                int l=f[i][k-1],r=f[i+(1<<(k-1))][k-1];
                f[i][k]=(better(a[l],a[r])?l:r);
            }
    }
    int queryIndex(int l,int r) {
        int k=__lg(r-l+1);
        int i=f[l][k],j=f[r-(1<<k)+1][k];
        return better(a[i],a[j])?i:j;
    }
    Int queryValue(int l,int r) {
        return a[queryIndex(l,r)];
    }
};

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x:v) is>>x;
    return is;
}

constexpr int inf = 2e9;
auto solve(vector<int> const& a, vector<pair<int,int>> const& b) {
    int n = a.size(), q = b.size();
    // vector<int> f(n), w(n);
    // for(int i=0; i<n; ++i) {
    //     f[i] = i-1;
    //     w[i] = a[i];
    //     while(f[i]!=-1 and a[f[i]]<=a[i]) {
    //         w[i] = min(w[i], w[f[i]]);
    //         f[i] = f[f[i]];
    //     }
    // }
    // for(int i=0; i<n; ++i) {
    //     w[i] += a[i];
    // }
    // debug();
    debug();
    debug(a);
    debug(b);
    // debug(f);
    // debug(w);

    SparseTable<int> st_mx0(a, [&](int x,int y){return x>=y;});
    SparseTable<int> st_mx1(a, [&](int x,int y){return x>y;});
    SparseTable<int> st_mn(a, [&](int x,int y){return x<y;});
    // SparseTable<int> stw(w, [&](int x,int y){return x<y;});

    vector<int> ans(q, inf);
    vector c(n, vector<array<int,4>>());
    for(int i=0; i<q; ++i) {
        auto [l,r] = b[i];
        int i0 = st_mx0.queryIndex(l, r);
        if(i0+2>r) continue;
        int i1 = st_mx1.queryIndex(i0+1, r);
        ans[i] = min({
            a[i0]+a[r-1]+a[r],
            a[i0]+a[i1]+st_mn.queryValue(i0+1, i1),
            // a[i0]+stw.queryValue(i0+1, r)
        });
        c[r].push_back({l, i0+1, i, a[i0]});
        // debug(i0, i1,ans[i]);
    }
    debug(ans);

    Segtree tr(0, n-1, a);
    vector<int> st;
    for(int i=0; i<n; ++i) {
        for(; st.size() and a[st.back()]<=a[i]; st.pop_back()) {
            int u = st.back();
            int v = st.size() >= 2 ? st.end()[-2] : -1;
            debug(u, v);
            tr.change(v+1, u, {a[i]-a[u]});
        }
        st.push_back(i);
        debug(i);
        // for(int j=0; j<=i; ++j) {
        //     debug(tr.query(j, j).mn);
        // }
        for(auto [l, p, id, mx]:c[i]) {
            if(p<i) ans[id] = min<ll>(ans[id], mx+tr.query(p, i-1).mn);
            debug(l, i, p, id, ans[id]);
        }
    }
    
    return ans;   
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin>>n>>q;
    vector<int> a(n);
    cin>>a;
    vector<pair<int,int>> b(q);
    for(auto& [l,r]:b) {
        cin>>l>>r;
        --l,--r;
    }

    vector<int> ans(q);
    SparseTable<int> st(a, [&](int x,int y){return x>y;});
    for(int i=0; i<q; ++i) {
        auto [l,r] = b[i];
        ans[i] = a[l]+a[r]+st.queryValue(l,r);
    }

    auto ans1 = solve(a, b);
    debug(ans1);
    
    // debug();
    // exit(0);

    reverse(ALL(a));
    for(auto& [l,r]:b) {
        int nl = n-1-r;
        int nr = n-1-l;
        l = nl;
        r = nr;
    }
    auto ans2 = solve(a, b);

    debug();
    debug(ans);
    debug(ans1);
    debug(ans2);
    for(int i=0; i<q; ++i) {
        cout<<min({ans[i],ans1[i],ans2[i]})<<"\n";
    }
    return 0;
}
/*
https://atcoder.jp/contests/arc180/tasks/arc180_d
拆成三部分，最小化三部分B1,B2,B3最大值总和
设区间最大值位置为 i0
分情况讨论：
1. i0在中心，那么两头的越短越好
2. i0在左边的块，那么
    1. 如果B2,B3中的最大值位于B2内，那么第三块取a[r]，第二块取a[r-1]最优。
    2. 如果B2,B3中的最大值位于B3内，此时B2的只取一个元素最优
    ans = mx + min{i0<i<r}( a[i] + max(a[i+1] ~ a[r]) )
    我们把询问按r排序来解决。
    固定 r，假设 w[i] = a[i] + max(a[i+1] ~ a[r]), 
    ans <- mx + min{i0<i<r}( w[i] )
    通过维护一个单调递减的栈，我们可以每次更新一段 w[i]
    用区间加，区间取min线段树维护
3. i0再右边的块，和在左边对称。

*/