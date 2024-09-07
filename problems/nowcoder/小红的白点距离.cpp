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

constexpr int N = 1010;
int n,k;
vector<int> g[N];
int dis[N];
void dfs(int u,int fa,int d) {
    dis[u] = d;
    for(int v:g[u]){
        if(v==fa) continue;
        dfs(v, u, d+1);
    }
}

int16_t dfs2(int u, int fa, int goal) {
    if(dis[u] == goal)
        return 1;
    int ans = 0;
    for(int v:g[u]){
        if(v==fa) continue;
        ans += dfs2(v, u, goal);
    }
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n>>k;
    k = n-k;// >=2
    for(int i=1; i<n; ++i) {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int ans = 1e9;
    for(int i=1; i<=n; ++i) {
        dfs(i, 0, 0);
        vector<int> v(dis, dis+1+n);
        sort(ALL(v));

        if(i == 2) {
            debug(v);
        }
        ans = min(ans, v[k]*2);

        int k0 = k;
        while(v[k0]+1!=v[k]) k0--;

        int tmp = k-k0;
        for(int x:g[i]) {
            int t = dfs2(x, i, v[k]);
            // debug(i, x, t, tmp);
            if(t >= tmp) {
                ans = min(ans, v[k]*2-1);
                break;
            }
        }
    }
    cout<<ans;
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85350/D
思维题
白点肯定形成连通块最优
要最小化这个连通块的直径
不妨枚举直径中心，考虑直径长度为奇偶数的情况
对于偶数情况，直接统计方圆几里内的节点数即可
对于奇数情况，为了避免中心偏移了真实直径，那么距离中心为 (d+1)/2 的点不能分别位于中心的两条分叉上

*/