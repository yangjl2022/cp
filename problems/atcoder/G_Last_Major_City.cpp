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

struct SteinerTree {// index-1
    static constexpr int N = 4000  + 10;
    static constexpr int K = 10;// 关键点个数
    vector<pair<int,int>> g[N];
    int n, m, k;
    ll f[1<<K][N];
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
        --k;
        for(int i=0,x; i<k; ++i) {
            f[1<<i][i+1]=0;
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
    void solve() {
        readGraph();
        minSteinerTree();
        for(int i=k+1; i<=n; ++i) {
            cout<<f[(1<<k)-1][i]<<"\n";
        }
    }
} steiner;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    steiner.solve();
    return 0;
}
/*
https://atcoder.jp/contests/abc364/tasks/abc364_g
最小斯坦纳树，多了一点变动，但回想minSteinerTree 的 DP 解法：
发现这题的所有答案都包括在了 DP 中，于是得解
dp[S][i] 表示一颗包括 i 节点，关键点的包括状态为 S 的最小斯坦纳树
复杂度 O(3^k n + 2^k m logm) dijkstra
复杂度 O(3^k n + 2^k n m) spfa
*/