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
    for(auto& x:v) is>>x;
    return is;
}

constexpr int N = 2e5 + 10;
struct Enode {
    int next, t;
    int l;
} edge[int(2e6)+10];
int en, head[N];
void initGraph(int n) {
    fill_n(head, n+1, -1), en = 0;
}
template<class... T>
void addEdge(int x, int y, T... args){
    edge[en] = {head[x], y, args...};
    head[x] = en++;
}

int dp[N][3];
multiset<int> st[N];
void Link(int u, int v, int w=1) {// update from bottom to top
    // TODO u -> v
    int t = dp[v][0]+1;
    if(t > dp[u][0]) swap(t, dp[u][0]);
    if(t > dp[u][1]) swap(t, dp[u][1]);
    if(t > dp[u][2]) swap(t, dp[u][2]);
    st[u].insert(*st[v].rbegin());
    st[u].insert(dp[v][0] + dp[v][1]);
}
void cut(int u, int v, int w=1) {// update from top to bottom
    // TODO u -\> v
    st[u].extract(*st[v].rbegin());
    st[u].extract(dp[v][0] + dp[v][1]);
    int t = dp[v][0]+1;
    if(dp[u][0] == t) {
        dp[u][0] = dp[u][1];
        dp[u][1] = dp[u][2];
        dp[u][2] = 0;
    }else if(dp[u][1] == t) {
        dp[u][1] = dp[u][2];
        dp[u][2] = 0;
    }else if(dp[u][2] == t) {
        dp[u][2] = 0;
    }
}
void dfs1(int u, int fa) {
    debug(u);
    // TODO u是孤点，初始化u的所有属性
    for (int i=head[u]; ~i; i=edge[i].next) {
        int v=edge[i].t, w=edge[i].l;
        if (v != fa) {
            dfs1(v,u);
            Link(u,v,w);
        }
    }
}

int f[N];
void dfs2(int u, int fa) {
    debug();
    debug(u);
    debug(st+1, 3);
    debug(dp+1, 3);
    
    // TODO 统计u作为根节点的信息
    for (int i=head[u]; ~i; i=edge[i].next) {
        int v=edge[i].t, w=edge[i].l;
        f[u] = max(f[u], *st[v].rbegin());
        f[u] = max(f[u], dp[v][0] + dp[v][1]);
    }
    for (int i=head[u]; ~i; i=edge[i].next) {
        int v=edge[i].t, w=edge[i].l;
        if (v!=fa) {
            cut(u,v,w);// u把v子树拆分出去
            // cerr<<"CUT: "<<u<<" "<<v<<endl;
            // debug(st+1, 3);
            // debug(dp+1, 3);
            Link(v,u,w);// v变成根节点
            // cerr<<"LINK: "<<v<<" "<<u<<endl;
            // debug(st+1, 3);
            // debug(dp+1, 3);
            dfs2(v,u);
            cut(v,u,w);
            Link(u,v,w);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    initGraph(n);
    for(int i=1; i<n; ++i) {
        int u,v;
        cin>>u>>v;
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1; i<=n; ++i) {
        st[i].insert(0);
    }

    dfs1(1, 0);
    // debug();
    // exit(0);

    dfs2(1, 0);
    for(int i=1; i<=n; ++i) {
        cout<<f[i]<<'\n';
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/86387/G
换根 DP
使用 DP 的方式维护经过 u 的最长路
使用 multiset 维护子树中的最长直径

*/