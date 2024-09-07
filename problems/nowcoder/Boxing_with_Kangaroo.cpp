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

namespace hpd {// index-1
    static constexpr int N = 2e5 + 10;// TODO
    struct Node {
        int t,l,next;
    } edge[N*2];
    int n, en, head[N];
    int f[N], deep[N], siz[N], son[N], toEdge[N];
    int top[N], ord[N], id[N], idn;
    void initTree(int _n) {
        n = _n;
        fill_n(head+1,n,-1), en = 0;
    }
    void addEdge(int x,int y,int z=0) {
        edge[en]={y,z,head[x]};
        head[x]=en++;
        edge[en]={x,z,head[y]};
        head[y]=en++;
    }
    void dfs1(int u, int fa, int deepth) {
        f[u]=fa;
        deep[u]=deepth;
        siz[u]=1;
        son[u]=0;
        for(int i=head[u]; ~i; i=edge[i].next) {
            int v=edge[i].t;
            if(v==fa) continue;
            dfs1(v, u, deepth+1);
            toEdge[v]=i/2;
            siz[u]+=siz[v];
            if(siz[v]>siz[son[u]])
                son[u]=v;
        }
    }
    void dfs2(int u, int topp) {
        top[u]=topp;
        ord[id[u]=++idn]=u;
        if(son[u])
            dfs2(son[u], topp);
        for(int i=head[u]; ~i; i=edge[i].next) {
            int v=edge[i].t;
            if(v!=f[u]&&v!=son[u])
                dfs2(v, v);
        }
    }
    void treePartition() {
        idn=0;
        dfs1(1,0,1);
        dfs2(1,1);
    }
    vector<pair<int,int>> decompose(int x,int y,bool isEdge=false) {
        vector<pair<int,int>> q;
        while(top[x]!=top[y]) {
            if(deep[top[x]]>=deep[top[y]]) {
                q.emplace_back(id[top[x]], id[x]);
                x=f[top[x]];
            }else {
                q.emplace_back(id[top[y]], id[y]);
                y=f[top[y]];
            }
        }
        if(id[x]==id[y]&&isEdge)
            return q;
        if(id[x]<id[y]) q.emplace_back(id[x]+isEdge, id[y]);
        else q.emplace_back(id[y]+isEdge, id[x]);
        return q;
    }
    template<class Func>
    void solve(int s, int t, Func func) {
        vector<pair<int,int>> q;
        while(top[s]!=top[t]) {
            if(deep[top[s]]>=deep[top[t]]) {
                func(id[s], id[top[s]]);
                s = f[top[s]];
            }else {
                q.emplace_back(id[top[t]], id[t]);
                t=f[top[t]];
            }
        }
        if(id[s]<id[t]) {
            func(id[s], id[t]);
        } else {
            q.emplace_back(id[s], id[t]);
        }
        reverse(q.begin(), q.end());
        for(auto [s,t]:q) {
            func(s, t);
        }
    }
    int lca(int x,int y) {
        while(top[x]!=top[y]) {
            if(deep[top[x]]<deep[top[y]])
                swap(x,y);
            x=f[top[x]];
        }
        if(deep[x]<deep[y])
            swap(x,y);
        return y;
    }
} // namespace hpd

