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

namespace NetFlow {
    using T = int;
    constexpr T INF = numeric_limits<T>::max()/2;
    constexpr int _V = 2e5 + 10;
    constexpr int _E = 2e6 + 10;
    int s0, t0, _n, head[_V], dis[_V], to[_E], nxt[_E], en;
    T fl[_E];
    void initGraph(int n = _V-2) {
        _n = n, s0 = _n++, t0 = _n++, en = 0, fill_n(head, _n, -1);
    }
    void addEdge(int x, int y, T z) {
        assert(x<_V && y<_V), assert(en+1<_E);
        to[en] = y, nxt[en] = head[x], fl[en] = z, head[x] = en++;
        to[en] = x, nxt[en] = head[y], fl[en] = 0, head[y] = en++;
    }
    bool bfs(int s,int t) {
        fill_n(dis, _n, -1);
        queue<int> q;
        q.push(s), dis[s]=0;
        while(q.size()) {
            int u=q.front();
            q.pop();
            for (int i=head[u]; ~i; i=nxt[i])
                if(dis[to[i]]==-1 && fl[i]>0)
                    q.push(to[i]), dis[to[i]] = dis[u]+1;
        }
        return dis[t] != -1;
    }
    T dfs(int u, int t, T flow) {
        if(u==t) return flow;
        T ans = flow;
        for (int i=head[u]; ~i && ans; i=nxt[i]) {
            int v = to[i];
            if (dis[v] == dis[u]+1 && fl[i]>0) {
                T temp=dfs(v, t, min(fl[i], ans));
                fl[i] -= temp;
                fl[i^1] += temp;
                ans -= temp;
            }
        }
        if(ans == flow) dis[u] = -1;
        return flow - ans;
    }
    T dinic(int s,int t) {
        T ans=0;
        while(bfs(s,t)) ans += dfs(s, t, INF);
        return ans;
    }
}
using namespace NetFlow;

void printGraph() {
    #ifndef YJL
    return;
    #endif
    auto dot=[&](int u)->string{
        if(u==s0) return "S";
        if(u==t0) return "T";
        return to_string(u);
    };
    cerr << endl << "Graph with " << en << " edges:" << endl;
    for(int i=1; i<en; i+=2) {
        if(fl[i] == 0) continue;
        cerr << dot(to[i^1]) << " -> " << dot(to[i]) <<" : ";
        cerr << (fl[i]==INF ? "INF" : to_string(fl[i])) << endl;
    }
}

int deg[NetFlow::_V];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int g,n;
    cin>>g>>n;
    string ans(n, '0');
    vector<vector<int>> ac(n,vector<int>(26, 1));
    vector<int> lowb(26), fixed(26);
    for(int iii=0; iii<g-1; ++iii) {
        string s,res;
        cin>>s>>res;
        vector<int> num(26);
        for(int j=0; j<n; ++j) {
            int x = s[j]-'a';
			
            if(res[j]=='G') {
                ans[j] = s[j];
                num[x]++;
            }else {
                ac[j][x] = 0;
                // Y | B
                if(res[j] == 'Y') {
                    num[x]++;
                }else {
                    debug(s,j,s[j]);
                    fixed[x] = 1;
                }
            }
        }
        for(int j=0; j<26; ++j) {
            lowb[j] = max(lowb[j], num[j]);
        }
    }

    for(int i=0; i<n; ++i) {
        if(ans[i] != '0') {
            lowb[ans[i]-'a'] = max(lowb[ans[i]-'a']-1, 0);
        }
    }

    // for(int i=0; i<26; ++i) {
    //     if(lowb[i]) {
    //         debug(char(i+'a'), lowb[i]);
    //     }
    // }

    debug(ans);
    debug(fixed[1]);

    initGraph();
    s0 = n+26;
    t0 = s0+1;
    int s1 = t0+1;
    int t1 = s1+1;
    for(int i=0; i<n; ++i) {
        if(ans[i] != '0') continue;
        // s0, i, [1,1]
        deg[s0] += 1;
        deg[i] -= 1;
    }
    for(int i=0; i<26; ++i) {
        if(!fixed[i]) {
            // n+i, t0, [lowb[i], n]
            addEdge(n+i, t0, n-lowb[i]);
        }else {
            // n+i, t0, [lowb[i], lowb[i]]
        }
        deg[n+i] += lowb[i];
        deg[t0] -= lowb[i];
    }
    for(int i=0; i<n; ++i) {
        for(int j=0; j<26; ++j) {
            if(ac[i][j]) {
                // i, n+j, [0,1]
                addEdge(i, n+j, 1);
            }
        }
    }

    for (int i = 0; i <= t0; ++i) {
        if (deg[i] > 0) {
            addEdge(i, t1, deg[i]);
        } else if (deg[i] < 0) {
            addEdge(s1, i, -deg[i]);
        }
    }

    addEdge(t0, s0, INF);
    dinic(s1, t1);
    for (int i = head[s1]; ~i; i = nxt[i]) {
        if (fl[i] > 0) {
            assert(0);
            return 0;
        }
    }
    int flow = fl[en-1];

    fl[en-1] = fl[en-2] = 0;
    flow += dinic(s0, t0);
    assert(flow == count(ALL(ans),'0'));


    for(int u=0; u<n; ++u) {
        for(int i=head[u]; ~i; i=nxt[i]) {
            int v = to[i];
            if(v>=n and v<n+26) {
                if(ac[u][v-n] and fl[i^1]) {
                    ans[u] = char(v-n+'a');
                    break;
                }
            }
        }
        assert(ans[u] != '0');
    }
    cout << ans;
    return 0;
}
/*
上下界网络流
G : 固定了该位置的答案
Y : 决定了元素数量的下界，同时说明这个位置不能放哪个元素
B : 决定了元素数量的上界，同时说明这个位置不能放哪个元素



*/