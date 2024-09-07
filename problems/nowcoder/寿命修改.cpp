#include "bits/stdc++.h"
#ifndef YJL
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

struct Tag {
    ll d;
    void init() {
        d = 0;
    }
    void unite(const Tag &val) {
        d += val.d;
    }
};
constexpr ll inf = 1e18;
struct Data {
    ll sumh, minh;
    int cnt;// live counter
    // init(l,args...)
    template<class T>
    void init(int i,const T& a) {
        sumh = minh = a[i];
        cnt = 1;
    }
    void add(const Tag &val,int l,int r) {
        sumh += val.d * cnt;
        minh += val.d;
    }
    friend Data operator+(const Data &lhs,const Data & rhs) {
        Data re;
        re.minh = min(lhs.minh, rhs.minh);
        re.sumh = lhs.sumh + rhs.sumh;
        re.cnt = lhs.cnt + rhs.cnt;
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
        if(!tr[u].cnt) return;
        push_lazy(u,l,r);
        if(l==ql&&r==qr) {
            // lz[u]=val;
            if(tr[u].minh + val.d > 0) {
                lz[u] = val;
                return;
            }
            if(l == r) {
                tr[u] = {0, inf, 0};
                return;
            }
            int mid=(l+r)>>1;
            if(qr<=mid) change(u1,l,mid,ql,qr,val);
            else if(ql>mid) change(u2,mid+1,r,ql,qr,val);
            else change(u1,l,mid,ql,mid,val),change(u2,mid+1,r,mid+1,qr,val);
            push_lazy(u1,l,mid),push_lazy(u2,mid+1,r);
            tr[u]=tr[u1]+tr[u2];
        }
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<int> a(n);
    cin>>a;
    
    Segtree tr(0, n-1, a);
    while(m--) {
        int op,l,r;
        cin>>op>>l>>r;
        --l,--r;
        if(op == 1) {
            int x;
            cin>>x;
            tr.change(l,r,{x});
        }else {
            cout<<tr.query(l,r).sumh<<'\n';
        }
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85333/A
经典标记死亡点的线段树
对于一次修改，若区间内没有死亡的，正常打标记即可
若区间内又死亡的，需要继续递归，直到叶子节点进行标记
推到叶子节点最多n次，相比普通线段树，多余的复杂度仍然是 O(n*logn)

*/