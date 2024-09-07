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

constexpr int N = 1e5 + 10, SQ = 400;

struct Dsu {
    vector<int> fa, sz;
    Dsu(int n): fa(n),sz(n,1) {
        iota(fa.begin(), fa.end(), 0);
    }
    bool unite(int x, int y) {
       x=get(x), y=get(y);
       if(x==y) return false;
       fa[x]=y;
       sz[y]+=sz[x];
       return true;
    }
    int get(int x) {
        return fa[x]==x ? x: fa[x]=get(fa[x]);
    }
    int size(int x) {
        return sz[get(x)];
    }
};

vector<int> g[N];
int deep[N], fa[N];
void dfs(int u, int ff) {
    for(int v:g[u]) {
        if(v == ff) continue;
        fa[v] = u;
        deep[v] = deep[u]+1;
        dfs(v, u);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(fa, -1, sizeof fa);
    int n,q;
    cin>>n>>q;
    ll X = 0;
    Dsu ds(n+1);
    for(int i=1; i<=q; ++i)  {
        ll a,b,c;
        cin>>a>>b>>c;
        a = 1+(a*(1+X)%998244353)%2;
        b = 1+(b*(1+X)%998244353)%n;
        c = 1+(c*(1+X)%998244353)%n;
        if(a == 1) {
            if(ds.size(b) > ds.size(b))
                swap(b, c);
            ds.unite(b, c);
            g[b].push_back(c);
            g[c].push_back(b);
            fa[b] = c;
            deep[b] = deep[c]+1;
            dfs(b, c);
        }else {
            if(deep[b] > deep[c])
                swap(b,c);
            X = 0;
            if(deep[c]-deep[b] == 2) {
                if(fa[fa[c]]==b)
                    X = fa[c];
            }else if(deep[b] == deep[c] and fa[b]!=-1 and fa[b]==fa[c]) {
                X = fa[b];
            }
            if(X) {cout<<X<<"\n";continue;}
            
            cout<<X<<"\n";
        }
    }
    return 0;
}
/*

https://atcoder.jp/contests/abc350/tasks/abc350_g
启发式
并查集
建树


*/