struct Data {
    ll sump, leastH;
    ll leastH_r;
    // init(int i,const T& args... )
    template<class T>
    void init(int i,const T& a) {
        add(a[hpd::ord[i]]);
        // debug(i, sump);
    }
    // add(const T& args... )
    void add(int val) {
        sump = leastH = leastH_r = val;
    }
    friend Data operator+(const Data &lhs,const Data & rhs) {
        Data re;
        re.sump = lhs.sump + rhs.sump;
        re.leastH = max(lhs.leastH, rhs.leastH - lhs.sump);
        re.leastH_r = max(rhs.leastH_r, lhs.leastH_r - rhs.sump);
        // if(re.sump == 15) {
        //     debug(re);
        //     debug(lhs);
        //     debug(rhs);
        // }
        return re;
    }
};
struct Segtree {
    #define u1 (u<<1)
    #define u2 (u<<1|1)
    vector<Data> tr;
    vector<int> mp;
    int Lpoint,Rpoint;
    template<class ...T>
    Segtree(int L,int R,const T&...args):Lpoint(L),Rpoint(R)
    ,tr(4<<__lg(R-L+1)),mp(R-L+1) {// a[L~R]建树
        build(1,L,R,args...);
    }
    template<class ...T>
    void build(int u,int l,int r,const T&...args) {
        if(l==r) {
            tr[u].init(l,args...);
            mp[l-Lpoint]=u;
            return;
        }
        int mid=(l+r)>>1;
        build(u1,l,mid,args...);
        build(u2,mid+1,r,args...);
        tr[u]=tr[u1]+tr[u2];
    }
    template<class ...T>
    void change(int pos,const T&...args) {
        int u=mp[pos-Lpoint];
        tr[u].add(args...);
        for (u>>=1; u; u>>=1) tr[u]=tr[u1]+tr[u2];
    }
    Data query(int l,int r) {
        return query(1,Lpoint,Rpoint,l,r);
    }
    Data query(int u,int l,int r,int ql,int qr) {
        if (l==ql&&r==qr) return tr[u];
        int mid=(l+r)>>1;
        if (qr<=mid) return query(u1,l,mid,ql,qr);
        if (ql>mid) return query(u2,mid+1,r,ql,qr);
        return query(u1,l,mid,ql,mid)+query(u2,mid+1,r,mid+1,qr);
    }
    // 返回 check 成功的区间长度
    template<class Func>
    int lfind(int u, int l, int r, int ql, int qr, Func const& chk) {
        if(l == ql and r == qr) {
            if(chk(tr[u])) return r-l+1;
            if(l == r) return 0;
        }
        int mid = (l + r) / 2;
        if (qr <= mid) return lfind(u1, l, mid, ql, qr, chk);
        if (ql > mid) return lfind(u2, mid+1, r, ql, qr, chk);
        int len = lfind(u1, l, mid, ql, mid, chk);
        if(len == mid-ql+1) len += lfind(u2, mid+1, r, mid+1, qr, chk);
        return len;
    }
    template<class Func>
    int rfind(int u, int l, int r, int ql, int qr, Func const& chk) {
        if(l == ql and r == qr) {
            if(chk(tr[u])) return r-l+1;
            if(l == r) return 0;
        }
        int mid = (l + r) / 2;
        if (qr <= mid) return rfind(u1, l, mid, ql, qr, chk);
        if (ql > mid) return rfind(u2, mid+1, r, ql, qr, chk);
        int len = rfind(u2, mid+1, r, mid+1, qr, chk);
        if(len == qr-mid) len += rfind(u1, l, mid, ql, mid, chk);
        return len;
    }
    #undef u1
    #undef u2
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<int> p(n+1);
    for(int i=1; i<=n; ++i) {
        cin>>p[i];
    }
    hpd::initTree(n);
    for(int i=1; i<n; ++i) {
        int u,v;
        cin>>u>>v;
        hpd::addEdge(u, v);
    }
    hpd::treePartition();

    debug(hpd::ord+1, n);

    Segtree tr(1, n, p);

    while(m--) {
        int op;
        cin>>op;
        if(op == 1) {
            int x,y;
            cin>>x>>y;
            tr.change(hpd::id[x], y);
        }else {
            debug();
            int s,t;
            ll k;
            cin>>s>>t>>k;
            int br = 0, sum_win = 0;
            hpd::solve(s, t, [&](int l, int r){
                debug(l,r);
                if(br) return;

                if(l <= r) {
                    int win = tr.lfind(1, 1, n, l, r, [&](Data const& node) {
                        if(k >= node.leastH) {
                            k += node.sump;
                            return 1;
                        }
                        return 0;
                    });
                    sum_win += win;
                    if(win != r-l+1) br = 1;
                }else {
                    int win = tr.rfind(1, 1, n, r, l, [&](Data const& node) {
                        debug(node);
                        if(k >= node.leastH_r) {
                            k += node.sump;
                            return 1;
                        }
                        return 0;
                    });
                    sum_win += win;
                    if(win != l-r+1) br = 1;
                }
            });
            cout<<sum_win<<'\n';
        }
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85910/I
经典树链剖分的题
思维上在于维护区间最小通关血量
树上二分找失败点
难点：树上区间要按s->t顺序去二分，所以树链剖分的区间操作顺序需要调整

*/